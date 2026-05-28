//=================================================================================================
//
//	CharaSele_Player_State
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=====================================================
	//アクタ　前方宣言
	class CharaSele; using WP_ChSl = std::weak_ptr < CharaSele >;
//	class CharaSele_Player; using WP_ChSl_Player = std::weak_ptr < CharaSele_Player >;
	class CharaSele_Player_Actor; using WP_ChSl_Plr_Actor = std::weak_ptr < CharaSele_Player_Actor >;

	//=====================================================

	class CharaSele_Player_State	: public TASK_VEC
	{
	protected:
		WP_ChSl			mwp_Main;
		WP_ChSl_Plr_Actor		mwp_Actor;

	public:
		CharaSele_Player_State ();
		CharaSele_Player_State ( const CharaSele_Player_State & rhs ) = delete;
		~CharaSele_Player_State ();

		void Load ();
		virtual void Move () {}
		virtual void Input () {}

		void SetwpCharaSeleMain ( WP_ChSl wp ) { mwp_Main = wp; }
		void SetwpCharaSele_Plr_Actor ( WP_ChSl_Plr_Actor wp ) { mwp_Actor = wp; }
	};

	using P_ChSl_Plr_Stt = std::shared_ptr < CharaSele_Player_State >;


	//---------------------------------------------------
	//	状態
	//---------------------------------------------------
	
	//待機
	class ChSl_Plr_Stt_Wait : public CharaSele_Player_State
	{
	public:
		void Input ();
	};
	using P_ChSl_Plr_Stt_Wait = std::shared_ptr < ChSl_Plr_Stt_Wait >;


	//移動
	class ChSl_Plr_Stt_Move : public CharaSele_Player_State
	{
	public:
		void Input ();
	};
	using P_ChSl_Plr_Stt_Move = std::shared_ptr < ChSl_Plr_Stt_Move >;


	//決定
	class ChSl_Plr_Stt_Decide : public CharaSele_Player_State
	{
	public:
		void Input ();
	};
	using P_ChSl_Plr_Stt_Decide = std::shared_ptr < ChSl_Plr_Stt_Decide >;

	//メニュ
	class ChSl_Plr_Stt_Menu : public CharaSele_Player_State
	{
	public:
		void Input ();
	};
	using P_ChSl_Plr_Stt_Menu = std::shared_ptr < ChSl_Plr_Stt_Menu >;



}	//namespace GAME

