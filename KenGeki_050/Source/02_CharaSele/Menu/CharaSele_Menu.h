//=================================================================================================
//
//	CharaSele_Menu
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../80_Common/SelectArrow.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class CharaSele_Menu	: public TASK_VEC
	{
		P_Grp		m_part_upper_back;	//回転背景
		P_Grp		m_part_upper;		//枠
//		P_Grp		m_part_upper_item;

		float		m_angle { 0 };
		float		m_omega { -0.005f };

#if 0

		P_Grp		m_arrow;		//矢印
		s3d::Array < P_Ob >		m_aryPob { 4 };		//操作用
		s3d::Array < VEC2 >		m_aryBasePos;	//基準位置
		float		m_arrow_frq{0};		//周波数
		float		m_arrow_time{0};	//時間
		float		m_arrow_w{0};	//幅

#endif // 0
		P_SelectArrow		m_arrow;	//選択矢印


		//メニュー項目
		P_Grp		m_Item;
		s3d::Array < VEC2 >		m_posItem;	//位置
		UINT32		m_pos { 0 };

		P_Grp		m_Btn5;
		P_Grp		m_Btn6;


	public:
		CharaSele_Menu ();
		CharaSele_Menu ( const CharaSele_Menu & rhs ) = delete;
		~CharaSele_Menu ();

		void Load ();
		void Move ();

		void Next ();
		void Prev ();

	private:
		void Pos ( UINT32 pos, UINT32 size );
	};

	using P_CharaSele_Menu = std::shared_ptr < CharaSele_Menu >;


}	//namespace GAME

