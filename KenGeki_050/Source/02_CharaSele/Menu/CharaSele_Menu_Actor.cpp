//=================================================================================================
//
//	CharaSele_Menu_Actor
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Menu_Actor.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_Menu_Actor::CharaSele_Menu_Actor ()
	{
		m_states.push_back ( std::make_shared < Ch_MnSt_Stage > () );
	}

	CharaSele_Menu_Actor::~CharaSele_Menu_Actor ()
	{
	}


	void CharaSele_Menu_Actor::Load ()
	{
		for ( P_Mn_State pState : m_states )
		{
			pState->SetwpActor ( shared_from_this () );
		}

		TASK_VEC::Load ();
	}

	void CharaSele_Menu_Actor::Move ()
	{
		//選択中の１つのみ動作
		m_state->Move ();

		TASK_VEC::Move ();
	}

}	//namespace GAME

