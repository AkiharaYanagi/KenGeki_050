//=================================================================================================
//
//	Prm_Result
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Prm_Result.h"
#include "../Const/FtgConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Prm_Result::Prm_Result ()
	{
	}

	//コピーコンストラクタ
	Prm_Result::Prm_Result ( const Prm_Result & rhs )
	{
		m_winner			= rhs.m_winner;		//勝者
		m_n_life_1p			= rhs.m_n_life_1p;		//残ライフ
		m_n_life_2p			= rhs.m_n_life_2p;		//
		m_n_input_1p		= rhs.m_n_input_1p;		//入力数
		m_n_input_2p		= rhs.m_n_input_2p;		//
		m_n_act_1p			= rhs.m_n_act_1p;		//アクション回数
		m_n_act_2p			= rhs.m_n_act_2p;		//
		m_n_offset			= rhs.m_n_offset;		//相殺数
		m_n_max_chain_1p	= rhs.m_n_max_chain_1p;		//連撃数
		m_n_max_chain_2p	= rhs.m_n_max_chain_2p;		//
		m_n_max_damege_1p	= rhs.m_n_max_damege_1p;		//最大連撃力
		m_n_max_damege_2p	= rhs.m_n_max_damege_2p;		//
	}

	Prm_Result::~Prm_Result ()
	{
	}


	void Prm_Result::Load ()
	{
	}

	void Prm_Result::Reset ()
	{
		m_winner = PLAYER_ID_1;		//勝者
		m_n_life_1p = LIFE_START;	//残ライフ
		m_n_life_2p = LIFE_START;	//
		m_n_input_1p = 0;			//入力数
		m_n_input_2p = 0;			//
		m_n_act_1p = 0;				//アクション回数
		m_n_act_2p = 0;				//
		m_n_offset = 0;				//相殺数
		m_n_max_chain_1p = 0;		//連撃数
		m_n_max_chain_2p = 0;		//
		m_n_max_damege_1p = 0;		//最大連撃力
		m_n_max_damege_2p = 0;		//
	}


	//最大だったら更新する
	void Prm_Result::UpdateIfMAX_DMG ( PLAYER_ID id, int n )
	{
		if ( id == PLAYER_ID_1 )
		{
			if (m_n_max_damege_1p < n)
			{
				m_n_max_damege_1p = n;
			}
		}
		else if ( id == PLAYER_ID_2 )
		{
			if ( m_n_max_damege_2p < n )
			{
				m_n_max_damege_2p = n;
			}
		}
	}

	void Prm_Result::UpdateIfMax_Chain ( PLAYER_ID id, int n )
	{
		if ( id == PLAYER_ID_1 )
		{
			if (m_n_max_chain_1p < n)
			{
				m_n_max_chain_1p = n;
			}
		}
		else if ( id == PLAYER_ID_2 )
		{
			if ( m_n_max_chain_2p < n )
			{
				m_n_max_chain_2p = n;
			}
		}
	}

	void Prm_Result::ResetBattleParam ()
	{
		Reset ();
	}


}	//namespace GAME

