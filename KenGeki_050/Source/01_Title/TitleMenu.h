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
		P_Grp		m_bg;
		float		m_theta { 0 };
		float		m_omega { 0 };

		//枠
		P_Grp		m_frame;

		//項目
		P_Grp		m_item;
		float		m_dx;
		float		m_vx;

		P_Ob		m_right;
		P_Ob		m_left;

		//矢印
		P_SelectArrow	m_arrow;

	public:
		//シーン選択
		enum class TITLE_TO
		{
			BATTLE_1Pvs2P,
			BATTLE_1PvsCPU,
			BATTLE_CPUvs2P,
			BATTLE_CPUvsCPU,
			TRAINING,
		};
	private:
		TITLE_TO	m_to { TITLE_TO::BATTLE_1Pvs2P };

	public:
		TitleMenu ();
		TitleMenu ( const TitleMenu & rhs ) = delete;
		~TitleMenu ();

		void ParamInit ();
		void Move ();

		void Left ();
		void Right ();

		//メニュ表示切替
		void On ();
		void Off ();

		//シーン選択取得
		TITLE_TO GetTo () const { return m_to; }

	private:
		//グラフィックオブジェクト生成(グラフィックリスト追加のためZ位置も同梱)
		P_Grp MakepGrp ( LPCUSTR filename, float Z );

		UINT32 RightIndex () const;
		UINT32 LeftIndex () const;

#pragma region CONST

		static const float MENU_X;
		static const float MENU_Y;
		static const float MENU_RX;
		static const float MENU_RY;
		static const float MENU_LX;
		static const float MENU_LY;

#pragma endregion

	};

	using P_TitleMenu = std::shared_ptr < TitleMenu >;


}	//namespace GAME

