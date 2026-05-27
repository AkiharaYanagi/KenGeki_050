//=================================================================================================
//
//	Title
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "01_Title/Title_lib.h"
#include "00_Core/SeConst.h"
#include "00_Core/VoiceConst.h"
#include "00_Core/DebugDisp.h"

#include "TitleChara_lib.h"
#include "TitleMenu_lib.h"
#include "TitleDemo_lib.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//--------------------------------------------------------
	//constexprは前方宣言
	constexpr uint32 FADE_IN_T = 16;
	constexpr uint32 FADE_OUT_T = 16;
	constexpr uint32 TITLE_CALL_WAIT = 2;


	Title_lib::Title_lib ()
	{
		//背景	
		m_bg = MakepGrp ( U"Title\\Title_BG.png", Z_BG );

		m_rect = MakepGrp ( U"Title\\Title_Rect.png", Z_BG - 0.01f );
		m_rect->SetPos ( VEC2 ( 1280 / 2 - 500 / 2, 100 ) );
		m_rect->SetRotationCenter ( VEC2 ( 250, 250 ) );
		m_rect->SetColor ( _CLR(0xffa0a0a0) );
		m_rect->AddObject ();
		P_Ob pob = m_rect->GetpObject ( 1 );
		pob->SetPos ( VEC2 ( 1280 / 2 - 500 / 2, 100 ) );
		pob->SetRotationCenter ( VEC2 ( 250, 250 ) );
		m_rect_omega1 = 0.01f;

		//キャラ
		m_chara = std::make_shared < TitleChara > ();
		AddpTask ( m_chara );

		//ロゴ
		m_logo = MakepGrp ( U"Title\\Title_Logo.png", Z_EFF );
		m_logo->AddTexture_FromArchive ( U"Title\\Title_Logo_En.png" );
		m_logo->SetPos ( VEC2 ( LOGO_X, LOGO_Y ) );

		//メニュー
		m_menu = std::make_shared < TitleMenu > ();
		AddpTask ( m_menu );

		//Ver.
		m_strVer = std::make_shared < GrpStr > ();
		m_strVer->SetPos ( 1280/2 - 40, 934 );
		m_strVer->SetZ ( Z_MENU - 0.001f );

		//std::ostringstream oss;
		//oss << "beta " << __DATE__ << " " << __TIME__;
		//m_strVer->SetStr ( Unicode::FromUTF8 ( oss.str().c_str() ) );
		//m_strVer->SetStr ( Ver );
		m_strVer->SetStr ( g_VERSION );

		AddpTask ( m_strVer );
		GRPLST_INSERT ( m_strVer );

		//Demo
		m_demo = std::make_shared < TitleDemo >();
		AddpTask ( m_demo );

		//Inst
		m_inst = MakepGrp ( U"Title\\Title_Inst.png", Z_MENU - 0.001f );
		m_inst->AddTexture_FromArchive ( U"Title\\Title_Inst_En.png" );
		m_inst->SetPos ( VEC2 ( 0, 0 ) );

		//フェードイン
		m_fade_in = std::make_shared < FadeRect > ();
		AddpTask ( m_fade_in );
		GRPLST_INSERT ( m_fade_in );
//		m_fade_in->StartWhiteIn ( FADE_IN_T );
		m_fade_in->StartBlackIn ( FADE_IN_T );

		//フェードアウト
		m_fade_out = std::make_shared < FadeRect > ();
		m_fade_out->SetAfterClear ( F );
		AddpTask ( m_fade_out );
		GRPLST_INSERT ( m_fade_out );

		//タイマ
		m_tmr_title_bgm = std::make_shared < Timer > ( FADE_IN_T );
		m_tmr_title_bgm->Start ();
		m_tmr_title_call = std::make_shared < Timer > ( TITLE_CALL_WAIT );
		m_tmr_title_call->Start ();


		//now loading
		m_now_loading = MakepGrp ( U"Title\\now_loading.png", Z_FADE - 0.01f );
		m_now_loading->SetPos ( VEC2 ( 1280 - 265, 960 - 228 ) );
	}

	P_Grp Title_lib::MakepGrp ( LPCUSTR filename, float Z = 0.5f )
	{
		P_Grp p = std::make_shared < GameGraphic > ();
		p->AddTexture_FromArchive ( filename );
		p->SetZ ( Z );
		AddpTask ( p );
		GRPLST_INSERT ( p );
		return p;
	}


	Title_lib::~Title_lib ()
	{
	}


	void Title_lib::ParamInit ()
	{
		P_Param pPrm = GetpParam();
		GameSettingFile stg = pPrm->GetGameSetting ();

		//パラメータからデモ切換
		m_demo->SetDemo ( stg.GetDemo() );
		if ( m_demo->IsDemo () )
		{
			OffMenu ();
		}
		else
		{	
			OnMenu ();
		}

		m_chara->SetpParam ( pPrm );
	}


	void Title_lib::Load ()
	{
		//==================================================
		//	Scene_lib共通
		//==================================================
		//遷移先を自身に設定
		//	(コンストラクタでは shared_from_this() が使えないため、Load() で呼び出す)
		Scene_lib::SetwpThis ( shared_from_this () );
		//==================================================


		Scene_lib::Load ();
	}

	void Title_lib::Move ()
	{
#if 0
		//BGM読込状況
		s3d::ClearPrint ();
		G_Audio::Inst()->CheckAudio ();
#endif // 0

		//start
		if ( ! m_bStart )
		{
			m_bStart = T;
			TASK_VEC::Move ();
			return;
		}

		//now loading
		if ( ! m_bLoading )
		{
			if ( g_bALL_CHARA_LOAD_IN_TITLE )
			{
				//全キャラデータを事前読込
				// ここで読込しないとき、バトルメインでキャラの個別読込
				GetpParam()->LoadCharaData_All ();
			}

			m_bLoading = T;
			m_now_loading->SetValid ( F );
		}

		//----------------------------------------------------------
		//背景四角
		m_rect_angle += m_rect_omega;
		m_rect->SetRadian ( m_rect_angle );
		m_rect_angle1 += m_rect_omega1;
		m_rect->GetpObject ( 1 )->SetRadian ( m_rect_angle1 );


		//BGM開始のチェック
		m_tmr_title_bgm->Move ();
		if ( m_tmr_title_bgm->IsLast () )
		{
			AUD_STOP_ALL_BGM ();
			if ( ! s3d::AudioAsset::IsReady ( BGM_Title ) )
			{
				s3d::AudioAsset::Wait ( BGM_Title );
			}
			AUD_PLAY_LOOP_BGM ( BGM_Title );
		}


		//タイトルコール
		m_tmr_title_call->Move ();
		if ( m_tmr_title_call->IsLast () )
		{
			const int N = 6;
			int rnd = s3d::Random ( 0, N );
			LPCUSTR vc_name = U"";

			switch ( rnd )
			{
			case 0: vc_name = VC_00_SAE_TITLE_CALL; break;
			case 1: vc_name = VC_01_RETSUDOU_TITLE_CALL; break;
			case 2: vc_name = VC_02_OUKA_TITLE_CALL; break;
			case 3: vc_name = VC_03_GAVA_TITLE_CALL; break;
			case 4: vc_name = VC_04_FERARIA_TITLE_CALL; break;
			case 5: vc_name = VC_05_TSUKI_TITLE_CALL; break;
			case 6: vc_name = VC_90_CONSOME_TITLE_CALL; break;
			}

			s3d::AudioAsset::Wait ( vc_name );
			AUD_PLAY_ONESHOT_VC ( vc_name );

			//BGM
			P_Param pPrm = GetpParam();
			switch ( rnd )
			{
			case 0: pPrm->Set_BGM_ID ( BGM_ID_SAE  ); break;
			case 1: pPrm->Set_BGM_ID ( BGM_ID_RETSU); break;
			case 2: pPrm->Set_BGM_ID ( BGM_ID_OUKA ); break;
			case 3: pPrm->Set_BGM_ID ( BGM_ID_GABA ); break;
			case 4: pPrm->Set_BGM_ID ( BGM_ID_FERA ); break;
			case 5: pPrm->Set_BGM_ID ( BGM_ID_TSUKI); break;
			case 6: pPrm->Set_BGM_ID ( BGM_ID_GABA ); break;
			}
			SaveParam ();

	}

		//----------------------------------------------------------
		//F9でデモ切替 (プレイヤーボタン：リセットでも切換)
		if ( WND_UTL::AscKey ( VK_F9 ) || CFG_PUSH_KEY_12 ( PLY_BTN7 ) )
		{
			//切替
			m_demo->Switch ();

			if ( m_demo->IsDemo () )
			{
				//OnMenu ();
				//m_menu->Off ();	
				OffMenu ();
			}
			else
			{	
				//OffMenu ();
				//m_menu->On ();
				OnMenu ();
			}

			//パラメータに反映
			GameSettingFile& stg = GetpParam()->GetGameSetting ();
			stg.SetDemo ( m_demo->IsDemo () );
			SaveParam ();
		}

		//----------------------------------
		//入力はデモ時以外のみ
		if ( ! m_demo->IsDemo () )
		{
			//入力
			Input ();
		}

		//----------------------------------
		//言語切替
		if ( WND_UTL::AscKey ( 'L' ) )
		{
			m_lang = ( m_lang + 1 ) % 2;
			//0:日本語, 1:英語
			m_logo->SetIndexTexture ( m_lang );
			m_inst->SetIndexTexture ( m_lang );
		}


		//----------------------------------
		TASK_VEC::Move ();
	}


	void Title_lib::Input ()
	{
		//----------------------------------------------------------
		//選択
		if ( CFG_PUSH_KEY_12 ( PLY_LEFT ) )
		{
			AUD_PLAY_ONESHOT_SE ( SE_select_move );
			m_menu->Left ();
		}
		if ( CFG_PUSH_KEY_12 ( PLY_RIGHT ) )
		{
			AUD_PLAY_ONESHOT_SE ( SE_select_move );
			m_menu->Right ();
		}

		//----------------------------------------------------------
		//決定
		if ( CFG_PUSH_KEY_12 ( PLY_BTN0 ) )
		{
			AUD_PLAY_ONESHOT_SE ( SE_Sys_Enter );

			//フェードアウト開始
			m_fade_out->StartBlackOut ( FADE_OUT_T );
		}
	}


	P_GameScene Title_lib::Transit ()
	{
		//-----------------------------------
		//デモ フェード待機開始
		if ( m_demo->IsLast () )
		{
			//パラメータに反映
			//すべてランダム
			P_Param pParam = Scene_lib::GetpParam ();
			GameSettingFile & rGameStg = pParam->GetGameSetting();
			rGameStg.SetCharaName_Rnd ();
			rGameStg.SetCharaClr_Rnd ();
			rGameStg.SetBGM_Rnd ();
			rGameStg.SetStage_Rnd ();

			rGameStg.SetDemo ( T );

			AUD_STOP_ALL_BGM ();
			SaveParam ();

			//Scene_lib::Transit_Fighting ( MUTCH_MODE::MODE_CPU_CPU );
			GetpParam ()->GetGameSetting().SetMutchMode ( MUTCH_MODE::MODE_CPU_CPU );
			Transit_FtgMain ();
		}

		//-----------------------------------
		//フェード待機開始
		if ( m_fade_out->IsLast () )
		{
			++ m_plus_wait;
		}

		//フェード待機後、遷移
		if ( m_plus_wait > 0 )
		{
			if ( m_plus_wait > FADE_OUT_T - 1 )
			{
				//ゲーム共通パラメータ
				P_Param pParam = Scene_lib::GetpParam ();
				GameSettingFile & rGameStg = pParam->GetGameSetting();

				switch ( m_menu->GetTo() )
				{
				case TitleMenu::TITLE_TO::BATTLE_1Pvs2P:
					rGameStg.SetMutchMode ( MODE_PLAYER_PLAYER );
					pParam->SetFtgMode ( FTG_MODE::MODE_FTG_MAIN );
					break;
				case TitleMenu::TITLE_TO::BATTLE_1PvsCPU:
					rGameStg.SetMutchMode ( MODE_PLAYER_CPU );
					pParam->SetFtgMode ( FTG_MODE::MODE_FTG_MAIN );
					break;
				case TitleMenu::TITLE_TO::BATTLE_CPUvs2P:
					rGameStg.SetMutchMode ( MODE_CPU_PLAYER );
					pParam->SetFtgMode ( FTG_MODE::MODE_FTG_MAIN );
					break;
				case TitleMenu::TITLE_TO::BATTLE_CPUvsCPU:
					rGameStg.SetMutchMode ( MODE_CPU_CPU );
					pParam->SetFtgMode ( FTG_MODE::MODE_FTG_MAIN );
					break;
				case TitleMenu::TITLE_TO::TRAINING:
					rGameStg.SetMutchMode ( MODE_PLAYER_PLAYER );
					pParam->SetFtgMode ( FTG_MODE::MODE_TRAINING );
					break;
				default: break;
				}

				AUD_STOP_ALL_BGM ();
				SaveParam ();
				//Scene_lib::Transit_CharaSele ();
				Transit_CharaSele ();

				m_plus_wait = 0;
			}

			++ m_plus_wait;
		}

		return Scene_lib::Transit ();
	}

	void Title_lib::SaveParam ()
	{
		//ゲーム共通パラメータ
		P_Param pParam = Scene_lib::GetpParam ();
		GameSettingFile & rGameStg = pParam->GetGameSetting();
		rGameStg.Save ();
	}

	void Title_lib::OnMenu ()
	{
		m_menu->On ();
	}

	void Title_lib::OffMenu ()
	{
		m_menu->Off ();
	}


#pragma region CONST


	const float Title_lib::BG_X = 0;
	const float Title_lib::BG_Y = 0;
	const float Title_lib::BG_VX = -64.f;
	const float Title_lib::BG_P = (-7680 + 1920);

	const float Title_lib::LOGO_X = -40 + 1280 / 2 - 900 / 2;
	const float Title_lib::LOGO_Y = - 110;

	const float Title_lib::CURSOR_X = 400;
	const float Title_lib::CURSOR_Y = 720;
	const float Title_lib::CURSOR_P = 50;

	const float Title_lib::INST_X = 0;
	const float Title_lib::INST_Y = 960 - 27;

	const uint32 Title_lib::FADE_IN_T = 16;
	const uint32 Title_lib::FADE_OUT_T = 16;

	const uint32 Title_lib::TITLE_CALL_WAIT = 2;


#pragma endregion


}	//namespace GAME

