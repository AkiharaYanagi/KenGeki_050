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
	//ソースファイル内定数
#if 0

	static constexpr float bx0 = 400;
	static constexpr float bx1 = bx0 + 200;
	static constexpr float by0 = 300;
	static constexpr float by1 = 400;
	static constexpr float by2 = 500;

	static constexpr float bx_on = bx1;
	static constexpr float bx_of = bx1 + 100;

	static constexpr float bx_csr = bx0 - 100;
	static constexpr float by_csr = 15;

#endif // 0

	//ソースファイル内のみ使用するための無名namespace
	namespace
	{
		constexpr float bx0 = 300;
		constexpr float bx1 = bx0 + 200;
		constexpr float by0 = 300;
		constexpr float by1 = 400;
		constexpr float by2 = 500;
		constexpr float by3 = 600;

		constexpr float pitch = 150;
		constexpr float bx_none		= bx1 + pitch * 0;
		constexpr float bx_normal	= bx1 + pitch * 1;
		constexpr float bx_random	= bx1 + pitch * 2;
		constexpr float bx_forced	= bx1 + pitch * 3;

		constexpr float bx_csr = bx0 - 100;
		constexpr float by_csr = 15;

		constexpr float width0 = pitch * 4;
		constexpr float height0 = 50;
	}
	//======================================================


	MenuItem_Taikou::MenuItem_Taikou ()
	{
		m_SelectBG = std::make_shared < PrmRect >();
		m_SelectBG->SetZ ( Z_MENU - 0.001f + 0.0001f );
		m_SelectBG->SetPos( VEC2(bx1 - 4, by0 - 4) );
		m_SelectBG->SetSize(VEC2(width0 + 8, height0 + 8));
		m_SelectBG->SetColor(0x40ffffff);
		AddpTask(m_SelectBG);
		GRPLST_INSERT(m_SelectBG);

		m_Select = std::make_shared < PrmRect >();
		m_Select->SetZ ( Z_MENU - 0.001f );
		m_Select->SetPos( VEC2(bx1, by0) );
		m_Select->SetSize(VEC2(pitch, height0));
		m_Select->SetColor(0x808080ff);
		AddpTask(m_Select);
		GRPLST_INSERT(m_Select);

		m_StrTaikou = MakeStr ( U"剣撃対抗", VEC2( 10 + bx0, 2 + by0) );

		m_StrNone = MakeStr ( U"なし", VEC2( 10 + bx_none, 2 + by0) );
		m_StrNormal = MakeStr ( U"通常", VEC2( 10 + bx_normal, 2 + by0) );
		m_StrRandom = MakeStr ( U"ランダム", VEC2( 10 + bx_random, 2 + by0) );
		m_StrForced = MakeStr ( U"常にオン", VEC2( 10 + bx_forced, 2 + by0) );

		m_Cursor = std::make_shared < PrmRect >();
		m_Cursor->SetZ ( Z_MENU - 0.001f );
		m_Cursor->SetPos( VEC2(bx1, by0) );
		m_Cursor->SetSize(VEC2(pitch, height0));
		m_Cursor->SetColor(0xffff0000);
		m_Cursor->SetFrame ( T );
		AddpTask(m_Cursor);
		GRPLST_INSERT(m_Cursor);

		SetPosCursor(VEC2(bx_csr, by0 + by_csr));
	}

	P_GrpStr MenuItem_Taikou::MakeStr ( LPCUSTR str, VEC2 pos )
	{
		P_GrpStr pStr = std::make_shared < GrpStr > ();
		pStr->SetSize ( G_Font::FONT_SIZE::SIZE_30 );
		pStr->SetZ ( Z_MENU - 0.001f );
		pStr->SetPos( pos );
		pStr->SetStr(str);
		AddpTask(pStr);
		GRPLST_INSERT(pStr);
		return pStr;
	}

	MenuItem_Taikou::~MenuItem_Taikou ()
	{
	}

	void MenuItem_Taikou::Init ()
	{
		SetActive ( F );
		MenuItem::Init ();
	}

	void MenuItem_Taikou::Load ()
	{
		MenuItem::Load ();
	}

	void MenuItem_Taikou::Move ()
	{
		MenuItem::Move ();
	}

	void MenuItem_Taikou::Do() 
	{
		//入力
		if ( CFG_PUSH_KEY_12 ( PLY_LEFT ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_move);
			PrevState ();
			m_Cursor->SetPos( GetPosFromState ( m_taikouState ) );
		}
		if ( CFG_PUSH_KEY_12 ( PLY_RIGHT ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_move);
			NextState ();
			m_Cursor->SetPos( GetPosFromState ( m_taikouState ) );
		}

		//決定
		if ( CFG_PUSH_KEY_12 ( PLY_BTN0 ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
			//選択表示
			m_Select->SetPos( GetPosFromState ( m_taikouState ) );

			//パラメータに設定
			m_pParam->GetPrmResult ().m_prp_Taikou.Set ( m_taikouState );

			//親メニュに戻る
			this->SetActive(F);
			mwp_Parent.lock()->SetActive ( T );
		}

		//キャンセル
		if ( CFG_PUSH_KEY_12 ( PLY_BTN1 ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
			this->SetActive(F);
			mwp_Parent.lock()->SetActive ( T );
		}
	}

	void MenuItem_Taikou::SetActive(bool b)
	{
		TrainingMenuItem::SetActive(b);
		m_SelectBG->SetValid(b);
		m_Cursor->SetValid(b);
	}

	void MenuItem_Taikou::Off()
	{
		m_SelectBG->SetValid ( F );
		m_StrTaikou->SetValid ( F );
		m_StrNone->SetValid ( F );
		m_StrNormal->SetValid ( F );
		m_StrRandom->SetValid ( F );
		m_StrForced->SetValid ( F );
		m_Select->SetValid ( F );
		TrainingMenuItem::Off();
	}

	void MenuItem_Taikou::On()
	{
		m_taikouState = m_pParam->GetPrmResult().m_prp_Taikou.Get ();
		m_Cursor->SetPos( GetPosFromState ( m_taikouState ) );
		m_Select->SetPos( GetPosFromState ( m_taikouState ) );

		m_StrTaikou->SetValid ( T );
		m_StrNone->SetValid ( T );
		m_StrNormal->SetValid ( T );
		m_StrRandom->SetValid ( T );
		m_StrForced->SetValid ( T );
		m_Select->SetValid ( T );
		TrainingMenuItem::On();
	}

	void MenuItem_Taikou::SetwpParentScene ( WP_Scene wp )
	{
		mwp_Scene = wp;
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

	VEC2 MenuItem_Taikou::GetPosFromState ( TaikouState state )
	{
		switch ( state )
		{
		case TaikouState::None: return VEC2( bx_none, by0 );
		case TaikouState::Normal: return VEC2( bx_normal, by0 );
		case TaikouState::Random: return VEC2( bx_random, by0 );
		case TaikouState::ForcedOn: return VEC2( bx_forced, by0 );
		}
		return VEC2( bx_none, by0 );
	}


	//======================================================
	namespace
	{
		constexpr float BOX_W = 50;
		constexpr float BOX_H = 50;
	}


	MenuItem_CPU_LEVEL::MenuItem_CPU_LEVEL ()
	{

		m_SelectBG = std::make_shared < PrmRect >();
		m_SelectBG->SetZ ( Z_MENU - 0.001f + 0.0001f );
		m_SelectBG->SetPos( VEC2(bx1 - 4, by1 - 4) );
		m_SelectBG->SetSize(VEC2(BOX_W * 8 + 8, 50 + 8));
		m_SelectBG->SetColor(0x40ffffff);
		AddpTask(m_SelectBG);
		GRPLST_INSERT(m_SelectBG);

		m_Select = std::make_shared < PrmRect > ();
		m_Select->SetZ ( Z_MENU - 0.001f );
		m_Select->SetPos( VEC2(bx1, by1) );
		m_Select->SetSize(VEC2(BOX_W, BOX_H));
		m_Select->SetColor(0x808080ff);
		AddpTask(m_Select);
		GRPLST_INSERT(m_Select);

		m_StrCpuLevel = std::make_shared < GrpStr > ();	//CPUレベル
		m_StrCpuLevel->SetSize ( G_Font::FONT_SIZE::SIZE_30 );
		m_StrCpuLevel->SetZ ( Z_MENU - 0.001f );
		m_StrCpuLevel->SetPos( VEC2( 10 + bx0, 2 + by1) );
		m_StrCpuLevel->SetStr(U"CPUレベル");
		AddpTask(m_StrCpuLevel);
		GRPLST_INSERT(m_StrCpuLevel);


		m_aryLvStr.resize( 8 );
		for ( INT32 i = 0; i < 8; ++ i )
		{
			m_aryLvStr[i] = std::make_shared < GrpStr > ();
			m_aryLvStr[i]->SetSize ( G_Font::FONT_SIZE::SIZE_30 );
			m_aryLvStr[i]->SetZ ( Z_MENU - 0.001f );
			m_aryLvStr[i]->SetPos( VEC2( bx1 + BOX_W * i + 15, 2 + by1) );
			m_aryLvStr[i]->SetStr( U"{}"_fmt( i + 1 ) );
			AddpTask(m_aryLvStr[i]);
			GRPLST_INSERT(m_aryLvStr[i]);
		}


		m_Cursor = std::make_shared < PrmRect > ();
		m_Cursor->SetZ ( Z_MENU - 0.001f );
		m_Cursor->SetPos( VEC2(bx1, by1) );
		m_Cursor->SetSize(VEC2(BOX_W, BOX_H));
		m_Cursor->SetColor(0xffff0000);
		m_Cursor->SetFrame ( T );
		AddpTask(m_Cursor);
		GRPLST_INSERT(m_Cursor);

		SetPosCursor(VEC2(bx0 - 100, by1 + by_csr));
	}


	MenuItem_CPU_LEVEL::~MenuItem_CPU_LEVEL ()
	{
	}

	void MenuItem_CPU_LEVEL::Init ()
	{
		SetActive ( F );
		TrainingMenuItem::Init ();
	}

	void MenuItem_CPU_LEVEL::Load ()
	{
		TrainingMenuItem::Load ();
	}

	void MenuItem_CPU_LEVEL::SetwpParentScene ( WP_Scene wp )
	{
		mwp_Scene = wp;
	}

	void MenuItem_CPU_LEVEL::Move ()
	{
		TrainingMenuItem::Move ();
	}

	void MenuItem_CPU_LEVEL::Do ()
	{
		//入力
		if ( CFG_PUSH_KEY_12 ( PLY_LEFT ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_move);
			if ( m_level == 0 )
			{
				m_level = 7;
			}
			else
			{
				-- m_level;
			}
			m_Cursor->SetPos( VEC2(bx1 + BOX_W * m_level, by1) );
		}
		if ( CFG_PUSH_KEY_12 ( PLY_RIGHT ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_move);
			if ( m_level == 7 )
			{
				m_level = 0;
			}
			else
			{
				++ m_level;
			}
			m_Cursor->SetPos( VEC2(bx1 + BOX_W * m_level, by1) );
		}

		//決定
		if ( CFG_PUSH_KEY_12 ( PLY_BTN0 ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
			this->SetActive(F);

			SetLevel(m_level);
			m_pParam->GetPrmResult ().m_prp_CpuLevel.Set ( m_level );

			mwp_Parent.lock()->SetActive ( T );
			mwp_Scene.lock ()->ParamReset ();
		}

		//キャンセル
		if ( CFG_PUSH_KEY_12 ( PLY_BTN1 ) )
		{
			AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
			this->SetActive(F);
			mwp_Parent.lock()->SetActive ( T );
		}
	}


	void MenuItem_CPU_LEVEL::SetActive(bool b)
	{
		TrainingMenuItem::SetActive(b);
		m_SelectBG->SetValid(b);
		m_Cursor->SetValid(b);
	}

	void MenuItem_CPU_LEVEL::SetLevel ( INT32 level )
	{
		if ( level < 0 || level > 7 )
		{
			level = 0;
		}
		m_level = level;
		m_Select->SetPos( VEC2(bx1 + BOX_W * m_level, by1) );
		m_Cursor->SetPos( VEC2(bx1 + BOX_W * m_level, by1) );
	}

	void MenuItem_CPU_LEVEL::Off()
	{
		m_StrCpuLevel->SetValid ( F );
		for ( P_GrpStr p : m_aryLvStr )
		{
			p->SetValid ( F );
		}
		m_Select->SetValid ( F );
		TrainingMenuItem::Off();
	}

	void MenuItem_CPU_LEVEL::On()
	{
		//最初の状態
		INT32 level = m_pParam->GetPrmResult().m_prp_CpuLevel.Get ();
		SetLevel ( level );

		m_StrCpuLevel->SetValid ( T );
		for ( P_GrpStr p : m_aryLvStr )
		{
			p->SetValid ( T );
		}
		m_Select->SetValid ( T );
		TrainingMenuItem::On();
	}

	//======================================================

	MenuItem_ToTitle::MenuItem_ToTitle ()
	{
		m_StrToTitle = std::make_shared < GrpStr > ();
		m_StrToTitle->SetSize ( G_Font::FONT_SIZE::SIZE_30 );
		m_StrToTitle->SetZ ( Z_MENU - 0.001f );
		m_StrToTitle->SetPos( VEC2( 10 + bx0, 2 + by2) );
		m_StrToTitle->SetStr(U"タイトルに戻る");
		AddpTask(m_StrToTitle);
		GRPLST_INSERT(m_StrToTitle);

		SetPosCursor(VEC2(bx0 - 100, by2 + by_csr));


		m_YesNoMenu = std::make_shared < YesNo_Menu > ();
		AddpTask ( m_YesNoMenu );

	}

	MenuItem_ToTitle::~MenuItem_ToTitle ()
	{
	}


	void MenuItem_ToTitle::Load ()
	{
		MenuItem::Load ();
	}

	void MenuItem_ToTitle::Move ()
	{
		MenuItem::Move ();
	}

	void MenuItem_ToTitle::Do ()
	{
	}

	void MenuItem_ToTitle::Decide ()
	{
		AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
		//確認メニュを表示
		m_YesNoMenu->On ();
	}


	void MenuItem_ToTitle::Off()
	{
		m_StrToTitle->SetValid ( F );
		TrainingMenuItem::Off();
	}

	void MenuItem_ToTitle::On()
	{
		m_StrToTitle->SetValid ( T );
		TrainingMenuItem::On();
	}

	//======================================================

	MenuItem_Return::MenuItem_Return ()
	{
		m_StrReturn = std::make_shared < GrpStr > ();
		m_StrReturn->SetSize ( G_Font::FONT_SIZE::SIZE_30 );
		m_StrReturn->SetZ ( Z_MENU - 0.001f );
		m_StrReturn->SetPos( VEC2( 10 + bx0, 2 + by3) );
		m_StrReturn->SetStr(U"ゲームに戻る");
		AddpTask(m_StrReturn);
		GRPLST_INSERT(m_StrReturn);

		SetPosCursor(VEC2(bx0 - 100, by3 + by_csr));
	}

	MenuItem_Return::~MenuItem_Return ()
	{
	}


	void MenuItem_Return::Load ()
	{
		TrainingMenuItem::Load ();
	}

	void MenuItem_Return::Move ()
	{
		TrainingMenuItem::Move ();
	}

	void MenuItem_Return::Do ()
	{
	}

	void MenuItem_Return::Decide ()
	{
		AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
		//決定
		//親と自身をオフにする
		this->SetActive(F);
		mwp_Parent.lock()->Off ();
		mwp_Parent.lock()->SetStopMain ( F );
		mwp_Parent.lock()->SetActive ( F );
	}

	void MenuItem_Return::Off()
	{
		m_StrReturn->SetValid ( F );
		TrainingMenuItem::Off();
	}

	void MenuItem_Return::On()
	{
		m_StrReturn->SetValid ( T );
		TrainingMenuItem::On();
	}


}	//namespace GAME

