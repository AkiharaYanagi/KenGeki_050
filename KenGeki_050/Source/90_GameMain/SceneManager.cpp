//=================================================================================================
//
// シーンマネージャ ソース
//		ゲームシーンを管理
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "SceneManager.h"
#include "00_Core/DebugDisp.h"

//状態遷移先
#include "01_Title/Title_lib.h"
#include "02_CharaSele/CharaSele.h"

#if 0
#include "../03_FtgMain/FtgMain.h"
#include "../04_Training/Training.h"
#endif // 0

#include "05_Result/Result_lib.h"



//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//====================================================================
	P_Scene_lib CreateTitle::Do () { return std::make_shared < Title_lib > (); }
	P_Scene_lib CreateCharaSele::Do () { return std::make_shared < CharaSele > (); }
	//P_Scene_lib CreateFtgMain::Do () { return std::make_shared < FtgMain_lib > (); }
	P_Scene_lib CreateFtgMain::Do () { return std::make_shared < Title_lib > (); }
	//P_Scene_lib CreateTraining::Do () { return std::make_shared < Training_lib > (); }
	P_Scene_lib CreateTraining::Do () { return std::make_shared < Title_lib > (); }
	P_Scene_lib CreateResult::Do () { return std::make_shared < Result_lib > (); }

	//====================================================================
	SceneManager_lib::SceneManager_lib()
	{
		//ゲーム共通パラメータ
		m_pParam = std::make_shared < Param > ();
	}

	SceneManager_lib::~SceneManager_lib()
	{
	}

	void SceneManager_lib::Load ()
	{
		//-------------------------------------
		//シーン共通パラメータ読込
		m_pParam->Load ();

		//シーン開始
		Start ();

		GameSceneManager::Load ();
	}

	void SceneManager_lib::Start()
	{
		//最初のシーンを設定ファイルから取得する
		GameSettingFile stgs = m_pParam->GetGameSetting ();
		START_MODE startMode = stgs.GetStartMode ();

#if 0
		//テスト用 開始状態選択
		startMode = START_TITLE;
//		startMode = START_CHARA_SELE;
//		startMode = START_BATTLE;
//		startMode = START_TRAINING;
//		startMode = START_RESULT;
#endif // 0

#if 0

		//デバッグ表示オン/オフ 初期状態
		//ExeChara 1p/2p のとき、1pの値を2pで上書きに注意
		if ( g_bDEBUG_DISP )
		{
			//ゲーム内ウィンドウデバッグ表示のオン
			DBGOUT_WND_ON ();
		}
		else
		{
			//Siv3D IDE出力 Loggerの非表示
			s3d::Logger.disable ();

			//ゲーム内表示のオフ
			DBGOUT_WND_OFF ();
			Print;
		}

#endif // 0


		//全キャラデータを事前読込
		// ->Titleで読み込みするように変更
#if 0
		if ( startMode == START_TITLE )
		{
//			// ここで読込しないとき、バトルメインでキャラの個別読込
			m_pParam->LoadCharaData_All ();
		}
#endif // 0


		//開始シーンの選択
		std::shared_ptr < Scene_lib > pScene = nullptr;

		switch ( startMode )
		{
		//---------------------------------------------
		//タイトルから開始
		case START_TITLE:
			pScene = MakeTitle ();
		break;

#if 0
		//---------------------------------------------
		//キャラセレから開始
		case START_CHARA_SELE:
			pScene = std::make_shared < CharaSele > ();
//			pScene = std::make_shared < _CharaSele > ();
		break;
		//---------------------------------------------
		//バトルから開始
		case START_BATTLE:
			pScene = std::make_shared < FtgMain > ();
		break;

		//---------------------------------------------
		case START_TRAINING:
			//トレーニングから開始
			pScene = std::make_shared < Training > ();
		break;
#endif // 0

		//---------------------------------------------
		case START_RESULT:
			//リザルトから開始
			pScene = MakeResult ();
		break;

		default: break;

		}


		//シーンの設定
		SetScene ( pScene );

		//-------------------------------------
		//最初のシーンにパラメータを設定する
		pScene->SetpParam ( std::move ( m_pParam ) );
		pScene->ParamInit ();
	}


	P_Scene_lib SceneManager_lib::MakeTitle()
	{
		P_Title_lib p = std::make_shared < Title_lib > ();
		p->SetpNext_CharaSele ( std::make_shared < CreateCharaSele > () );
		//p->SetpNext_FtgMain ( std::make_shared < CreateFtgMain > () );
		p->SetpNext_FtgMain ( std::make_shared < CreateTitle > () );
		return p;
	}

	P_Scene_lib SceneManager_lib::MakeCharaSele()
	{
		P_ChSl p = std::make_shared < CharaSele > ();
		//p->SetpNext_Fighting ( std::make_shared < CreateFtgMain > () );
		p->SetpNext_Fighting ( std::make_shared < CreateTitle > () );
		//p->SetpNext_Training ( std::make_shared < CreateTraining > () );
		p->SetpNext_Training ( std::make_shared < CreateTitle > () );
		p->SetpNext_Title ( std::make_shared < CreateTitle > () );
		return p;
	}

	P_Scene_lib SceneManager_lib::MakeFtgMain()
	{
#if 0
		P_Title_lib p = std::make_shared < FtgMain_lib > ();
		p->SetpNext_CharaSele ( std::make_shared < CreateCharaSele > () );
		p->SetpNext_Fighting ( std::make_shared < CreateCharaSele > () );
		return p;

#endif // 0
		return std::make_shared < Title_lib > ();
	}

	P_Scene_lib SceneManager_lib::MakeTraining()
	{
#if 0
		P_Title_lib p = std::make_shared < Title_lib > ();
		p->SetpNext_CharaSele ( std::make_shared < CreateCharaSele > () );
		p->SetpNext_Fighting ( std::make_shared < CreateCharaSele > () );
		return p;
#endif // 0
		return std::make_shared < Title_lib > ();
	}

	P_Scene_lib SceneManager_lib::MakeResult()
	{
		P_Result_lib p = std::make_shared < Result_lib > ();
		p->SetpNext_CharaSele ( std::make_shared < CreateCharaSele > () );
		p->SetpNext_Title ( std::make_shared < CreateTitle > () );
		return p;
	}



}	//namespace GAME

