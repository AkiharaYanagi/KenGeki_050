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
		Prp_UINT32		m_id{ 0 };		//エフェクト生成のID
		Prp_UINT32		m_index{ 0 };	//指定Efインデックス
		Property < VEC2 >		m_pos;		//生成位置
		Property < float >		m_z;		//z位置
		bool	m_gnrt{ F };		//生成
		bool	m_loop{ F };		//繰返
		bool	m_sync{ F };		//同期
		UINT32	m_shader{ 0 };		//シェーダ利用(ビットマスク選択)

		float	m_rotate{ 0 };		//基準回転[rad]
		VEC2	m_rotate_center{ 0, 0 };	//基準回転中心(x,y)

	public:
		EffectGenerate();
		EffectGenerate(const EffectGenerate& rhs) = delete;
		~EffectGenerate();

		void Load();
	};

	using P_EfGnrt = std::shared_ptr < EffectGenerate >;
	using AP_EfGnrt = s3d::Array < P_EfGnrt >;
	using PAP_EfGnrt = std::shared_ptr < AP_EfGnrt >;


}	//namespace GAME

