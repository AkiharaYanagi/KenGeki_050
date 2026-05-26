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
#include "DebugDisp.h"

//状態遷移先
#include "../01_Title/Title.h"
#include "../02_CharaSele/CharaSele.h"
#include "../03_FtgMain/FtgMain.h"
#include "../04_Training/Training.h"

#include "05_Result/Result_lib.h"



//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
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

		//-------------------------------------
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

		//リザルトから開始
		pScene = std::make_shared < Result_lib > ();

#if 0
		P_Scene pScene = nullptr;

		switch ( startMode )
		{
		//---------------------------------------------
		//タイトルから開始
		case START_TITLE:
			pScene = std::make_shared < Title > ();
		break;

		//---------------------------------------------
		//バトルから開始
		case START_BATTLE:
			pScene = std::make_shared < FtgMain > ();
		break;

		//---------------------------------------------
		//キャラセレから開始
		case START_CHARA_SELE:
			pScene = std::make_shared < CharaSele > ();
//			pScene = std::make_shared < _CharaSele > ();
		break;

		//---------------------------------------------
		case START_RESULT:
			//リザルトから開始
			pScene = std::make_shared < Result_lib > ();
		break;

		//---------------------------------------------
		case START_TRAINING:
			//トレーニングから開始
			pScene = std::make_shared < Training > ();
		break;

		case TEST_VOID:
			//テスト：空のシーン
			pScene = std::make_shared < TestScene > ();
			break;

		//---------------------------------------------
		default: break;

		}

#endif // 0

		//シーンの設定
		SetScene ( pScene );

		//-------------------------------------
		//最初のシーンにパラメータを設定する
		pScene->SetpParam ( std::move ( m_pParam ) );
		pScene->ParamInit ();
	}


}	//namespace GAME

