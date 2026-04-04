//=================================================================================================
//
//	EfClangSng ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../90_GameMain/GameConst.h"
#include "../FtgConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//相殺時エフェクト
	class EfClangSng : public TASK_VEC
	{
		P_GrpEf		m_thunder0;
		P_GrpEf		m_circle;
		P_GrpEf		m_impact;
		double		m_r { 0 };

	public:
		EfClangSng ();
		EfClangSng ( const EfClangSng & rhs ) = delete;
		~EfClangSng ();

		void Load ();
		void Move ();

		void On ( VEC2 center );

	private:
		void SetScale ( P_Grp pGrp, const VEC2 & v );

		void Load_Tx ();
	};

	using P_EfClangSng = std::shared_ptr < EfClangSng >;


}	//namespace GAME


