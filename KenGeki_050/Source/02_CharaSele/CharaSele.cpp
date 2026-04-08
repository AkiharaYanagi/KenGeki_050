//=================================================================================================
//
//	CharaSele_Main ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele.h"
#include "../90_GameMain/SeConst.h"
#include "../90_GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele::CharaSele()
	{
		//ステージ
		m_stage = std::make_shared < CharaSele_Stage > ();
		AddpTask ( m_stage );


		//上部メニュ
		m_menu = std::make_shared < CharaSele_Menu > ();
		AddpTask ( m_menu );


		//開戦ボタン
		m_center_button = MakepGrp ( U"CharaSele\\center_button.png", Z_SHADOW );
		m_center_button->SetPos ( 640 - 435 / 2, 960 - 435 / 2 );
		m_KaiSen = MakepGrp ( U"CharaSele\\KaiSen.png", Z_EFF );
		m_KaiSen->SetPos ( 640 - 198 / 2, 960 - 104 );

		//1P,2P,CPU表示
		m_playerInput = MakepGrp ( U"Player_1P.png", Z_EFF );
		m_playerInput->AddTexture_FromArchive ( U"Player_2P.png" );
		m_playerInput->AddTexture_FromArchive ( U"Player_CPU.png" );

		m_playerInput->AddObject ();
		m_pl_1p = m_playerInput->GetpObject ( 0 );
		m_pl_1p->SetPos ( VEC2 ( PL_1P_X, PL_Y ) );
		m_pl_2p = m_playerInput->GetpObject ( 1 );
		m_pl_2p->SetPos ( VEC2 ( PL_2P_X, PL_Y ) );


		//操作位置1P,2P
		m_input_pos = MakepGrp ( U"Demo_1P.png", Z_EFF );
		m_input_pos->AddTexture_FromArchive ( U"Demo_2P.png" );

		m_input_pos->AddObject ();

		m_ob_input_1p = m_input_pos->GetpObject ( 0 );
		m_ob_input_1p->SetPos ( VEC2 ( INPUT_1P_X, INPUT_Y ) );
		m_ob_input_1p->SetIndexTexture ( 0 );

		m_ob_input_2p = m_input_pos->GetpObject ( 1 );
		m_ob_input_2p->SetIndexTexture ( 1 );
		m_ob_input_2p->SetPos ( VEC2 ( INPUT_2P_X, INPUT_Y ) );

		m_input_pos->SetValid ( F );


		//トレーニング表示
		m_training = MakepGrp ( U"Title\\Training.png", Z_EFF );
		m_training->SetPos ( 640 - 303.f * 0.5f, 320 );
		m_training->SetValid ( F );


		//アクタ (1p/2p)
		m_plrActor_1p = std::make_shared < CharaSele_Player_Actor > ();
		m_plrActor_1p->SetPlayerID ( PLAYER_ID_1 );
		AddpTask ( m_plrActor_1p );

		m_plrActor_2p = std::make_shared < CharaSele_Player_Actor > ();
		m_plrActor_2p->SetPlayerID ( PLAYER_ID_2 );
		AddpTask ( m_plrActor_2p );


		//タイマ
		m_battleTime = std::make_shared < BattleTime > ();
		AddpTask ( m_battleTime );
		m_battleTime->SetTime ( 600 );
		m_battleTime->Start ();

		m_battleTime->SetPos_BG ( VEC2 ( (1280 / 2) - (185 / 2), 10 ) );
		m_battleTime->SetPos_Digit ( VEC2 { 16 + (1280 * 0.5f) - (128 / 2), 15 } );
		m_battleTime->SetZ ( Z_SYS );
		m_battleTime->ValidBG ( F );


		//BGM
		m_bgmName = MakepGrp ( U"Battle\\BGM_NAME_main_NoBGM.png", Z_EFF );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM_NAME_main_GYAVA.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM_NAME_main_Ouka.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM_NAME_main_Sae.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM_NAME_main_Retsudou.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM_NAME_main_FERARIA.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM_NAME_main_TSUKI.png" );
		m_bgmName->SetPos ( 640 - 303.f/2, 2 );


		//保存用共通パラメータ
		m_pParam = std::make_shared < Param > ();

		//フェードイン
		m_fade_in = std::make_shared < FadeRect > ();
		AddpTask ( m_fade_in );
		GRPLST_INSERT ( m_fade_in );
		m_fade_in->StartBlackIn ( FADE_IN_T );

		//フェードアウト
		m_fade_toTitle = std::make_shared < FadeRect > ();
		m_fade_toTitle->SetAfterClear ( F );
		AddpTask ( m_fade_toTitle );
		GRPLST_INSERT ( m_fade_toTitle );

		m_fade_toFighting = std::make_shared < FadeRect > ();
		m_fade_toFighting->SetAfterClear ( F );
		AddpTask ( m_fade_toFighting );
		GRPLST_INSERT ( m_fade_toFighting );

	}

	P_Grp CharaSele::MakepGrp ( const s3d::String & filename, float z )
	{
		P_Grp p = std::make_shared < GameGraphic > ();
		p->AddTexture_FromArchive ( filename );
		p->SetZ ( z );
		AddpTask ( p );
		GRPLST_INSERT ( p );
		return p;
	}

	CharaSele::~CharaSele()
	{

	}

	void CharaSele::ParamInit()
	{
		P_Param p = GetpParam ();
		m_pParam = p;
		m_stage->SetpParam ( p );
		m_plrActor_1p->SetpParam ( p );
		m_plrActor_2p->SetpParam ( p );

		//対戦によって操作・表示切替
		const GameSettingFile stg = p->GetGameSetting ();

		//トレーニング
		if ( FTG_MODE::MODE_TRAINING == p->GetFtgMode () )
		{
			m_training->SetValid ( T );

			// MODE_PLAYER_PLAYER : で操作は両者とも1P
			m_pl_1p->SetIndexTexture ( PL_INDEX_1P );
			m_plrActor_1p->SetInputPlayer ( PLAYER_ID_1 );
			m_plrActor_1p->Set_Active ();

			m_pl_2p->SetIndexTexture ( PL_INDEX_2P );
			m_plrActor_2p->SetInputPlayer ( PLAYER_ID_1 );
			m_plrActor_2p->Set_Wait ();
			m_ob_input_2p->SetValid ( F );
		}
		else //通常バトル
		{
			SwitchMode ();
		}

		BGM_ID bgm_id = p->GetGameSetting().GetBGM_ID ();
		m_bgmName->SetIndexTexture ( bgm_id );
	}

	void CharaSele::SwitchMode()
	{
		P_Param p = GetpParam ();
		const GameSettingFile stg = p->GetGameSetting ();

		//バトル
		//プレイヤーによって表示と操作を設定
		switch ( stg.GetMutchMode () )
		{
		case MODE_PLAYER_PLAYER :
			m_pl_1p->SetIndexTexture ( PL_INDEX_1P );
			m_plrActor_1p->SetInputPlayer ( PLAYER_ID_1 );
			m_plrActor_1p->Set_Active ();

			m_pl_2p->SetIndexTexture ( PL_INDEX_2P );
			m_plrActor_2p->SetInputPlayer ( PLAYER_ID_2 );
			m_plrActor_2p->Set_Active ();
		break;

		case MODE_PLAYER_CPU:
			m_pl_1p->SetIndexTexture ( PL_INDEX_1P );
			m_plrActor_1p->SetInputPlayer ( PLAYER_ID_1 );
			m_plrActor_1p->Set_Active ();

			m_pl_2p->SetIndexTexture ( PL_INDEX_CPU );
			m_plrActor_2p->SetInputPlayer ( PLAYER_ID_1 );
			m_plrActor_2p->Set_Wait ();
			m_ob_input_2p->SetValid ( F );
		break;

		case MODE_CPU_PLAYER:
			m_pl_1p->SetIndexTexture ( PL_INDEX_CPU );
			m_plrActor_1p->SetInputPlayer ( PLAYER_ID_2 );
			m_plrActor_1p->Set_Wait ();
			m_ob_input_1p->SetValid ( F );

			m_pl_2p->SetIndexTexture ( PL_INDEX_2P );
			m_plrActor_2p->SetInputPlayer ( PLAYER_ID_2 );
			m_plrActor_2p->Set_Active ();
		break;

		case MODE_CPU_CPU:
			m_pl_1p->SetIndexTexture ( PL_INDEX_CPU );
			m_plrActor_1p->SetInputPlayer ( PLAYER_ID_1 );
			m_plrActor_1p->Set_Active ();

			m_pl_2p->SetIndexTexture ( PL_INDEX_CPU );
			m_plrActor_2p->SetInputPlayer ( PLAYER_ID_1 );
			m_plrActor_2p->Set_Wait ();
			m_ob_input_2p->SetValid ( F );
		break;

		case MODE_PLAYER_NETWORK:
			m_pl_1p->SetIndexTexture ( PL_INDEX_1P );
			m_plrActor_1p->SetInputPlayer ( PLAYER_ID_1 );
			m_plrActor_1p->Set_Active ();

			m_pl_2p->SetIndexTexture ( PL_INDEX_2P );
			m_plrActor_2p->SetInputPlayer ( PLAYER_ID_1 );
			m_plrActor_2p->Set_Wait ();
		break;

		}
	}

	void CharaSele::Load()
	{
		//==================================================
		//	Scene共通
		//==================================================
		//遷移先を自身に設定
		//	(コンストラクタでは shared_from_this() が使えないため、Load() で呼び出す)
		Scene::SetwpThis ( shared_from_this () );
		//==================================================

		//アクタに親ポインタを設定
		m_plrActor_1p->SetwpCharaSeleMain ( shared_from_this () );
		m_plrActor_2p->SetwpCharaSeleMain ( shared_from_this () );

		//互いを設定
		m_plrActor_1p->SetwpOther ( m_plrActor_2p );
		m_plrActor_2p->SetwpOther ( m_plrActor_1p );


		//SOUND
		AUD_STOP_ALL_BGM();
		AUD_PLAY_LOOP_BGM ( BGM_CharaSele );	//初期BGMはキャラセレBGM

		Scene::Load ();
	}

	void CharaSele::Move()
	{
		//全体操作
		Input ();

		//ステージ選択
		if ( CFG_PUSH_KEY_12 ( PLY_BTN4 ) )
		{
			m_stage->Next ();
			AUD_PLAY_ONESHOT_SE ( SE_select_move );
		}
		if ( CFG_PUSH_KEY_12 ( PLY_BTN5 ) )
		{
			m_stage->Prev ();
			AUD_PLAY_ONESHOT_SE ( SE_select_move );
		}


		//BGM選択
		if ( CFG_PUSH_KEY_12 ( PLY_BTN2 ) )
		{
			GameSettingFile& stg = m_pParam->GetGameSetting();
			stg.NextBGM ();
			m_bgmName->SetIndexTexture ( stg.GetBGM_ID () );

			//BGMなし以外は再生開始
			AUD_STOP_ALL_BGM ();
			BGM_ID bgm_id = m_pParam->Get_BGM_ID ();
			if ( BGM_ID_NONE != bgm_id )
			{
				AUD_PLAY_LOOP_BGM ( BGM_ID_TO_NAME [ bgm_id ] );
			}
		}
		if ( CFG_PUSH_KEY_12 ( PLY_BTN3 ) )
		{
			GameSettingFile& stg = m_pParam->GetGameSetting();
			stg.PrevBGM ();
			m_bgmName->SetIndexTexture ( stg.GetBGM_ID () );

			//BGMなし以外は再生開始
			AUD_STOP_ALL_BGM ();
			BGM_ID bgm_id = m_pParam->Get_BGM_ID ();
			if ( BGM_ID_NONE != bgm_id )
			{
				AUD_PLAY_LOOP_BGM ( BGM_ID_TO_NAME [ bgm_id ] );
			}
		}

		Scene::Move ();
	}


	//全体操作
	void CharaSele::Input ()
	{
		//BackSpaceでタイトルに戻る (ESCは直接終了)
		//コントローラ(7:リセットボタン)でも戻る
		if ( ! m_fade_toTitle->IsActive () )
		{
			bool bBackSpace = WND_UTL::AscKey ( VK_BACK );
			bool bCtrlReset = CFG_PUSH_KEY_12 ( PLAYER_INPUT::PLY_BTN7 );
			if ( bBackSpace || bCtrlReset )
			{
				AUD_PLAY_ONESHOT_SE ( SE_select_Cancel );

				//フェード開始
				m_fade_toTitle->StartBlackOut ( 8 );
			}
		}
	}


	P_GameScene CharaSele::Transit()
	{
		//---------------------------------------------------
		//タイトルに移行
		if ( m_fade_toTitle->IsLast () )
		{
			Save ();
			AUD_STOP_ALL_BGM();
			Scene::Transit_Title ();
		}


		//---------------------------------------------------
		//プレイヤ２人が決定済みなら移項
		if ( ! m_fade_toFighting->IsActive () )
		{
			bool b1 = m_plrActor_1p->Is_Decided ();
			bool b2 = m_plrActor_2p->Is_Decided ();
			if ( b1 && b2 )
			{
				AUD_PLAY_ONESHOT_SE ( SE_Sys_Enter );
				//フェード開始
				m_fade_toFighting->Reset ();
				m_fade_toFighting->StartBlackOut ( 8 );
			}
		}

		//タイマで強制移行
		if ( m_battleTime->IsTimeUp () )
		{
			if ( ! m_fade_toFighting->IsActive () )
			{
				//カラー優先チェック
			PrimalColor1p2p ();

				//強制決定
				m_plrActor_1p->Change_CharaPick_to_Decide ();
				m_plrActor_2p->Change_CharaPick_to_Decide ();
				AUD_PLAY_ONESHOT_SE ( SE_Sys_Enter );
				//フェード開始
				m_fade_toFighting->Reset ();
				m_fade_toFighting->StartBlackOut ( 8 );
			}
		}

		//戦闘に移行
		if ( m_fade_toFighting->IsLast () )
		{
			Save ();
			AUD_STOP_ALL_BGM ();

			m_fade_toFighting->ShiftTargetColor ();

			//通常戦闘かトレーニングの分岐
			P_Param pPrm = Scene::GetpParam ();
			if ( FTG_MODE::MODE_FTG_MAIN == pPrm->GetFtgMode () )
			{
				Scene::Transit_Fighting ();
			}
			else
			{
				Scene::Transit_Training ();
			}
		}


		//---------------------------------------------------
		//通常時は自身を返す
		//他のシーンが確保されたなら遷移する
		return Scene::Transit ();
	}

	//指定アクタがどちらの操作か取得
	PLAYER_ID CharaSele::GetInputPlayer ( PLAYER_ID id )
	{
		PLAYER_ID ret = PLAYER_ID_1;
		if ( PLAYER_ID_1 == id )
		{
			ret = m_plrActor_1p->GetInputPlayer ();
		}
		else
		{
			ret = m_plrActor_2p->GetInputPlayer ();
		}
		return ret;
	}

	//入力開始
	bool CharaSele::IsWait ( PLAYER_ID id ) const
	{
		bool ret = T;
		if ( PLAYER_ID_1 == id )
		{
			ret = m_plrActor_1p->Is_Wait ();
		}
		else
		{
			ret = m_plrActor_2p->Is_Wait ();
		}
		return ret;
	}

	//入力開始
	void CharaSele::StartInput ( PLAYER_ID id )
	{
		if ( PLAYER_ID_1 == id )
		{
			m_plrActor_1p->Set_Active ();
		}
		else
		{
			m_plrActor_2p->Set_Active ();
		}
	}


	//=========================================
	//	内部関数
	//=========================================

	//キャラ選択、ステージ選択をパラメータ（ゲーム設定ファイル）に記録
	void CharaSele::Save ()
	{
		//パラメータには随時設定されているので書出のみ
		P_Param pPrm = Scene::GetpParam ();

		//設定ファイルに書出
		pPrm->GetGameSetting().Save ();
	}

	//カラー優先チェック
	void CharaSele::PrimalColor1p2p ()
	{
		//両者同一キャラ同一カラーか(未決定のみ)
		if ( SameCharaSameColor () )
		{
			GameSettingFile& stg = m_pParam->GetGameSetting();
			CHARA_COLOR color1 = stg.GetCharaColor1p ();

			//1p優先
			CHARA_COLOR another_color = ( color1 == CH_CLR_1 ) ? CH_CLR_2 : CH_CLR_1;
			m_plrActor_2p->SetColor ( another_color );
		}
	}

	//両者同一キャラ同一カラーか
	bool CharaSele::SameCharaSameColor () const
	{
		GameSettingFile& stg = m_pParam->GetGameSetting();

		CHARA_NAME name1 = stg.GetCharaName1p ();
		CHARA_NAME name2 = stg.GetCharaName2p ();
		bool same_chara = ( name1 == name2 );

		CHARA_COLOR color1 = stg.GetCharaColor1p ();
		CHARA_COLOR color2 = stg.GetCharaColor2p ();
		bool same_color = ( color1 == color2 );

		if ( same_chara && same_color )
		{
			return T;
		}
		return F;
	}


#pragma region CONST
	const uint32 CharaSele::FADE_IN_T = 8;
	const uint32 CharaSele::FADE_OUT_T = 8;

	const UINT32 CharaSele::PL_INDEX_1P = 0;
	const UINT32 CharaSele::PL_INDEX_2P = 1;
	const UINT32 CharaSele::PL_INDEX_CPU = 2;

	const float CharaSele::PL_1P_X = 19;
	const float CharaSele::PL_2P_X = 1280 - 19 - 64;
	const float CharaSele::PL_Y = 89;

	const float CharaSele::INPUT_1P_X = 250;
	const float CharaSele::INPUT_2P_X = 1280 - 200 - 256;
	const float CharaSele::INPUT_Y = 960 - 250;
#pragma endregion



}

