//=================================================================================================
//
//	Title
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Title.h"
#include "../90_GameMain/SeConst.h"
#include "../90_GameMain/VoiceConst.h"
#include "../90_GameMain/DebugDisp.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#if 0
//		ver 0.55	2026/01/13(火) ２ラウンド同時取得バグ修正
//		ver 0.54	2026/01/04(日) ごちゃまぜゲーム会 + 修正
//		ver 0.53	2025/12/12(金) 修正
//		ver 0.52	2025/12/04(木) 修正
//		ver 0.51	2025/11/25(火) デジゲー博2025 + 修正
//		ver 0.50	2025/11/09(日) デジゲー博2025
//		--------------------------------------------------------------
//		ver 0.25	2025/04/26(土) ガード修正版
//		ver 0.24	2025/04/20(日) バトル修正版
//		ver 0.23	2025/02/22(土) 修正版
//		ver 0.22	2025/02/10(日) Steam対応開始に合わせた修正版
//		ver 0.21	2025/01/26(日) バトルアップデート版
//		ver 0.20	2024/12/30(月) コミックマーケット105 (2024冬コミ) 公開
//		ver 0.15	2024/12/15(日) 変な格ゲー会 ロケテスト
//		ver 0.12	2024/11/	　 バグ修正
//		ver 0.10	2024/11/03(日) デジゲー博2024 公開
#endif // 0
	const char32_t Title::Ver[] = U"ver 0.55";


	//--------------------------------------------------------
	//constexprは前方宣言
	constexpr uint32 FADE_IN_T = 16;
	constexpr uint32 FADE_OUT_T = 16;
	constexpr uint32 TITLE_CALL_WAIT = 2;


	Title::Title ()
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
		m_logo->SetPos ( VEC2 ( LOGO_X, LOGO_Y ) );

		//メニュー
		m_menu = std::make_shared < TitleMenu > ();
		AddpTask ( m_menu );

		//Ver.
		m_strVer = std::make_shared < GrpStr > ();
		m_strVer->SetPos ( 1280/2 - 40, 934 );
		m_strVer->SetZ ( Z_MENU - 0.001f );
		m_strVer->SetStr ( Ver );
		AddpTask ( m_strVer );
		GRPLST_INSERT ( m_strVer );

		//Demo
		m_demo = std::make_shared < TitleDemo >();
		AddpTask ( m_demo );

		//Inst
		m_inst = MakepGrp ( U"Title\\Title_Inst.png", Z_MENU - 0.001f );
		m_inst->SetPos ( VEC2 ( 0, 0 ) );
		//m_inst->SetValid ( F );

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

	P_Grp Title::MakepGrp ( LPCUSTR filename, float Z = 0.5f )
	{
		P_Grp p = std::make_shared < GameGraphic > ();
		p->AddTexture_FromArchive ( filename );
		p->SetZ ( Z );
		AddpTask ( p );
		GRPLST_INSERT ( p );
		return p;
	}


	Title::~Title ()
	{
	}


	void Title::ParamInit ()
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


	void Title::Load ()
	{
		//==================================================
		//	Scene共通
		//==================================================
		//遷移先を自身に設定
		//	(コンストラクタでは shared_from_this() が使えないため、Load() で呼び出す)
		Scene::SetwpThis ( shared_from_this () );
		//==================================================


		Scene::Load ();
	}

	void Title::Move ()
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
#if 0
			LPCUSTR vc_name = VC_04_FERARIA_TITLE_CALL;

#endif // 0
			int rnd = s3d::Random ( 0, 4 );
			LPCUSTR vc_name = U"";
			switch ( rnd )
			{
			case 0: vc_name = VC_00_SAE_TITLE_CALL; break;
			case 1: vc_name = VC_01_RETSUDOU_TITLE_CALL; break;
			case 2: vc_name = VC_02_OUKA_TITLE_CALL; break;
			case 3: vc_name = VC_04_FERARIA_TITLE_CALL; break;
			case 4: vc_name = VC_90_CONSOME_TITLE_CALL; break;
			}

			s3d::AudioAsset::Wait ( vc_name );
			AUD_PLAY_ONESHOT_VC ( vc_name );
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

		TASK_VEC::Move ();
	}


	void Title::Input ()
	{


		//----------------------------------------------------------
		//選択
		if ( CFG_PUSH_KEY_12 ( PLY_LEFT ) )
		{
#if 0

			switch ( m_to )
			{
			case TITLE_TO::BATTLE_1Pvs2P:
				m_to = TITLE_TO::BATTLE_1PvsCPU;
				m_item->SetIndexTexture ( 1 );
			break;
			case TITLE_TO::BATTLE_1PvsCPU:
				m_to = TITLE_TO::BATTLE_CPUvs2P;
				m_item->SetIndexTexture ( 2 );
			break;
			case TITLE_TO::BATTLE_CPUvs2P:
				m_to = TITLE_TO::BATTLE_CPUvsCPU;
				m_item->SetIndexTexture ( 3 );
			break;
			case TITLE_TO::BATTLE_CPUvsCPU:
				m_to = TITLE_TO::TRAINING;
				m_item->SetIndexTexture ( 4 );
			break;
			case TITLE_TO::TRAINING:
				m_to = TITLE_TO::BATTLE_1Pvs2P;
				m_item->SetIndexTexture ( 0 );
			break;
			default: break;
			}
			m_item_x -= 50;
			m_item->SetPos ( VEC2 ( m_item_x, 960 - 200 ) );

#endif // 0

			AUD_PLAY_ONESHOT_SE ( SE_select_move );
			m_menu->Left ();
		}
		if ( CFG_PUSH_KEY_12 ( PLY_RIGHT ) )
		{
#if 0

			switch ( m_to )
			{
			case TITLE_TO::BATTLE_1Pvs2P:
				m_to = TITLE_TO::BATTLE_1PvsCPU;
				m_item->SetIndexTexture ( 1 );
			break;
			case TITLE_TO::BATTLE_1PvsCPU:
				m_to = TITLE_TO::BATTLE_CPUvs2P;
				m_item->SetIndexTexture ( 2 );
			break;
			case TITLE_TO::BATTLE_CPUvs2P:
				m_to = TITLE_TO::BATTLE_CPUvsCPU;
				m_item->SetIndexTexture ( 3 );
			break;
			case TITLE_TO::BATTLE_CPUvsCPU:
				m_to = TITLE_TO::TRAINING;
				m_item->SetIndexTexture ( 4 );
			break;
			case TITLE_TO::TRAINING:
				m_to = TITLE_TO::BATTLE_1Pvs2P;
				m_item->SetIndexTexture ( 0 );
			break;
			default: break;
			}
			m_item_x += 50;
			m_item->SetPos ( VEC2 ( m_item_x, 960 - 200 ) );

#endif // 0

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


	P_GameScene Title::Transit ()
	{
		//-----------------------------------
		//デモ フェード待機開始
		if ( m_demo->IsLast () )
		{
			//パラメータに反映
			//すべてランダム
			P_Param pParam = Scene::GetpParam ();
			GameSettingFile & rGameStg = pParam->GetGameSetting();
			rGameStg.SetCharaName_Rnd ();
			rGameStg.SetCharaClr_Rnd ();
			rGameStg.SetBGM_Rnd ();
			rGameStg.SetStage_Rnd ();

			rGameStg.SetDemo ( T );

			AUD_STOP_ALL_BGM ();
			SaveParam ();
			Scene::Transit_Fighting ( MUTCH_MODE::MODE_CPU_CPU );
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
				P_Param pParam = Scene::GetpParam ();
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
				Scene::Transit_CharaSele ();

				m_plus_wait = 0;
			}

			++ m_plus_wait;
		}

		return Scene::Transit ();
	}

	void Title::SaveParam ()
	{
		//ゲーム共通パラメータ
		P_Param pParam = Scene::GetpParam ();
		GameSettingFile & rGameStg = pParam->GetGameSetting();
		rGameStg.Save ();
	}

	void Title::OnMenu ()
	{
		m_menu->On ();
	}

	void Title::OffMenu ()
	{
		m_menu->Off ();
	}


#pragma region CONST


	const float Title::BG_X = 0;
	const float Title::BG_Y = 0;
	const float Title::BG_VX = -64.f;
	const float Title::BG_P = (-7680 + 1920);

	const float Title::LOGO_X = -40 + 1280 / 2 - 900 / 2;
	const float Title::LOGO_Y = - 110;

	const float Title::CURSOR_X = 400;
	const float Title::CURSOR_Y = 720;
	const float Title::CURSOR_P = 50;

	const float Title::INST_X = 0;
	const float Title::INST_Y = 960 - 27;

	const uint32 Title::FADE_IN_T = 16;
	const uint32 Title::FADE_OUT_T = 16;

	const uint32 Title::TITLE_CALL_WAIT = 2;


#pragma endregion


}	//namespace GAME

