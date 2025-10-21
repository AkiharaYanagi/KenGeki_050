//=================================================================================================
//
//	CharaSele_Grp
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../90_GameMain/GameConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//キャラ立ち絵テクスチャを保持する

	using P_GridTx = std::shared_ptr < s3d::Grid < P_Tx > >;

	class CharaSele_Grp
	{
		//パディング用
		P_Tx	m_tx_Pad;

		//キャラテクスチャ配列 [キャラ名][カラー]
		P_GridTx		m_gridTx;

	public:
		CharaSele_Grp ();
		CharaSele_Grp ( const CharaSele_Grp & rhs ) = delete;
		~CharaSele_Grp ();

		void Load ();

		//設定用（inline実装）
		P_Tx GetpTx ( const s3d::String & filename );

		//キャラ名とカラーでテクスチャを取得
		P_Tx GetpTx ( CHARA_NAME name, CHARA_COLOR clr );
	};

	using P_ChSl_Grp = std::shared_ptr < CharaSele_Grp >;


}	//namespace GAME

