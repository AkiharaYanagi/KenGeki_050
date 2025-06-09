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

	class EffectGenerate
	{
	public:
		EffectGenerate () {}
		EffectGenerate ( const EffectGenerate & rhs ) = delete;
		~EffectGenerate () {}

		//---------------------------------------------------
		//Property
		Prp_UINT32		Id { 0 };			//エフェクト生成のID
		Prp_UINT32		Index { 0 };		//指定Efインデックス
		Prp_VEC2		Pos { VEC2 ( 0, 0 ) };	//生成位置
		Prp_float		Z { 0 };			//z位置
		Prp_bool		Gnrt { F };		//生成
		Prp_bool		Loop { F };		//繰返
		Prp_bool		Sync { F };		//同期
		Prp_UINT32		Shader { 0 };		//シェーダ利用(ビットマスク選択)

		Prp_float		Rotate { 0 };		//基準回転[rad]
		Prp_VEC2		Rotate_center { VEC2 ( 0, 0 ) };	//基準回転中心(x,y)

		//---------------------------------------------------
	};

	using P_EfGnrt = std::shared_ptr < EffectGenerate >;
	using AP_EfGnrt = s3d::Array < P_EfGnrt >;
	using PAP_EfGnrt = std::shared_ptr < AP_EfGnrt >;


}	//namespace GAME

