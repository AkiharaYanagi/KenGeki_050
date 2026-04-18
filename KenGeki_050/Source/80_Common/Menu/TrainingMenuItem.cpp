//=================================================================================================
//
//	TestMenuItem
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TrainingMenuItem.h"
#include "../../04_Training/Training.h"
#include "../../90_GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//======================================================
	//ソースファイル内のみ使用するための無名namespaceによる定数
	namespace
	{
		constexpr float bx0 = 250;			//見出し
		constexpr float bx1 = bx0 + 250;	//項目

		constexpr float py  = 80;	//ピッチ
		constexpr float by  = 250;	//基準y
		constexpr float by0 = by + py * 0;	//受身
		constexpr float by1 = by + py * 1;	//ガード
		constexpr float by2 = by + py * 2;	//剣撃対抗
		constexpr float by3 = by + py * 3;	//CPUレベル
		constexpr float by4 = by + py * 4;	//タイトル
		constexpr float by5 = by + py * 5;	//戻る

		//全体
		constexpr float width0 = 600;
		constexpr float height0 = 50;

		//項目2つ
		constexpr float pitch2 = 100;
		constexpr float width2 = 200;
		constexpr float bx_True		= bx1 + pitch2 * 0;
		constexpr float bx_False	= bx1 + pitch2 * 1;
		
		//項目4つ
		constexpr float pitch4 = 150;
		constexpr float bx_4_0 = bx1 + pitch4 * 0;
		constexpr float bx_4_1 = bx1 + pitch4 * 1;
		constexpr float bx_4_2 = bx1 + pitch4 * 2;
		constexpr float bx_4_3 = bx1 + pitch4 * 3;

		//親カーソル位置
		constexpr float bx_csr = bx0 - 100;
		constexpr float by_csr = 15;

		//文字列パディング
		constexpr float STR_PAD = 10;

		//MenuのZ値はBGで、Z_MENU(0.02)が基準
		constexpr float Z_SEL_BG  = Z_MENU - 0.001f;
		constexpr float Z_SELECT  = Z_MENU - 0.002f;
		constexpr float Z_MAINSTR = Z_MENU - 0.003f;
		constexpr float Z_CURSOR  = Z_MENU - 0.004f;
	}


	//======================================================
	TrainingMenuItem::TrainingMenuItem ()
	{
		m_StrMain = MakeStr ();
		m_StrMain->SetStr ( U"Item" );
		m_SelectBG = MakeSelectBGRect ();
		m_Select = MakeSelectRect ();
		m_Cursor = MakeCursorRect ();
		Off ();
	}

	void TrainingMenuItem::SetwpParentScene ( WP_Scene wp )
	{
		mwp_Scene = wp;
	}

	void TrainingMenuItem::SetActive ( bool b )
	{
		if ( m_bUseSelect )
		{
			m_SelectBG->SetValid ( b );
			m_Cursor->SetValid ( b );
		}
		MenuItem::SetActive ( b );
	}

	void TrainingMenuItem::On ()
	{
		m_StrMain->SetValid ( T );
		if ( m_bUseSelect )
		{
			m_Select->SetValid ( T );
		}
		SetActive ( F );	//選択は解除
	}

	void TrainingMenuItem::Off ()
	{
		m_StrMain->SetValid ( F );
		m_SelectBG->SetValid ( F );
		m_Select->SetValid ( F );
		m_Cursor->SetValid ( F );
		SetActive ( F );
	}

	//-------------------------------------------------
	P_GrpStr TrainingMenuItem::MakeStr ()
	{
		P_GrpStr pStr = std::make_shared < GrpStr > ();
		pStr->SetSize ( G_Font::FONT_SIZE::SIZE_30 );
		pStr->SetZ ( Z_MAINSTR );
		AddpTask(pStr);
		GRPLST_INSERT(pStr);
		return pStr;
	}
	P_GrpStr TrainingMenuItem::MakeStr ( LPCUSTR str, VEC2 pos )
	{
		P_GrpStr pStr = MakeStr ();
		pStr->SetPos( pos );
		pStr->SetStr(str);
		return pStr;
	}

	void TrainingMenuItem::SetStrMain ( LPCUSTR str, VEC2 pos )
	{
		m_StrMain->SetStr ( str );
		m_StrMain->SetPos ( pos );
	}

	P_PrmRect TrainingMenuItem::MakePrmRect ( float Z )
	{
		P_PrmRect p = std::make_shared < PrmRect >();
		p->SetZ ( Z );
		AddpTask ( p );
		GRPLST_INSERT ( p );
		return p;
	}

	P_PrmRect TrainingMenuItem::MakeSelectBGRect ()
	{
		P_PrmRect p = MakePrmRect ( Z_SEL_BG );
		p->SetColor(0x40ffffff);
		return p;
	}

	void TrainingMenuItem::SetSelectBGRect ( VEC2 pos, VEC2 size )
	{
		m_SelectBG->SetPos ( pos );
		m_SelectBG->SetSize ( size );
	}

	P_PrmRect TrainingMenuItem::MakeSelectRect ()
	{
		P_PrmRect p = MakePrmRect ( Z_SELECT );
		p->SetColor(0x808080ff);
		return p;
	}

	void TrainingMenuItem::SetSelectRect ( VEC2 pos, VEC2 size )
	{
		m_Select->SetPos ( pos );
		m_Select->SetSize ( size );
	}

	void TrainingMenuItem::SetSelectWidth ( VEC2 size )
	{
		m_Select->SetSize ( size );
	}

	P_PrmRect TrainingMenuItem::MakeCursorRect ()
	{
		P_PrmRect p = MakePrmRect ( Z_CURSOR );
		p->SetColor(0xffff0000);
		p->SetFrame ( T );
		return p;
	}

	void TrainingMenuItem::SetCursorRect ( VEC2 pos, VEC2 size )
	{
		m_Cursor->SetPos ( pos );
		m_Cursor->SetSize ( size );
	}

	void TrainingMenuItem::SetCursorWidth ( VEC2 size )
	{
		m_Cursor->SetSize ( size );
	}

	void TrainingMenuItem::SetBasePos ( float y )
	{
		m_y = y;
		SetSelectBGRect ( VEC2 ( bx1 - 4, y - 4 ), VEC2 ( width0 + 8, height0 + 8 ) );
		SetSelectPos ( VEC2 ( bx1, y ) );
		SetCursorPos ( VEC2 ( bx1, y ) );
		SetPosPrtCursor ( VEC2 ( bx_csr, y + by_csr ) );	//親カーソル位置
	}

	void TrainingMenuItem::SetWidth ( float w )
	{
		SetSelectWidth ( VEC2 ( w, height0 ) );
		SetCursorWidth ( VEC2 ( w, height0 ) );
	}


	//======================================================
	MenuItem_Ukemi::MenuItem_Ukemi ()
	{
		SetBasePos ( by0 );
		SetWidth ( pitch2 );
		SetStrMain ( U"受身", VEC2( STR_PAD + bx0, 2 + m_y ) );
		m_StrOn = MakeStr ( U"ON", VEC2( STR_PAD + bx_True, 2 + m_y) );
		m_StrOff = MakeStr ( U"OFF", VEC2( STR_PAD + bx_False, 2 + m_y) );
	}

	void MenuItem_Ukemi::Do() 
	{
		//入力
		if ( CFG_PUSH_KEY_12 ( PLY_LEFT ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_move);
			PrevState ();
			SetCursorPos ( GetPosFromState () );
		}
		if ( CFG_PUSH_KEY_12 ( PLY_RIGHT ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_move);
			NextState ();
			SetCursorPos ( GetPosFromState () );
		}

		//決定
		if ( CFG_PUSH_KEY_12 ( PLY_BTN0 ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_Cancel);

			//選択表示
			SetSelectPos( GetPosFromState () );

			//パラメータに設定
			GetpParam()->GetPrmResult ().m_prp_Ukemi.Set (m_ukemiState);

			//親メニュに戻る
			this->SetActive(F);
			mwp_Parent.lock()->SetActive ( T );
		}

		//キャンセル
		if ( CFG_PUSH_KEY_12 ( PLY_BTN1 ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_Cancel);

			//設定しないで親メニュに戻る
			this->SetActive(F);
			mwp_Parent.lock()->SetActive ( T );
		}
	}

	void MenuItem_Ukemi::Off()
	{
		m_StrOn->SetValid ( F );
		m_StrOff->SetValid ( F );
		TrainingMenuItem::Off();
	}

	void MenuItem_Ukemi::On()
	{
		m_ukemiState = GetpParam()->GetPrmResult ().m_prp_Ukemi.Get ();
		SetSelectPos( GetPosFromState () );
		SetCursorPos ( GetPosFromState () );
		m_StrOn->SetValid ( T );
		m_StrOff->SetValid ( T );
		TrainingMenuItem::On();
	}

	void MenuItem_Ukemi::NextState ()
	{
		//@info !=は自分に否定を代入ではなく、bool値を返す演算子
		m_ukemiState = ! m_ukemiState;
	}

	void MenuItem_Ukemi::PrevState ()
	{
		m_ukemiState = ! m_ukemiState;
	}

	VEC2 MenuItem_Ukemi::GetPosFromState () const
	{
		float x = m_ukemiState ? bx_True: bx_False;
		return VEC2( x, m_y );
	}


	//======================================================
	MenuItem_Guard::MenuItem_Guard ()
	{
		SetBasePos ( by1 );
		SetWidth ( pitch2 );
		SetStrMain ( U"ガード", VEC2( STR_PAD + bx0, 2 + m_y ) );
		m_StrNormal = MakeStr ( U"通常", VEC2( 10 + bx_4_0, 2 + m_y) );
		m_StrHit1 = MakeStr ( U"1hit~", VEC2( 10 + bx_4_1, 2 + m_y) );
		m_StrRandom = MakeStr ( U"ランダム", VEC2( 10 + bx_4_2, 2 + m_y) );
		m_StrForced = MakeStr ( U"すべて", VEC2( 10 + bx_4_3, 2 + m_y) );
	}

	void MenuItem_Guard::Do() 
	{
		//入力
		if ( CFG_PUSH_KEY_12 ( PLY_LEFT ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_move);
			PrevState ();
			SetCursorPos ( GetPosFromState () );
		}
		if ( CFG_PUSH_KEY_12 ( PLY_RIGHT ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_move);
			NextState ();
			SetCursorPos ( GetPosFromState () );
		}

		//決定
		if ( CFG_PUSH_KEY_12 ( PLY_BTN0 ) )
		{
			//選択表示
			SetSelectPos ( GetPosFromState () );

			//パラメータに設定
			GetpParam()->GetPrmResult ().m_prp_Guard.Set ( m_guardState );

			//親メニュに戻る
			Back ();
		}

		//キャンセル
		if ( CFG_PUSH_KEY_12 ( PLY_BTN1 ) )
		{
			//親メニュに戻る
			Back ();
		}
	}

	void MenuItem_Guard::Off()
	{
		m_StrNormal->SetValid ( F );
		m_StrHit1->SetValid ( F );
		m_StrRandom->SetValid ( F );
		m_StrForced->SetValid ( F );
		TrainingMenuItem::Off();
	}

	void MenuItem_Guard::On()
	{
		m_guardState = GetpParam()->GetPrmResult ().m_prp_Guard.Get ();
		SetSelectPos( GetPosFromState () );
		SetCursorPos ( GetPosFromState () );
		m_StrNormal->SetValid ( T );
		m_StrHit1->SetValid ( T );
		m_StrRandom->SetValid ( T );
		m_StrForced->SetValid ( T );
		TrainingMenuItem::On();
	}

	void MenuItem_Guard::Back ()
	{
		AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
		this->SetActive(F);
		mwp_Parent.lock()->SetActive ( T );
	}

	void MenuItem_Guard::NextState ()
	{
		switch ( m_guardState )
		{
		case GuardState::Normal: m_guardState = GuardState::Hit1; break;
		case GuardState::Hit1: m_guardState = GuardState::Random; break;
		case GuardState::Random: m_guardState = GuardState::ForcedOn; break;
		case GuardState::ForcedOn: m_guardState = GuardState::Normal; break;
		}
	}

	void MenuItem_Guard::PrevState ()
	{
		switch ( m_guardState )
		{
		case GuardState::Normal: m_guardState = GuardState::Hit1; break;
		case GuardState::Hit1: m_guardState = GuardState::Random; break;
		case GuardState::Random: m_guardState = GuardState::ForcedOn; break;
		case GuardState::ForcedOn: m_guardState = GuardState::Normal; break;
		}
	}

	VEC2 MenuItem_Guard::GetPosFromState ()
	{
		switch ( m_guardState )
		{
		case GuardState::Normal: return VEC2( bx_4_0, m_y );
		case GuardState::Hit1: return VEC2( bx_4_1, m_y );
		case GuardState::Random: return VEC2( bx_4_2, m_y );
		case GuardState::ForcedOn: return VEC2( bx_4_3, m_y );
		}
		return VEC2( bx_4_0, m_y );
	}


	//======================================================


	MenuItem_Taikou::MenuItem_Taikou ()
	{
		SetBasePos ( by2 );
		SetWidth ( pitch4 );
		SetStrMain ( U"剣撃対抗", VEC2( 10 + bx0, 2 + m_y) );

		m_StrNone = MakeStr ( U"なし", VEC2( 10 + bx_4_0, 2 + m_y) );
		m_StrNormal = MakeStr ( U"通常", VEC2( 10 + bx_4_1, 2 + m_y) );
		m_StrRandom = MakeStr ( U"ランダム", VEC2( 10 + bx_4_2, 2 + m_y) );
		m_StrForced = MakeStr ( U"常にオン", VEC2( 10 + bx_4_3, 2 + m_y) );
	}

	void MenuItem_Taikou::Do() 
	{
		//入力
		if ( CFG_PUSH_KEY_12 ( PLY_LEFT ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_move);
			PrevState ();
			SetCursorPos( GetPosFromState () );
		}
		if ( CFG_PUSH_KEY_12 ( PLY_RIGHT ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_move);
			NextState ();
			SetCursorPos( GetPosFromState () );
		}

		//決定
		if ( CFG_PUSH_KEY_12 ( PLY_BTN0 ) )
		{
			//選択表示
			SetSelectPos ( GetPosFromState () );

			//パラメータに設定
			GetpParam()->GetPrmResult ().m_prp_Taikou.Set ( m_taikouState );

			Back ();
		}

		//キャンセル
		if ( CFG_PUSH_KEY_12 ( PLY_BTN1 ) )
		{
			Back ();
		}
	}

	void MenuItem_Taikou::Back()
	{
		AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
		this->SetActive(F);
		mwp_Parent.lock()->SetActive ( T );		//親メニュに戻る
	}

	void MenuItem_Taikou::Off()
	{
		m_StrNone->SetValid ( F );
		m_StrNormal->SetValid ( F );
		m_StrRandom->SetValid ( F );
		m_StrForced->SetValid ( F );
		TrainingMenuItem::Off();
	}

	void MenuItem_Taikou::On()
	{
		m_taikouState = GetpParam()->GetPrmResult ().m_prp_Taikou.Get ();
		SetSelectPos( GetPosFromState () );
		SetCursorPos ( GetPosFromState () );
		m_StrNone->SetValid ( T );
		m_StrNormal->SetValid ( T );
		m_StrRandom->SetValid ( T );
		m_StrForced->SetValid ( T );
		TrainingMenuItem::On();
	}

	void MenuItem_Taikou::NextState ()
	{
		switch ( m_taikouState )
		{
		case TaikouState::None: m_taikouState = TaikouState::Normal; break;
		case TaikouState::Normal: m_taikouState = TaikouState::Random; break;
		case TaikouState::Random: m_taikouState = TaikouState::ForcedOn; break;
		case TaikouState::ForcedOn: m_taikouState = TaikouState::None; break;
		}
	}

	void MenuItem_Taikou::PrevState ()
	{
		switch ( m_taikouState )
		{
		case TaikouState::None: m_taikouState = TaikouState::ForcedOn; break;
		case TaikouState::Normal: m_taikouState = TaikouState::None; break;
		case TaikouState::Random: m_taikouState = TaikouState::Normal; break;
		case TaikouState::ForcedOn: m_taikouState = TaikouState::Random; break;
		}
	}

	VEC2 MenuItem_Taikou::GetPosFromState ()
	{
		switch ( m_taikouState )
		{
		case TaikouState::None: return VEC2( bx_4_0, m_y );
		case TaikouState::Normal: return VEC2( bx_4_1, m_y );
		case TaikouState::Random: return VEC2( bx_4_2, m_y );
		case TaikouState::ForcedOn: return VEC2( bx_4_3, m_y );
		}
		return VEC2( bx_4_0, m_y );
	}


	//======================================================
	namespace
	{
		constexpr float BOX_W = 50;
		constexpr float BOX_H = 50;
	}

	MenuItem_CPU_LEVEL::MenuItem_CPU_LEVEL ()
	{
		SetBasePos ( by3 );
		SetWidth ( BOX_W );
		SetStrMain ( U"CPUレベル", VEC2( 10 + bx0, 2 + m_y ) );

		m_aryLvStr.resize( 8 );
		for ( INT32 i = 0; i < 8; ++ i )
		{
			VEC2 pos = VEC2 ( bx1 + BOX_W * i + 15, 2 + m_y );
			m_aryLvStr [ i ] = MakeStr ( U"{}"_fmt ( i + 1 ).c_str(), pos);
		}
	}

	void MenuItem_CPU_LEVEL::Do ()
	{
		//入力
		if ( CFG_PUSH_KEY_12 ( PLY_LEFT ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_move);
			PrevLevel ();
			SetCursorPos ( GetPosFromState() );
		}
		if ( CFG_PUSH_KEY_12 ( PLY_RIGHT ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_move);
			NextLevel ();
			SetCursorPos( GetPosFromState() );
		}

		//決定
		if ( CFG_PUSH_KEY_12 ( PLY_BTN0 ) )
		{
			GetpParam()->GetPrmResult ().m_prp_CpuLevel.Set (m_level);
			Back ();
			GetwpParentScene().lock ()->ParamReset ();
		}

		//キャンセル
		if ( CFG_PUSH_KEY_12 ( PLY_BTN1 ) )
		{
			Back ();
		}
	}

	void MenuItem_CPU_LEVEL::On()
	{
		//最初の状態
		INT32 level = GetpParam()->GetPrmResult ().m_prp_CpuLevel.Get ();
		SetLevel ( level );
		SetSelectPos( GetPosFromState () );
		SetCursorPos ( GetPosFromState () );

		for ( P_GrpStr p : m_aryLvStr )
		{
			p->SetValid ( T );
		}
		TrainingMenuItem::On();
	}

	void MenuItem_CPU_LEVEL::Off()
	{
		for ( P_GrpStr p : m_aryLvStr )
		{
			p->SetValid ( F );
		}
		TrainingMenuItem::Off();
	}

	void MenuItem_CPU_LEVEL::Back ()
	{
		AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
		this->SetActive(F);
		mwp_Parent.lock()->SetActive ( T );
	}

	void MenuItem_CPU_LEVEL::SetLevel ( INT32 level )
	{
		if ( level < 0 || level > 7 ) { level = 0; }
		m_level = level;
	}

	void MenuItem_CPU_LEVEL::NextLevel ()
	{
		if ( m_level == 7 ) { m_level = 0; }
		else { ++ m_level; }
	}

	void MenuItem_CPU_LEVEL::PrevLevel ()
	{
		if ( m_level == 0 ) { m_level = 7; }
		else { -- m_level; }
	}

	VEC2 MenuItem_CPU_LEVEL::GetPosFromState ()
	{
		return VEC2( bx1 + BOX_W * m_level, m_y );
	}

	//======================================================

	MenuItem_ToTitle::MenuItem_ToTitle ()
	{
		SetBasePos ( by4 );
		SetbUseSelect ( F );	//選択表示はなし

		SetStrMain ( U"タイトルに戻る", VEC2 ( 10 + bx0, 2 + m_y ) );

		m_YesNoMenu = std::make_shared < YesNo_Menu > ();
		AddpTask ( m_YesNoMenu );
	}

	void MenuItem_ToTitle::Decide ()
	{
		AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
		//確認メニュを表示
		m_YesNoMenu->On ();
	}


	//======================================================
	MenuItem_Return::MenuItem_Return ()
	{
		SetBasePos ( by5 );
		SetbUseSelect ( F );	//選択表示はなし
		SetStrMain ( U"ゲームに戻る", VEC2 ( 10 + bx0, 2 + m_y ) );
	}

	//決定
	void MenuItem_Return::Decide ()
	{
		AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
		//親と自身をオフにする
		this->SetActive(F);
		mwp_Parent.lock()->Off ();
		mwp_Parent.lock()->SetStopMain ( F );
		mwp_Parent.lock()->SetActive ( F );
	}


}	//namespace GAME

