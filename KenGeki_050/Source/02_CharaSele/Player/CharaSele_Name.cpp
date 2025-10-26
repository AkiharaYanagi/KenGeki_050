//=================================================================================================
//
//	CharaSele_Name
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Name.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_Name::CharaSele_Name ()
	{
		//テクスチャ読込
		m_grp = std::make_shared < GameGraphic > ();
		m_grp->AddTexture_FromArchive ( U"Name\\CharaSele_Name_OUKA.png");
		m_grp->AddTexture_FromArchive ( U"Name\\CharaSele_Name_SAE.png");
		m_grp->AddTexture_FromArchive ( U"Name\\CharaSele_Name_RETSU.png");
		m_grp->AddTexture_FromArchive ( U"Name\\CharaSele_Name_GYAVA.png");
		m_grp->AddTexture_FromArchive ( U"Name\\CharaSele_Name_FERA.png");
		m_grp->AddTexture_FromArchive ( U"Name\\CharaSele_Name_TSUKI.png");
		m_grp->AddTexture_FromArchive ( U"Name\\CharaSele_Name_REINA.png");
		m_grp->AddTexture_FromArchive ( U"Name\\CharaSele_Name_HERO.ng");
		m_grp->AddTexture_FromArchive ( U"Name\\CharaSele_Name_DOX.png");
		m_grp->AddTexture_FromArchive ( U"Name\\CharaSele_Name_E0.png");

		AddpTask ( m_grp );
		GRPLST_INSERT ( m_grp );
	}

	CharaSele_Name::~CharaSele_Name ()
	{
	}

	void CharaSele_Name::Load ()
	{
		TASK_VEC::Load ();
	}

	void CharaSele_Name::Init ()
	{
		//位置の設定
		if ( PLAYER_ID_1 == m_id )
		{
			m_grp->SetPos ( 0 - 0.5f - 715 / 2, 960 + 0.5f -36 - 715 / 2 );
			m_grp->SetRotationCenter ( VEC2 { - 0.5f + 715 / 2, 0.5f + 715 / 2 } );
			P_Ob pob = m_grp->GetpObject(1);
			pob->SetPos ( 0 - 0.5f - 715 / 2, 960 + 0.5f -36 - 715 / 2 );
			pob->SetRotationCenter ( VEC2 { 0.5f + 715 / 2, 0.5f + 715 / 2 } );
			m_omega = 0.01f;
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			m_grp->SetPos ( 1280 + 0.5f - 715 / 2, 960 + 0.5f -36 - 715 / 2 );
			m_grp->SetRotationCenter ( VEC2 { 0.5f + 715 / 2, 0.5f + 715 / 2 } );
			P_Ob pob = m_grp->GetpObject(1);
			pob->SetPos ( 1280 + 0.5f - 715 / 2, 960 + 0.5f -36 - 715 / 2 );
			pob->SetRotationCenter ( VEC2 { 0.5f + 715 / 2, 0.5f + 715 / 2 } );
			m_omega = -0.01f;
		}
		TASK_VEC::Init ();
	}


	void CharaSele_Name::Move ()
	{
		//名前角度
#if 0
		if ( CFG_IS_KEY ( P1_BTN0 ) )
		{
			m_angle0 += m_omega;
		}
		if ( CFG_IS_KEY ( P1_BTN1 ) )
		{
			m_angle0 -= m_omega;
		}
		m_ch_name->SetRadian ( m_angle0 );
#endif // 0

		//1つ目
		m_angle0 += m_omega;	//負数方向

		if ( m_angle0 < - m_theta )
		{
			m_angle0 += 2 * m_theta;	//２周めはtheta2つ分戻ってからスタート
		}
		m_grp->SetRadian ( m_angle0 );

		//２つ目
		m_angle1 += m_omega;	//負数方向
		P_Ob pob = m_grp->GetpObject(1);
		if ( m_angle1 < - m_theta )
		{
			m_angle1 += 2 * m_theta;	//２周めはtheta2つ分戻ってからスタート
		}
		pob->SetRadian ( m_angle1 );

		//DBGOUT_WND_F ( DBGOUT_0, U"theta0 = {}"_fmt( m_angle0 ) );
		//DBGOUT_WND_F ( DBGOUT_1, U"theta1 = {}"_fmt( m_angle1 ) );


		TASK_VEC::Move ();
	}

	void CharaSele_Name::Next ()
	{
	}

	void CharaSele_Name::Prev ()
	{
	}


}	//namespace GAME

