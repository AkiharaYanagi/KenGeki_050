//=================================================================================================
//
//	CharaSele_Menu_State
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Menu_State.h"
#include "../../90_GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_Menu_State::CharaSele_Menu_State ()
	{
	}

	CharaSele_Menu_State::~CharaSele_Menu_State ()
	{
	}

	void CharaSele_Menu_State::Load ()
	{
		TASK_VEC::Load ();
	}

	void CharaSele_Menu_State::Move ()
	{
		//左右でメニュー変更
		if ( CFG_PUSH_KEY_PL ( m_id, PLY_LEFT ) )
		{
			SND_PLAY_ONESHOT_SE ( SE_select_move );
		}
		if ( CFG_PUSH_KEY_PL ( m_id, PLY_RIGHT ) )
		{
			SND_PLAY_ONESHOT_SE ( SE_select_move );
		}
		TASK_VEC::Move ();
	}


	//-------------------------------------------------------------------
	//ステージ選択
	void Ch_MnSt_Stage::Move ()
	{
		//上下でステージ変更
		if ( CFG_PUSH_KEY_PL ( m_id, PLY_UP ) )
		{
			SND_PLAY_ONESHOT_SE ( SE_select_move );
		}
		if ( CFG_PUSH_KEY_PL ( m_id, PLY_DOWN ) )
		{
			SND_PLAY_ONESHOT_SE ( SE_select_move );
		}
	}


}	//namespace GAME

