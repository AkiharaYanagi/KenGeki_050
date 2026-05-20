//=================================================================================================
//
//	EfString ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "00_Core/GameConst.h"
#include "../FtgConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//相殺時エフェクト
	class EfString : public TASK_VEC
	{
		//P_Grp		m_grp;

		P_Grp		m_ef_zero;
		P_Grp		m_ef_siki;
		P_Grp		m_ef_ninn;
		P_Grp		m_ef_jutu;

		int32		m_timer { 0 };
		std::array < float, 4 >		m_scaling;

	public:
		EfString ();
		EfString ( const EfString & rhs ) = delete;
		~EfString ();

		void Load ();
		void Init ();
		void Move ();

		void On ();
		void Off ();

		void Start () { On (); m_timer = 1; }

	private:
		void SE ();
	};

	using P_EfString = std::shared_ptr < EfString >;


}	//namespace GAME


