//=================================================================================================
//
//	SelectArrow.h
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

	class SelectArrow	: public TASK_VEC
	{
	public:
		enum class DIR
		{
			UP_DOWN,
			LEFT_RIGHT,
			ALL
		};

	private:

		DIR			m_dir;				//方向
		P_Grp		m_arrow;			//画像
		VEC2		m_pos { VEC2{0, 0} };	//基準位置
		float		m_w{ 100 };			//左右幅
		float		m_h{ 100 };			//上下幅
		float		m_time{0};	//時間
		float		m_frq{0};		//周波数(frequency)
		float		m_amp{0};		//振幅(amplitude)

	public:
		SelectArrow () = delete;
		SelectArrow ( DIR dir, float z = 0.5f );
		SelectArrow ( const SelectArrow & rhs ) = delete;
		~SelectArrow ();

		void Load ();
		void Move ();

		void SetPos ( const VEC2& pos ) { m_pos = pos; }
		void SetW( const float w ) { m_w = w; }
		void SetH( const float h ) { m_h = h; }
		void SetZ(const float z) { m_arrow->SetZ(z); GRPLST_REINSERT ( m_arrow ); }

		//各初期化
		void SetUpDown ();
		void SetLeftRight ();
		void SetAll ();

		//各動作
		void MoveUpDown ( float offset );
		void MoveLeftRight ( float offset );
		void MoveAll ( float offset );

		//表示切替
		void Off ();
		void On ();
	};

	using P_SelectArrow = std::shared_ptr < SelectArrow >;


}	//namespace GAME

