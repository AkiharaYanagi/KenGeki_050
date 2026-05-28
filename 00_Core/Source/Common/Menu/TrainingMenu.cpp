//=================================================================================================
//
//	TrainingMenu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "00_Core/Menu/TrainingMenu.h"
#include "00_Core/Menu/PauseMenu_Const.h"
#include "00_Core/SeConst.h"



//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//======================================================
	//ソースファイル内のみ使用するための無名namespaceによる定数
	namespace
	{
		constexpr float bx0 = 400;
		constexpr float by0 = 100;	//基準
	}

	//======================================================


	TrainingMenu::TrainingMenu ()
	{
		//--------------------------------------------
		//基本背景
		GameMenu::SetBG_use ( T );
		GameMenu::SetBG_Color ( 0xd0000000 );
		GameMenu::SetBG_Size( MENU_BG_W, MENU_BG_H );
		GameMenu::SetBG_Pos ( MENU_BG_X, MENU_BG_Y );

		//--------------------------------------------
		//見出文字
		m_str->SetPos( VEC2(bx0, by0) );
		m_str->SetStr(U"- Training Menu -");

		//--------------------------------------------
		//項目
		m_item_Ukemi = std::make_shared < MenuItem_Ukemi >();
		AddpTask ( m_item_Ukemi );

		m_item_Guard = std::make_shared < MenuItem_Guard >();
		AddpTask ( m_item_Guard );

		m_item_Taikou = std::make_shared < MenuItem_Taikou >();
		AddpTask ( m_item_Taikou );

		m_item_CpuLevel = std::make_shared < MenuItem_CPU_LEVEL >();
		AddpTask ( m_item_CpuLevel );

		m_item_ToTitle = std::make_shared < MenuItem_ToTitle >();
		AddpTask ( m_item_ToTitle );

		m_item_Return = std::make_shared < MenuItem_Return >();
		AddpTask ( m_item_Return );

		//--------------------------------------------
		//カーソル
		m_cursor = std::make_shared < GameGraphic >();
		m_cursor->AddTexture_FromArchive(U"cursor.png");
		m_cursor->SetZ ( Z_MENU_STR );
		m_cursor->SetScalingCenter ( 0, 12.5f );
		AddpTask(m_cursor);
		GRPLST_INSERT(m_cursor);
		m_cursor->SetPos ( m_item_Ukemi->GetPosPrtCursor () );

		//--------------------------------------------
		//初期状態はOff
		Off ();
	}

	void TrainingMenu::SetpParam ( P_Param p )
	{
		m_item_Ukemi->SetpParam ( p );
		m_item_Guard->SetpParam ( p );
		m_item_Taikou->SetpParam ( p );
		m_item_CpuLevel->SetpParam ( p );
		m_item_ToTitle->SetpParam ( p );
		m_item_Return->SetpParam ( p );

#if 0
		for ( P_MenuItem pItem : Menu::GetvpMenuItem() )
		{
			( dynamic_pointer_cast < TrainingMenuItem > ( pItem ) )->SetpParam ( p );
		}
#endif // 0

#if 0
		std::function < void ( P_GameMenuItem ) > func = [ p ] ( P_GameMenuItem pItem )
		{
			P_TrainingMenuItem pT = std::dynamic_pointer_cast < TrainingMenuItem > ( pItem );
			pT->SetpParam ( p );
		};
		Menu::ForEachMenuItem_Do ( func );
#endif // 0

		Menu::SetpParam ( p );

	}

	void TrainingMenu::Load ()
	{
		//メニューリストに登録
		GameMenu::SetpMenuItem ( m_item_Ukemi );
		GameMenu::SetpMenuItem ( m_item_Guard );
		GameMenu::SetpMenuItem ( m_item_Taikou );
		GameMenu::SetpMenuItem ( m_item_CpuLevel );
		GameMenu::SetpMenuItem ( m_item_ToTitle );
		GameMenu::SetpMenuItem ( m_item_Return );

		//特殊設定
		m_item_ToTitle->SetwpParentMenu ( shared_from_this() );
		m_item_ToTitle->SetwpEndMenu ( shared_from_this() );


		//最初の選択
		GameMenu::SelectTop();
		SetCursorPos();

		TASK_VEC::Load ();

		AllOff ();
	}

	void TrainingMenu::Move ()
	{
		//メイン停止以外は何もしない
		if ( ! GetStopMain () ) { return; }

		//Move()は常に実行
		
		//active時
		if ( GetActive () )
		{
			//位置選択
			if ( CFG_PUSH_KEY_12 ( PLY_UP ) )
			{
				AUD_PLAY_ONESHOT_SE (SE_select_move);
				Menu::Prev();
				SetCursorPos();
			}
			if ( CFG_PUSH_KEY_12 ( PLY_DOWN ) )
			{
				AUD_PLAY_ONESHOT_SE (SE_select_move);
				Menu::Next();
				SetCursorPos();
			}

			//決定
			if ( CFG_PUSH_KEY_12 ( PLY_BTN0 ) )
			{
				AUD_PLAY_ONESHOT_SE (SE_select_Cancel);

				//選択したItemをActiveにする
				GetpMenuItem()->SetActive(T);

				//最初の１回のみDecide()を実行
				GetpMenuItem ()->Decide ();

				//自身は非Activeにする
				SetActive(F);
			}

			//キャンセル
			if ( CFG_PUSH_KEY_12 ( PLY_BTN1 ) )
			{
				AUD_PLAY_ONESHOT_SE (SE_select_Cancel);
				this->SetActive(F);
				SetStopMain ( F );
			}
		}
		else
		{
			//ItemのDo()のみ実行
			Do ();
		}

		//カーソル回転
		m_cursor_scaling_y += m_cursor_scaling_vy;
		if (m_cursor_scaling_y >= 1.f) { m_cursor_scaling_vy = -0.1f; }
		if (m_cursor_scaling_y <= -1.f) { m_cursor_scaling_vy = 0.1f; }
		m_cursor->SetScaling(1.f, m_cursor_scaling_y);


		Menu::Move ();
	}

	void TrainingMenu::SetActive ( bool b )
	{
		Menu::SetActive ( b );

		//カーソルも表示/非表示
		m_cursor->SetValid ( b );
	}


	void TrainingMenu::SetCursorPos ()
	{
		P_GameMenuItem pItem = GetpMenuItem();	
		P_TrainingMenuItem p = std::dynamic_pointer_cast<TrainingMenuItem>(pItem);
		m_cursor->SetPos( p->GetPosPrtCursor() );
	}


	void TrainingMenu::SetwpParentScene ( WP_Scene wp )
	{
		m_item_Ukemi->SetwpParentScene ( wp );
		m_item_Guard->SetwpParentScene ( wp );
		m_item_Taikou->SetwpParentScene ( wp );
		m_item_CpuLevel->SetwpParentScene ( wp );
		m_item_ToTitle->SetwpParentScene ( wp );
		m_item_Return->SetwpParentScene ( wp );

		//特殊設定
		m_item_ToTitle->SetwpParentScene_YS ( wp );
	}

	bool TrainingMenu::MenuInput ()
	{
		//メニュポーズ中
		if ( GetActive () )
		{
			//メニュポーズ解除
			bool bEsc = WND_UTL::AscKey ( VK_ESCAPE );
			bool bMenuBtn = CFG_PUSH_KEY_12 ( PLY_BTN6 );
			bool bCancelBtn = CFG_PUSH_KEY_12 ( PLY_BTN1 );
			if ( bEsc || bMenuBtn || bCancelBtn )
			{
				Back ();
				return F;
			}
		}

		//メニュポーズ開始
		bool bEsc = ( WND_UTL::AscKey ( VK_ESCAPE ) );
		bool bMenuBtn = ( CFG_PUSH_KEY ( P1_BTN6 ) || CFG_PUSH_KEY ( P2_BTN6 ) );
		if ( bEsc || bMenuBtn )
		{
			//振動オフ(外部機能)
			G_GrpTx::Inst()->VibOff ();

			AUD_PLAY_ONESHOT_SE (SE_select_move);
			On ();
			SetStopMain ( T );
		}

		return F;
	}

	void TrainingMenu::Off ()
	{
		m_str->SetValid ( F );

		m_item_Ukemi->Off ();
		m_item_Guard->Off ();
		m_item_Taikou->Off ();
		m_item_CpuLevel->Off ();
		m_item_ToTitle->Off ();
		m_item_Return->Off ();

		m_cursor->SetValid ( F );
		SetActive ( F );
		Menu::Off ();
	}

	void TrainingMenu::On ()
	{
		m_str->SetValid ( T );

		m_item_Ukemi->On ();
		m_item_Guard->On ();
		m_item_Taikou->On ();
		m_item_CpuLevel->On ();
		m_item_ToTitle->On ();
		m_item_Return->On ();

		m_cursor->SetValid ( T );
		SetActive ( T );
		Menu::On ();
	}

	void TrainingMenu::Back ()
	{
		AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
		//すべて非アクティブ
		for ( P_GameMenuItem pItem : GameMenu::GetvpMenuItem() )
		{
			 pItem->SetActive ( F );
		}
		Off ();
		SetStopMain ( F );
	}


}	//namespace GAME

