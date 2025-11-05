//=================================================================================================
//
//	CharaSele_Player_Actor
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "CharaSele_Player_State.h"
#include "../Player/CharaSele_Stand.h"
#include "../Player/CharaSele_Face.h"
#include "../Player/CharaSele_Color.h"
#include "../Player/CharaSele_PickFrame.h"
#include "../../91_Param/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class CharaSele_Player_Actor	: public TASK_VEC, public std::enable_shared_from_this < CharaSele_Player_Actor >
	{
		//プレイヤID(表示側・指定側)
		PLAYER_ID		m_id { _PLAYER_NUM };

		//操作プレイヤID（1P vs CPUなどは2P側も1P操作）
		PLAYER_ID		m_input_id { PLAYER_ID_1 };

		//親オブジェクト
		WP_ChSl			mwp_Main;

		//保存用共通パラメータ
		P_Param			m_pParam;

		//現在のステート
		P_ChSl_Plr_Stt	m_state;

		//すべてのステート
		s3d::Array < P_ChSl_Plr_Stt >	m_aryState;

		//各種ステート
		P_ChSl_Plr_Stt_Wait		mp_sttWait;
		P_ChSl_Plr_Stt_Active	mp_sttActive;
		P_ChSl_Plr_Stt_Decide	mp_sttDecide;
		P_ChSl_Plr_Stt_Menu		mp_sttMenu;

		//-----------------------------
		P_ChSl_Std	m_ch_stand;		//キャラ立絵

#if 0

		//後ろ
		P_Grp		m_chara_pick_Back;		//背景
		P_Grp		m_C2;
		P_Grp		m_chara_pick_Frame2;		//枠
		P_Grp		m_chara_pick_Clr;		//色選択
		P_Grp		m_C1;
		P_Grp		m_C0;
		P_Grp		m_chara_pick_Frame0;		//枠
		//前

		P_ChSl_Fc	m_ch_face;		//キャラ顔

		float		m_angle2 { 0 };
		float		m_omega2 { -0.005f };

		float		m_angle1 { 0 };
		float		m_omega1 { 0.005f };

		float		m_angle0 { 0 };
		float		m_omega0 { -0.005f };

		enum Z
		{	//後
			Z_BACK,
			Z_C2,
			Z_F2,
			Z_Clr,
			Z_C1,
			Z_C0,
			Z_F0,
		};	//前

#endif // 0
		P_ChSl_PickFrame	m_pickFrame;	//選択枠

		P_ChSl_Fc	m_ch_face;		//キャラ顔

		P_CharaSele_Color		m_ch_color;	//カラー

	public:
		CharaSele_Player_Actor ();
		CharaSele_Player_Actor ( const CharaSele_Player_Actor & rhs ) = delete;
		~CharaSele_Player_Actor ();

		void SetpParam ( P_Param p );
		void Load ();
		void Init ();
		void Move ();


		void SetInputPlayer ( PLAYER_ID id ) { m_input_id = id; }

		void SetwpCharaSeleMain ( WP_ChSl wp );
		void SetPlayerID ( PLAYER_ID id );


		//State別
		void Input_CharaPick ();
		void Input_Menu ();

		//State変更
		void Set_Wait ();
		void Set_Active ();
		void Change_CharaPick_to_Menu ();

		bool Is_Decided () const;

	private:
		P_Grp MakepGrp ( const s3d::String & filename );
	};

	using P_ChSl_Plr_Actor = std::shared_ptr < CharaSele_Player_Actor >;


}	//namespace GAME

