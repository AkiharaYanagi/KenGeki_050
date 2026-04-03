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
		//最初の１回
		if ( m_wait > 0 )
		{
			m_wait = 0;

			//稼働開始
			mwp_Actor.lock ()->Set_Active ();
		}

		//１フレーム待機
		++ m_wait;
	}

	void ChSl_Plr_Stt_Active::Input ()
	{
		//最初の１フレームは移行のための待ち
		if ( m_wait == 0 ) { return; }


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

		//ボタンで決定
		if ( CFG_PUSH_KEY_PL ( input_id, PLY_BTN0 ) )
		{
			mwp_Actor.lock ()->Decide ();
		}
	}

	//---------------------------------------------------
	void ChSl_Plr_Stt_Decide::Input ()
	{
	}

	//---------------------------------------------------
	void ChSl_Plr_Stt_Menu::Input ()
	{
		mwp_Actor.lock()->Input_Menu ();
	}


}	//namespace GAME

