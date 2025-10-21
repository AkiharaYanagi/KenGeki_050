//=================================================================================================
//
// シーン
//		解放と確保を伴う状態遷移
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Scene.h"

//状態遷移先
#include "../01_Title/Title.h"
#include "../02_CharaSele/CharaSele.h"
#include "../03_FtgMain/FtgMain.h"
#include "../04_Training/Training.h"
#include "../05_Result/Result.h"

#if 0
#include "../GameMain/SoundConst.h"
#include "../GameMain/DebugDisp.h"
#endif // 0


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------------

	Scene::Scene ()
	{
	}

	Scene::~Scene ()
	{
	}

	void Scene::Load ()
	{
		//	※	継承先
		//		Load ()内で shared_from_this()をScene側に登録する
		//		Scene::Load (); も呼ぶ
		GameScene::Load ();
	}

	//状態遷移
	P_GameScene Scene::Transit ()
	{
		//他のシーンが確保されたなら遷移する
		if ( mp_Transit.use_count () != 0 )
		{
			return mp_Transit;
		}

		//通常時
		return mwp_This.lock ();
	}




	//[シーン遷移] タイトルに戻る
	void Scene::Transit_Title ()
	{
		GRPLST_CLEAR ();
		mp_Transit = std::make_shared < Title > ();
	}

	//[シーン遷移] ファイティングに移行
	void Scene::Transit_Fighting ()
	{
		GRPLST_CLEAR ();
		mp_Transit = std::make_shared < FtgMain > ();
	}

	void Scene::Transit_Fighting ( MUTCH_MODE mode )
	{
		GetpParam ()->GetGameSetting().SetMutchMode ( mode );
		Transit_Fighting ();
	}

	//[シーン遷移] トレーニングに移行
	void Scene::Transit_Training ()
	{
		GRPLST_CLEAR ();
		mp_Transit = std::make_shared < Training > ();
	}
	
	//[シーン遷移] キャラセレに移行
	void Scene::Transit_CharaSele ()
	{
		GRPLST_CLEAR ();
		mp_Transit = std::make_shared < CharaSele > ();
	}

	//[シーン遷移] リザルトに移行
	void Scene::Transit_Result ()
	{
		GRPLST_CLEAR ();
		mp_Transit = std::make_shared < Result > ();
	}



	//====================================================================
	SceneManager::SceneManager()
	{
		//ゲーム共通パラメータ
		m_pParam = std::make_shared < Param > ();
	}

	SceneManager::~SceneManager()
	{
	}

	void SceneManager::Load ()
	{
		//-------------------------------------
		//シーン共通
		//格闘部分共通パラメータシングルトン生成
		G_Ftg::Create ();

		m_pParam->Load ();
		//-------------------------------------
		//シーン開始
		Start ();

		GameSceneManager::Load ();
	}

	void SceneManager::Start()
	{
		//最初のシーンを設定ファイルから取得する
		GameSettingFile stgs = m_pParam->GetGameSetting ();
		START_MODE startMode = stgs.GetStartMode ();

		//テスト用 開始状態選択
		startMode = START_TITLE;
//		startMode = START_CHARA_SELE;
//		startMode = START_BATTLE;
//		startMode = START_TRAINING;
//		startMode = START_RESULT;
#if 0
#endif // 0


#if 0
		//デバッグ表示オン/オフ 初期状態
		//ExeChara 1p/2p のとき、1pの値を2pで上書きに注意
#if DEBUG_DISP		
		//ゲーム内表示のオフ
		DBGOUT_WND_ON ();

		//コマンドプロンプト表示
//		DebugOutPrint::Create ();
		DebugOutPrint::OpenPrompt ();
		PRINT_F_S ( U"start DebugOutPrint.\n" );

#else
		//Siv3D IDE出力 Loggerの非表示
		s3d::Logger.disable ();

		//ゲーム内表示のオフ
		DBGOUT_WND_OFF ();
		Print;
#endif	//DEBUG_DISP


		if ( startMode == START_TITLE )
		{
			//全キャラデータを事前読込
//			// ここで読込しないとき、バトルメインでキャラの個別読込
			m_pParam->LoadCharaData_All ();
		}

#endif // 0


		//開始シーンの選択
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
			pScene = std::make_shared < Result > ();
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

		//シーンの設定
		SetScene ( pScene );

		//-------------------------------------
		//最初のシーンにパラメータを設定する
		pScene->SetpParam ( std::move ( m_pParam ) );
		pScene->ParamInit ();

	}


	void SceneManager::Move ()
	{
		GameSceneManager::Move ();
	}


}	//namespace GAME

