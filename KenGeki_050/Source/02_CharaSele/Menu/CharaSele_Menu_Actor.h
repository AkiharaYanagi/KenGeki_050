//=================================================================================================
//
//	CharaSele_Menu_Actor
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "CharaSele_Menu_State.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class CharaSele_Menu_Actor	: public TASK_VEC, public std::enable_shared_from_this < CharaSele_Menu_Actor >
	{
		P_Mn_State	m_state;
		s3d::Array < P_Mn_State >	m_states;

	public:
		CharaSele_Menu_Actor ();
		CharaSele_Menu_Actor ( const CharaSele_Menu_Actor & rhs ) = delete;
		~CharaSele_Menu_Actor ();

		void Load ();
		void Move ();
	};

	using P_Mn_Actor = std::shared_ptr < CharaSele_Menu_Actor >;


}	//namespace GAME

