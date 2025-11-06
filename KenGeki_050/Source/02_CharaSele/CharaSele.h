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

		//1P,2P,CPU表示
		P_Grp		m_playerInput;
		P_Ob		m_pl_1p;
		P_Ob		m_pl_2p;

		//操作位置1P,2P
		P_Grp		m_input_pos;
		P_Ob		m_ob_input_1p;
		P_Ob		m_ob_input_2p;

		//トレーニング表示
		P_Grp		m_training;


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
		P_Grp MakepGrp ( const s3d::String & filename, float z );
		void Input ();
		void Save ();

		void SwitchMode ();

#pragma region CONST
		static const uint32 FADE_IN_T;
		static const uint32 FADE_OUT_T;

		static const UINT32 PL_INDEX_1P;
		static const UINT32 PL_INDEX_2P;
		static const UINT32 PL_INDEX_CPU;

		static const float PL_1P_X;
		static const float PL_2P_X;
		static const float PL_Y;

		static const float INPUT_1P_X;
		static const float INPUT_2P_X;
		static const float INPUT_Y;
#pragma endregion
	};

	using P_ChSl = std::shared_ptr < CharaSele >;


}	//namespace GAME


