//=================================================================================================
//
//	TitleMenu
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../80_Common/SelectArrow.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class TitleMenu : public TASK_VEC
	{
		//背景
		P_Grp		m_menu_back;
		float		m_angle { 0 };
		float		m_omega { -0.005f };


		//枠
		P_Grp		m_menu;

		//項目
		P_Grp		m_item;
		P_SelectArrow	m_arrow_obj;
		float		m_item_x;
		float		m_item_vx;
		float		m_item_bx;


		//シーン選択
		enum class TITLE_TO
		{
			BATTLE_1Pvs2P,
			BATTLE_1PvsCPU,
			BATTLE_CPUvs2P,
			BATTLE_CPUvsCPU,
			TRAINING,
		};
		TITLE_TO	m_to { TITLE_TO::BATTLE_1PvsCPU };

	public:
		TitleMenu ();
		TitleMenu ( const TitleMenu & rhs ) = delete;
		~TitleMenu ();

		void ParamInit ();
		void Load ();
		void Move ();

		void Input();

	private:

		//メニュ表示切替
		void On ();
		void Off ();


#pragma region CONST

		static const float MENU_X;
		static const float MENU_Y;
		static const float MENU_Y0;
		static const float MENU_Y1;
		static const float MENU_Y2;
		static const float MENU_Y3;

#pragma endregion

	};

	using P_TitleMenu = std::shared_ptr < TitleMenu >;


}	//namespace GAME

