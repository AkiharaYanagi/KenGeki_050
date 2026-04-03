//=================================================================================================
//
//	EfClangMlt ヘッダファイル
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
	class EfClangMlt : public TASK_VEC
	{
		P_GrpEf		m_thunder0;
//		P_GrpEf		m_thunder1;
		P_GrpEf		m_circle;
		P_GrpEf		m_impact;

		double	m_r { 0 };


//		P_GrpEf		m_test;


	public:
		EfClangMlt ();
		EfClangMlt ( const EfClangMlt & rhs ) = delete;
		~EfClangMlt ();

		void Load ();
		void Move ();

		void On ( VEC2 center );


	private:
		void SetScale ( P_Grp pGrp, const VEC2 & v );
	};

	using P_EfClangMlt = std::shared_ptr < EfClangMlt >;


}	//namespace GAME


