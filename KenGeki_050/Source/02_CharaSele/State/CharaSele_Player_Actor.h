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
	using WP_ChPl_Actor = std::weak_ptr < CharaSele_Player_Actor >;


	class CharaSele_Player_Actor	: public TASK_VEC, public std::enable_shared_from_this < CharaSele_Player_Actor >
	{
		//プレイヤID(表示側・指定側)
		PLAYER_ID		m_id { _PLAYER_NUM };

		//操作プレイヤID（1P vs CPUなどは2P側も1P操作）
		PLAYER_ID		m_input_id { PLAYER_ID_1 };

		//親オブジェクト
		WP_ChSl			mwp_Main;

		//反対側ポインタ
		WP_ChPl_Actor	mwp_Other;

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
		P_ChSl_Std				m_ch_stand;		//キャラ立絵
		P_ChSl_PickFrame		m_pickFrame;	//選択枠
		P_ChSl_Fc				m_ch_face;		//キャラ顔
		P_CharaSele_Color		m_ch_color;		//カラー

		//決定時の１フレーム待ち
		//bool	m_decide_wait { F };


	public:
		CharaSele_Player_Actor ();
		CharaSele_Player_Actor ( const CharaSele_Player_Actor & rhs ) = delete;
		~CharaSele_Player_Actor ();

		//表示プレイヤー側（生成後即指定）
		void SetPlayerID ( PLAYER_ID id );
		PLAYER_ID GetPlayerID () const { return m_id; }

		void SetpParam ( P_Param p );
		void Load ();
		void Init ();
		void Move ();

		//親オブジェクト設定
		void SetwpCharaSeleMain ( WP_ChSl wp );

		//反対側プレイヤー設定
		void SetwpOther ( WP_ChPl_Actor wp ) { mwp_Other = wp; }

		//操作プレイヤー側指定
		void SetInputPlayer ( PLAYER_ID id );
		PLAYER_ID GetInputPlayer () const { return m_input_id; }

		//State別
		void Input_CharaPick ();
		void Input_Menu ();

		//State変更
		void Set_Wait ();
		void Set_Active ();
		void Change_CharaPick_to_Decide ();
		void Change_CharaPick_to_Menu ();
		void Change_CharaPick_to_Active ();

		bool Is_Wait() const;
		bool Is_Decided () const;

		//----------------------------------------------------------------
		//操作
		void PrevChara ();
		void NextChara ();
		void AssignChara ();

		//----------------------------------------------------------------
		void PrevColor ();
		void NextColor ();
		void AssignColor ();
		//相手が使っていない方のカラー
		CHARA_COLOR Another_Color () const;
		//外部から指定
		void SetColor ( CHARA_COLOR clr );

		//----------------------------------------------------------------
		void Decide ();
		void Cancel ();
		void PlayerReturn ();

	//----------------------------------------------------------------
		bool SameChara () const;


	private:
//		P_Grp MakepGrp ( const s3d::String & filename );


		//相手が決定済み、同キャラなら残りのカラー
		bool Is_Other_Decided_SameChara () const;

		//相手の残りのカラー
		void Set_another_color ();
	};

	using P_ChSl_Plr_Actor = std::shared_ptr < CharaSele_Player_Actor >;


}	//namespace GAME

