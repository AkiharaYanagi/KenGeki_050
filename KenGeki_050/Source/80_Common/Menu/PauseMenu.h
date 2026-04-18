//=================================================================================================
//
//	PauseMenu
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

	class PauseMenu : public Menu
	{
		P_MenuItem_CPU_LEVEL	m_item_CpuLevel;	//CPUレベル
		P_MenuItem_ToTitle		m_item_ToTitle;		//タイトル
		P_MenuItem_Return		m_item_Return;		//戻る

		//カーソル
		P_Grp		m_cursor;
		float		m_cursor_scaling_vy { 0.05f };
		float		m_cursor_scaling_y { 1.f };

	public:
		PauseMenu ();
		PauseMenu ( const PauseMenu & rhs ) = delete;
		~PauseMenu ();

		void Load () override;
		void Move () override;

//		void SetwpParent ( WP_FtgMain p );
		void SetwpParentScene ( WP_Scene wp );

		//メインMove()中でチェックしてtrueのとき他を処理しないでreturnする
		bool MenuInput ();

		//稼働
		void SetActive(bool b) override;
		void On ();
		void Off ();
		void Back ();

	private:
		void SetCursorPos ();
	};


	using P_PauseMenu = std::shared_ptr < PauseMenu >;


}	//namespace GAME

