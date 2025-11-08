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
#include "../91_Param/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class TitleChara	: public TASK_VEC
	{
		//保存用共通パラメータ
		P_Param			m_pParam;

		//キャラグラフィック
		P_Grp		m_chara_1p;
		P_Grp		m_chara_2p;

		bool		m_active1 { T };
		bool		m_active2 { T };
		float		m_x1 { 0 };
		float		m_x2 { 0 };

		float		m_vx { 0 };

		//タイマ
		P_Timer		m_tmr;

	public:
		TitleChara ();
		TitleChara ( const TitleChara & rhs ) = delete;
		~TitleChara ();

		void SetpParam ( P_Param p );
		void Load ();
		void Init ();
		void Move ();

		void ResetChara ();

	private:
#pragma region CONST
		static const float TX_W;
		static const float START_X_1P;
		static const float START_X_2P;
		static const float TARGET_X_1P;
		static const float TARGET_X_2P;

#pragma endregion
	};

	using P_TitleChara = std::shared_ptr < TitleChara >;


}	//namespace GAME

