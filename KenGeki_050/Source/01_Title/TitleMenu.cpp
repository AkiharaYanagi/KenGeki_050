//=================================================================================================
//
//	TitleMenu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TitleMenu.h"
#include "../90_GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	TitleMenu::TitleMenu ()
	{
		//背景
		m_bg = MakepGrp ( U"Title\\Title_Menu_Back.png", Z_MENU + 0.001f );
		m_bg->SetPos ( VEC2 ( 1280/2-664/2, 960 - 664/2 +60 ) );
		m_bg->SetRotationCenter ( VEC2 ( 664/2, 664/2 ) );
		m_omega = -0.001f;

		//枠
		m_frame = MakepGrp ( U"Title\\Title_Menu.png", Z_MENU );
		m_frame->SetPos ( VEC2 ( 0, 960 - 300 ) );

		//項目
		m_item_vx = 10;
		m_item_x = MENU_X;
		m_item = MakepGrp ( U"Title\\1P_vs_2P.png", Z_MENU );
		m_item->SetPos ( VEC2 ( MENU_X, MENU_Y ) );
		m_item->AddTexture_FromArchive ( U"Title\\1P_vs_CPU.png" );
		m_item->AddTexture_FromArchive ( U"Title\\CPU_vs_2P.png" );
		m_item->AddTexture_FromArchive ( U"Title\\CPU_vs_CPU.png" );
		m_item->AddTexture_FromArchive ( U"Title\\Training.png" );

		//左右サブ表示
		m_item->AddObject ();
		m_right = m_item->GetpObject ( 1 );
		m_right->SetPos ( VEC2 ( MENU_RX, MENU_RY ) );
		m_right->SetScalingCenter ( VEC2 ( 303.f * 0.5f, 58 * 0.5f ) );
		m_right->SetScaling ( VEC2 ( 0.6f, 0.6f ) );

		m_item->AddObject ();
		m_left = m_item->GetpObject ( 2 );
		m_left->SetPos ( VEC2 ( MENU_LX, MENU_LY ) );
		m_left->SetScalingCenter ( VEC2 ( 303.f * 0.5f, 58 * 0.5f ) );
		m_left->SetScaling ( VEC2 ( 0.6f, 0.6f ) );

		m_right->SetIndexTexture ( RightIndex () );
		m_left->SetIndexTexture ( LeftIndex () );


		//矢印
		m_arrow = std::make_shared < SelectArrow > ( SelectArrow::DIR::LEFT_RIGHT, Z_MENU );
		AddpTask(m_arrow);
		m_arrow->SetPos ( VEC2 ( 1280 / 2, 790 ) );
		m_arrow->SetW ( 375 );

	}

	P_Grp TitleMenu::MakepGrp ( LPCUSTR filename, float Z = 0.5f )
	{
		P_Grp p = std::make_shared < GameGraphic > ();
		p->AddTexture_FromArchive ( filename );
		p->SetZ ( Z );
		AddpTask ( p );
		GRPLST_INSERT ( p );
		return p;
	}

	TitleMenu::~TitleMenu ()
	{
	}


	void TitleMenu::ParamInit ()
	{
	}

	void TitleMenu::Move ()
	{
#if 0
		//メニュー背景回転
		m_angle += m_omega;
		m_menu_back->SetRadian ( m_angle );

#endif // 0

		//位置
		if ( m_item_x < MENU_X )
		{
			m_item_x += m_item_vx;
		}
		else if ( MENU_X < m_item_x )
		{
			m_item_x -= m_item_vx;
		}

		//差が少ないならば固定
		if ( std::abs ( MENU_X - m_item_x ) < 0.1f )
		{
			m_item_x = MENU_X;
		}
		m_item->SetPos ( VEC2 ( m_item_x, MENU_Y ) );


		//背景回転
		m_theta += m_omega;
		m_bg->SetRadian ( m_theta );

		TASK_VEC::Move ();
	}

	void TitleMenu::Left ()
	{
		switch ( m_to )
		{
		case TITLE_TO::BATTLE_1Pvs2P:
			m_to = TITLE_TO::TRAINING;
			m_item->SetIndexTexture ( (int)TITLE_TO::TRAINING );
		break;
		case TITLE_TO::BATTLE_1PvsCPU:
			m_to = TITLE_TO::BATTLE_1Pvs2P;
			m_item->SetIndexTexture ( (int)TITLE_TO::BATTLE_1Pvs2P );
		break;
		case TITLE_TO::BATTLE_CPUvs2P:
			m_to = TITLE_TO::BATTLE_1PvsCPU;
			m_item->SetIndexTexture ( (int)TITLE_TO::BATTLE_1PvsCPU );
		break;
		case TITLE_TO::BATTLE_CPUvsCPU:
			m_to = TITLE_TO::BATTLE_CPUvs2P;
			m_item->SetIndexTexture ( (int)TITLE_TO::BATTLE_CPUvs2P );
		break;
		case TITLE_TO::TRAINING:
			m_to = TITLE_TO::BATTLE_CPUvsCPU;
			m_item->SetIndexTexture ( (int)TITLE_TO::BATTLE_CPUvsCPU );
		break;
		default: break;
		}

		m_right->SetIndexTexture ( RightIndex () );
		m_left->SetIndexTexture ( LeftIndex () );

		//位置
		m_item_x -= 50;
		m_item->SetPos ( VEC2 ( m_item_x, MENU_Y ) );
	}


	void TitleMenu::Right ()
	{
		switch ( m_to )
		{
		case TITLE_TO::BATTLE_1Pvs2P:
			m_to = TITLE_TO::BATTLE_1PvsCPU;
			m_item->SetIndexTexture ( (int)TITLE_TO::BATTLE_1PvsCPU );
		break;
		case TITLE_TO::BATTLE_1PvsCPU:
			m_to = TITLE_TO::BATTLE_CPUvs2P;
			m_item->SetIndexTexture ( (int)TITLE_TO::BATTLE_CPUvs2P );
		break;
		case TITLE_TO::BATTLE_CPUvs2P:
			m_to = TITLE_TO::BATTLE_CPUvsCPU;
			m_item->SetIndexTexture ( (int)TITLE_TO::BATTLE_CPUvsCPU );
		break;
		case TITLE_TO::BATTLE_CPUvsCPU:
			m_to = TITLE_TO::TRAINING;
			m_item->SetIndexTexture ( (int)TITLE_TO::TRAINING );
		break;
		case TITLE_TO::TRAINING:
			m_to = TITLE_TO::BATTLE_1Pvs2P;
			m_item->SetIndexTexture ( (int)TITLE_TO::BATTLE_1Pvs2P );
		break;
		//default:を入れないで全列挙網羅のコンパイル時警告
		}

		m_right->SetIndexTexture ( RightIndex () );
		m_left->SetIndexTexture ( LeftIndex () );

		//位置
		m_item_x += 50;
		m_item->SetPos ( VEC2 ( m_item_x, MENU_Y ) );
	}


	void TitleMenu::On ()
	{
		m_arrow->On ();
		m_item->SetValid ( T );
	}

	void TitleMenu::Off ()
	{
		m_arrow->Off ();
		m_item->SetValid ( F );
	}

	UINT32 TitleMenu::RightIndex () const
	{
		UINT32 index = m_item->GetIndexTexture ();
		return ( index == 4 ) ? 0 : index + 1;
	}

	UINT32 TitleMenu::LeftIndex () const
	{
		UINT32 index = m_item->GetIndexTexture ();
		return ( index == 0 ) ? 4 : index - 1;
	}


#pragma region CONST

	const float TitleMenu::MENU_X = 1280/2- 303.f/2;
	const float TitleMenu::MENU_Y = 960 - 190;
	const float TitleMenu::MENU_RX = 1280/2- 303.f/2 + 195;
	const float TitleMenu::MENU_RY = 960 - 90;
	const float TitleMenu::MENU_LX = 1280/2- 303.f/2 - 195;
	const float TitleMenu::MENU_LY = 960 - 90;

#pragma endregion


}	//namespace GAME

