//=================================================================================================
//
//	SelectArrow
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "00_Core/SelectArrow.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	SelectArrow::SelectArrow ( DIR dir, float z )
	{
		//矢印
		m_arrow = std::make_shared < GameGraphic > ();

		//左方向が画像の基準
		m_arrow->AddTexture_FromArchive ( U"Title\\Arrow.png" );
		
		AddpTask ( m_arrow );

		m_arrow->SetZ ( z );
		GRPLST_INSERT ( m_arrow );

		//最低２つ、上限４つ
		m_arrow->AddObject();

		m_dir = dir;	
		switch ( m_dir )
		{
		case DIR::UP_DOWN:		SetUpDown ();		break;
		case DIR::LEFT_RIGHT:	SetLeftRight ();	break;
		case DIR::ALL:			SetAll ();			break;
		default: break;
		}

		m_frq = 0.15f;
		m_amp = 3.f;
	}

	SelectArrow::~SelectArrow ()
	{
	}

	void SelectArrow::Load ()
	{
		TASK_VEC::Load ();
	}

	void SelectArrow::Move ()
	{
		//時間更新
		const float MAX_TIME = 10000.f;
		++ m_time;
		if ( m_time >= MAX_TIME ) { m_time = 0; }

		//幅
		float period = D3DX_PI_TWICE / m_frq;
		float wrappedTime = fmod ( m_time, period );
		float offset = m_amp * sin ( m_frq * wrappedTime );

		switch ( m_dir )
		{
		case DIR::UP_DOWN:		MoveUpDown ( offset );		break;
		case DIR::LEFT_RIGHT:	MoveLeftRight ( offset );	break;
		case DIR::ALL:			MoveAll ( offset );			break;
		default: break;
		}
		TASK_VEC::Move ();
	}



	void SelectArrow::SetUpDown ()
	{
		P_Ob pob0 = m_arrow->GetpObject(0);
		P_Ob pob1 = m_arrow->GetpObject(1);
		pob0->SetRotationCenter ( VEC2( 18/2, 32/2 ) );	//上
		pob0->SetRadian( + D3DX_PI_HALF );	//上
		pob1->SetRotationCenter ( VEC2( 18/2, 32/2 ) );	//下
		pob1->SetRadian( ( - D3DX_PI_HALF ) );	//下
	}

	void SelectArrow::MoveUpDown ( float offset )
	{
		P_Ob pob0 = m_arrow->GetpObject(0);
		P_Ob pob1 = m_arrow->GetpObject(1);
		pob0->SetPos ( VEC2 ( m_pos + VEC2(  0,  1 ) * offset ) );
		pob1->SetPos ( VEC2 ( m_pos + VEC2(  0, -1 ) * offset ) );

		float x0 = m_pos.x;
		float y0 = m_pos.y - m_h / 2 - offset;
		float x1 = m_pos.x;
		float y1 = m_pos.y + m_h / 2 + offset;

		pob0->SetPos ( x0, y0 );
		pob1->SetPos ( x1, y1 );
	}


	void SelectArrow::SetLeftRight ()
	{
		P_Ob pob0 = m_arrow->GetpObject(0);
		P_Ob pob1 = m_arrow->GetpObject(1);
		pob1->SetScaling(-1, 1);	//逆(右)
	}
	void SelectArrow::MoveLeftRight ( float offset )
	{
		P_Ob pob0 = m_arrow->GetpObject(0);
		P_Ob pob1 = m_arrow->GetpObject(1);

		float x0 = m_pos.x - m_w / 2 - offset;
		float y0 = m_pos.y;
		float x1 = m_pos.x + m_w / 2 + offset;
		float y1 = m_pos.y;

		pob0->SetPos ( x0, y0 );
		pob1->SetPos ( x1, y1 );
	}



	void SelectArrow::SetAll ()
	{
		m_arrow->AddObject();
		m_arrow->AddObject();
		P_Ob pob0 = m_arrow->GetpObject(0);	//左
		P_Ob pob1 = m_arrow->GetpObject(1);	//上
		P_Ob pob2 = m_arrow->GetpObject(2);	//右
		P_Ob pob3 = m_arrow->GetpObject(3);	//下
		pob1->SetRotationCenter ( VEC2( 18/2, 32/2 ) );
		pob1->SetRadian( ( + D3DX_PI_HALF ) );	//上
		pob2->SetRotationCenter ( VEC2( 18/2, 32/2 ) );
		pob2->SetRadian( ( + D3DX_PI ) );	//右
		pob3->SetRotationCenter ( VEC2( 18/2, 32/2 ) );
		pob3->SetRadian( ( - D3DX_PI_HALF ) );	//下
	}

	void SelectArrow::MoveAll ( float offset )
	{
		P_Ob pob0 = m_arrow->GetpObject(0);	//左
		P_Ob pob1 = m_arrow->GetpObject(1);	//上
		P_Ob pob2 = m_arrow->GetpObject(2);	//右
		P_Ob pob3 = m_arrow->GetpObject(3);	//下

		float x0 = m_pos.x - m_w / 2 + offset;
		float y0 = m_pos.y;
		float x2 = m_pos.x + m_w / 2 - offset;
		float y2 = m_pos.y;

		float x1 = m_pos.x;
		float y1 = m_pos.y - m_h / 2 + offset;
		float x3 = m_pos.x;
		float y3 = m_pos.y + m_h / 2 - offset;


		pob0->SetPos ( x0, y0 );
		pob1->SetPos ( x1, y1 );
		pob2->SetPos ( x2, y2 );
		pob3->SetPos ( x3, y3 );
	}

	void SelectArrow::On ()
	{
		m_arrow->SetValid ( T );
	}

	void SelectArrow::Off ()
	{
		m_arrow->SetValid ( F );
	}



}	//namespace GAME

