//=================================================================================================
//
//	EfParticle ヘッダファイル
//		打合時に発生するの回収可能な粒子
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
	struct PrmEfParticle
	{
		VEC2	m_startPos;
		VEC2	m_pos;
		VEC2	m_startVel;
		VEC2	m_vel;
		VEC2	m_G;
		float	m_angle;	//[rad]

		bool	m_flag;

	public:
		PrmEfParticle ()
			: m_startPos ( 0, 0 ), m_pos ( 0, 0 )
			, m_startVel ( 0, 0 ), m_vel ( 0, 0 )
			, m_G ( 0, 0 ), m_angle ( 0 ), m_flag ( F )
		{}
	};

	//粒子エフェクトクラス
	class EfParticle : public GrpEf
	{
		enum NUM
		{
			SPARK_NUM = 300,
		};
		std::vector < PrmEfParticle >	m_vPrm;

	public:
		EfParticle ();
		EfParticle ( const EfParticle & rhs ) = delete;
		~EfParticle ();

		//初期化
		void Init ();

		//上限
		//1回30個　→　全300個程度

		//発生(追加)

		//時間による解放

		//回収による解放
		
		void Move ();
		void On ( VEC2 center );

		void Draw ();
	};

	using P_EfParticle = std::shared_ptr < EfParticle >;

}	//namespace GAME


