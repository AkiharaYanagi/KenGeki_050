//=================================================================================================
//
//	CharaSele_GrpSet
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_GrpSet.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_GrpSet::CharaSele_GrpSet ()
	{
		m_ch_stand_large = MakepGrp ();
		m_ch_stand_large->SetZ ( Z_BG - 0.01f );

		m_ch_stand_small = MakepGrp ();
		m_ch_stand_small->SetZ ( Z_BG - 0.01f );

		m_ch_name = MakepGrp ();
		m_ch_name->SetZ ( Z_EFB - 0.01f * 2 - 0.005f );

		m_ch_name->AddObject ();
		P_Ob pob = m_ch_name->GetpObject(1);
		pob->SetColor ( 0xffff0000 );

		m_base_y = 70;
		m_vx = 20;
		m_start_x = 140;

		m_theta = 1.9f;
		m_angle0 = 0;
		m_angle1 = 0 - m_theta;


	}

	P_Grp CharaSele_GrpSet::MakepGrp ()
	{
		P_Grp p = std::make_shared < GameGraphic > ();
		AddpTask ( p );
		GRPLST_INSERT ( p );
		return p;
	}

	CharaSele_GrpSet::~CharaSele_GrpSet ()
	{
	}

	void CharaSele_GrpSet::Load ()
	{
		TASK_VEC::Load ();
	}

	void CharaSele_GrpSet::Init ()
	{
		//位置の設定
		if ( PLAYER_ID_1 == m_id )
		{
			m_base_x = 0 + 700;
			m_ch_stand_large->SetPos ( m_base_x, m_base_y );
			m_ch_stand_small->SetPos ( m_base_x, 400 );
			m_ch_name->SetPos ( 0 - 0.5f - 715 / 2, 960 + 0.5f -36 - 715 / 2 );
			m_ch_name->SetRotationCenter ( VEC2 { - 0.5f + 715 / 2, 0.5f + 715 / 2 } );
			P_Ob pob = m_ch_name->GetpObject(1);
			pob->SetPos ( 0 - 0.5f - 715 / 2, 960 + 0.5f -36 - 715 / 2 );
			pob->SetRotationCenter ( VEC2 { 0.5f + 715 / 2, 0.5f + 715 / 2 } );

			m_ch_stand_large->SetScaling ( -1.f, 1.f );
			m_ch_stand_small->SetScaling ( -0.5f, 0.5f );
			m_omega = 0.01f;
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			m_base_x = 1280 - 700;
			m_ch_stand_large->SetPos ( m_base_x, m_base_y );
			m_ch_stand_small->SetPos ( m_base_x, 400 );
			m_ch_name->SetPos ( 1280 + 0.5f - 715 / 2, 960 + 0.5f -36 - 715 / 2 );
			m_ch_name->SetRotationCenter ( VEC2 { 0.5f + 715 / 2, 0.5f + 715 / 2 } );
			P_Ob pob = m_ch_name->GetpObject(1);
			pob->SetPos ( 1280 + 0.5f - 715 / 2, 960 + 0.5f -36 - 715 / 2 );
			pob->SetRotationCenter ( VEC2 { 0.5f + 715 / 2, 0.5f + 715 / 2 } );

			m_ch_stand_large->SetScaling ( 1.f, 1.f );
			m_ch_stand_small->SetScaling ( 0.5f, 0.5f );
			m_omega = -0.01f;
		}
		TASK_VEC::Init ();
	}

	void CharaSele_GrpSet::Move ()
	{

		if ( m_ch_name->GetValid () )
		{
			//---------------------------------------------------
			//名前角度
#if 0
			if ( CFG_IS_KEY ( P1_BTN0 ) )
			{
				m_angle0 += m_omega;
			}
			if ( CFG_IS_KEY ( P1_BTN1 ) )
			{
				m_angle0 -= m_omega;
			}
			m_ch_name->SetRadian ( m_angle0 );
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

			//DBGOUT_WND_F ( DBGOUT_0, U"theta0 = {}"_fmt( m_angle0 ) );
			//DBGOUT_WND_F ( DBGOUT_1, U"theta1 = {}"_fmt( m_angle1 ) );
		}


		TASK_VEC::Move ();
	}



	void CharaSele_GrpSet::SetName ( CHARA_NAME name )
	{
		m_name = name;
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
	}



	void CharaSele_GrpSet::SetpGrp ( P_ChSl_Grp p )
	{
		m_ch_stand_large->AddpTexture ( p->GetpTx ( m_name, CH_CLR_1 ) );
		m_ch_stand_large->AddpTexture ( p->GetpTx ( m_name, CH_CLR_2 ) );

		m_ch_stand_small->AddpTexture ( p->GetpTx ( m_name, CH_CLR_1 ) );
		m_ch_stand_small->AddpTexture ( p->GetpTx ( m_name, CH_CLR_2 ) );
	}


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

	void CharaSele_GrpSet::NextColor ()
	{
		if ( 0 == m_ch_stand_large->GetIndexTexture () )
		{
			m_ch_stand_large->SetIndexTexture ( 1 );
			m_ch_stand_small->SetIndexTexture ( 1 );
		}
		else if ( 1 == m_ch_stand_large->GetIndexTexture () )
		{
			m_ch_stand_large->SetIndexTexture ( 0 );
			m_ch_stand_small->SetIndexTexture ( 0 );
		}
	}

	void CharaSele_GrpSet::PrevColor ()
	{
		if ( 0 == m_ch_stand_large->GetIndexTexture () )
		{
			m_ch_stand_large->SetIndexTexture ( 1 );
			m_ch_stand_small->SetIndexTexture ( 1 );
		}
		else if ( 1 == m_ch_stand_large->GetIndexTexture () )
		{
			m_ch_stand_large->SetIndexTexture ( 0 );
			m_ch_stand_small->SetIndexTexture ( 0 );
		}
	}




}	//namespace GAME

