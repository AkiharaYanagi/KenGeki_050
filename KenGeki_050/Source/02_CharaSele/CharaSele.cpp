//=================================================================================================
//
//	CharaSele　メインクラス ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele.h"
#include "../90_GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele::CharaSele()
	{
		//背景
		m_bg = std::make_shared < GameGraphic > ();
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\bg.png" );
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );


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
	}

	CharaSele::~CharaSele()
	{

	}

	void CharaSele::ParamInit ()
	{
		P_Param pPrm = GetpParam();
		GameSettingFile stg = pPrm->GetGameSetting ();
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

		//BGM
		SND_STOP_ALL_BGM ();
		SND_PLAY_LOOP_BGM ( BGM_CharaSele );



		TASK_VEC::Load ();
	}

	void CharaSele::Move()
	{
		TASK_VEC::Move ();
	}

	P_GameScene CharaSele::Transit ()
	{
		//キー1でシーンを進める
		if ( CFG_PUSH_KEY ( P1_BTN0 ) || CFG_PUSH_KEY ( P2_BTN0 ) )
		{
//			SND_PLAY_ONESHOT_SE ( SE_select_decide );

			//フェード開始
//			m_fade_out->StartBlackOut ( FADE_OUT_T );


			SND_STOP_ALL_BGM ();
			Scene::Transit_Training ();
		}

		return Scene::Transit ();
	}

}

