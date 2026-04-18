//=================================================================================================
//
//	TrainingMenu
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "TrainingMenuItem.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class TrainingMenu	: public Menu
	{
		P_MenuItem_Ukemi		m_item_Ukemi;		//受け身
		P_MenuItem_Guard		m_item_Guard;		//ガード
		P_MenuItem_Taikou		m_item_Taikou;		//剣撃対抗
		P_MenuItem_CPU_LEVEL	m_item_CpuLevel;	//CPUレベル
		P_MenuItem_ToTitle		m_item_ToTitle;		//タイトル
		P_MenuItem_Return		m_item_Return;		//戻る

		P_Grp		m_cursor;	//カーソル
		float		m_cursor_scaling_vy{ 0.05f };
		float		m_cursor_scaling_y{ 1.f };

	public:
		TrainingMenu ();
		TrainingMenu ( const TrainingMenu & rhs ) = delete;
		~TrainingMenu () = default;

		void Load () override;
		void Move () override;

		void SetpParam ( P_Param p );
		void SetwpParentScene ( WP_Scene wp );

		//メインMove()中でチェックしてtrueのとき他を処理しないでreturnする
		bool MenuInput ();

		void SetActive(bool b) override;
		void On ();
		void Off ();
		void Back ();

	private:
		void SetCursorPos ();
	};

	using P_TrainingMenu = std::shared_ptr < TrainingMenu >;


}	//namespace GAME

