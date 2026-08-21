//=================================================================================================
//
//	FtgMain ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "03_FtgMain/FtgMain.h"
#include "03_FtgMain/Fighting.h"
#include "03_FtgMain/G_Ftg.h"
#include "00_Core/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FtgMain::FtgMain ()
	{
		//戦闘
		m_fighting = std::make_shared < Fighting > ();
		AddpTask ( m_fighting );

		//ポーズメニュ
		m_pauseMenu = std::make_shared < PauseMenu > ();
		AddpTask ( m_pauseMenu );
#if 0
		m_trainingMenu = std::make_shared < TrainingMenu > ();
		AddpTask ( m_trainingMenu );
#endif // 0


#if 0

		//ロード中
		m_rectLoad = make_shared < PrmRect > ();
		m_rectLoad->SetSize ( VEC2 ( 1280, 960 ) );
		m_rectLoad->SetPos ( VEC2 ( 0, 0 ) );
		m_rectLoad->SetAllColor ( 0xff000000 );
		m_rectLoad->SetZ ( Z_FADE );

		m_rectLoad->Load ();
		m_rectLoad->Move ();

//		m_rectLoad->SetFadeOut ( 10 );	//SetFadeOut()は0xffffffff->0x00ffffffなので白くなる
		m_rectLoad->SetFade ( 3, _CLR(0xff000000), _CLR(0x00000000UL) );	//開始値、目標値を手動設定

		AddpTask ( m_rectLoad );
		GRPLST_INSERT_MAIN ( m_rectLoad );
		m_wait = 0;

		
		m_NowLoading = make_shared < GrpStr > ();
		m_NowLoading->SetStr ( _T ( "Now Loading..." ) );
		m_NowLoading->SetPos ( VEC2 ( 1000, 915 ) );
		m_NowLoading->Load ();
		m_NowLoading->Move ();
		m_NowLoading->SetZ ( Z_FADE - 0.01f );
		AddpTask ( m_NowLoading );
		GRPLST_INSERT_MAIN ( m_NowLoading );
#endif // 0


		//----------------------------------------------------
		//@info コンストラクタでshared_from_this()を用いない
	}

	FtgMain::~FtgMain ()
	{
	}

	void FtgMain::ParamInit ()
	{
		P_Param pPrm = GetpParam ();
		m_fighting->ParamInit ( pPrm );

		m_pauseMenu->SetpParam ( pPrm );
		//m_trainingMenu->SetpParam ( GetpParam () );
		// 
		//トレーニングモードでないとき、トレモ用設定をオフ
		Prm_Result& prmRslt = pPrm->GetPrmResult ();
		prmRslt.m_prp_Ukemi.Set ( F );
		prmRslt.m_prp_Guard.Set ( GuardState::Normal );
		prmRslt.m_prp_Taikou.Set ( TaikouState::Normal );
	}

	void FtgMain::ParamReset ()
	{
		m_fighting->ParamReset ();
	}

	void FtgMain::Load ()
	{
		//戦闘共通
		G_Ftg::inst()->Init ();

		//遷移先指定にthisを保存
		Scene_lib::SetwpThis ( shared_from_this () );

		//Menu用にthisを保存
		m_pauseMenu->SetwpParentScene ( shared_from_this () );
#if 0
		m_trainingMenu->SetwpParentScene ( shared_from_this () );
#endif // 0


#if 0
		//BGM
		P_Param pParam = Scene::GetpParam ();
		BGM_ID bgm_id = pParam->Get_BGM_ID ();
		AUD_STOP_ALL_BGM ();
		AUD_PLAY_LOOP_BGM ( BGM_ID_TO_NAME [ bgm_id ] );

		//-> FtgStateに移行
#endif // 0


		m_sw.Start ();



		Scene_lib::Load ();
	}


	void FtgMain::Move ()
	{


		m_sw.ReStart ();


#if 0
		//NowLoading終了
		if ( m_rectLoad->GetFadeTimer () == 0 )
		{
			m_NowLoading->SetValid ( F );
		}
#endif // 0


		//メニュポーズ中
#if 0
		if ( m_pauseMenu->MenuCheck () )
		{
			return;
		}
		//m_trainingMenu->MenuInput ();
		//if ( m_trainingMenu->GetStopMain () )
		{
			//メニュ動作のみ
			m_trainingMenu->Move ();
			return;
		}
#endif // 0

		m_pauseMenu->MenuInput ();
		if ( m_pauseMenu->GetStopMain () )
		{
			//メニュ動作のみ
			m_pauseMenu->Move ();
			return;
		}




#if 0
		//トレーニングリセット
		bool p1Reset = CFG_PUSH_KEY ( P1_BTN7 );
		bool p2Reset = CFG_PUSH_KEY ( P2_BTN7 );
		bool sysReset = WND_UTL::AscKey ( VK_BACK );
		if ( p1Reset || p2Reset || sysReset )
		{
			m_fighting->TrainingRestart ();
		}
#endif // 0
		//デモ Win_1p
		if ( WND_UTL::AscKey ( 'i' ) )
		{
			m_fighting->Test_Win_1p ();
		}

		//デモ Win_2p
		if ( WND_UTL::AscKey ( 'o' ) )
		{
			m_fighting->Test_Win_2p ();
		}

		//デモ リスタート[
		if ( WND_UTL::AscKey ( 'p' ) )
		{
			m_fighting->DemoRestart ();
		}


		//m_sw.Disp ( DBGOUT_0, U"FtgMain::Move();" );



		//通常動作
		Scene_lib::Move ();


		//m_sw.Disp ( DBGOUT_1, U"Scene_lib::Move();" );
		m_sw.Count ();

	}

	//状態遷移
	P_GameScene FtgMain::Transit ()
	{
		//終了チェック
		if ( m_fighting->IsEnd () )
		{
			//BGM終了
			AUD_STOP_ALL_BGM ();

			//シーン遷移
			Transit_Result ();
		}

		//引分終了
		if ( m_fighting->IsDrawEnd () )
		{
			//BGM終了
			AUD_STOP_ALL_BGM ();

			//シーン遷移
			Transit_CharaSele ();
		}

		return Scene_lib::Transit ();
	}
	
}	//namespace GAME

