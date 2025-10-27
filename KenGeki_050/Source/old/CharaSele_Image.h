//=================================================================================================
//
//	キャラセレイメージ
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
	using P_GridTx = std::shared_ptr < s3d::Grid < P_Tx > >;


	class CharaSele_Image	: public TASK_VEC
	{
		//キャラテクスチャ配列 [キャラ名][カラー]
		P_GridTx		m_gridTx;

		//パディング用
		P_Tx	m_tx_Pad;

	public:
		CharaSele_Image ();
		CharaSele_Image ( const CharaSele_Image & rhs ) = delete;
		~CharaSele_Image ();

		void Load ();


		//定数内は範囲保証
		P_Tx GetpTx ( CHARA_NAME id, CHARA_COLOR clr );
	};

	using P_CharaSele_Image = std::shared_ptr < CharaSele_Image >;


}	//namespace GAME

