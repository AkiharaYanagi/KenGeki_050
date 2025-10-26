//=================================================================================================
//
//	CharaSele_Stage
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../90_GameMain/GameConst.h"
#include "../91_Param/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class CharaSele_Stage	: public TASK_VEC
	{
		//保存用共通パラメータ
		P_Param			m_pParam;

		P_Grp		m_bg;
		INT32		m_index { 0 };
		constexpr static INT32 STAGE_NUM { 9 };

	public:
		CharaSele_Stage ();
		CharaSele_Stage ( const CharaSele_Stage & rhs ) = delete;
		~CharaSele_Stage ();

		void SetpParam ( P_Param p ) { m_pParam = p; }
		void Load ();
		void Move ();

		void Next ();
		void Prev ();

		STAGE_NAME GetStageName () const
		{
			return static_cast < STAGE_NAME > ( m_index );
		}
	};

	using P_CharaSele_Stage = std::shared_ptr < CharaSele_Stage >;


}	//namespace GAME

