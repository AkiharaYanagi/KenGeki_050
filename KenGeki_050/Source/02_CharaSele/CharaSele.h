//=================================================================================================
//
//	CharaSele ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../90_GameMain/Scene.h"
#include "State/CharaSele_Player_Actor.h"
#include "../80_Common/BattleTime.h"
#include "Menu/CharaSele_Menu.h"
#include "CharaSele_Stage.h"
#include "../91_Param/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class CharaSele : public Scene, public std::enable_shared_from_this < CharaSele >
	{
		//背景
		P_CharaSele_Stage	m_stage;


		//上部メニュ
		P_CharaSele_Menu	m_menu;


		//開戦ボタン
		P_Grp		m_center_button;
		P_Grp		m_KaiSen;


		//アクタ・ステート
		P_ChSl_Plr_Actor	m_plrActor_1p;
		P_ChSl_Plr_Actor	m_plrActor_2p;


		//タイマ
		P_BattleTime		m_battleTime;

		//保存用共通パラメータ
		P_Param			m_pParam;

		//フェード (シーン移行フラグを兼ねる)
		P_FadeRect		m_fade_in;
		P_FadeRect		m_fade_toTitle;
		P_FadeRect		m_fade_toFighting;
		uint32			m_plus_wait { 0 };

	public:
		CharaSele ();
		CharaSele ( const CharaSele & rhs ) = delete;
		~CharaSele ();

		void ParamInit () override;
		void Load ();
		void Move ();


		void Menu_Next () { m_menu->Next(); }
		void Menu_Prev () { m_menu->Prev(); }
		P_GameScene Transit () override;


	private:
		void Input ();
		void Save ();

#pragma region CONST
		static const uint32 FADE_IN_T;
		static const uint32 FADE_OUT_T;
#pragma endregion
	};

	using P_ChSl = std::shared_ptr < CharaSele >;


}	//namespace GAME


