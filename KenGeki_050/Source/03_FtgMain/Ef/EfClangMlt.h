//=================================================================================================
//
//	EfClangMlt ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
//#include "../../90_GameMain/GameConst.h"
#include "../FtgConst.h"
#include "EfClangSng.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using P_ArrayTx = std::shared_ptr < s3d::Array < P_Tx > >;


	//相殺時エフェクト
	class EfClangMlt : public TASK_VEC
	{
		//共通Tx
		P_ArrayTx	m_tx_impact;
		P_ArrayTx	m_tx_circle;
		P_ArrayTx	m_tx_thunder;

		s3d::Array < EfClangSng >	m_aryClang;	//相殺エフェクトを複数同時に発生させるための配列

	public:
		EfClangMlt ();
		EfClangMlt ( const EfClangMlt & rhs ) = delete;
		~EfClangMlt ();

		void Load ();
		void Move ();

		void On ( VEC2 center );


	private:
		void SetScale ( P_Grp pGrp, const VEC2 & v );

		static const size_t TX_NUM;
		static LPCUSTR PATH_IMP;
		static LPCUSTR PATH_CCL;
		static LPCUSTR PATH_TND;
	};

	using P_EfClangMlt = std::shared_ptr < EfClangMlt >;


}	//namespace GAME


