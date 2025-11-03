//=================================================================================================
//
//	TitleDemo
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TitleDemo.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	TitleDemo::TitleDemo ()
	{
		//デモ
		m_strDemo = std::make_shared < GrpStr > ();
		m_strDemo->SetSize ( G_Font::SIZE_40 );
		m_strDemo->SetPos ( 500, 1.f * BY );
		m_strDemo->SetZ ( Z_MENU );
		m_strDemo->SetStr ( U"- Demo Mode -" );
		AddpTask ( m_strDemo );
		GRPLST_INSERT ( m_strDemo );

		//時間表示バー
		m_barDemo = std::make_shared < PrmRect > ();
		m_barDemo->SetSize ( 300, 2 );
		m_barDemo->SetColor ( _CLR ( 0xffff8080 ) );
		m_barDemo->SetPos ( 640 - 150, BAR_Y );
		m_barDemo->SetZ ( Z_MENU );
		AddpTask ( m_barDemo );
		GRPLST_INSERT ( m_barDemo );

		//デモ操作切換表示
		m_strDemoSwitch = std::make_shared < GrpStr > ();
		m_strDemoSwitch->SetSize ( G_Font::SIZE_20 );
		m_strDemoSwitch->SetPos ( 522, 1.f * STR_Y );
		m_strDemoSwitch->SetZ ( Z_MENU );
		m_strDemoSwitch->SetStr(U"( デモモード：F9で切換 )");
		AddpTask ( m_strDemoSwitch );
		GRPLST_INSERT ( m_strDemoSwitch );

		//タイマ設定
		m_tmrDemo.SetTargetTime ( WAIT_DEMO );
		m_tmrDemo.Start ();

		//フェード
		m_fade_demo = std::make_shared < FadeRect > ();
		m_fade_demo->SetAfterClear ( F );
		m_fade_demo->SetZ ( Z_FADE );
		AddpTask ( m_fade_demo );
		GRPLST_INSERT ( m_fade_demo );

		//初期値はOff
		OffDemo ();
	}

	TitleDemo::~TitleDemo ()
	{
	}

	void TitleDemo::Load ()
	{
		TASK_VEC::Load ();
	}

	void TitleDemo::Move ()
	{
		if ( m_bDemo )
		{
			m_tmrDemo.Move ();

			uint32 t = m_tmrDemo.GetTime ();
			int32 w = (int32) ( (WAIT_DEMO - t) * 300.0 / WAIT_DEMO );
			m_barDemo->SetSize ( w, 2 );
			m_barDemo->SetPos ( 640 + 150 - w, BAR_Y );
		}

		TASK_VEC::Move ();
	}


	void TitleDemo::SetDemo ( bool b )
	{
		m_bDemo = b;
		if ( m_bDemo )
		{
			OnDemo();
		}
		else
		{
			OffDemo();
		}
	}


	void TitleDemo::Switch ()
	{
		if ( m_bDemo )
		{
			m_bDemo = F;
			OffDemo();
		}
		else
		{
			m_bDemo = T;
			OnDemo();
		}
	}

	void TitleDemo::OnDemo ()
	{
		m_strDemo->SetValid ( T );
		m_barDemo->SetValid ( T );
		m_strDemoSwitch->SetValid ( T );

		//デモモードタイマのスタート
		m_tmrDemo.Start ();
	}

	void TitleDemo::OffDemo ()
	{
		m_strDemo->SetValid ( F );
		m_barDemo->SetValid ( F );
		m_strDemoSwitch->SetValid ( F );

		//デモモードタイマのリセット
		m_tmrDemo.Reset ();
	}


	const int32 TitleDemo::WAIT_DEMO = 300;
//	const int32 TitleTitleDemo::WAIT_DEMO = 180;
	const int32 TitleDemo::BY = 750;
	const int32 TitleDemo::BAR_Y = BY + 52;
	const int32 TitleDemo::STR_Y = BY + 58;


}	//namespace GAME

