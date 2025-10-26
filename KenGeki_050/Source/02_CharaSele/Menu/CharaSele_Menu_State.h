//=================================================================================================
//
//	CharaSele_Menu_State
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
	class CharaSele_Main; using WP_ChSl_Main = std::weak_ptr < CharaSele_Main >;
	class CharaSele_Menu_Actor; using WP_Mn_Actor = std::weak_ptr < CharaSele_Menu_Actor >;

	//=====================================================

	class CharaSele_Menu_State	: public TASK_VEC
	{
	protected:
		WP_Mn_Actor		mwp_Actor;

		PLAYER_ID		m_id {};

	public:
		CharaSele_Menu_State ();
		CharaSele_Menu_State ( const CharaSele_Menu_State & rhs ) = delete;
		~CharaSele_Menu_State ();

		void Load ();
		void Move ();
		void Input ();

		void SetwpActor ( WP_Mn_Actor wp ) { mwp_Actor = wp; }
		void SetPlayerID ( PLAYER_ID id ) { m_id = id; }
	};

	using P_Mn_State = std::shared_ptr < CharaSele_Menu_State >;



	//-------------------------------------------------------------------
	//ステージ選択
	class Ch_MnSt_Stage : public CharaSele_Menu_State
	{
	public:
		void Move ();
		void Input ();
	};




}	//namespace GAME

