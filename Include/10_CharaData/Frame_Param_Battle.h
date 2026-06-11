//=================================================================================================
//
//	Frame_Param_Battle
//		フレーム内パラメータ（戦闘）
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
using namespace GAME;

#include "Chara_Const.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace CHARA
{
	using Prp_Brc_CLCST = Property < CLC_ST >;	//プロパティ


	class Frame_Param_Battle
	{
	public:
		Frame_Param_Battle();
		Frame_Param_Battle ( const Frame_Param_Battle& rhs ); //コピー可能
		~Frame_Param_Battle();

		//------------------------------------------------
		//Property
		Prp_Brc_CLCST	CalcState{ CLC_SUBSTITUDE };	//計算状態
		Prp_VEC2 Vel{ VEC2 ( 0, 0 ) };		//速度
		Prp_VEC2 Acc{ VEC2 ( 0, 0 ) };		//加速度

		Prp_INT32 Power{ 0 };			//攻撃値
		Prp_INT32 DirectDamage_I{ 0 };	//直接ダメージ(自分)
		Prp_INT32 DirectDamage_E{ 0 };	//直接ダメージ(相手)

		Prp_INT32 Recoil_I{ 0 };		//反動(x,y)(自分)
		Prp_INT32 Recoil_E{ 0 };		//反動(x,y)(相手)
		Prp_INT32 Balance_I{ 0 };		//バランス増減(自分)
		Prp_INT32 Balance_E{ 0 };		//バランス増減(相手)
		Prp_INT32 Gauge_I{ 0 };			//ゲージ増減(自分)
		Prp_INT32 Gauge_E{ 0 };			//ゲージ増減(相手)

		Prp_INT32 Warp_I{ 0 };			//ヒットストップ追加(自分)
		Prp_INT32 Warp_E { 0 };			//ヒットストップ追加(相手)(== ヒット時のけぞり[F])
		Prp_INT32 GuardWarp_I{ 0 };		//ガード硬直（自分）
		Prp_INT32 GuardWarp_E{ 0 };		//ガード硬直（相手）

	};


}	//namespace GAME

