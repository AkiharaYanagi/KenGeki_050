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

#include "00_Core/Scene_lib.h"
#include "00_Core/SelectArrow.h"
#include "00_Core/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-----------------------------------------------------
	//前方宣言
	class TitleChara; using P_TitleChara = std::shared_ptr < TitleChara >;
	class TitleMenu; using P_TitleMenu = std::shared_ptr < TitleMenu >;
	class TitleDemo; using P_TitleDemo = std::shared_ptr < TitleDemo >;


	//-----------------------------------------------------
	class Title_lib
		: public Scene_lib
		, public std::enable_shared_from_this < Title_lib >
	{
		//----------------------------------------
		//シーン移行
		P_Scene_lib		mp_Title;		//次のシーン
		P_Scene_lib		mp_CharaSele;	//次のシーン
		//----------------------------------------

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
		P_TitleMenu m_menu;

		//Ver.
		P_GrpStr	m_strVer;

		//Demoモード
		P_TitleDemo	m_demo;

		//Inst
		P_Grp		m_inst;

		//フェード
		P_FadeRect	m_fade_in;
		P_FadeRect	m_fade_out;
		uint32		m_plus_wait { 0 };

		//タイマ
		P_Timer		m_tmr_title_bgm;
		P_Timer		m_tmr_title_call;

		//now loading
		P_Grp		m_now_loading;
		bool		m_bLoading { F };
		bool		m_bStart { F };

		//Jp/En切替
		uint32		m_lang { 0 };

	public:
		Title_lib ();
		Title_lib ( const Title_lib & rhs ) = delete;
		~Title_lib ();

		void ParamInit ();
		void Load ();
		void Move ();

		void Input();
		P_GameScene Transit ();

		void SetpNext_Title ( P_Scene_lib p ) { mp_Title = p; }
		void Transit_Fighting () { Scene_lib::SetpNextScene ( mp_Title ); }

		void SetpNext_CharaSele ( P_Scene_lib p ) { mp_CharaSele = p; }
		void Transit_CharaSele () { Scene_lib::SetpNextScene ( mp_CharaSele ); }

		void SaveParam ();

	private:

		//グラフィックオブジェクト生成(グラフィックリスト追加のためZ位置も同梱)
		P_Grp MakepGrp ( LPCUSTR filename, float Z );

		//メニュ表示切替
		void OnMenu ();
		void OffMenu ();


#pragma region CONST

//		static const char32_t Ver[];	//Version

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

	using P_Title_lib = std::shared_ptr < Title_lib >;


}	//namespace GAME

