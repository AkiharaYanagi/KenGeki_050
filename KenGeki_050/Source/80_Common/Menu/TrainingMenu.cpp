//=================================================================================================
//
//	TrainingMenu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TrainingMenu.h"
#include "../../90_GameMain/SeConst.h"



//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	TrainingMenu::TrainingMenu ()
	{
		GameMenu::SetBG_Color ( 0xa0000000 );
		GameMenu::SetBG_Size ( VEC2 ( 1000, 800 ) );
		GameMenu::SetBG_Pos ( VEC2 ( 1280 / 2 - 1000 / 2, 960 / 2 - 800 / 2 ) );

		m_str->SetPos( VEC2(300, 150) );
		m_str->SetStr(U"ポーズ メニュー");
		AddpTask(m_str);
		GRPLST_INSERT ( m_str );


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


		m_cursor = std::make_shared < GameGraphic >();
		m_cursor->AddTexture_FromArchive(U"cursor.png");
		m_cursor->SetZ(Z_MENU - 0.001f);
		AddpTask(m_cursor);
		GRPLST_INSERT(m_cursor);
		m_cursor->SetPos ( m_item_Ukemi->GetPosCursor () );


		//初期状態は非Active
		SetActive( F );
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
		//メニューに登録
		GameMenu::SetpMenuItem ( m_item_Ukemi );
		GameMenu::SetpMenuItem ( m_item_Guard );
		GameMenu::SetpMenuItem ( m_item_Taikou );
		GameMenu::SetpMenuItem ( m_item_CpuLevel );
		GameMenu::SetpMenuItem ( m_item_ToTitle );
		GameMenu::SetpMenuItem ( m_item_Return );


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


		TASK_VEC::Move ();
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
		m_cursor->SetPos( p->GetPosCursor() );
	}


	void TrainingMenu::SetwpParentScene ( WP_Scene wp )
	{
		m_item_Ukemi->SetwpParentScene ( wp );
		m_item_Guard->SetwpParentScene ( wp );
		m_item_Taikou->SetwpParentScene ( wp );
		m_item_CpuLevel->SetwpParentScene ( wp );
		m_item_ToTitle->SetwpParentScene ( wp );
		m_item_Return->SetwpParentScene ( wp );
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
				AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
				Off ();
				SetStopMain ( F );
				return F;
			}
		}

		//メニュポーズ開始
		bool bEsc = ( WND_UTL::AscKey ( VK_ESCAPE ) );
		bool bMenuBtn = ( CFG_PUSH_KEY ( P1_BTN6 ) || CFG_PUSH_KEY ( P2_BTN6 ) );
		if ( bEsc || bMenuBtn )
		{
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


}	//namespace GAME

