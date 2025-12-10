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
#include "../../90_GameMain/Scene.h"
#include "TrainingMenuItem.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class TrainingMenu	: public Menu
	{
		P_MenuItem_Taikou		m_item_Taikou;		//剣撃対抗
		P_MenuItem_CPU_LEVEL	m_item_CpuLevel;	//CPUレベル
		P_MenuItem_ToTitle		m_item_ToTitle;		//タイトル
		P_MenuItem_Return		m_item_Return;		//戻る

		P_Grp		m_cursor;	//カーソル

	public:
		TrainingMenu ();
		TrainingMenu ( const TrainingMenu & rhs ) = delete;
		~TrainingMenu ();

		void Load () override;
		void Move () override;

		void SetActive(bool b) override;

		void SetpParam ( P_Param p );
		void SetwpParentScene ( WP_Scene wp );

		//メインMove()中でチェックしてtrueのとき他を処理しないでreturnする
		bool MenuInput ();

		void Off ();
		void On ();


	private:
		void SetCursorPos ();
	};

	using P_TrainingMenu = std::shared_ptr < TrainingMenu >;


}	//namespace GAME

