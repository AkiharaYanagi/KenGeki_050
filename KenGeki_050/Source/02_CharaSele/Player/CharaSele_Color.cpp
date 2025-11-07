//=================================================================================================
//
//	CharaSele_Color
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Color.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_Color::CharaSele_Color ()
	{
		//カラー番号表示
		m_color = std::make_shared < GameGraphic > ();
		m_color->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Color1.png" );
		AddpTask ( m_color );
		GRPLST_INSERT ( m_color );
		m_color->AddTexture_FromArchive ( U"CharaSele\\CharaSele_Color2.png" );

		//矢印
		m_arrow = std::make_shared < GameGraphic > ();
		m_arrow->AddTexture_FromArchive ( U"CharaSele\\Arrow.png" );
		AddpTask ( m_arrow );
		GRPLST_INSERT ( m_arrow );

		//矢印にオブジェクトを増やす
		m_arrow->AddObject ();


		//値
		m_color_bx = 435;	//基準位置(端からの距離)

		m_arrow_bx = m_color_bx + 40;	//基準位置
		m_arrow_by = 960 - 52;

		m_arrow_frq = 0.15f;
		m_arrow_w = 3.f;
	}

	CharaSele_Color::~CharaSele_Color ()
	{
	}

	void CharaSele_Color::Load ()
	{
		TASK_VEC::Load ();
	}

	void CharaSele_Color::SetPlayerID ( PLAYER_ID id )
	{
		m_id = id;
	}

	void CharaSele_Color::Init ()
	{
		float cx = m_color_bx;
		float ax = m_arrow_bx;
		float y = m_arrow_by;
		float w = 96;
		float p = 120;

		if ( PLAYER_ID_1 == m_id )
		{
			//P1はテクスチャ向き逆(文字はそのまま)
			m_color->SetPos ( VEC2( 0 + cx - w, y + 0 ) );
			//m_color->SetScaling ( -1, 1 );	//逆向

			m_arrow->SetPos ( VEC2( 0 + ax, y ) );
			m_arrow->SetScaling ( -1, 1 );	//逆向

			P_Ob pob = m_arrow->GetpObject ( 1 );
			pob->SetScaling ( 1, 1 );	//逆の逆で正
			pob->SetPos ( VEC2( ax - p, y + 2 ) );
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			//P2がテクスチャ向き正
			m_color->SetPos ( VEC2( 1280 - cx, y + 0 ) );

			m_arrow->SetPos ( VEC2( 1280 - ax, y ) );
			P_Ob pob = m_arrow->GetpObject ( 1 );
			pob->SetScaling ( -1, 1 );	//逆
			pob->SetPos ( VEC2( 1280 - ax + p, y + 2 ) );
		}

		TASK_VEC::Init ();
	}

	void CharaSele_Color::Move ()
	{
		//時間
		const float MAX_TIME = 10000.f;
		++ m_arrow_time;
		if ( m_arrow_time >= MAX_TIME ) { m_arrow_time = 0; }

		//角度と位置
		float period = D3DX_PI_TWICE / m_arrow_frq;
		float wrappedTime = fmod ( m_arrow_time, period );
		float dx = m_arrow_w * sin ( m_arrow_frq * wrappedTime );
		DBGOUT_WND_F ( DBGOUT_2, U"arrow_x = {}"_fmt( dx ) );

		float bx = m_arrow_bx;
		float by = m_arrow_by;
		float p = 160;
		P_Ob pob = m_arrow->GetpObject ( 1 );

		//プレイヤ別
		if ( PLAYER_ID_1 == m_id )
		{
			//位置に設定
			m_arrow->SetPos ( VEC2 ( bx - dx, by ) );
			pob->SetPos ( VEC2 ( bx - p + dx, by ) );
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			//位置に設定
			m_arrow->SetPos ( VEC2( 1280 - bx + dx, by ) );
			pob->SetPos ( VEC2( 1280 - bx + p - dx, by ) );
		}

		TASK_VEC::Move ();
	}


	void CharaSele_Color::Next ()
	{
		if ( 0 == m_color->GetIndexTexture () )
		{
			m_color->SetIndexTexture ( 1 );
		}
		else if ( 1 == m_color->GetIndexTexture () )
		{
			m_color->SetIndexTexture ( 0 );
		}
	}

	void CharaSele_Color::Prev ()
	{
		if ( 0 == m_color->GetIndexTexture () )
		{
			m_color->SetIndexTexture ( 1 );
		}
		else if ( 1 == m_color->GetIndexTexture () )
		{
			m_color->SetIndexTexture ( 0 );
		}
	}


}	//namespace GAME

