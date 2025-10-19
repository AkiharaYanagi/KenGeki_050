//=================================================================================================
//
//	CharaSele_Grp
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Grp.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_Grp::CharaSele_Grp ()
	{
		m_gridTx = std::make_shared < s3d::Grid < P_Tx > > ();
		m_gridTx->resize( CHARA_NAME_NUM, 2 );	//キャラ数 * 色数
	}

	CharaSele_Grp::~CharaSele_Grp ()
	{
	}

	void CharaSele_Grp::Load ()
	{
		m_tx_Pad = TxUtl::MakeTx_FromArchive ( U"dummy.png" );

		//アーカイブ内ファイル名から、P_Txを作成し取得する
		//(GameGraphicを介しない)
//		(*m_gridTx)[CH_CLR_1][CHARA_TEST] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
//		(*m_gridTx)[CH_CLR_2][CHARA_TEST] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );

		(*m_gridTx)[CH_CLR_1][CHARA_OUKA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand\\Stand_Ouka.png" );
		(*m_gridTx)[CH_CLR_2][CHARA_OUKA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand\\Stand_Ouka_2p.png" );
		(*m_gridTx)[CH_CLR_1][CHARA_SAE] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand\\Stand_Sae.png" );
		(*m_gridTx)[CH_CLR_2][CHARA_SAE] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand\\Stand_Sae_2p.png" );
		(*m_gridTx)[CH_CLR_1][CHARA_RETSUDOU] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand\\Stand_Retsu.png" );
		(*m_gridTx)[CH_CLR_2][CHARA_RETSUDOU] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand\\Stand_Retsu_2p.png" );
		(*m_gridTx)[CH_CLR_1][CHARA_GABADARUGA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand\\Stand_Gaba.png" );
		(*m_gridTx)[CH_CLR_2][CHARA_GABADARUGA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand\\Stand_Gaba_2p.png" );
		(*m_gridTx)[CH_CLR_1][CHARA_FERARIA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand\\Stand_Fera.png" );
		(*m_gridTx)[CH_CLR_2][CHARA_FERARIA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand\\Stand_Fera_2p.png" );
		(*m_gridTx)[CH_CLR_1][CHARA_TSUKIHIBOSHI] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand\\Stand_Tsuki.png" );
		(*m_gridTx)[CH_CLR_2][CHARA_TSUKIHIBOSHI] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand\\Stand_Tsuki_2p.png" );
		(*m_gridTx)[CH_CLR_1][CHARA_REINA] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTx)[CH_CLR_2][CHARA_REINA] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTx)[CH_CLR_1][CHARA_KISHI] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTx)[CH_CLR_2][CHARA_KISHI] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTx)[CH_CLR_1][CHARA_DOXTUKA] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTx)[CH_CLR_2][CHARA_DOXTUKA] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTx)[CH_CLR_1][CHARA_ENEMY_ZERO] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTx)[CH_CLR_2][CHARA_ENEMY_ZERO] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );

		(*m_gridTx)[CH_CLR_1][CHARA_RANDUM] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTx)[CH_CLR_2][CHARA_RANDUM] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );

	}

	inline P_Tx CharaSele_Grp::GetpTx ( const s3d::String & filename )
	{
		return TxUtl::MakeTx_FromArchive ( filename );
	}

	P_Tx CharaSele_Grp::GetpTx ( CHARA_NAME name, CHARA_COLOR clr )
	{
		return (*m_gridTx) [clr][name];
	}

}	//namespace GAME

