//=================================================================================================
//
//	Frame_Param_Staging
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Frame_Param_Staging.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Frame_Param_Staging::Frame_Param_Staging ()
	{
	}

	Frame_Param_Staging::Frame_Param_Staging ( const Frame_Param_Staging & rhs )
	{
		//演出(全体)
		BlackOut = rhs.BlackOut;	//暗転[F]
		Vibration = rhs.Vibration;	//振動[F](全体)
		Stop = rhs.Stop;			//停止[F](全体)

		//------
		//演出(個別)
		Rotate = rhs.Rotate;				//回転[rad] ( 0->2π, π/100 )
		Rotate_center = rhs.Rotate_center;	//回転中心(x,y)
		Omega = rhs.Omega;					//角速度[rad/F] ( 0->2π )
		AfterImage_N = rhs.AfterImage_N;	//残像[個]
		AfterImage_time = rhs.AfterImage_time;		//残像[F] 持続
		AfterImage_pitch = rhs.AfterImage_pitch;	//残像[F] pitch
		Vibration_S = rhs.Vibration_S;		//振動[F](個別)
		Color = rhs.Color;					//色調変更
		Color_time = rhs.Color_time;		//色調変更[F] 持続

		Scaling = rhs.Scaling;		//拡大縮小
		Shader = rhs.Shader;	//シェーダ利用(ビットマスク選択)

	}

	Frame_Param_Staging::~Frame_Param_Staging ()
	{
	}

}	//namespace GAME

