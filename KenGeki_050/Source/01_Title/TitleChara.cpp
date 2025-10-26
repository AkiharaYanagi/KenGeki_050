//=================================================================================================
//
//	TitleChara
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TitleChara.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	TitleChara::TitleChara ()
	{
		m_chara = std::make_shared < GameGraphic > ();
		m_chara->AddTexture_FromArchive ( U"Title\\CutIn_Ouka_1p.png" );
		m_chara->AddTexture_FromArchive ( U"Title\\CutIn_Sae_1p.png" );
		m_chara->AddTexture_FromArchive ( U"Title\\CutIn_Retsu_1p.png" );
		m_chara->AddTexture_FromArchive ( U"Title\\CutIn_Fera_1p.png" );
		AddpTask ( m_chara );
		GRPLST_INSERT ( m_chara );

		m_chara->AddObject ();

		m_ob_1p = m_chara->GetpObject ( 0 );
		m_ob_2p = m_chara->GetpObject ( 1 );

		m_start_pos_1p = VEC2 ( -900, 0 );
		m_tx1 = -350;
		m_ob_1p->SetPos ( m_start_pos_1p );

		m_start_pos_2p = VEC2 ( 1280 - 950 + 900, 0 );
		m_tx2 = 1280 - 950 + 350;
		m_ob_2p->SetPos ( m_start_pos_2p );
		m_ob_2p->SetScalingCenter ( VEC2 ( 950/2, 1000/2 ) );
		m_ob_2p->SetScaling ( VEC2 ( -1, 1 ) );

		m_vx = 50.f;

		//タイマ
		m_tmr = std::make_shared < Timer > ( 60 * 5 );
		AddpTask ( m_tmr );
	}

	TitleChara::~TitleChara ()
	{
	}

	void TitleChara::Load ()
	{
		TASK_VEC::Load ();
	}

	void TitleChara::Init ()
	{
		m_x1 = m_start_pos_1p.x;
		m_active1 = T;
		m_ob_1p->SetIndexTexture ( s3d::Random(0,3) );

		m_x2 = m_start_pos_2p.x;
		m_active2 = T;
		m_ob_2p->SetIndexTexture ( s3d::Random(0,3) );

		m_tmr->Start ();

		TASK_VEC::Init ();
	}

	void TitleChara::Move ()
	{
		if ( m_active1 )
		{
			if ( m_x1 > m_tx1 + 50 )
			{
				m_x1 = m_tx1;
				m_active1 = F;
			}
			else
			{
				m_x1 += m_vx;
			}
		}

		if ( m_active2 )
		{
			if ( m_x2 < m_tx2 - 50 )
			{
				m_x2 = m_tx2;
				m_active2 = F;
			}
			else
			{
				m_x2 -= m_vx;
			}
		}

		m_ob_1p->SetPosX ( m_x1 );
		m_ob_2p->SetPosX ( m_x2 );


#if 0
		if ( CFG_PUSH_KEY_12 ( PLY_BTN0 ) )
		{
			Init();
		}
#endif // 0

		//タイマでリセット
		if ( m_tmr->IsLast () )
		{
			Init ();
			m_tmr->Start ();
		}


		TASK_VEC::Move ();
	}


}	//namespace GAME

