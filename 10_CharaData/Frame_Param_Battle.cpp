//=================================================================================================
//
//	Frame_Param_Battle
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Frame_Param_Battle.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Frame_Param_Battle::Frame_Param_Battle ()
	{
	}

	Frame_Param_Battle::Frame_Param_Battle ( const Frame_Param_Battle & rhs )
	{
		CalcState = rhs.CalcState;	//計算状態
		Vel = rhs.Vel;		//速度
		Acc = rhs.Acc;		//加速度

		Power = rhs.Power;			//攻撃値
		DirectDamage_I = rhs.DirectDamage_I;	//直接ダメージ(自分)
		DirectDamage_E = rhs.DirectDamage_E;	//直接ダメージ(相手)

		Recoil_I = rhs.Recoil_I;		//反動(x,y)(自分)
		Recoil_E = rhs.Recoil_E;		//反動(x,y)(相手)
		Balance_I = rhs.Balance_I;		//バランス増減(自分)
		Balance_E = rhs.Balance_E;		//バランス増減(相手)
		Gauge_I = rhs.Gauge_I;		//ゲージ増減(自分)
		Gauge_E = rhs.Gauge_E;		//ゲージ増減(相手)

		Warp_I = rhs.Warp_I;		//ヒットストップ追加(自分)
		Warp_E = rhs.Warp_E;		//ヒット時のけぞり[F] == ヒットストップ追加(相手)
		GuardWarp_I = rhs.GuardWarp_I;	//ガード硬直（自分）
		GuardWarp_E = rhs.GuardWarp_E;	//ガード硬直（相手）
	}

	Frame_Param_Battle::~Frame_Param_Battle ()
	{
	}

}	//namespace GAME

