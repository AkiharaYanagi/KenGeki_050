//=================================================================================================
//
//	TestMenuItem
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TrainingMenuItem.h"

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
		constexpr float bx0 = 400;
		constexpr float bx1 = bx0 + 200;
		constexpr float by0 = 300;
		constexpr float by1 = 400;
		constexpr float by2 = 500;
		constexpr float by3 = 600;

		constexpr float bx_on = bx1;
		constexpr float bx_of = bx1 + 100;

		constexpr float bx_csr = bx0 - 100;
		constexpr float by_csr = 15;
	}
	//======================================================


	MenuItem_Taikou::MenuItem_Taikou ()
	{

		m_SelectBG = std::make_shared < PrmRect >();
		m_SelectBG->SetZ ( Z_MENU - 0.001f + 0.0001f );
		m_SelectBG->SetPos( VEC2(bx1 - 4, by0 - 4) );
		m_SelectBG->SetSize(VEC2(200 + 8, 50 + 8));
		m_SelectBG->SetColor(0x40ffffff);
		AddpTask(m_SelectBG);
		GRPLST_INSERT(m_SelectBG);

		m_Select = std::make_shared < PrmRect >();
		m_Select->SetZ ( Z_MENU - 0.001f );
		m_Select->SetPos( VEC2(bx1, by0) );
		m_Select->SetSize(VEC2(100, 50));
		m_Select->SetColor(0x808080ff);
		AddpTask(m_Select);
		GRPLST_INSERT(m_Select);

		m_StrTaikou = std::make_shared < GrpStr >();
		m_StrTaikou->SetSize ( G_Font::FONT_SIZE::SIZE_30 );
		m_StrTaikou->SetZ ( Z_MENU - 0.001f );
		m_StrTaikou->SetPos( VEC2( 10 + bx0, 2 + by0) );
		m_StrTaikou->SetStr(U"剣撃対抗");
		AddpTask(m_StrTaikou);
		GRPLST_INSERT(m_StrTaikou);

		m_StrOn = std::make_shared < GrpStr >();
		m_StrOn->SetSize ( G_Font::FONT_SIZE::SIZE_30 );
		m_StrOn->SetZ ( Z_MENU - 0.001f );
		m_StrOn->SetPos( VEC2( 10 + bx_on, 2 + by0) );
		m_StrOn->SetStr(U"ON");
		AddpTask(m_StrOn);
		GRPLST_INSERT(m_StrOn);

		m_StrOff = std::make_shared < GrpStr >();
		m_StrOff->SetSize ( G_Font::FONT_SIZE::SIZE_30 );
		m_StrOff->SetZ ( Z_MENU - 0.001f );
		m_StrOff->SetPos( VEC2( 10 + bx_of, 2 + by0) );
		m_StrOff->SetStr(U" OFF");
		AddpTask(m_StrOff);
		GRPLST_INSERT(m_StrOff);

		m_Cursor = std::make_shared < PrmRect >();
		m_Cursor->SetZ ( Z_MENU - 0.001f );
		m_Cursor->SetPos( VEC2(bx1, by0) );
		m_Cursor->SetSize(VEC2(100, 50));
		m_Cursor->SetColor(0xffff0000);
		m_Cursor->SetFrame ( T );
		AddpTask(m_Cursor);
		GRPLST_INSERT(m_Cursor);


		SetPosCursor(VEC2(bx_csr, by0 + by_csr));
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
		if ( m_state )
		{
			m_Select->SetPos( VEC2(bx_on, by0) );
		}
		else
		{
			m_Select->SetPos( VEC2(bx_of, by0) );
		}

		MenuItem::Move ();
	}

	void MenuItem_Taikou::Do() 
	{
		//入力
		if ( CFG_PUSH_KEY_12 ( PLY_LEFT ) )
		{
			m_Cursor->SetPos( VEC2(bx_on, by0) );
		}
		if ( CFG_PUSH_KEY_12 ( PLY_RIGHT ) )
		{
			m_Cursor->SetPos( VEC2(bx_of, by0) );
		}

		//決定
		if ( CFG_PUSH_KEY_12 ( PLY_BTN0 ) )
		{
			if ( m_Cursor->GetPos ().x == bx_on )
			{
				m_state = T;
			}
			else
			{
				m_state = F;
			}

			this->SetActive(F);
			mwp_Parent.lock()->SetActive ( T );
		}

		//キャンセル
		if ( CFG_PUSH_KEY_12 ( PLY_BTN1 ) )
		{
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
		m_StrTaikou->SetValid ( F );
		m_StrOn->SetValid ( F );
		m_StrOff->SetValid ( F );
		m_Select->SetValid ( F );
		TrainingMenuItem::Off();
	}

	void MenuItem_Taikou::On()
	{
		m_StrTaikou->SetValid ( T );
		m_StrOn->SetValid ( T );
		m_StrOff->SetValid ( T );
		m_Select->SetValid ( T );
		TrainingMenuItem::On();
	}


	//======================================================
	constexpr float BOX_W = 50;
	constexpr float BOX_H = 50;


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

	void MenuItem_CPU_LEVEL::Move ()
	{
		TrainingMenuItem::Move ();
	}

	void MenuItem_CPU_LEVEL::Do ()
	{
		//入力
		if ( CFG_PUSH_KEY ( P1_LEFT ) )
		{
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
		if ( CFG_PUSH_KEY ( P1_RIGHT ) )
		{
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
		if ( CFG_PUSH_KEY ( P1_BTN0 ) )
		{
			this->SetActive(F);
			mwp_Parent.lock()->SetActive ( T );
			SetLevel(m_level);
		}

		//キャンセル
		if ( CFG_PUSH_KEY ( P1_BTN1 ) )
		{
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
		m_StrCpuLevel->SetValid ( T );
		for ( P_GrpStr p : m_aryLvStr )
		{
			p->SetValid ( T );
		}
		m_Select->SetValid ( T );
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


}	//namespace GAME

