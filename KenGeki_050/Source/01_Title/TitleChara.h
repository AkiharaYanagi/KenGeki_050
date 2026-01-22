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

//		bool		m_active1 { T };
//		bool		m_active2 { T };
		float		m_x1 { 0 };
		float		m_x2 { 0 };

		float		m_vx1 { 0 };
		float		m_vx2 { 0 };

		//タイマ
		P_Timer		m_tmr1;
		P_Timer		m_tmr2;

		//位置補正
		inline static const 
		std::unordered_map < CHARA_NAME, float > m_posAdjustMap =
		{
			{ CHARA_OUKA		, -55.f },
			{ CHARA_SAE			, 0.f },
			{ CHARA_RETSUDOU	, -130.f },
			{ CHARA_GYAVADARUGA	, -200.f },
			{ CHARA_FERARIA		, -80.f },
		};

		float		m_revX1 { 0 };
		float		m_revX2 { 0 };

	public:
		TitleChara ();
		TitleChara ( const TitleChara & rhs ) = delete;
		~TitleChara ();

		void SetpParam ( P_Param p );
		void Load ();
		void Init ();
		void Move ();

		void RandomStartChara ();

	private:
		void SetChara ( CHARA_NAME name1, CHARA_COLOR clr1, CHARA_NAME name2, CHARA_COLOR clr2 );
		CHARA_NAME GetRandomCharaName () const;

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

