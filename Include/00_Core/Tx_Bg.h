//=================================================================================================
//
//	Tx　共通アセット 遅延読込
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class TxBg
	{
		//背景テクスチャ
		s3d::HashTable < STAGE_NAME, s3d::String >		m_hashBgName;

	public:
		TxBg ();
		TxBg ( const TxBg & rhs ) = delete;
		~TxBg ();

		//ゲーム利用
		//BG識別定数からテクスチャを取得
		s3d::Texture GetTx ( STAGE_NAME stagename );

		//テクスチャアセットの登録名(String)からテクスチャを取得
		s3d::Texture GetTx ( const s3d::String & assetname )
		{
			return s3d::TextureAsset ( assetname );
		}


		void LoadAsync ( STAGE_NAME stagename );
		void LoadAsync ( const s3d::String & assetname );
	};

	using P_TxBg = std::shared_ptr < TxBg >;


}	//namespace GAME

