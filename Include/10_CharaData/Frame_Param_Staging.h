//=================================================================================================
//
//	Frame_Param_Staging
//		フレーム内パラメータ（演出）
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
using namespace GAME;


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace CHARA
{

	class Frame_Param_Staging
	{

	public:
		Frame_Param_Staging ();
		Frame_Param_Staging ( const Frame_Param_Staging & rhs );	//コピー可能
		~Frame_Param_Staging ();

		//------------------------------------------------
		//Property
		
		//演出(全体)
		Prp_UINT32		BlackOut { 0 };		//暗転[F]
		Prp_UINT32		Vibration { 0 };	//振動[F](全体)
		Prp_UINT32		Stop { 0 };			//停止[F](全体)

		//------
		//演出(個別)
		Prp_INT32		Rotate { 0 };				//回転[rad] ( 0->2π, π/100 )
		Prp_VEC2		Rotate_center { VEC2 ( 0, 0 ) };		//回転中心(x,y)
		Prp_float		Omega { 0 };				//角速度[rad/F] ( 0->2π )
		Prp_UINT32		AfterImage_N { 0 };			//残像[個]
		Prp_UINT32		AfterImage_time { 0 };		//残像[F] 持続
		Prp_UINT32		AfterImage_pitch { 0 };		//残像[F] pitch
		Prp_UINT32		Vibration_S { 0 };			//振動[F](個別)
		Prp_CLR			Color { 0xffffffff };		//色調変更
		Prp_UINT32		Color_time { 0 };			//色調変更[F] 持続

		Prp_VEC2		Scaling { VEC2( 1.f, 1.f ) };	//拡大縮小
		Prp_VEC2		Scaling_center { VEC2( 0.f, 0.f ) };	//拡大縮小中心
	};


}	//namespace GAME

