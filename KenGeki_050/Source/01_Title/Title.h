//=================================================================================================
//
//	Title
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../90_GameMain/Scene.h"
#include "TitleChara.h"
#include "TitleMenu.h"
#include "TitleDemo.h"
#include "../80_Common/SelectArrow.h"
#include "../91_Param/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Title : public Scene, public std::enable_shared_from_this < Title >
	{
		//背景
		P_Grp		m_bg;
		P_Grp		m_rect;
		float		m_rect_angle { 0 };
		float		m_rect_omega { -0.05f };
		float		m_rect_angle1 { 0 };
		float		m_rect_omega1 { 0.05f };

		//キャラ
		P_TitleChara	m_chara;

		//ロゴ
		P_Grp		m_logo;

		//メニュー
#if 0
		P_Grp		m_menu;
		P_Grp		m_menu_back;
		float		m_angle { 0 };
		float		m_omega { -0.005f };
		P_Grp		m_item;
		P_SelectArrow	m_arrow_obj;
		float		m_item_x;
		float		m_item_vx;
		float		m_item_bx;
#endif // 0
		P_TitleMenu m_menu;

		//Ver.
		P_GrpStr	m_strVer;

		//Demoモード
		P_TitleDemo	m_demo;

		//フェード
		P_FadeRect	m_fade_in;
		P_FadeRect	m_fade_out;
		uint32		m_plus_wait { 0 };

		//タイマ
		P_Timer		m_tmr_title_bgm;
		P_Timer		m_tmr_title_call;

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
		Title ();
		Title ( const Title & rhs ) = delete;
		~Title ();

		void ParamInit ();
		void Load ();
		void Move ();

		void Input();
		P_GameScene Transit ();

		void SaveParam ();

	private:

		//グラフィックオブジェクト生成(グラフィックリスト追加のためZ位置も同梱)
		P_Grp MakepGrp ( LPCUSTR filename, float Z );

		//メニュ表示切替
		void OnMenu ();
		void OffMenu ();


#pragma region CONST

		static const char32_t Ver[];	//Version
		static const float BG_X;
		static const float BG_Y;
		static const float BG_VX;
		static const float BG_P;

		static const float LOGO_X;
		static const float LOGO_Y;

		static const float CURSOR_X;
		static const float CURSOR_Y;
		static const float CURSOR_P;

		static const float INST_X;
		static const float INST_Y;

		static const uint32 FADE_IN_T;
		static const uint32 FADE_OUT_T;

		static const uint32 TITLE_CALL_WAIT;

#pragma endregion

	};

	using P_Title = std::shared_ptr < Title >;


}	//namespace GAME

