//=================================================================================================
//
//	CharaSele_CharaGrp
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_CharaGrp.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_CharaGrp::CharaSele_CharaGrp ()
	{
		//キャラ立ち絵（大）
		m_ch_stand_large = MakepGrp ( Z_BG - 0.01f );

		//キャラ立ち絵（小）
		m_ch_stand_small = MakepGrp ( Z_BG - 0.01f );

		//キャラ名前
		m_name = std::make_shared < CharaSele_Name > ();
		AddpTask ( m_name );


		m_base_y = 70;
		m_vx = 20;
		m_start_x = 140;
	}

	P_Grp CharaSele_CharaGrp::MakepGrp ( float z )
	{
		P_Grp p = std::make_shared < GameGraphic > ();
		p->AddTexture();	//空を１つ確保
		p->SetZ ( z );	//GRPLST_INSERT前にZ値を設定
		AddpTask ( p );
		GRPLST_INSERT ( p );
		return p;
	}

	CharaSele_CharaGrp::~CharaSele_CharaGrp ()
	{
	}

	void CharaSele_CharaGrp::SetpParam ( P_Param p )
	{
		m_pParam = p;
		m_name->SetpParam ( p );
	}

	void CharaSele_CharaGrp::Load ()
	{
		TASK_VEC::Load ();
	}

	void CharaSele_CharaGrp::Init ()
	{
		//位置の設定
		if ( PLAYER_ID_1 == m_id )
		{
			m_base_x = 0 + 700;
			m_ch_stand_large->SetPos ( m_base_x, m_base_y );
			m_ch_stand_small->SetPos ( m_base_x, 200 );

			m_ch_stand_large->SetScaling ( -1.f, 1.f );
			m_ch_stand_small->SetScaling ( -1.f, 1.f );
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			m_base_x = 1280 - 700;
			m_ch_stand_large->SetPos ( m_base_x, m_base_y );
			m_ch_stand_small->SetPos ( m_base_x, 200 );
		}
		TASK_VEC::Init ();

	}

	void CharaSele_CharaGrp::Move ()
	{
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
		if ( PLAYER_ID_1 == m_id )
		{
#if 0
			if ( CFG_IS_KEY ( P1_BTN4 ) )
			{
				m_angle0 += m_omega;
				m_angle1 += m_omega;
			}
			if ( CFG_IS_KEY ( P1_BTN5 ) )
			{
				m_angle0 -= m_omega;
				m_angle1 -= m_omega;
			}

			if ( m_angle0 > D3DX_PI )
			{
				m_angle0 -= 2 * m_theta;	//２周めはtheta2つ分戻ってからスタート
			}
			if ( m_angle1 > D3DX_PI )
			{
				m_angle1 -= 2 * m_theta;	//２周めはtheta2つ分戻ってからスタート
			}
			m_ch_name->SetRadian ( m_angle0 );
			P_Ob pob = m_ch_name->GetpObject(1);
			pob->SetRadian ( m_angle1 );
#endif // 0

			//1つ目
			m_angle0 += m_omega;	//正数方向
			if ( m_angle0 > D3DX_PI )
			{
				m_angle0 -= 2 * m_theta;	//２周めはtheta2つ分戻ってからスタート
			}

			//２つ目
			m_angle1 += m_omega;	//正数方向
			if ( m_angle1 > D3DX_PI  )
			{
				m_angle1 -= 2 * m_theta;	//２周めはtheta2つ分戻ってからスタート
			}

#if 0

			//DBGOUT_WND_F ( DBGOUT_0, U"theta0 = {}"_fmt( m_angle0 ) );
			//DBGOUT_WND_F ( DBGOUT_1, U"theta1 = {}"_fmt( m_angle1 ) );

#endif // 0
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			//1つ目
			m_angle0 += m_omega;	//負数方向
			if ( m_angle0 < - m_theta )
			{
				m_angle0 += 2 * m_theta;	//２周めはtheta2つ分戻ってからスタート
			}

			//２つ目
			m_angle1 += m_omega;	//負数方向
			if ( m_angle1 < - m_theta )
			{
				m_angle1 += 2 * m_theta;	//２周めはtheta2つ分戻ってからスタート
			}
		}
		m_ch_name->SetRadian ( m_angle0 );
		P_Ob pob = m_ch_name->GetpObject(1);
		pob->SetRadian ( m_angle1 );
#endif // 0


		TASK_VEC::Move ();
	}

#if 0


	void CharaSele_CharaGrp::SetName ( CHARA_NAME name )
	{
		m_name = name;

#if 0

		LPCUSTR filename = U"";
		switch ( m_name )
		{
		case CHARA_OUKA:		filename = U"Name\\CharaSele_Name_OUKA.png";		break;
		case CHARA_SAE:			filename = U"Name\\CharaSele_Name_SAE.png";		break;
		case CHARA_RETSUDOU:	filename = U"Name\\CharaSele_Name_RETSU.png";		break;
		case CHARA_GABADARUGA:	filename = U"Name\\CharaSele_Name_GYAVA.png";		break;
		case CHARA_FERARIA:		filename = U"Name\\CharaSele_Name_FERA.png";		break;
		case CHARA_TSUKIHIBOSHI:filename = U"Name\\CharaSele_Name_TSUKI.png";		break;
		case CHARA_REINA:		filename = U"dummy.png";		break;
		case CHARA_KISHI:		filename = U"dummy.png";		break;
		case CHARA_DOXTUKA:		filename = U"dummy.png";		break;
		case CHARA_ENEMY_ZERO:	filename = U"dummy.png";		break;
#if 0
		case CHARA_REINA:		filename = U"CharaSele_Name_REINA.png";		break;
		case CHARA_KISHI:		filename = U"CharaSele_Name_KISHI.png";		break;
		case CHARA_DOXTUKA:		filename = U"CharaSele_Name_DOX.png";		break;
		case CHARA_ENEMY_ZERO:	filename = U"CharaSele_Name_E0.png";		break;
#endif // 0
		default: break;
		}
		m_ch_name->AddTexture_FromArchive ( filename );

#endif // 0
	}



	void CharaSele_CharaGrp::SetpGrp ( P_ChSl_TxSet p )
	{
		m_ch_stand_large->AddpTexture ( p->GetpTx_FullBody ( m_name, CH_CLR_1 ) );
		m_ch_stand_large->AddpTexture ( p->GetpTx_FullBody ( m_name, CH_CLR_2 ) );

		m_ch_stand_small->AddpTexture ( p->GetpTx_Stand ( m_name, CH_CLR_1 ) );
		m_ch_stand_small->AddpTexture ( p->GetpTx_Stand ( m_name, CH_CLR_2 ) );
	}

#endif // 0

#if 0
	void CharaSele_GrpSet::On ()
	{
		m_ch_stand_large->SetValid ( T );
		m_ch_stand_small->SetValid ( T );
		m_ch_name->SetValid ( T );
	}

	void CharaSele_GrpSet::Off ()
	{
		m_ch_stand_large->SetValid ( F );
		m_ch_stand_small->SetValid ( F );
		m_ch_name->SetValid ( F );
	}
#endif // 0


	void CharaSele_CharaGrp::Assign ( CHARA_NAME name, CHARA_COLOR clr )
	{
		P_Ch_TxSet ptxSet = m_pParam->GetpChara_TxSet ();
		m_ch_stand_large->AssignpTexture( ptxSet->GetpTx_FullBody ( name, clr ) );
		m_ch_stand_small->AssignpTexture( ptxSet->GetpTx_Stand ( name, clr ) );

		//===============================================================
		//@info
		//		２つ目以降のObjectは最初のテクスチャサイズを持っていて、
		//		Draw時にサイズ０ではないとき、前のサイズ（範囲）で描画してしまう。
		// ->描画範囲を手動で０にした
		//	@todo いずれかのタイミングでサイズ０リセットする
		//===============================================================
		m_name->Assign ( name );

#if 0

		m_ch_name->AssignpTexture ( ptxSet->GetpTx_Name ( name ) );
		m_ch_name->GetpObject ( 1 )->SetRectF ( RectF { 0, 0, 0, 0 } );

		AngleInit ( name );

#endif // 0
		
#if 0
		m_theta = ARY_NAME_THETA [ static_cast < int > ( name ) ];
		m_angle1 = - m_theta;
		m_angle0 = 0;

		m_test->AssignpTexture ( m_txSet->GetpTx_Name ( name ) );
		m_test->GetpObject ( 1 )->SetRectF ( RectF { 0, 0, 0, 0 } );

#endif // 0
	}

#if 0

	void CharaSele_CharaGrp::AngleInit ( CHARA_NAME name )
	{
		//位置の設定
		if ( PLAYER_ID_1 == m_id )
		{
			m_omega = 0.01f;
			m_theta = ARY_NAME_THETA [ static_cast < int > ( name ) ];
//			m_angle0 = D3DX_PI;
			m_angle0 = D3DX_PI - m_theta;
			m_angle1 = m_angle0 - m_theta;
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			m_omega = -0.01f;
			m_theta = ARY_NAME_THETA [ static_cast < int > ( name ) ];
			m_angle0 = 0;
			m_angle1 = m_angle0 - m_theta;
		}
	}

#endif // 0

#if 0

	void CharaSele_CharaGrp::NextColor ()
	{
		if ( 0 == m_ch_stand_large->GetIndexTexture () )
		{
			m_ch_stand_large->SetIndexTexture ( CLR_1 );
			m_ch_stand_small->SetIndexTexture ( CLR_1 );
		}
		else if ( 1 == m_ch_stand_large->GetIndexTexture () )
		{
			m_ch_stand_large->SetIndexTexture ( CLR_0 );
			m_ch_stand_small->SetIndexTexture ( CLR_0 );
		}
	}

	void CharaSele_CharaGrp::PrevColor ()
	{
		if ( 0 == m_ch_stand_large->GetIndexTexture () )
		{
			m_ch_stand_large->SetIndexTexture ( CLR_1 );
			m_ch_stand_small->SetIndexTexture ( CLR_1 );
		}
		else if ( 1 == m_ch_stand_large->GetIndexTexture () )
		{
			m_ch_stand_large->SetIndexTexture ( CLR_0 );
			m_ch_stand_small->SetIndexTexture ( CLR_0 );
		}
	}


#endif // 0



}	//namespace GAME

