//=================================================================================================
//
//	FtgGrp ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "FtgGrp.h"
#include "../G_Ftg.h"	


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FtgGrp::FtgGrp ()
	{
		//------------------------------------------------
		//暗転
		m_bg_black = std::make_shared < PrmRect > ();
		m_bg_black->SetRect ( 0, 0, 1280, 960 );
		m_bg_black->SetColor ( s3d::Color ( 0, 0, 0, 192 ) );
		m_bg_black->SetZ ( Z_BG );
		AddpTask ( m_bg_black );
		GRPLST_INSERT ( m_bg_black );
		m_bg_black->SetValid ( F );

		//------------------------------------------------
		//白転
		m_bg_White = std::make_shared < PrmRect > ();
		m_bg_White->SetRect ( 0, 0, 1280, 960 );
		m_bg_White->SetColor ( s3d::Color ( 255, 255, 255, 255 ) );
		m_bg_White->SetZ ( Z_BG );
		AddpTask ( m_bg_White );
		GRPLST_INSERT ( m_bg_White );
		m_bg_White->SetValid ( F );

		//------------------------------------------------
		//フェード白
		m_fade_white = std::make_shared < FadeRect > ();
		TASK_VEC::AddpTask ( m_fade_white );
		GRPLST_INSERT ( m_fade_white );
		m_fade_white->Off ();

		//------------------------------------------------
		//全部黒
		m_bg_All_Black = std::make_shared < PrmRect > ();
		m_bg_All_Black->SetRect ( 0, 0, 1280, 960 );
		m_bg_All_Black->SetColor ( s3d::Color ( 0, 0, 0, 255 ) );
		m_bg_All_Black->SetZ ( Z_EFF + 0.01f );	//全面エフェクト
		AddpTask ( m_bg_All_Black );
		GRPLST_INSERT ( m_bg_All_Black );
		m_bg_All_Black->SetValid ( F );

		//------------------------------------------------
		//スクロール背景
		m_grpBG_scroll = std::make_shared < GameGraphic > ();
		m_grpBG_scroll->AddTexture_FromArchive ( U"BG_scroll\\BG_scroll.png" );
		m_grpBG_scroll->SetPos ( 0, - 1300 );
		m_grpBG_scroll->SetScaling ( 1.f, 2.f );
		m_grpBG_scroll->SetZ ( Z_BG - 0.01f );
		AddpTask ( m_grpBG_scroll );
		GRPLST_INSERT ( m_grpBG_scroll );
		m_grpBG_scroll->SetValid ( F );


		//------------------------------------------------
		//エフェクト：必殺技文字
		m_efString = std::make_shared < EfString > ();
		AddpTask ( m_efString );


		//------------------------------------------------
		//エフェクト：マンダラ
		m_ef_mandara = std::make_shared < GameGraphic > ();
		m_ef_mandara->AddTexture_FromArchive ( U"Chara\\Tsukihibosi\\zetsumandara_R.png" );
		m_ef_mandara->SetPos ( 640, 0 );
		m_ef_mandara->SetZ ( Z_CH + 0.01f );
		m_ef_mandara->AddObject ();
		P_Ob pob = m_ef_mandara->GetpObject ( 1 );
		pob->SetIndexTexture ( 0 );
		pob->SetPos ( 640, 0 );
		pob->SetScaling ( -1.f, 1.f );
		AddpTask ( m_ef_mandara );
		GRPLST_INSERT ( m_ef_mandara );
		m_ef_mandara->SetValid ( F );
	}

	FtgGrp::~FtgGrp ()
	{
	}

	void FtgGrp::Load ()
	{
#if 0
		//test 動画
		mp_vtx = std::make_unique < s3d::VideoTexture > ( U"raiden.mp4", s3d::Loop::No );
		GrpLst::Inst()->SetupVtx ( std::move ( mp_vtx ) );
#endif // 0

		TASK_VEC::Load ();
	}

	void FtgGrp::Init ()
	{
		m_tmrScpStop.Clear ();
		m_tmrBlackOut.Clear ();
		m_tmrWhiteOut.Clear ();
		m_tmrSlow.Clear ();
		m_tmrVibration.Clear ( );

		//TaskでInit()しないものを手動で初期化
		m_bg_black->SetValid ( F );
		m_bg_White->SetValid ( F );
		m_fade_white->Off ();
		m_bg_All_Black->SetValid ( F );

		m_grpBG_scroll->SetValid ( F );
		m_scl_bg_time = 0;

		m_ef_mandara->SetValid ( F );
		m_ef_mandara->SetColor ( _CLR(0xffffffff) );
		m_mnd_bg_time = 0;

		TASK_VEC::Init ();
	}

	void FtgGrp::Reset ()
	{
		Init ();
		TASK_VEC::Reset ();
	}

	void FtgGrp::Move ()
	{
		//-------------------------------------------------------
		//一時停止

		//-------------------------------------------------------
		//暗転
		if ( m_tmrBlackOut.IsActive () )
		{
			//初回
			if ( m_tmrBlackOut.IsStart () )
			{
				m_bg_black->SetValid ( T );
			}
			//終回
			if ( m_tmrBlackOut.IsLast () )
			{
				m_bg_black->SetValid ( F );
			}
		}

		//-------------------------------------------------------
		//白転
		if ( m_tmrWhiteOut.IsActive () )
		{
			//初回
			if ( m_tmrWhiteOut.IsStart () )
			{
				m_bg_White->SetValid ( T );
			}
			//終回
			if ( m_tmrWhiteOut.IsLast () )
			{
				m_bg_White->SetValid ( F );
			}
		}

		//---------------------------------------------------
		//超必殺カットイン
		if ( m_overdrive )
		{
#if 0
			m_fade_white->SetWhiteOut ( 60 );
			GrpLst::Inst()->StartVtx ();
#endif // 0
			m_overdrive = F;	//条件をオフ
		}


		//---------------------------------------------------
		//振動
		if ( m_tmrVibration.IsActive () )
		{
			if ( m_tmrVibration.IsStart () )
			{
				G_GrpTx::Inst()->VibOn ();
			}
			if ( m_tmrVibration.IsLast () )
			{
				G_GrpTx::Inst()->VibOff ();
			}

		}



		//---------------------------------------------------
		//タイマ動作
		m_tmrScpStop.Move ();
		m_tmrBlackOut.Move ();
		m_tmrWhiteOut.Move ();
		m_tmrSlow.Move ();
		m_tmrVibration.Move ();


		//---------------------------------------------------
		//スクロール背景

		//フェードアウト 背景カラーを指定しているのでフェードは機能は手動
		if ( m_scl_bg_time > 0 )
		{
			-- m_scl_bg_time;

			//CoreではなくObのカラーを取得
			_CLR clr = m_grpBG_scroll->GetpObject(0)->GetColor ();
			if ( m_scl_bg_time == 0 )
			{
				clr.a = 1.0f;
				m_grpBG_scroll->SetValid ( F );
			}	
			else
			{
				clr.a = (1.f / 8) * m_scl_bg_time;
			}
			m_grpBG_scroll->SetColor ( clr );
		}

		// G_BASE_POS()はゲーム位置
		//画面表示位置に直す
		if ( G_BASE_POS().y >= 1000 )
		{
			//固定位置
			m_grpBG_scroll->SetPos ( 0, 0 );
		}
		else
		{
			m_grpBG_scroll->SetPos ( 0, G_BASE_POS().y - 1300 );
		}
		DBGOUT_WND_F ( DBGOUT_4, U"G_BASE_POS().y = {}"_fmt( G_BASE_POS().y ) );


		//---------------------------------------------------
		//文字テスト
#if 0

		if ( WND_UTL::AscKey ( 'P' ) )
		{
			m_efString->Start ();
		}

#endif // 0

		//---------------------------------------------------
		//曼荼羅
		if ( m_mnd_bg_time > 0 )
		{
			-- m_mnd_bg_time;

			//CoreではなくObのカラーを取得
			_CLR clr = m_ef_mandara->GetpObject(0)->GetColor ();
			if ( m_mnd_bg_time == 0 )
			{
				clr.a = 1.0f;
				m_ef_mandara->SetValid ( F );
			}	
			else
			{
				clr.a = (1.f / 8) * m_mnd_bg_time;
			}
			m_ef_mandara->SetColor ( clr );
		}



		TASK_VEC::Move ();
	}

	void FtgGrp::StartAerial ()
	{
		m_grpBG_scroll->SetValid ( T );
		//m_grpBG_scroll->SetFadeIn ( 1 );
	}
	void FtgGrp::EndAerial ()
	{
		//m_grpBG_scroll->SetValid ( F );
		//m_grpBG_scroll->SetFadeOut ( 15 );
		m_scl_bg_time = 8;		//フェードアウトスタート
	}

}	//namespace GAME

