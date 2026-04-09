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
#include "../../90_GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//---------------------------------------------------
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


	//---------------------------------------------------

	//---------------------------------------------------
	void ChSl_Plr_Stt_Active::Move ()
	{
	}

	void ChSl_Plr_Stt_Active::Input ()
	{
		//最初の１フレームは移行のための待ち
		if ( m_wait == 0 ) { ++ m_wait; return; }


		//入力処理
		//mwp_Actor.lock()->Input_CharaPick ();
		PLAYER_ID input_id = mwp_Actor.lock ()->GetInputPlayer ();

		//上下でキャラ変更
		if ( CFG_PUSH_KEY_PL ( input_id, PLY_UP ) )
		{
			mwp_Actor.lock ()->PrevChara ();
		}
		if ( CFG_PUSH_KEY_PL ( input_id, PLY_DOWN ) )
		{
			mwp_Actor.lock ()->NextChara ();
		}

		//左右でカラー変更
		if ( CFG_PUSH_KEY_PL ( input_id, PLY_LEFT ) )
		{
			mwp_Actor.lock ()->PrevColor ();
		}
		if ( CFG_PUSH_KEY_PL ( input_id, PLY_RIGHT ) )
		{
			mwp_Actor.lock ()->NextColor ();
		}

		//ボタン1で決定
		if ( CFG_PUSH_KEY_PL ( input_id, PLY_BTN0 ) )
		{
			mwp_Actor.lock ()->Decide ();
		}


		//1pが操作する2p側のみ
		PLAYER_ID m_id = mwp_Actor.lock ()->GetPlayerID ();
		if ( (PLAYER_ID_1 == input_id) && (PLAYER_ID_2 == m_id) )
		{
			//ボタン2でプレイヤー戻り(2p->1p)
			if ( CFG_PUSH_KEY_PL ( input_id, PLY_BTN1 ) )
			{
				mwp_Actor.lock ()->PlayerReturn ();
				AUD_PLAY_ONESHOT_SE ( SE_select_Cancel );
			}
		}
	}

	//---------------------------------------------------
	void ChSl_Plr_Stt_Decide::Input ()
	{
		PLAYER_ID input_id = mwp_Actor.lock ()->GetInputPlayer ();

		//ボタン2でキャンセル
		if ( CFG_PUSH_KEY_PL ( input_id, PLY_BTN1 ) )
		{
			mwp_Actor.lock ()->Cancel ();
		}
	}

	//---------------------------------------------------
	void ChSl_Plr_Stt_Menu::Input ()
	{
		mwp_Actor.lock()->Input_Menu ();
	}


}	//namespace GAME

