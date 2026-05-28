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
		WP_Mn_Actor		mwp_Actor;

	public:
		CharaSele_Menu_State ();
		CharaSele_Menu_State ( const CharaSele_Menu_State & rhs ) = delete;
		~CharaSele_Menu_State ();

		void Load ();

		void SetwpActor ( WP_Mn_Actor wp ) { mwp_Actor = wp; }
	};

	using P_Mn_State = std::shared_ptr < CharaSele_Menu_State >;



	//-------------------------------------------------------------------
	class Ch_MnSt_Stage : public CharaSele_Menu_State
	{
	};




}	//namespace GAME

