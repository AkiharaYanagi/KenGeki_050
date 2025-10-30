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
		m_bg = MakepGrp ( U"Title\\Title_BG.png", Z_BG );

		m_rect = MakepGrp ( U"Title\\Title_Rect.png", Z_BG - 0.01f );


		//メニュー
		m_menu_back = MakepGrp ( U"Title\\Title_Menu_Back.png", Z_MENU + 0.001f );
		m_menu_back->SetPos ( VEC2 ( 1280/2-664/2, 960 - 664/2 +60 ) );
		m_menu_back->SetRotationCenter ( VEC2 ( 664/2, 664/2 ) );

		m_menu = MakepGrp ( U"Title\\Title_Menu.png", Z_MENU );
		m_menu->SetPos ( VEC2 ( 0, 960 - 300 ) );

		m_item_bx = 1280/2- 303.f/2;
		m_item_vx = 10;
		m_item_x = m_item_bx;
		m_item = MakepGrp ( U"Title\\1P_vs_2P.png", Z_MENU );
		m_item->SetPos ( VEC2 ( m_item_x, 960 - 200 ) );
		m_item->AddTexture_FromArchive ( U"Title\\1P_vs_CPU.png" );
		m_item->AddTexture_FromArchive ( U"Title\\CPU_vs_2P.png" );
		m_item->AddTexture_FromArchive ( U"Title\\CPU_vs_CPU.png" );
		m_item->AddTexture_FromArchive ( U"Title\\Training.png" );



		//矢印
		m_arrow_obj = std::make_shared < SelectArrow > ( SelectArrow::DIR::LEFT_RIGHT, Z_MENU );
		AddpTask(m_arrow_obj);
		m_arrow_obj->SetPos ( VEC2 ( 1280 / 2, 775 ) );
		m_arrow_obj->SetW ( 380 );

	}

	TitleMenu::~TitleMenu ()
	{
	}


	void TitleMenu::ParamInit ()
	{
	}


	void TitleMenu::Load ()
	{
		TASK_VEC::Load ();
	}

	void TitleMenu::Move ()
	{
#if 0
		//メニュー背景回転
		m_angle += m_omega;
		m_menu_back->SetRadian ( m_angle );

#endif // 0

		//menu
		if ( m_item_x < m_item_bx )
		{
			m_item_x += m_item_vx;
		}
		else if ( m_item_bx < m_item_x )
		{
			m_item_x -= m_item_vx;
		}

		//m_item_x = m_item_bx;
		m_item->SetPos ( VEC2 ( m_item_x, 960 - 200 ) );



		TASK_VEC::Move ();
	}


	void TitleMenu::Input ()
	{
		//選択
		if ( CFG_PUSH_KEY_12 ( PLY_LEFT ) )
		{
			AUD_PLAY_ONESHOT_SE ( SE_select_move );
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
			m_item_x -= 50;
			m_item->SetPos ( VEC2 ( m_item_x, 960 - 200 ) );
		}
		if ( CFG_PUSH_KEY_12 ( PLY_RIGHT ) )
		{
			AUD_PLAY_ONESHOT_SE ( SE_select_move );
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
			m_item_x += 50;
			m_item->SetPos ( VEC2 ( m_item_x, 960 - 200 ) );
		}
	}


	void TitleMenu::On ()
	{
		m_arrow_obj->On ();
		m_item->SetValid ( T );
	}

	void TitleMenu::Off ()
	{
		m_arrow_obj->Off ();
		m_item->SetValid ( F );
	}


#pragma region CONST

	const float TitleMenu::MENU_X = CURSOR_X + 100;
	const float TitleMenu::MENU_Y = CURSOR_Y - 7;
	const float TitleMenu::MENU_Y0 = MENU_Y  + 0;
	const float TitleMenu::MENU_Y1 = MENU_Y0 + CURSOR_P;
	const float TitleMenu::MENU_Y2 = MENU_Y1 + CURSOR_P;
	const float TitleMenu::MENU_Y3 = MENU_Y2 + CURSOR_P;

#pragma endregion


}	//namespace GAME

