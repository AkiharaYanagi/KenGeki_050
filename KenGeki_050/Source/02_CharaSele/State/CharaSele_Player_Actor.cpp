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

#if 0

		//グラフィック
		m_chara_pick_Back = MakepGrp ( U"CharaSele\\Pick\\CharaPick_Back.png" );
		m_C2 = MakepGrp ( U"CharaSele\\Pick\\C2.png" );
		m_chara_pick_Frame2 = MakepGrp ( U"CharaSele\\Pick\\CharaPick_Frame2.png" );
		m_chara_pick_Clr = MakepGrp ( U"CharaSele\\Pick\\CharaPick_Clr.png" );
		m_C1 = MakepGrp ( U"CharaSele\\Pick\\C1.png" );
		m_C0 = MakepGrp ( U"CharaSele\\Pick\\C0.png" );
		m_chara_pick_Frame0 = MakepGrp ( U"CharaSele\\Pick\\CharaPick_Frame0.png" );

		m_chara_pick_Back	->SetZ ( Z_EFB - 0.01f * (int)Z_BACK );
		m_C2				->SetZ ( Z_EFB - 0.01f * (int)Z_C2 );
		m_chara_pick_Frame2	->SetZ ( Z_EFB - 0.01f * (int)Z_F2 );
		m_chara_pick_Clr	->SetZ ( Z_EFB - 0.01f * (int)Z_Clr );
		m_C1				->SetZ ( Z_EFB - 0.01f * (int)Z_C1 );
		m_C0				->SetZ ( Z_EFB - 0.01f * (int)Z_C0 );
		m_chara_pick_Frame0	->SetZ ( Z_EFB - 0.01f * (int)Z_F0 );

		GRPLST_INSERT ( m_chara_pick_Back );
		GRPLST_INSERT ( m_C2 );
		GRPLST_INSERT ( m_chara_pick_Frame2 );
		GRPLST_INSERT ( m_chara_pick_Clr );
		GRPLST_INSERT ( m_C1 );
		GRPLST_INSERT ( m_C0 );
		GRPLST_INSERT ( m_chara_pick_Frame0 );

#endif // 0

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
		//移行時、入力を連続で見てしまうため１フレーム待つ
		if ( m_wait > 0 )
		{
			m_wait = 0;
			TASK_VEC::Move ();
			return;
		}

		//各種ステートのInput()
		m_state->Input ();
		
		TASK_VEC::Move ();
	}

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
			m_ch_stand->Prev_Color ();
			CHARA_COLOR clr = m_pParam->GetGameSetting ().GetCharaColor ( m_id );
			m_ch_color->Assign ( clr );
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

			Change_CharaPick_to_Decide ();
			AUD_PLAY_ONESHOT_SE ( SE_select_decide );
		}
	}

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

	void CharaSele_Player_Actor::Set_Wait ()
	{
		m_state = mp_sttWait;
		m_pickFrame->Wait ();
		m_ch_color->Wait ();
	}

	void CharaSele_Player_Actor::Set_Active ()
	{
		m_state = mp_sttActive;
		m_wait = 1;
		m_pickFrame->Start ();
		m_ch_color->Active ();
	}


	//決定
	void CharaSele_Player_Actor::Change_CharaPick_to_Decide ()
	{
		m_state = mp_sttDecide;

		m_pickFrame->Decide ();
		m_ch_color->Decide ();

		//決定後、反対側を操作するかどうか
#if 0
//		PLAYER_ID other_id = ( PLAYER_ID_1 == m_id ) ? PLAYER_ID_2: PLAYER_ID_1;
//		PLAYER_ID input_id = mwp_Main.lock()->GetInputPlayer( other_id );
		//反対側が待機状態なら入力受付開始
		if ( mwp_Main.lock()->IsWait ( other_id ) )
		{
			 mwp_Main.lock()->StartInput ( other_id );
		}
#endif // 0

		//反対側入力ID
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





}	//namespace GAME

