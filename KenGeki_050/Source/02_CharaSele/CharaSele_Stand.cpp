//=================================================================================================
//
//	CharaSele_Stand
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Stand.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{


	constexpr std::array < CHARA_NAME, CHARA_NAME_COUNT > chara_name =
	{
		CHARA_OUKA,			//鵯桜花
		CHARA_SAE,			//巴紗絵
		CHARA_RETSUDOU,		//烈火烈堂
		CHARA_GABADARUGA,	//ギャバダルガ
		CHARA_FERARIA,		//フェラリア
		CHARA_TSUKIHIBOSHI,	//月日星
		CHARA_REINA,		//レイナ
		CHARA_KISHI,		//忘れられた英雄
		CHARA_DOXTUKA,		//ドッカードボル
		CHARA_ENEMY_ZERO,	//エネミーゼロ
	};	//10個



	CharaSele_Stand::CharaSele_Stand ()
	{
		//グラフィック
		m_grp = std::make_shared < CharaSele_Grp > ();

		//各キャラ
		map_ChGrp.resize ( CHARA_NAME_COUNT );

		size_t index = 0;
		for ( CHARA_NAME name : chara_name )
		{
			P_ChSl_GrpSet p = std::make_shared < CharaSele_GrpSet > ();
			map_ChGrp[ static_cast < size_t > ( index )] = p;
			p->SetName ( name );
			p->Off ();
			p->SetNameTheta ( ARY_NAME_THETA [ index ] );
			AddpTask ( p );

			++ index;
		}

		//最初の選択
		m_selectedIndex = 0;
		selectedCh = map_ChGrp [ m_selectedIndex ];
		selectedCh->On ();
	}

	CharaSele_Stand::~CharaSele_Stand ()
	{
	}

	void CharaSele_Stand::Load ()
	{
		m_grp->Load ();
		for ( P_ChSl_GrpSet p : map_ChGrp )
		{
			p->SetpGrp ( m_grp );
		}

		TASK_VEC::Load ();
	}

	void CharaSele_Stand::Init ()
	{
		//位置の設定
		if ( PLAYER_ID_1 == m_id )
		{
		}
		else if ( PLAYER_ID_2 == m_id )
		{
		}
		TASK_VEC::Init ();
	}

	void CharaSele_Stand::Move ()
	{
#if 0

		//---------------------------------------------------
		//キャラ立絵(大) 位置
		if ( 0 < m_dx )
		{
			m_dx -= m_vx;
		}
		else
		{
			m_dx = 0;
		}

		m_ch_stand_large->SetPos ( VEC2 { m_base_x + m_dx, m_base_y } );

		//---------------------------------------------------
		//名前角度
#if 0
		if ( CFG_IS_KEY ( P1_UP ) )
		{
			m_angle += m_omega;
		}
		if ( CFG_IS_KEY ( P1_DOWN ) )
		{
			m_angle -= m_omega;
		}
		m_ch_name->SetRadian ( m_angle );
#endif // 0

		//1つ目
		m_angle0 += m_omega;	//負数方向

		if ( m_angle0 < - m_theta )
		{
			m_angle0 += 2 * m_theta;	//２周めはtheta2つ分戻ってからスタート
		}
		m_ch_name->SetRadian ( m_angle0 );

		//２つ目
		m_angle1 += m_omega;	//負数方向
		P_Ob pob = m_ch_name->GetpObject(1);
		if ( m_angle1 < - m_theta )
		{
			m_angle1 += 2 * m_theta;	//２周めはtheta2つ分戻ってからスタート
		}
		pob->SetRadian ( m_angle1 );

		DBGOUT_WND_F ( DBGOUT_0, U"theta0 = {}"_fmt( m_angle0 ) );
		DBGOUT_WND_F ( DBGOUT_1, U"theta1 = {}"_fmt( m_angle1 ) );

#endif // 0

		//---------------------------------------------------
		TASK_VEC::Move ();
	}


	void CharaSele_Stand::Next_Chara ()
	{
#if 0

		//現在値を取得してから
		CHARA_NAME name = selectedCh->GetName ();

		//サーチ
		int nextIndex = 0;
		for ( int i = 0; i < CHARA_NAME_COUNT; ++ i )
		{
			P_ChSl_GrpSet p = map_ChGrp [ i ];
			if ( name == p->GetName () )
			{
				if ( i + 1 == CHARA_NAME_COUNT )
				{
					nextIndex = 0;
				}
				else
				{
					nextIndex = i + 1;
				}
				break;
			}
		}

#endif // 0
//		const int N = 6;
		const int N = 5;

		if ( N <= m_selectedIndex + 1 )
		{
			m_selectedIndex = 0;
		}
		else
		{
			++ m_selectedIndex;
		}

		//全部オフしてから、選択のみをオン
		GrpAll_Off ();
		selectedCh = map_ChGrp [ m_selectedIndex ];
		selectedCh->On ();
	}

	void CharaSele_Stand::Prev_Chara ()
	{
#if 0

		CHARA_NAME name = selectedCh->GetName ();

		int prevIndex = 0;
//		int CHARA_NUM = CHARA_NAME_COUNT - 1;
		int CHARA_NUM = 6;
		for ( int i = CHARA_NUM - 1; i >= 0; -- i )
		{
			P_ChSl_GrpSet p = map_ChGrp [ i ];
			if ( name == p->GetName () )
			{
				if ( i - 1 < 0 )
				{
					prevIndex = CHARA_NUM - 1;
				}
				else
				{
					prevIndex = i - 1;
				}
				break;
			}
		}

#endif // 0
//		const int N = 6;
		const int N = 5;

		if ( m_selectedIndex < 1 )
		{
			m_selectedIndex = N - 1;
		}
		else
		{
			-- m_selectedIndex;
		}


		//全部オフしてから、選択のみをオン
		GrpAll_Off ();
		selectedCh = map_ChGrp [ m_selectedIndex ];
		selectedCh->On ();

	}

	void CharaSele_Stand::Next_Color ()
	{
		selectedCh->NextColor ();
	}

	void CharaSele_Stand::Prev_Color ()
	{
		selectedCh->PrevColor ();
	}

	void CharaSele_Stand::GrpAll_Off ()
	{
		for ( P_ChSl_GrpSet p : map_ChGrp )
		{
			p->Off ();
		}
	}

#pragma region CONST

#pragma endregion


}	//namespace GAME

