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


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//====================================================================
	//シーン生成関数
	//	各シーンで、遷移先のシーン生成を設定しておく
	P_Scene_lib CreateTitle::Do () { return MakeTitle (); }
	P_Scene_lib CreateCharaSele::Do () { return MakeCharaSele (); }
	P_Scene_lib CreateFtgMain::Do () { return MakeFtgMain (); }
	P_Scene_lib CreateTraining::Do () { return MakeTraining (); }
	P_Scene_lib CreateResult::Do () { return MakeResult (); }


	//各シーンの生成　（TitleはScene全て）
	P_Scene_lib MakeTitle()
	{
		GRPLST_CLEAR ();
		P_Title_lib p = std::make_shared < Title_lib > ();
		p->SetpNext_Title ( std::make_shared < CreateTitle > () );
		p->SetpNext_CharaSele ( std::make_shared < CreateCharaSele > () );
		p->SetpNext_FtgMain ( std::make_shared < CreateFtgMain > () );
		return p;
	}

	P_Scene_lib MakeCharaSele()
	{
		GRPLST_CLEAR ();
		P_ChSl p = std::make_shared < CharaSele > ();
		p->SetpNext_Title ( std::make_shared < CreateTitle > () );
		p->SetpNext_Fighting ( std::make_shared < CreateFtgMain > () );
		p->SetpNext_Training ( std::make_shared < CreateTraining > () );
		return p;
	}

	P_Scene_lib MakeFtgMain()
	{
		GRPLST_CLEAR ();
		P_FtgMain p = std::make_shared < FtgMain > ();
		p->SetpNext_Title ( std::make_shared < CreateTitle > () );
		p->SetpNext_CharaSele ( std::make_shared < CreateCharaSele > () );
		p->SetpNext_Result ( std::make_shared < CreateResult > () );
		return p;
	}

	P_Scene_lib MakeTraining()
	{
		GRPLST_CLEAR ();
		P_Training p = std::make_shared < Training > ();
		p->SetpNext_Title ( std::make_shared < CreateTitle > () );
		return p;
	}

	P_Scene_lib MakeResult()
	{
		GRPLST_CLEAR ();
		P_Result_lib p = std::make_shared < Result_lib > ();
		p->SetpNext_Title ( std::make_shared < CreateTitle > () );
		p->SetpNext_CharaSele ( std::make_shared < CreateCharaSele > () );
		return p;
	}


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
		case START_TITLE:		pScene = MakeTitle (); break;		//タイトルから開始
		case START_CHARA_SELE:	pScene = MakeCharaSele (); break;	//キャラセレから開始
		case START_BATTLE:		pScene = MakeFtgMain (); break;		//バトルから開始
		case START_TRAINING:	pScene = MakeTraining (); break;	//トレーニングから開始
		case START_RESULT:		pScene = MakeResult (); break;		//リザルトから開始
		default: break;
		}

		//シーンの設定
		SetScene ( pScene );

		//-------------------------------------
		//最初のシーンにパラメータを設定する
		pScene->SetpParam ( std::move ( m_pParam ) );
		pScene->ParamInit ();
	}

}	//namespace GAME

