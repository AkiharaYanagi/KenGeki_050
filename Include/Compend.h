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

		P_Sqc & GetpSqc ( uint32 index ) { return mpap_Sqc->at ( index ); }

		//指定シークエンス名が存在するかどうか
		bool ExistSqc ( const s3d::String & name ) const;

		//テクスチャ配列の設定
		void SetpapTx_Main ( PAP_Tx paptx ) { mpap_Tx = paptx; }
		PAP_Tx GetpapTx () { return mpap_Tx; }
	};

	using P_CCompend = std::shared_ptr < Compend >;


}	//namespace GAME

