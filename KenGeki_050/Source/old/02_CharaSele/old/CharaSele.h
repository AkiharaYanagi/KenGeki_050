//=================================================================================================
//
//	CharaSele　メインクラス ソースファイル
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


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class CharaSele : public Scene, public std::enable_shared_from_this < CharaSele >
	{
		//背景
		P_Grp		m_bg;


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

	public:
		CharaSele ();
		CharaSele ( const CharaSele & rhs ) = delete;
		~CharaSele ();

		void ParamInit ();

		void Load ();
		void Move ();

		P_GameScene Transit ();

		void Menu_Next () { m_menu->Next(); }
		void Menu_Prev () { m_menu->Prev(); }
	};

	using P_CharaSele = std::shared_ptr < CharaSele >;


}	//namespace GAME


