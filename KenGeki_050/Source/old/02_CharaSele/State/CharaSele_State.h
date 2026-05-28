//=================================================================================================
//
//	CharaSele_State
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
//	class CharaSele_Player; using WP_ChSl_Player = std::weak_ptr < CharaSele_Player >;
	class CharaSele_Actor; using WP_ChSl_Actor = std::weak_ptr < CharaSele_Actor >;

	//=====================================================

	class CharaSele_State	: public TASK_VEC
	{

	public:
		CharaSele_State ();
		CharaSele_State ( const CharaSele_State & rhs ) = delete;
		~CharaSele_State ();

		void Load ();
	};

	using P_CharaSele_State = std::shared_ptr < CharaSele_State >;


}	//namespace GAME

