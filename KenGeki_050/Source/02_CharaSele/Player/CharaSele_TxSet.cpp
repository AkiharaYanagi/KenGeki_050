//=================================================================================================
//
//	CharaSele_Grp
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_TxSet.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_TxSet::CharaSele_TxSet ()
	{
		m_gridTxFullBody = std::make_shared < s3d::Grid < P_Tx > > ();
		m_gridTxFullBody->resize( CHARA_NAME_NUM, 2 );	//キャラ数 * 色数

		m_gridTxStand = std::make_shared < s3d::Grid < P_Tx > > ();
		m_gridTxStand->resize( CHARA_NAME_NUM, 2 );	//キャラ数 * 色数

		m_aryTxName = std::make_shared < s3d::Array < P_Tx > > ();
		m_aryTxName->resize( CHARA_NAME_NUM );	//キャラ数
	}

	CharaSele_TxSet::~CharaSele_TxSet ()
	{
	}

	void CharaSele_TxSet::Load ()
	{
		m_tx_Pad = TxUtl::MakeTx_FromArchive ( U"dummy.png" );

		//アーカイブ内ファイル名から、P_Txを作成し取得する
		//(GameGraphicを介しない)
//		(*m_gridTxFullBody)[CH_CLR_1][CHARA_TEST] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
//		(*m_gridTxFullBody)[CH_CLR_2][CHARA_TEST] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxFullBody)[CH_CLR_1][CHARA_OUKA] = TxUtl::MakeTx_FromArchive ( U"FullBody\\Stand_Ouka.png" );
		(*m_gridTxFullBody)[CH_CLR_2][CHARA_OUKA] = TxUtl::MakeTx_FromArchive ( U"FullBody\\Stand_Ouka_2p.png" );
		(*m_gridTxFullBody)[CH_CLR_1][CHARA_SAE] = TxUtl::MakeTx_FromArchive ( U"FullBody\\Stand_Sae.png" );
		(*m_gridTxFullBody)[CH_CLR_2][CHARA_SAE] = TxUtl::MakeTx_FromArchive ( U"FullBody\\Stand_Sae_2p.png" );
		(*m_gridTxFullBody)[CH_CLR_1][CHARA_RETSUDOU] = TxUtl::MakeTx_FromArchive ( U"FullBody\\Stand_Retsu.png" );
		(*m_gridTxFullBody)[CH_CLR_2][CHARA_RETSUDOU] = TxUtl::MakeTx_FromArchive ( U"FullBody\\Stand_Retsu_2p.png" );
		(*m_gridTxFullBody)[CH_CLR_1][CHARA_GABADARUGA] = TxUtl::MakeTx_FromArchive ( U"FullBody\\Stand_Gaba.png" );
		(*m_gridTxFullBody)[CH_CLR_2][CHARA_GABADARUGA] = TxUtl::MakeTx_FromArchive ( U"FullBody\\Stand_Gaba_2p.png" );
		(*m_gridTxFullBody)[CH_CLR_1][CHARA_FERARIA] = TxUtl::MakeTx_FromArchive ( U"FullBody\\Stand_Fera.png" );
		(*m_gridTxFullBody)[CH_CLR_2][CHARA_FERARIA] = TxUtl::MakeTx_FromArchive ( U"FullBody\\Stand_Fera_2p.png" );
		(*m_gridTxFullBody)[CH_CLR_1][CHARA_TSUKIHIBOSHI] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxFullBody)[CH_CLR_2][CHARA_TSUKIHIBOSHI] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxFullBody)[CH_CLR_1][CHARA_REINA] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxFullBody)[CH_CLR_2][CHARA_REINA] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxFullBody)[CH_CLR_1][CHARA_KISHI] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxFullBody)[CH_CLR_2][CHARA_KISHI] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxFullBody)[CH_CLR_1][CHARA_DOXTUKA] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxFullBody)[CH_CLR_2][CHARA_DOXTUKA] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxFullBody)[CH_CLR_1][CHARA_ENEMY_ZERO] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxFullBody)[CH_CLR_2][CHARA_ENEMY_ZERO] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
//		(*m_gridTxFullBody)[CH_CLR_1][CHARA_RANDUM] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
//		(*m_gridTxFullBody)[CH_CLR_2][CHARA_RANDUM] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );


		//=============================================================================================
//		(*m_gridTxStand)[CH_CLR_1][CHARA_TEST] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
//		(*m_gridTxStand)[CH_CLR_2][CHARA_TEST] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxStand)[CH_CLR_1][CHARA_OUKA] = TxUtl::MakeTx_FromArchive ( U"Stand\\o1.png" );
		(*m_gridTxStand)[CH_CLR_2][CHARA_OUKA] = TxUtl::MakeTx_FromArchive ( U"Stand\\o2.png" );
		(*m_gridTxStand)[CH_CLR_1][CHARA_SAE] = TxUtl::MakeTx_FromArchive ( U"Stand\\s1.png" );
		(*m_gridTxStand)[CH_CLR_2][CHARA_SAE] = TxUtl::MakeTx_FromArchive ( U"Stand\\s2.png" );
		(*m_gridTxStand)[CH_CLR_1][CHARA_RETSUDOU] = TxUtl::MakeTx_FromArchive ( U"Stand\\r1.png" );
		(*m_gridTxStand)[CH_CLR_2][CHARA_RETSUDOU] = TxUtl::MakeTx_FromArchive ( U"Stand\\r2.png" );
		(*m_gridTxStand)[CH_CLR_1][CHARA_GABADARUGA] = TxUtl::MakeTx_FromArchive ( U"Stand\\g1.png" );
		(*m_gridTxStand)[CH_CLR_2][CHARA_GABADARUGA] = TxUtl::MakeTx_FromArchive ( U"Stand\\g2.png" );
		(*m_gridTxStand)[CH_CLR_1][CHARA_FERARIA] = TxUtl::MakeTx_FromArchive ( U"Stand\\f1.png" );
		(*m_gridTxStand)[CH_CLR_2][CHARA_FERARIA] = TxUtl::MakeTx_FromArchive ( U"Stand\\f2.png" );
		(*m_gridTxStand)[CH_CLR_1][CHARA_TSUKIHIBOSHI] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxStand)[CH_CLR_2][CHARA_TSUKIHIBOSHI] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxStand)[CH_CLR_1][CHARA_REINA] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxStand)[CH_CLR_2][CHARA_REINA] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxStand)[CH_CLR_1][CHARA_KISHI] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxStand)[CH_CLR_2][CHARA_KISHI] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxStand)[CH_CLR_1][CHARA_DOXTUKA] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxStand)[CH_CLR_2][CHARA_DOXTUKA] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxStand)[CH_CLR_1][CHARA_ENEMY_ZERO] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
		(*m_gridTxStand)[CH_CLR_2][CHARA_ENEMY_ZERO] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
//		(*m_gridTxStand)[CH_CLR_1][CHARA_RANDUM] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );
//		(*m_gridTxStand)[CH_CLR_2][CHARA_RANDUM] = TxUtl::MakeTx_FromArchive ( U"dummy.png" );


		//=============================================================================================
		(*m_aryTxName)[CHARA_OUKA] = TxUtl::MakeTx_FromArchive			( U"CharaSele\\Name\\CharaSele_Name_OUKA.png" );
		(*m_aryTxName)[CHARA_SAE] = TxUtl::MakeTx_FromArchive			( U"CharaSele\\Name\\CharaSele_Name_SAE.png" );
		(*m_aryTxName)[CHARA_RETSUDOU] = TxUtl::MakeTx_FromArchive		( U"CharaSele\\Name\\CharaSele_Name_RETSU.png" );
		(*m_aryTxName)[CHARA_GABADARUGA] = TxUtl::MakeTx_FromArchive	( U"CharaSele\\Name\\CharaSele_Name_GYAVA.png" );
		(*m_aryTxName)[CHARA_FERARIA] = TxUtl::MakeTx_FromArchive		( U"CharaSele\\Name\\CharaSele_Name_FERA.png" );
		(*m_aryTxName)[CHARA_TSUKIHIBOSHI] = TxUtl::MakeTx_FromArchive	( U"dummy.png" );
		(*m_aryTxName)[CHARA_REINA] = TxUtl::MakeTx_FromArchive			( U"dummy.png" );
		(*m_aryTxName)[CHARA_KISHI] = TxUtl::MakeTx_FromArchive			( U"dummy.png" );
		(*m_aryTxName)[CHARA_DOXTUKA] = TxUtl::MakeTx_FromArchive		( U"dummy.png" );
		(*m_aryTxName)[CHARA_ENEMY_ZERO] = TxUtl::MakeTx_FromArchive	( U"dummy.png" );
	}

#if 0
	inline P_Tx CharaSele_Grp::GetpTx ( const s3d::String & filename )
	{
		return TxUtl::MakeTx_FromArchive ( filename );
	}
#endif // 0

	P_Tx CharaSele_TxSet::GetpTx_FullBody ( CHARA_NAME name, CHARA_COLOR clr )
	{
		return (*m_gridTxFullBody) [clr][name];
	}

	P_Tx CharaSele_TxSet::GetpTx_Stand ( CHARA_NAME name, CHARA_COLOR clr )
	{
		return (*m_gridTxStand) [clr][name];
	}

	P_Tx CharaSele_TxSet::GetpTx_Name ( CHARA_NAME name )
	{
		return (*m_aryTxName)[name];
	}


}	//namespace GAME

