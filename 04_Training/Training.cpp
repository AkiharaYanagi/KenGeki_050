//=================================================================================================
//
//	Training ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "04_Training/Training.h"
#include "03_FtgMain/Fighting.h"
#include "03_FtgMain/G_Ftg.h"

#if 0

#include "../Title/Title.h"
#include "../GameMain/SoundConst.h"

#endif // 0


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//定数
	const float Training::BX = ( 1280 - 206 ) * 0.5f;
	const float Training::BY = 190.f;
	const float Training::BX_KI = ( 1280 - 512 ) * 0.5f;
	const float Training::BY_KI = 900.f;


	Training::Training ()
	{
		//トレーニング表示
		m_training = std::make_shared < GameGraphic > ();
		m_training->AddTexture_FromArchive ( U"training.png" );
		m_training->SetPos ( BX, BY );
		m_training->SetZ ( Z_CH );
		AddpTask ( m_training );
		GRPLST_INSERT ( m_training );

		m_training_Intro0 = std::make_shared < GameGraphic > ();
//		m_training_Intro0->AddTexture_FromArchive ( U"Training\\Intro_Training0.png" );
		m_training_Intro0->SetPos ( 0, 960 - 29 );
		m_training_Intro0->SetZ ( Z_MENU );
		AddpTask ( m_training_Intro0 );
		GRPLST_INSERT ( m_training_Intro0 );

		m_training_Intro1 = std::make_shared < GameGraphic > ();
//		m_training_Intro1->AddTexture_FromArchive ( U"Training\\Intro_Training1.png" );
		m_training_Intro1->SetPos ( 0, 0 );
		m_training_Intro1->SetZ ( Z_MENU );
		AddpTask ( m_training_Intro1 );
		GRPLST_INSERT ( m_training_Intro1 );


		//戦闘
		m_fighting = std::make_shared < Fighting > ();
		AddpTask ( m_fighting );


		//ポーズメニュ
		m_trainingMenu = std::make_shared < TrainingMenu > ();
		AddpTask ( m_trainingMenu );
	}

	Training::~Training ()
	{
	}


	void Training::ParamInit ()
	{
		m_fighting->ParamInit ( GetpParam () );
		m_trainingMenu->SetpParam ( GetpParam () );
	}


	void Training::ParamReset ()
	{
		m_fighting->ParamReset ();
	}


	void Training::Load ()
	{
		//遷移先指定にthisを保存
		Scene_lib::SetwpThis ( shared_from_this () );
		P_Param pParam = Scene_lib::GetpParam ();

		//直接トレーニング開始時に状態を設定する
		pParam->SetFtgMode ( FTG_MODE::MODE_TRAINING );

		//戦闘共通
		G_Ftg::inst()->Init ();

		//BGM
		AUD_STOP_ALL_BGM ();

		//BGMなし以外は再生開始
		BGM_ID bgm_id = pParam->Get_BGM_ID ();

		if ( BGM_ID::NONE != bgm_id )
		{
			//ロード済チェックしてから再生
			BGM_NAME bgm_name = BGM_ID_TO_NAME [ static_cast < size_t > ( bgm_id ) ];
			if ( ! s3d::AudioAsset::IsReady ( bgm_name ) )
			{
				s3d::AudioAsset::Wait ( bgm_name );
			}

			AUD_PLAY_LOOP_BGM ( bgm_name );
		}

		//両者の操作をCPUではなくプレイヤに初期設定
		pParam->GetGameSetting().SetMutchMode ( MUTCH_MODE::MODE_PLAYER_PLAYER );

		//Fighting
		m_fighting->SetbTraining ( T );	//トレーニングモード設定(タイマ無効など)


		//Menu用にthisを保存
		m_trainingMenu->SetwpParentScene ( shared_from_this () );


		Scene_lib::Load ();
	}

	void Training::Init ()
	{
		//デモをスキップ
		m_fighting->SetDemoSkip ();

		Scene_lib::Init ();

		//通常Initの後に行う
		m_fighting->TrainingRestart ();
	}

	void Training::Move ()
	{
		//メニュポーズ中
		m_trainingMenu->MenuInput ();
		if ( m_trainingMenu->GetStopMain () )
		{
			//メニュ動作のみ
			m_trainingMenu->Move ();
			return;
		}


		//トレーニングリセット
		bool p1Reset = CFG_PUSH_KEY ( P1_BTN7 );
		bool p2Reset = CFG_PUSH_KEY ( P2_BTN7 );
		bool sysReset = WND_UTL::AscKey( '0' );
		if ( p1Reset || p2Reset || sysReset )
		{
			m_fighting->TrainingRestart ();
		}


		//通常動作
		Scene_lib::Move ();
	}

	P_GameScene Training::Transit ()
	{
		//BackSpaceで戻る
		if ( WND_UTL::AscKey ( VK_BACK ) )
		{
			AUD_STOP_ALL_BGM ();
			GetwpThis().lock ()->Transit_Title ();
		}

		return Scene_lib::Transit ();
	}



}	//namespace GAME

