//=================================================================================================
//
//	CharaSele_PickFrame
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_PickFrame.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_PickFrame::CharaSele_PickFrame ()
	{
		//グラフィック
		m_chara_pick_Back = MakepGrp ( U"CharaSele\\Pick\\CharaPick_Back.png" );
		m_C2 = MakepGrp ( U"CharaSele\\Pick\\C2.png" );
		m_chara_pick_Frame2 = MakepGrp ( U"CharaSele\\Pick\\CharaPick_Frame2.png" );
		m_chara_pick_Clr = MakepGrp ( U"CharaSele\\Pick\\CharaPick_Clr.png" );
		m_C1 = MakepGrp ( U"CharaSele\\Pick\\C1.png" );
		m_C0 = MakepGrp ( U"CharaSele\\Pick\\C0.png" );
		m_chara_pick_Frame0 = MakepGrp ( U"CharaSele\\Pick\\CharaPick_Frame0.png" );

		m_chara_pick_Back	->SetZ ( Z_EFB - 0.01f * (int)Z_BACK );
		m_C2				->SetZ ( Z_EFB - 0.01f * (int)Z_C2 );
		m_chara_pick_Frame2	->SetZ ( Z_EFB - 0.01f * (int)Z_F2 );
		m_chara_pick_Clr	->SetZ ( Z_EFB - 0.01f * (int)Z_Clr );
		m_C1				->SetZ ( Z_EFB - 0.01f * (int)Z_C1 );
		m_C0				->SetZ ( Z_EFB - 0.01f * (int)Z_C0 );
		m_chara_pick_Frame0	->SetZ ( Z_EFB - 0.01f * (int)Z_F0 );

		GRPLST_INSERT ( m_chara_pick_Back );
		GRPLST_INSERT ( m_C2 );
		GRPLST_INSERT ( m_chara_pick_Frame2 );
		GRPLST_INSERT ( m_chara_pick_Clr );
		GRPLST_INSERT ( m_C1 );
		GRPLST_INSERT ( m_C0 );
		GRPLST_INSERT ( m_chara_pick_Frame0 );


		//選択矢印
		m_arrow = std::make_shared < SelectArrow > ( SelectArrow::DIR::UP_DOWN, Z_MENU );
		m_arrow->SetH ( 150 );
		AddpTask ( m_arrow );
	}

	P_Grp CharaSele_PickFrame::MakepGrp ( const s3d::String & filename )
	{
		P_Grp p = std::make_shared < GameGraphic > ();
		p->AddTexture_FromArchive ( filename );
		AddpTask ( p );
		return p;
	}

	CharaSele_PickFrame::~CharaSele_PickFrame ()
	{
	}

	void CharaSele_PickFrame::SetPlayerID ( PLAYER_ID id )
	{
		m_id = id;

		//位置の設定
		if ( PLAYER_ID_1 == m_id )
		{
			m_arrow->SetPos ( VEC2 ( 135, 763 ) );
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			m_arrow->SetPos ( VEC2 ( 1280 - 135 - 16, 763 ) );
		}
		//位置の設定
		if ( PLAYER_ID_1 == m_id )
		{
			m_chara_pick_Back->SetPos ( 0 + 527, 960 - 439 );
			m_C2->SetPos ( 0 + 704 / 2, 960 - 36 - 704 / 2 );
			m_C2->SetRotationCenter ( VEC2 { - 704 / 2, 704 / 2 } );
			m_chara_pick_Frame2->SetPos ( 0 + 353, 960 - 393 );
			m_chara_pick_Clr->SetPos ( 0 + 527, 960 - 439 );
			m_C1->SetPos ( 0 + 576 / 2, 960 - 36 - 576 / 2 );
			m_C1->SetRotationCenter ( VEC2 { - 576 / 2, 576 / 2 } );
			m_C0->SetPos ( 0 + 246 / 2, 960 - 36 - 246 / 2);
			m_C0->SetRotationCenter ( VEC2 { - 246 / 2, 246 / 2 } );
			m_chara_pick_Frame0->SetPos ( 0 + 290, 960 - 330 );

			m_chara_pick_Back->SetScaling ( -1, 1 );
			m_C2->SetScaling ( -1, 1 );
			m_chara_pick_Frame2->SetScaling ( -1, 1 );
			m_chara_pick_Clr->SetScaling ( -1, 1 );
			m_C1->SetScaling ( -1, 1 );
			m_C0->SetScaling ( -1, 1 );
			m_chara_pick_Frame0->SetScaling ( -1, 1 );

			m_omega2 =  0.005f;
			m_omega1 = -0.005f;
			m_omega0 =  0.005f;
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			m_chara_pick_Back->SetPos ( 1280 - 527, 960 - 439 );
			m_C2->SetPos ( 1280 - 704 / 2, 960 - 36 - 704 / 2 );
			m_C2->SetRotationCenter ( VEC2 { 704 / 2, 704 / 2 } );
			m_chara_pick_Frame2->SetPos ( 1280 - 353, 960 - 393 );
			m_chara_pick_Clr->SetPos ( 1280 - 527, 960 - 439 );
			m_C1->SetPos ( 1280 - 576 / 2, 960 - 36 - 576 / 2 );
			m_C1->SetRotationCenter ( VEC2 { 576 / 2, 576 / 2 } );
			m_C0->SetPos ( 1280 - 246 / 2, 960 - 36 - 246 / 2);
			m_C0->SetRotationCenter ( VEC2 { 246 / 2, 246 / 2 } );
			m_chara_pick_Frame0->SetPos ( 1280 - 290, 960 - 330 );

			m_omega2 = -0.005f;
			m_omega1 =  0.005f;
			m_omega0 = -0.005f;
		}

	}

	void CharaSele_PickFrame::SetpParam ( P_Param p )
	{
		m_pParam = p;
	}

	void CharaSele_PickFrame::Load ()
	{
		TASK_VEC::Load ();
	}

	void CharaSele_PickFrame::Init ()
	{
		TASK_VEC::Init ();
	}

	void CharaSele_PickFrame::Move ()
	{
		m_angle2 += m_omega2;
		m_C2->SetRadian ( m_angle0 );

		m_angle1 += m_omega1;
		m_C1->SetRadian ( m_angle1 );

		m_angle0 += m_omega0;
		m_C0->SetRadian ( m_angle0 );

		TASK_VEC::Move ();

	}

	void CharaSele_PickFrame::Wait ()
	{
		//回転停止
		if ( PLAYER_ID_1 == m_id )
		{
			m_omega2 = 0;
			m_omega1 = 0;
			m_omega0 = 0;
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			m_omega2 = 0;
			m_omega1 = 0;
			m_omega0 = 0;
		}

		//矢印消去
		m_arrow->Off ();
	}

	void CharaSele_PickFrame::Start ()
	{
		//通常回転
		if ( PLAYER_ID_1 == m_id )
		{
			m_omega2 =  0.005f;
			m_omega1 = -0.005f;
			m_omega0 =  0.005f;
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			m_omega2 = -0.005f;
			m_omega1 =  0.005f;
			m_omega0 = -0.005f;
		}

		//矢印消去
		m_arrow->On ();
	}

	void CharaSele_PickFrame::Decide ()
	{
		//高速回転
		if ( PLAYER_ID_1 == m_id )
		{
			m_omega1 = -0.5f;
			m_omega0 =  0.5f;
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			m_omega1 =  0.5f;
			m_omega0 = -0.5f;
		}

		//矢印消去
		m_arrow->Off ();
	}


#pragma region CONST

#pragma endregion


}	//namespace GAME

