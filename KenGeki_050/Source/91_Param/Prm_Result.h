//=================================================================================================
//
//	パラメータ　キャラ
//		事前読込やカラー指定のため保持するポインタ類
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Prm_Const.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	
	//-----------------------------------------
	//リザルト用データ
	class Prm_Result
	{
		//リザルト用
		PLAYER_ID		m_winner { PLAYER_ID_1 };		//勝者
		int32		m_n_life_1p { 0 };		//残ライフ
		int32		m_n_life_2p { 0 };		//
		int32		m_n_input_1p { 0 };		//入力数
		int32		m_n_input_2p { 0 };		//
		int32		m_n_act_1p { 0 };		//アクション回数
		int32		m_n_act_2p { 0 };		//
		int32		m_n_offset { 0 };		//相殺数
		int32		m_n_max_chain_1p { 0 };		//連撃数
		int32		m_n_max_chain_2p { 0 };		//
		int32		m_n_max_damege_1p { 0 };		//最大連撃力
		int32		m_n_max_damege_2p { 0 };		//

	public:
		Prm_Result ();
		Prm_Result ( const Prm_Result & rhs );	//コピー可能
		~Prm_Result ();

		//すべて読込
		void Load ();

		void Reset ();

		//--------------------------------------------------------
		//リザルト用

		void SetWinner ( PLAYER_ID plr ) { m_winner = plr; }
		PLAYER_ID GetWinner () const { return m_winner; }

		void SetN_Life1p ( int n ) { m_n_life_1p = n; }
		int GetN_Life1p () const { return m_n_life_1p; }
		void SetN_Life2p ( int n ) { m_n_life_2p = n; }
		int GetN_Life2p () const { return m_n_life_2p; }

		void SetN_Input1p ( int n ) { m_n_input_1p = n; }
		int GetN_Input1p () const { return m_n_input_1p; }
		void SetN_Input2p ( int n ) { m_n_input_2p = n; }
		int GetN_Input2p () const { return m_n_input_2p; }

		void SetN_Act1p ( int n ) { m_n_act_1p = n; }
		int GetN_Act1p () const { return m_n_act_1p; }
		void SetN_Act2p ( int n ) { m_n_act_2p = n; }
		int GetN_Act2p () const { return m_n_act_2p; }

		GET_SET ( int, GetOffset, SetOffset, m_n_offset )	//相殺数
		void AddOffset ( int32 n ) { m_n_offset += n; }

		GET_SET ( int, Get_MAX_DMG_1P, Set_MAX_DMG_1P, m_n_max_damege_1p	)		//最大ダメージ
		GET_SET ( int, Get_MAX_DMG_2P, Set_MAX_DMG_2P, m_n_max_damege_2p	)		//最大ダメージ
		GET_SET ( int, Get_MAX_CHN_1P, Set_MAX_CHN_1P, m_n_max_chain_1p	)		//連撃数
		GET_SET ( int, Get_MAX_CHN_2P, Set_MAX_CHN_2P, m_n_max_chain_2p	)		//連撃数



		//-----------------------------------------------------
		void UpdateIfMAX_DMG ( PLAYER_ID id, int n );
		void UpdateIfMax_Chain ( PLAYER_ID id, int n );

		void ResetBattleParam ();

		//トレモ用プロパティ
		Prp_bool		m_prp_Ukemi { F };		//受身
		Prp_bool		m_prp_Guard { F };		//ガード
		Property < TaikouState >	m_prp_Taikou { TaikouState::Normal };	//CPU剣撃対抗状態
		Prp_INT32		m_prp_CpuLevel { 4 };	//CPUレベル
	};


}	//namespace GAME

