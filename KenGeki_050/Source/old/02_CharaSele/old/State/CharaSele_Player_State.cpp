//=================================================================================================
//
//	CharaSele_Player_State
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Player_State.h"
#include "CharaSele_Player_Actor.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_Player_State::CharaSele_Player_State ()
	{
	}

	CharaSele_Player_State::~CharaSele_Player_State ()
	{
	}

	void CharaSele_Player_State::Load ()
	{
		TASK_VEC::Load ();
	}


	void ChSl_Plr_Stt_Wait::Input ()
	{
		mwp_Actor.lock()->Input_CharaPick ();
	}


	void ChSl_Plr_Stt_Move::Input ()
	{
	}

	void ChSl_Plr_Stt_Decide::Input ()
	{
	}

	void ChSl_Plr_Stt_Menu::Input ()
	{
		mwp_Actor.lock()->Input_Menu ();
	}


}	//namespace GAME

