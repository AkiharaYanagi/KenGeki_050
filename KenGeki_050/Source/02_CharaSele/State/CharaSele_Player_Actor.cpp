//=================================================================================================
//
//	CharaSele_Player_Actor
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Player_Actor.h"
#include "../CharaSele.h"
#include "../../90_GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_Player_Actor::CharaSele_Player_Actor ()
	{
		//state
		mp_sttWait = std::make_shared < ChSl_Plr_Stt_Wait > ();
		mp_sttActive = std::make_shared < ChSl_Plr_Stt_Active > ();
		mp_sttDecide = std::make_shared < ChSl_Plr_Stt_Decide > ();
		mp_sttMenu = std::make_shared < ChSl_Plr_Stt_Menu > ();

		m_aryState.push_back ( mp_sttWait );
		m_aryState.push_back ( mp_sttActive );
		m_aryState.push_back ( mp_sttDecide );
		m_aryState.push_back ( mp_sttMenu );

		//最初のステート
		m_state = mp_sttWait;


		//キャラ立絵
		m_ch_stand = std::make_shared < CharaSele_Stand > ();
		AddpTask ( m_ch_stand );

		//選択枠
		m_pickFrame = std::make_shared < CharaSele_PickFrame > ();
		AddpTask ( m_pickFrame );

		//円顔
		m_ch_face = std::make_shared < CharaSele_Face > ();
		AddpTask ( m_ch_face );

		//カラー選択
		m_ch_color = std::make_shared < CharaSele_Color > ();
		AddpTask ( m_ch_color );

	}


	CharaSele_Player_Actor::~CharaSele_Player_Actor ()
	{
	}

	//表示プレイヤー側（生成後即指定）
	void CharaSele_Player_Actor::SetPlayerID ( PLAYER_ID id )
	{
		m_id = id;
		m_ch_stand->SetPlayerID ( id );
		m_ch_face->SetPlayerID ( id );
		m_ch_color->SetPlayerID ( id );
		m_pickFrame->SetPlayerID ( id );
	}

	void CharaSele_Player_Actor::SetwpCharaSeleMain ( WP_ChSl wp )
	{
		 mwp_Main = wp;

		//各子ステートに親アクタポインタを設置
		for ( P_ChSl_Plr_Stt pSt : m_aryState )
		{
			pSt->SetwpCharaSeleMain ( wp );
		}
	}

	//操作プレイヤー側指定
	void CharaSele_Player_Actor:: SetInputPlayer ( PLAYER_ID id )
	{
		m_input_id = id;
	}

	void CharaSele_Player_Actor::SetpParam ( P_Param p )
	{
		m_pParam = p;

		m_ch_stand->SetpParam ( p );
		m_ch_stand->Assign ();
		CHARA_NAME name = p->GetGameSetting ().GetCharaName ( m_id );
		m_ch_face->Assign ( name );
		m_pickFrame->SetpParam ( p );
		CHARA_COLOR clr = m_pParam->GetGameSetting ().GetCharaColor ( m_id );
		m_ch_color->Assign ( clr );
	}


	void CharaSele_Player_Actor::Load ()
	{
		//各子ステートに親アクタポインタを設置
		for ( P_ChSl_Plr_Stt pSt : m_aryState )
		{
			pSt->SetwpCharaSele_Plr_Actor ( shared_from_this () );
		}
		TASK_VEC::Load ();
	}

	void CharaSele_Player_Actor::Init ()
	{
		TASK_VEC::Init ();
	}

	void CharaSele_Player_Actor::Move ()
	{
		//各種ステートのMove()
		m_state->Move ();

		//各種ステートのInput()
		m_state->Input ();

		TASK_VEC::Move ();
	}

#if 0

	void CharaSele_Player_Actor::Input_CharaPick ()
	{
		//上下でキャラ変更
		if ( CFG_PUSH_KEY_PL ( m_input_id, PLY_UP ) )
		{
			m_ch_stand->Prev_Chara ();
			CHARA_NAME name = m_pParam->GetGameSetting ().GetCharaName ( m_id );
			m_ch_face->Assign ( name );
			AUD_PLAY_ONESHOT_SE ( SE_select_move );
		}
		if ( CFG_PUSH_KEY_PL ( m_input_id, PLY_DOWN ) )
		{
			m_ch_stand->Next_Chara ();
			CHARA_NAME name = m_pParam->GetGameSetting ().GetCharaName ( m_id );
			m_ch_face->Assign ( name );
			AUD_PLAY_ONESHOT_SE ( SE_select_move );
		}

		//左右でカラー変更
		if ( CFG_PUSH_KEY_PL ( m_input_id, PLY_LEFT ) )
		{
			//相手が決定済みなら残りのカラー
			if ( mwp_Other.lock ()->Is_Decided () )
			{
				PLAYER_ID other_id = m_id == PLAYER_ID_1 ? PLAYER_ID_2 : PLAYER_ID_1;
				CHARA_COLOR other_clr = m_pParam->GetGameSetting ().GetCharaColor ( other_id );
				CHARA_COLOR my_clr = other_clr == CH_CLR_1 ? CH_CLR_2 : CH_CLR_1;
				m_ch_stand->Assign ();	//変えずに決定
				m_ch_color->Assign ( my_clr );
			}
			else
			{
				m_ch_stand->Prev_Color ();
				CHARA_COLOR clr = m_pParam->GetGameSetting ().GetCharaColor ( m_id );
				m_ch_color->Assign ( clr );
			}
			AUD_PLAY_ONESHOT_SE ( SE_select_move );
		}
		if ( CFG_PUSH_KEY_PL ( m_input_id, PLY_RIGHT ) )
		{
			m_ch_stand->Next_Color ();
			CHARA_COLOR clr = m_pParam->GetGameSetting ().GetCharaColor ( m_id );
			m_ch_color->Assign ( clr );
			AUD_PLAY_ONESHOT_SE ( SE_select_move );
		}

		//ボタンで決定
		if ( CFG_PUSH_KEY_PL ( m_input_id, PLY_BTN0 ) )
		{
			m_pParam->GetGameSetting().Save ();	//ファイルに保存

			m_decide_wait = T;
			Change_CharaPick_to_Decide ();
			AUD_PLAY_ONESHOT_SE ( SE_select_decide );
		}
	}

#endif // 0



	void CharaSele_Player_Actor::Input_Menu ()
	{
		//左右でメニュ項目変更
		if ( CFG_PUSH_KEY_PL ( m_id, PLY_LEFT ) )
		{
			mwp_Main.lock()->Menu_Next ();
		}
		if ( CFG_PUSH_KEY_PL ( m_id, PLY_RIGHT ) )
		{
			mwp_Main.lock()->Menu_Prev ();
		}
	}


	//待機
	void CharaSele_Player_Actor::Set_Wait ()
	{
		m_state = mp_sttWait;
		m_pickFrame->Wait ();
		m_ch_color->Wait ();
	}

	//稼働
	void CharaSele_Player_Actor::Set_Active ()
	{
		m_state = mp_sttActive;
		m_pickFrame->Start ();
		m_ch_color->Active ();
	}

	//決定
	void CharaSele_Player_Actor::Change_CharaPick_to_Decide ()
	{
		m_state = mp_sttDecide;

		m_pickFrame->Decide ();
		m_ch_color->Decide ();

		//決定後、反対側入力IDに移行
		PLAYER_ID input_id = mwp_Other.lock()->GetInputPlayer();
		if ( input_id == m_id )
		{
			//反対側が待機状態なら入力受付開始
			if ( mwp_Other.lock()->Is_Wait () )
			{
				mwp_Other.lock()->Set_Active ();
			}
		}
		
	}

	void CharaSele_Player_Actor::Change_CharaPick_to_Menu ()
	{
		m_state = mp_sttMenu;
		m_pickFrame->Decide ();
	}

	bool CharaSele_Player_Actor::Is_Wait () const
	{
		return ( m_state == mp_sttWait );
	}
	bool CharaSele_Player_Actor::Is_Decided () const
	{
		return ( m_state == mp_sttDecide );
	}


	void CharaSele_Player_Actor::Set_another_color ()
	{
		//自分の選択キャラと同じなら
		if ( SameChara () )
		{
			//相手のカラーと異なる色を選択
			CHARA_COLOR another_clr = Another_Color ();
			m_ch_stand->Assign_Color ( another_clr );
			m_ch_color->Assign ( another_clr );
		}
	}


	//----------------------------------------------------------------
	void CharaSele_Player_Actor::PrevChara ()
	{
		//キャラ選択・前
		m_ch_stand->Prev_Chara ();
		AssignChara ();
	}

	void CharaSele_Player_Actor::NextChara ()
	{
		//キャラ選択・次
		m_ch_stand->Next_Chara ();
		AssignChara ();
	}

	void CharaSele_Player_Actor::AssignChara ()
	{
		//パラメータに保存されたキャラを取得して顔グラに反映
		CHARA_NAME name = m_pParam->GetGameSetting ().GetCharaName ( m_id );
		m_ch_face->Assign ( name );
		AUD_PLAY_ONESHOT_SE ( SE_select_move );
	}


	//----------------------------------------------------------------
	//カラー選択・前
	void CharaSele_Player_Actor::PrevColor ()
	{
		//相手が決定済みなら残りのカラー
		if ( mwp_Other.lock ()->Is_Decided () )
		{
			m_ch_stand->Assign_Color ( Another_Color () );	//更新
		}
		else
		{
			m_ch_stand->Prev_Color ();	//通常選択
		}
		AssignColor ();
	}

	//カラー選択・次
	void CharaSele_Player_Actor::NextColor ()
	{
		//相手が決定済みなら残りのカラー
		if ( mwp_Other.lock ()->Is_Decided () )
		{
			m_ch_stand->Assign_Color ( Another_Color () );	//更新
		}
		else
		{
			m_ch_stand->Next_Color ();	//通常選択
		}
		AssignColor ();
	}

	void CharaSele_Player_Actor::AssignColor ()
	{
		//パラメータに保存されたカラーを取得してカラー表示に反映
		CHARA_COLOR clr = m_pParam->GetGameSetting ().GetCharaColor ( m_id );
		m_ch_color->Assign ( clr );
		AUD_PLAY_ONESHOT_SE ( SE_select_move );
	}

	CHARA_COLOR CharaSele_Player_Actor::Another_Color () const
	{
		PLAYER_ID other_id = m_id == PLAYER_ID_1 ? PLAYER_ID_2 : PLAYER_ID_1;
		CHARA_COLOR other_clr = m_pParam->GetGameSetting ().GetCharaColor ( other_id );
		return other_clr == CH_CLR_1 ? CH_CLR_2 : CH_CLR_1;
	}

	//----------------------------------------------------------------
	void CharaSele_Player_Actor::Decide ()
	{
		m_pParam->GetGameSetting().Save ();	//ファイルに保存

		//決定した瞬間、同キャラだったら色を変える
		mwp_Other.lock ()->Set_another_color ();

		//状態を移行
		Change_CharaPick_to_Decide ();
		AUD_PLAY_ONESHOT_SE ( SE_select_decide );
	}

	bool CharaSele_Player_Actor::SameChara () const
	{
		//自分のIDから相手のIDを取得
		PLAYER_ID other_id = m_id == PLAYER_ID_1 ? PLAYER_ID_2 : PLAYER_ID_1;

		//相手のキャラを取得
		CHARA_NAME other_name = m_pParam->GetGameSetting ().GetCharaName ( other_id );
		CHARA_NAME my_name = m_pParam->GetGameSetting ().GetCharaName ( m_id );

		return ( my_name == other_name );
	}


}	//namespace GAME

