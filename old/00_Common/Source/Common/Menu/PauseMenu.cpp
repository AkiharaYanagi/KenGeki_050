//=================================================================================================
//
//	PauseMenu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "PauseMenu.h"
#include "PauseMenu_Const.h"
#include "../../Const/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//ソースファイル内のみ使用するための無名namespaceによる定数
	namespace
	{
		constexpr float bx0 = 250;			//見出し
		constexpr float bx1 = bx0 + 250;	//項目

		constexpr float py  = 80;	//ピッチ
		constexpr float by  = 250;	//基準y
		constexpr float by0 = by + py * 0;	//CPUレベル
		constexpr float by1 = by + py * 1;	//タイトル
		constexpr float by2 = by + py * 2;	//戻る
		constexpr float by3 = by + py * 3;	//
		constexpr float by4 = by + py * 4;	//
		constexpr float by5 = by + py * 5;	//
	}


	PauseMenu::PauseMenu ()
	{
		//--------------------------------------------
		//基本背景
		GameMenu::SetBG_use ( T );
		GameMenu::SetBG_Size ( MENU_BG_W, MENU_BG_H );
		GameMenu::SetBG_Pos ( MENU_BG_X, MENU_BG_Y);
		GameMenu::SetBG_Color ( 0xd0000000 );

		//--------------------------------------------
		//見出文字
		m_str->SetStr ( U"- PAUSE -" );
		m_str->SetPos ( 500, 120 );

		//--------------------------------------------
		//項目

		//CPUレベル
		m_item_CpuLevel = std::make_shared < MenuItem_CPU_LEVEL >();
		AddpTask ( m_item_CpuLevel );
		m_item_CpuLevel->ResetBasePos ( by0 );

		//タイトルに戻る
		m_item_ToTitle = std::make_shared < MenuItem_ToTitle >();
		AddpTask ( m_item_ToTitle );
		m_item_ToTitle->ResetBasePos ( by1 );

		//ゲームに戻る
		m_item_Return = std::make_shared < MenuItem_Return >();
		AddpTask ( m_item_Return );
		m_item_Return->ResetBasePos ( by2 );

		//--------------------------------------------
		//カーソル
		m_cursor = std::make_shared < GameGraphic > ();
		m_cursor->AddTexture_FromArchive ( U"cursor.png" );
		m_cursor->SetZ ( Z_MENU_STR );
		m_cursor->SetScalingCenter ( 0, 12.5f );
		AddpTask ( m_cursor );
		GRPLST_INSERT ( m_cursor );
		m_cursor->SetPos ( m_item_CpuLevel->GetPosPrtCursor () );

		//--------------------------------------------
		//初期状態はOff
		Off ();
	}

	PauseMenu::~PauseMenu ()
	{
	}

	void PauseMenu::SetpParam ( P_Param p )
	{
		m_item_CpuLevel->SetpParam ( p );
		m_item_ToTitle->SetpParam ( p );
		m_item_Return->SetpParam ( p );
		Menu::SetpParam ( p );
	}

	void PauseMenu::Load ()
	{
		//--------------------------------------------
		//メニューリストに登録
		GameMenu::SetpMenuItem ( m_item_CpuLevel );
		GameMenu::SetpMenuItem ( m_item_ToTitle );
		GameMenu::SetpMenuItem ( m_item_Return );

		//特殊設定
		m_item_ToTitle->SetwpParentMenu ( shared_from_this() );
		m_item_ToTitle->SetwpEndMenu ( shared_from_this() );

		Menu::Load ();
	}

	void PauseMenu::Move ()
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
		if ( m_cursor_scaling_y >=  1.f ) { m_cursor_scaling_vy = - 0.1f; }
		if ( m_cursor_scaling_y <= -1.f ) { m_cursor_scaling_vy =   0.1f; }
		m_cursor->SetScaling ( 1.f, m_cursor_scaling_y );

		Menu::Move ();
	}

	void PauseMenu::SetActive ( bool b )
	{
		Menu::SetActive ( b );

		//カーソルも表示/非表示
		m_cursor->SetValid ( b );
	}


	void PauseMenu::SetCursorPos ()
	{
		P_GameMenuItem pItem = GetpMenuItem();	
		P_TrainingMenuItem p = std::dynamic_pointer_cast<TrainingMenuItem>(pItem);
		m_cursor->SetPos( p->GetPosPrtCursor() );
	}


	void PauseMenu::SetwpParentScene ( WP_Scene wp )
	{
		m_item_CpuLevel->SetwpParentScene ( wp );
		m_item_ToTitle->SetwpParentScene ( wp );
		m_item_Return->SetwpParentScene ( wp );

		//特殊設定
		m_item_ToTitle->SetwpParentScene_YS ( wp );
	}

	bool PauseMenu::MenuInput ()
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

	void PauseMenu::Off ()
	{
		m_str->SetValid ( F );

		m_item_CpuLevel->Off ();
		m_item_ToTitle->Off ();
		m_item_Return->Off ();

		m_cursor->SetValid ( F );
		SetActive ( F );
		Menu::Off ();
	}

	void PauseMenu::On ()
	{
		m_str->SetValid ( T );

		m_item_CpuLevel->On ();
		m_item_ToTitle->On ();
		m_item_Return->On ();

		m_cursor->SetValid ( T );
		SetActive ( T );
		Menu::On ();
	}

	void PauseMenu::Back ()
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

