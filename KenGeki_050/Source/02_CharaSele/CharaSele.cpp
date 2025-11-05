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
		m_center_button = std::make_shared < GameGraphic > ();
		m_center_button->AddTexture_FromArchive ( U"CharaSele\\center_button.png" );
		m_center_button->SetPos ( 640 - 435 / 2, 960 - 435 / 2 );
		m_center_button->SetZ ( Z_SHADOW );
		AddpTask ( m_center_button );
		GRPLST_INSERT ( m_center_button );

		m_KaiSen = std::make_shared < GameGraphic > ();
		m_KaiSen->AddTexture_FromArchive ( U"CharaSele\\KaiSen.png" );
		m_KaiSen->SetPos ( 640 - 198 / 2, 960 - 104 );
		m_KaiSen->SetZ ( Z_EFF );
		AddpTask ( m_KaiSen );
		GRPLST_INSERT ( m_KaiSen );


		//1P,2P,CPU表示
		m_playerInput = std::make_shared < GameGraphic > ();
		m_playerInput->AddTexture_FromArchive ( U"Player_1P.png" );
		m_playerInput->AddTexture_FromArchive ( U"Player_2P.png" );
		m_playerInput->AddTexture_FromArchive ( U"Player_CPU.png" );
		m_playerInput->SetZ ( Z_EFF );
		AddpTask ( m_playerInput );
		GRPLST_INSERT ( m_playerInput );

		m_playerInput->AddObject ();
		m_pl_1p = m_playerInput->GetpObject ( 0 );
		m_pl_1p->SetPos ( VEC2 ( PL_1P_X, PL_Y ) );
		m_pl_2p = m_playerInput->GetpObject ( 1 );
		m_pl_2p->SetPos ( VEC2 ( PL_2P_X, PL_Y ) );


		//トレーニング表示
		m_training = std::make_shared < GameGraphic > ();
		m_training->AddTexture_FromArchive ( U"Title\\Training.png" );
		m_training->SetPos ( 640 - 303.f * 0.5f, 320 );
		m_training->SetZ ( Z_EFF );
		AddpTask ( m_training );
		GRPLST_INSERT ( m_training );
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
		m_battleTime->Start ();

		m_battleTime->SetPos_BG ( VEC2 ( (1280 / 2) - (185 / 2), 0 ) );
		m_battleTime->SetPos_Digit ( VEC2 { 16 + (1280 * 0.5f) - (128 / 2), 15 } );
		m_battleTime->SetZ ( Z_SYS );
		m_battleTime->ValidBG ( F );


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

	CharaSele::~CharaSele()
	{

	}

	void CharaSele::ParamInit()
	{
		P_Param p = GetpParam ();
		m_stage->SetpParam ( p );
		m_plrActor_1p->SetpParam ( p );
		m_plrActor_2p->SetpParam ( p );

#if 0

		//プレイヤーCPU操作表示
		PLAYER_MODE plMode1p = stg.GetPlayerMode1p ();
		if ( MODE_PLAYER == plMode1p )
		{
			m_pl_1p->SetIndexTexture ( PL_INDEX_1P );
		}
		else if ( MODE_CPU == plMode1p )
		{
			m_pl_1p->SetIndexTexture ( PL_INDEX_CPU );
		}
		PLAYER_MODE plMode2p = p->GetGameSetting ().GetPlayerMode2p ();
		if ( MODE_PLAYER == plMode2p )
		{
			m_pl_2p->SetIndexTexture ( PL_INDEX_2P );
		}
		else if ( MODE_CPU == plMode2p )
		{
			m_pl_2p->SetIndexTexture ( PL_INDEX_CPU );
		}

#endif // 0

		//対戦によって操作・表示切替
		const GameSettingFile stg = p->GetGameSetting ();
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
		break;

		case MODE_CPU_PLAYER:
			m_pl_1p->SetIndexTexture ( PL_INDEX_CPU );
			m_plrActor_1p->SetInputPlayer ( PLAYER_ID_2 );
			m_plrActor_1p->Set_Wait ();

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

		//トレーニング表示
		FTG_MODE ftgMode = p->GetFtgMode();
		if ( FTG_MODE::MODE_TRAINING == ftgMode )
		{
			m_training->SetValid ( T );
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

		m_plrActor_1p->SetwpCharaSeleMain ( shared_from_this () );
		m_plrActor_2p->SetwpCharaSeleMain ( shared_from_this () );

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
		if ( CFG_PUSH_KEY_12 ( PLY_BTN1 ) )
		{
			m_stage->Next ();
			AUD_PLAY_ONESHOT_SE ( SE_select_move );
		}
		if ( CFG_PUSH_KEY_12 ( PLY_BTN2 ) )
		{
			m_stage->Prev ();
			AUD_PLAY_ONESHOT_SE ( SE_select_move );
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


#pragma region CONST
	const uint32 CharaSele::FADE_IN_T = 8;
	const uint32 CharaSele::FADE_OUT_T = 8;

	const UINT32 CharaSele::PL_INDEX_1P = 0;
	const UINT32 CharaSele::PL_INDEX_2P = 1;
	const UINT32 CharaSele::PL_INDEX_CPU = 2;

	const float CharaSele::PL_1P_X = 20;
	const float CharaSele::PL_2P_X = 1280 - 20 - 64;
	const float CharaSele::PL_Y = 100;
#pragma endregion



}

