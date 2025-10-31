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
		//メニュー
		m_bg = MakepGrp ( U"Title\\Title_Menu_Back.png", Z_MENU + 0.001f );
		m_bg->SetPos ( VEC2 ( 1280/2-664/2, 960 - 664/2 +60 ) );
		m_bg->SetRotationCenter ( VEC2 ( 664/2, 664/2 ) );

		m_frame = MakepGrp ( U"Title\\Title_Menu.png", Z_MENU );
		m_frame->SetPos ( VEC2 ( 0, 960 - 300 ) );

		m_item_vx = 10;
		m_item_x = MENU_X;
		m_item = MakepGrp ( U"Title\\1P_vs_2P.png", Z_MENU );
		m_item->SetPos ( VEC2 ( MENU_X, MENU_Y ) );
		m_item->AddTexture_FromArchive ( U"Title\\1P_vs_CPU.png" );
		m_item->AddTexture_FromArchive ( U"Title\\CPU_vs_2P.png" );
		m_item->AddTexture_FromArchive ( U"Title\\CPU_vs_CPU.png" );
		m_item->AddTexture_FromArchive ( U"Title\\Training.png" );

		//矢印
		m_arrow = std::make_shared < SelectArrow > ( SelectArrow::DIR::LEFT_RIGHT, Z_MENU );
		AddpTask(m_arrow);
		m_arrow->SetPos ( VEC2 ( 1280 / 2, 775 ) );
		m_arrow->SetW ( 380 );

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
		m_item->SetPos ( VEC2 ( m_item_x, 960 - 200 ) );


		TASK_VEC::Move ();
	}

	void TitleMenu::Left ()
	{
		switch ( m_to )
		{
		case TITLE_TO::BATTLE_1Pvs2P:
			m_to = TITLE_TO::BATTLE_1PvsCPU;
			m_item->SetIndexTexture ( 1 );
		break;
		case TITLE_TO::BATTLE_1PvsCPU:
			m_to = TITLE_TO::BATTLE_CPUvs2P;
			m_item->SetIndexTexture ( 2 );
		break;
		case TITLE_TO::BATTLE_CPUvs2P:
			m_to = TITLE_TO::BATTLE_CPUvsCPU;
			m_item->SetIndexTexture ( 3 );
		break;
		case TITLE_TO::BATTLE_CPUvsCPU:
			m_to = TITLE_TO::TRAINING;
			m_item->SetIndexTexture ( 4 );
		break;
		case TITLE_TO::TRAINING:
			m_to = TITLE_TO::BATTLE_1Pvs2P;
			m_item->SetIndexTexture ( 0 );
		break;
		default: break;
		}

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
			m_item->SetIndexTexture ( 1 );
		break;
		case TITLE_TO::BATTLE_1PvsCPU:
			m_to = TITLE_TO::BATTLE_CPUvs2P;
			m_item->SetIndexTexture ( 2 );
		break;
		case TITLE_TO::BATTLE_CPUvs2P:
			m_to = TITLE_TO::BATTLE_CPUvsCPU;
			m_item->SetIndexTexture ( 3 );
		break;
		case TITLE_TO::BATTLE_CPUvsCPU:
			m_to = TITLE_TO::TRAINING;
			m_item->SetIndexTexture ( 4 );
		break;
		case TITLE_TO::TRAINING:
			m_to = TITLE_TO::BATTLE_1Pvs2P;
			m_item->SetIndexTexture ( 0 );
		break;
		default: break;
		}

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


#pragma region CONST

	const float TitleMenu::MENU_X = 1280/2- 303.f/2;
	const float TitleMenu::MENU_Y = 960 - 200;

#pragma endregion


}	//namespace GAME

