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


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_Player_Actor::CharaSele_Player_Actor ()
	{
		//state
		mp_sttWait = std::make_shared < ChSl_Plr_Stt_Wait > ();
		mp_sttMove = std::make_shared < ChSl_Plr_Stt_Move > ();
		mp_sttDecide = std::make_shared < ChSl_Plr_Stt_Decide > ();
		mp_sttMenu = std::make_shared < ChSl_Plr_Stt_Menu > ();

		m_aryState.push_back ( mp_sttWait );
		m_aryState.push_back ( mp_sttMove );
		m_aryState.push_back ( mp_sttDecide );
		m_aryState.push_back ( mp_sttMenu );

		//最初のステート
		m_state = mp_sttWait;


		//キャラ立絵
		m_ch_stand = std::make_shared < CharaSele_Stand > ();
		AddpTask ( m_ch_stand );


		//グラフィック
		m_chara_pick_Back = MakepGrp ( U"CharaSele\\CharaPick_Back.png" );
		m_C2 = MakepGrp ( U"CharaSele\\C2.png" );
		m_chara_pick_Frame2 = MakepGrp ( U"CharaSele\\CharaPick_Frame2.png" );
		m_chara_pick_Clr = MakepGrp ( U"CharaSele\\CharaPick_Clr.png" );
		m_C1 = MakepGrp ( U"CharaSele\\C1.png" );
		m_C0 = MakepGrp ( U"CharaSele\\C0.png" );
		m_chara_pick_Frame0 = MakepGrp ( U"CharaSele\\CharaPick_Frame0.png" );

		m_chara_pick_Back	->SetZ ( Z_EFB - 0.01f * (int)Z_BACK );
		m_C2				->SetZ ( Z_EFB - 0.01f * (int)Z_C2 );
		m_chara_pick_Frame2	->SetZ ( Z_EFB - 0.01f * (int)Z_F2 );
		m_chara_pick_Clr	->SetZ ( Z_EFB - 0.01f * (int)Z_Clr );
		m_C1				->SetZ ( Z_EFB - 0.01f * (int)Z_C1 );
		m_C0				->SetZ ( Z_EFB - 0.01f * (int)Z_C0 );
		m_chara_pick_Frame0	->SetZ ( Z_EFB - 0.01f * (int)Z_F0 );


		//円顔
		m_ch_face = std::make_shared < CharaSele_Face > ();
		AddpTask ( m_ch_face );

		//カラー選択
		m_ch_color = std::make_shared < CharaSele_Color > ();
		AddpTask ( m_ch_color );
	}

	P_Grp CharaSele_Player_Actor::MakepGrp ( const s3d::String & filename )
	{
		P_Grp p = std::make_shared < GameGraphic > ();
		p->AddTexture_FromArchive ( filename );
		AddpTask ( p );
		GRPLST_INSERT ( p );
		return p;
	}

	CharaSele_Player_Actor::~CharaSele_Player_Actor ()
	{
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

	void CharaSele_Player_Actor::Load ()
	{
		//各子ステートに親アクタポインタを設置
		for ( P_ChSl_Plr_Stt pSt : m_aryState )
		{
			pSt->SetwpCharaSele_Plr_Actor ( shared_from_this () );
		}
		TASK_VEC::Load ();
	}
	void CharaSele_Player_Actor::SetPlayerID ( PLAYER_ID id )
	{
		m_id = id;
		m_ch_stand->SetPlayerID ( id );
		m_ch_face->SetPlayerID ( id );
		m_ch_color->SetPlayerID ( id );
	}

	void CharaSele_Player_Actor::Init ()
	{
		//位置の設定
		if ( PLAYER_ID_1 == m_id )
		{
			m_chara_pick_Back->SetPos ( 0 + 527, 960 - 439 );
			m_C2->SetPos ( 0 + 704 / 2, 960 - 36 - 704 / 2 );
			m_C2->SetRotationCenter ( VEC2 { - 704 / 2, 704 / 2 } );
			m_chara_pick_Frame2->SetPos ( 0 + 353, 960 - 393 );
			m_chara_pick_Clr->SetPos ( 0 + 527, 960 - 439 );
			m_C1->SetPos ( 0 + 576 / 2, 960 - 36 - 576 / 2 );
			m_C1->SetRotationCenter ( VEC2 { - 576 / 2, 576 / 2 } );
			m_C0->SetPos ( 0 + 246 / 2, 960 - 36 - 246 / 2);
			m_C0->SetRotationCenter ( VEC2 { - 246 / 2, 246 / 2 } );
			m_chara_pick_Frame0->SetPos ( 0 + 290, 960 - 330 );

			m_chara_pick_Back->SetScaling ( -1, 1 );
			m_C2->SetScaling ( -1, 1 );
			m_chara_pick_Frame2->SetScaling ( -1, 1 );
			m_chara_pick_Clr->SetScaling ( -1, 1 );
			m_C1->SetScaling ( -1, 1 );
			m_C0->SetScaling ( -1, 1 );
			m_chara_pick_Frame0->SetScaling ( -1, 1 );

			m_omega = 0.005f;
			m_omega1 = -0.005f;

//			m_arrow_bx = 0 + 450;
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			m_chara_pick_Back->SetPos ( 1280 - 527, 960 - 439 );
			m_C2->SetPos ( 1280 - 704 / 2, 960 - 36 - 704 / 2 );
			m_C2->SetRotationCenter ( VEC2 { 704 / 2, 704 / 2 } );
			m_chara_pick_Frame2->SetPos ( 1280 - 353, 960 - 393 );
			m_chara_pick_Clr->SetPos ( 1280 - 527, 960 - 439 );
			m_C1->SetPos ( 1280 - 576 / 2, 960 - 36 - 576 / 2 );
			m_C1->SetRotationCenter ( VEC2 { 576 / 2, 576 / 2 } );
			m_C0->SetPos ( 1280 - 246 / 2, 960 - 36 - 246 / 2);
			m_C0->SetRotationCenter ( VEC2 { 246 / 2, 246 / 2 } );
			m_chara_pick_Frame0->SetPos ( 1280 - 290, 960 - 330 );

			m_omega = -0.005f;
			m_omega1 = 0.005f;

//			m_arrow_bx = 1280 - 460;
		}

		TASK_VEC::Init ();
	}

	void CharaSele_Player_Actor::Move ()
	{
		//各種ステートのInput()
		m_state->Input ();


		m_angle += m_omega;
		m_C0->SetRadian ( m_angle );
		m_C2->SetRadian ( m_angle );

		m_angle1 += m_omega1;
		m_C1->SetRadian ( m_angle1 );


		//矢印
#if 0

		const float MAX_TIME = 10000.f;
		++ m_arrow_time;
		if ( m_arrow_time >= MAX_TIME ) { m_arrow_time = 0; }
		float period = D3DX_PI_TWICE / m_arrow_frq;
		float wrappedTime = fmod ( m_arrow_time, period );
		float dx = m_arrow_w * sin ( m_arrow_frq * wrappedTime );
		float ay = 960 - 50;

		P_Ob pob = m_arrow->GetpObject ( 1 );
		m_arrow->SetPos ( VEC2 ( m_arrow_bx + dx, ay ) );
		pob->SetPos ( VEC2 ( m_arrow_bx + 160 - dx, ay ) );

		if ( PLAYER_ID_1 == m_id )
		{
			DBGOUT_WND_F ( DBGOUT_2, U"arrow_x = {}"_fmt( dx ) );
		}

#endif // 0

		TASK_VEC::Move ();
	}

	void CharaSele_Player_Actor::Input_CharaPick ()
	{
		//上下でキャラ変更
		if ( CFG_PUSH_KEY_PL ( m_id, PLY_UP ) )
		{
			m_ch_stand->Prev_Chara ();
			m_ch_face->Prev ();
		}
		if ( CFG_PUSH_KEY_PL ( m_id, PLY_DOWN ) )
		{
			m_ch_stand->Next_Chara ();
			m_ch_face->Next ();
		}
		//左右でカラー変更
		if ( CFG_PUSH_KEY_PL ( m_id, PLY_LEFT ) )
		{
			m_ch_stand->Prev_Color ();
			m_ch_color->Prev ();
		}
		if ( CFG_PUSH_KEY_PL ( m_id, PLY_RIGHT ) )
		{
			m_ch_stand->Next_Color ();
			m_ch_color->Next ();
		}

		//ボタンで決定
		if ( CFG_PUSH_KEY_PL ( m_id, PLY_BTN0 ) )
		{
			Change_CharaPick_to_Menu ();
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

	void CharaSele_Player_Actor::Change_CharaPick_to_Menu ()
	{
		m_state = mp_sttMenu;
		m_omega1 = 0.5f;
	}





}	//namespace GAME

