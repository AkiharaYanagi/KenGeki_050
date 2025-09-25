//=================================================================================================
//
//	Compend ヘッダ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"
#include "Sequence.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Compend
	{
		PAP_Tx		mpap_Tx;		//イメージ テクスチャ配列
		PAP_Sqc		mpap_Sqc;		//シークエンス配列

		PAP_Adi		mpap_VC;		//ボイス
		PAP_Adi		mpap_SE;		//SE

	public:
		Compend ();
		Compend( const Compend& rhs ) = delete;
		~Compend ();


		//シークエンス配列
		void SetpSqc ( UP_AP_Sqc papSqc );
		PAP_Sqc GetpapSqc () { return mpap_Sqc; }

		//指定シークエンス名が存在するかどうか
		bool ExistSqc ( const s3d::String & name ) const;

		//シークエンス参照を取得
		P_Sqc & GetpSqc ( UINT32 index ) { return mpap_Sqc->at ( index ); }
		P_Sqc & GetpSqc ( const s3d::String & name ) { return GetpSqc ( GetSqcID ( name ) ); }

		//---------------------------------------------------------------------
		//名前からアクションIDを取得する(無いときはNO_ACTION(0x7FFF0001)を返す)
		UINT32 GetSqcID ( const s3d::String & name ) const;

		//テクスチャ配列の設定
		void SetpapTx_Main ( PAP_Tx paptx ) { mpap_Tx = paptx; }
		PAP_Tx GetpapTx () { return mpap_Tx; }
	};

	using P_CCompend = std::shared_ptr < Compend >;


}	//namespace GAME

