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
		SND_STOP_ALL_BGM();
		SND_PLAY_LOOP_BGM ( BGM_CharaSele );	//初期BGMはキャラセレBGM

		Scene::Load ();
	}

	void CharaSele::Move()
	{
		Input ();

		//ステージ選択
		if ( CFG_PUSH_KEY_12 ( PLY_BTN1 ) )
		{
			m_stage->Next ();
			SND_PLAY_ONESHOT_SE ( SE_select_move );
		}
		if ( CFG_PUSH_KEY_12 ( PLY_BTN2 ) )
		{
			m_stage->Prev ();
			SND_PLAY_ONESHOT_SE ( SE_select_move );
		}

		if ( CFG_PUSH_KEY ( P1_BTN7 ) )
		{
			SND_STOP_ALL_BGM();
			SND_PLAY_LOOP_BGM ( U"BGM01_CharaSele.wav" );
		}
		Scene::Move ();
	}

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
				SND_PLAY_ONESHOT_SE ( SE_select_Cancel );

				//フェード開始
				m_fade_toTitle->StartBlackOut ( 8 );
			}
		}


		//プレイヤ２人が決定済みなら移項
		if ( ! m_fade_toFighting->IsActive () )
		{
			bool b1 = m_plrActor_1p->Is_Decided ();
			bool b2 = m_plrActor_2p->Is_Decided ();
			if ( b1 && b2 )
			{
				SND_PLAY_ONESHOT_SE ( SE_Sys_Enter );
				//フェード開始
				m_fade_toFighting->StartBlackOut ( 8 );
			}
		}

	}

	P_GameScene CharaSele::Transit()
	{

		//タイトルに移行
		if ( m_fade_toTitle->IsLast () )
		{
			Save ();
			SND_STOP_ALL_BGM();
			Scene::Transit_Title ();
		}

		//戦闘に移行
		if ( m_fade_toFighting->IsLast () )
		{
			Save ();
			SND_STOP_ALL_BGM ();

			m_fade_toFighting->ShiftTargetColor ();

			//通常戦闘かトレーニングの分岐
			P_Param pPrm = Scene::GetpParam ();
			if ( FTG_MODE::MODE_FTG_MAIN == pPrm->GetFtgMode () )
			{
				Scene::Transit_Fighting ();
			}
			else if ( FTG_MODE::MODE_TRAINING == pPrm->GetFtgMode () )
			{
				Scene::Transit_Training ();
			}
		}


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
#if 0
		//パラメータに記録し、次シーン以降で用いる
		P_Param pPrm = Scene::GetpParam ();
		GameSettingFile& rGameStg = pPrm->GetGameSetting ();

		rGameStg.SetCharaName1p ( m_plrActor_1p->GetCharaName() );
		rGameStg.SetCharaName2p ( m_plrActor_2p->GetCharaName() );
		rGameStg.SetCharaColor1p ( m_plrActor_1p->GetColor() );
		rGameStg.SetCharaColor2p ( m_plrActor_2p->GetColor() );
		rGameStg.SetStage_Name ( m_stage->GetStageName () );
		rGameStg.SetBGM_ID ( m_bgm->Get_ID () );

#endif // 0

		//設定ファイルに書出
		pPrm->GetGameSetting().Save ();
	}


#pragma region CONST
	const uint32 CharaSele::FADE_IN_T = 8;
	const uint32 CharaSele::FADE_OUT_T = 8;
#pragma endregion



}

