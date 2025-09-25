//=================================================================================================
//
//	EffectGenerate
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "Define_Siv3D.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//描画モード
	enum DRAW_MODE
	{
		DM_NORMAL,	//通常
		DM_SCREEN,	//スクリーン
	};

	using Prp_DRAW_MODE = Property < DRAW_MODE >;	//プロパティ
	using Prp_GNRT_CND = Property < GENERATE_CONDITION >;	//プロパティ


	class EffectGenerate
	{
	public:
		EffectGenerate () {}
		EffectGenerate ( const EffectGenerate & rhs ) = delete;
		~EffectGenerate () {}

		//---------------------------------------------------
		//Property
		Prp_Str			Name;			//エフェクト生成名
		Prp_Str			Ef_Name;		//対象EF名
		Prp_UINT32		Index { 0 };	//指定EfのID

		Prp_VEC2		Pos { VEC2 ( 0, 0 ) };	//生成位置
		Prp_float		Z { 0 };			//z位置
		Prp_bool		Gnrt { F };		//生成
		Prp_bool		Sync { F };		//同期

		Prp_GNRT_CND	GnrtCnd { GNRT_ALL };	//生成条件
		Prp_DRAW_MODE	DrawMode { DM_NORMAL };	//描画モード

		Prp_INT32		Loop { 1 };			//ループ回数(0は無限)
		Prp_bool		DeleteOut { T };	//画面外で終了
		Prp_INT32		DeleteCount { 0 };	//カウントで終了(0は無限)

		Prp_float		Rotate { 0 };		//基準回転[rad]
		Prp_VEC2		Rotate_center { VEC2 ( 0, 0 ) };	//基準回転中心(x,y)

		Prp_Str			NextName;			//終了時、次のエフェクト生成

		//---------------------------------------------------
	};

	using P_EfGnrt = std::shared_ptr < EffectGenerate >;
	using AP_EfGnrt = s3d::Array < P_EfGnrt >;
	using PAP_EfGnrt = std::shared_ptr < AP_EfGnrt >;


}	//namespace GAME

