//=================================================================================================
//
//	TitleChara
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class TitleChara	: public TASK_VEC
	{
		P_Grp		m_chara;
		P_Ob		m_ob_1p;
		P_Ob		m_ob_2p;

		VEC2		m_start_pos_1p { 0, 0 };
		VEC2		m_start_pos_2p { 0, 0 };

		bool		m_active1 { T };
		bool		m_active2 { T };
		float		m_tx1 { 0 };
		float		m_tx2 { 0 };
		float		m_x1 { 0 };
		float		m_x2 { 0 };

		float		m_vx { 0 };

		//タイマ
		P_Timer		m_tmr;

	public:
		TitleChara ();
		TitleChara ( const TitleChara & rhs ) = delete;
		~TitleChara ();

		void Load ();
		void Init ();
		void Move ();
	};

	using P_TitleChara = std::shared_ptr < TitleChara >;


}	//namespace GAME

