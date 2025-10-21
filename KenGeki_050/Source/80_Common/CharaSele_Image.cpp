//=================================================================================================
//
//	CharaSele_Image
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Image.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#if 0

		//キャラ名
	enum CHARA_NAME
	{
		CHARA_TEST,

		CHARA_OUKA,			//鵯桜花
		CHARA_SAE,			//巴紗絵
		CHARA_RETSUDOU,		//烈火烈堂
		CHARA_GABADARUGA,	//ギャバダルガ
		CHARA_FERARIA,		//フェラリア
		CHARA_TSUKIHIBOSHI,	//月日星
		CHARA_REINA,		//レイナ
		CHARA_KISHI,		//忘れられた英雄
		CHARA_DOXTUKA,		//ドッカードボル
		CHARA_ENEMY_ZERO,	//エネミーゼロ

		CHARA_RANDUM,
		CHARA_NAME_NUM,
	};

#endif // 0


	CharaSele_Image::CharaSele_Image ()
	{
		//キャラ数で再初期化（test や　randumを含む）
		m_gridTx->resize ( CHARA_NAME_NUM, CH_CLR_NUM );

		//パディング用
		m_tx_Pad = TxUtl::MakeTx_FromArchive ( U"16_16_Padding.png" );

		//テクスチャグリッド
		m_gridTx = std::make_shared < s3d::Grid < P_Tx > > ();
//		(*m_gridTx)[0][CHARA_TEST] = m_tx_Pad;
//		(*m_gridTx)[1][CHARA_TEST] = m_tx_Pad;
		(*m_gridTx)[0][CHARA_OUKA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Ouka.png" );
		(*m_gridTx)[1][CHARA_OUKA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Ouka_2p.png" );
		(*m_gridTx)[0][CHARA_SAE] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Sae.png" );
		(*m_gridTx)[1][CHARA_SAE] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Sae_2p.png" );
		(*m_gridTx)[0][CHARA_RETSUDOU] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Retsudou.png" );
		(*m_gridTx)[1][CHARA_RETSUDOU] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Retsudou_2p.png" );
		(*m_gridTx)[0][CHARA_GABADARUGA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[1][CHARA_GABADARUGA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[0][CHARA_FERARIA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[1][CHARA_FERARIA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[0][CHARA_TSUKIHIBOSHI] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[1][CHARA_TSUKIHIBOSHI] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[0][CHARA_REINA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[1][CHARA_REINA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[0][CHARA_KISHI] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[1][CHARA_KISHI] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[0][CHARA_DOXTUKA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[1][CHARA_DOXTUKA] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[0][CHARA_ENEMY_ZERO] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[1][CHARA_ENEMY_ZERO] = TxUtl::MakeTx_FromArchive ( U"CharaSele\\Stand_Gabadaruga.png" );
		(*m_gridTx)[0][CHARA_RANDUM] = m_tx_Pad;
		(*m_gridTx)[1][CHARA_RANDUM] = m_tx_Pad;
	}

	CharaSele_Image::~CharaSele_Image ()
	{
	}

	void CharaSele_Image::Load ()
	{
		TASK_VEC::Load ();
	}

	P_Tx CharaSele_Image::GetpTx ( CHARA_NAME id, CHARA_COLOR clr )
	{
		return (*m_gridTx) [clr][id];
	}


}	//namespace GAME

