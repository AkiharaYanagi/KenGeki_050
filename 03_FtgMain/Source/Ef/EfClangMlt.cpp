//=================================================================================================
//
//	EfClangMlt ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "EfClangMlt.h"
#include "03_FtgMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const size_t EfClangMlt::TX_NUM = 25;
	LPCUSTR EfClangMlt::PATH_IMP = U"Ef_Clang\\Ef_Impact\\Ef_impact_{:02}.png";
	LPCUSTR EfClangMlt::PATH_CCL = U"Ef_Clang\\Ef_Circle\\Ef_Circle_{:02}.png";
	LPCUSTR EfClangMlt::PATH_TND = U"Ef_Clang\\Ef_Thunder0\\Ef_Thunder0_{:02}.png";


	EfClangMlt::EfClangMlt ()
	{
		m_tx_impact->resize ( TX_NUM );		//テクスチャ数
		m_tx_circle->resize ( TX_NUM );		//テクスチャ数
		m_tx_thunder->resize ( TX_NUM );	//テクスチャ数
	}

	EfClangMlt::~EfClangMlt ()
	{
	}



	void EfClangMlt::Load ()
	{
		//アーカイブ内ファイル名から、P_Txを作成し取得する
		//(GameGraphicを介しない)

		for ( size_t i = 0; i < TX_NUM; ++ i )
		{
			s3d::String fn_imp = s3d::Format ( PATH_IMP, i );
			( *m_tx_impact ) [ i ] = TxUtl::MakeTx_FromArchive ( fn_imp );

			s3d::String fn_ccl = s3d::Format ( PATH_CCL, i );
			( *m_tx_circle ) [ i ] = TxUtl::MakeTx_FromArchive ( fn_ccl );

			s3d::String fn_tnd = s3d::Format ( PATH_TND, i );
			( *m_tx_thunder ) [ i ] = TxUtl::MakeTx_FromArchive ( fn_tnd );
		}

		TASK_VEC::Load ();
	}



	void EfClangMlt::Move ()
	{
		TASK_VEC::Move ();
	}

	void EfClangMlt::On ( VEC2 center )
	{
		( void ) center;
	}

	void EfClangMlt::SetScale ( P_Grp pGrp, const VEC2 & v )
	{
		( void ) pGrp;	//未使用
		( void ) v;	//未使用
	}


}
