//=================================================================================================
//
//	EfSpark ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../90_GameMain/GameConst.h"
#include "../FtgConst.h"
#include "../../90_GameMain/G_Ftg.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//パラメータ
	struct PrmEfSpark
	{
		VEC2	m_pos;
		VEC2	m_startVel;
		VEC2	m_vel;
		VEC2	m_G;
		float	m_angle;
	public:
		PrmEfSpark () : m_angle ( 0 ) {}
	};

	//火花エフェクトクラス
	class EfSpark : public GrpEf
	{
		enum NUM
		{
			SPARK_NUM = 30,
		};
		std::vector < PrmEfSpark >		m_vPrm;

	public:
		EfSpark ();
		EfSpark ( const EfSpark & rhs ) = delete;
		~EfSpark ();

		void Move ();
		void On ( VEC2 center );
	};

	using P_EfSpark = std::shared_ptr < EfSpark >;

}	//namespace GAME


