//=================================================================================================
//
//	Chara_TxSet
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "00_Common/GameConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//キャラ立ち絵テクスチャを保持する

	using P_GridTx = std::shared_ptr < s3d::Grid < P_Tx > >;
	using P_ArrayTx = std::shared_ptr < s3d::Array < P_Tx > >;

	class Chara_TxSet
	{
		//パディング用
		P_Tx	m_tx_Pad;

		//キャラテクスチャ配列 [キャラ別][カラー]
		//キャラセレ全身
		P_GridTx		m_gridTxFullBody;	//FullBody
		//立絵
		P_GridTx		m_gridTxStand;		//Stand

		//キャラテクスチャ配列 [キャラ名前]
		P_ArrayTx		m_aryTxName;		//Name

		//カットイン
		P_GridTx		m_gridTxCutIn;		//cutin

	public:
		Chara_TxSet ();
		Chara_TxSet ( const Chara_TxSet & rhs ) = delete;
		~Chara_TxSet ();

		void Load ();

		//設定用（inline実装）
//		P_Tx GetpTx ( const s3d::String & filename );

		//キャラ名とカラーでテクスチャを取得
		P_Tx GetpTx_FullBody ( CHARA_NAME name, CHARA_COLOR clr );
		P_Tx GetpTx_Stand ( CHARA_NAME name, CHARA_COLOR clr );

		//名前テクスチャ
		P_Tx GetpTx_Name ( CHARA_NAME name );

		//カットイン
		P_Tx GetpTx_CutIn ( CHARA_NAME name, CHARA_COLOR clr );
	};

	using P_Ch_TxSet = std::shared_ptr < Chara_TxSet >;


}	//namespace GAME

