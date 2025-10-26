//=================================================================================================
//
//	TitleDemo
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

	class TitleDemo	: public TASK_VEC
	{
		//デモモード
		bool		m_bDemo { F };
		P_GrpStr	m_strDemo;	//デモ表示 "- Demo Mode -"文字列
		P_GrpStr	m_strDemoSwitch;	//デモ操作切換 "F9で切換" 文字列
		P_PrmRect	m_barDemo;	//時間表示バー
		Timer		m_tmrDemo;	//タイマ
		P_FadeRect	m_fade_demo;	//フェード

		bool		m_bStartDemo { F };	//デモでゲームメインを開始

	public:
		TitleDemo ();
		TitleDemo ( const TitleDemo & rhs ) = delete;
		~TitleDemo ();

		void Load ();
		void Move ();
		void Input ();

		void OnDemo();
		void OffDemo();

		bool IsStartDemo () const { return m_bStartDemo; }

		bool IsLast () const { return m_tmrDemo.IsLast (); }

	private:
		static const int32 WAIT_DEMO;
	//	static const int32 WAIT_DEMO;
		static const int32 BY;
		static const int32 BAR_Y;
		static const int32 STR_Y;
	};

	using P_TitleDemo = std::shared_ptr < TitleDemo >;


}	//namespace GAME

