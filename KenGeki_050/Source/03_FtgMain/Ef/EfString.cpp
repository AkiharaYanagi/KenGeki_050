//=================================================================================================
//
//	EfString ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "EfString.h"
#include "../G_Ftg.h"
#include "../../90_GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	EfString::EfString ()
	{
#if 0
		m_grp = std::make_shared < GameGraphic > ();
		m_grp->AddTexture_FromArchive ( U"Chara\\Tsukihibosi\\zero.png" );
		AddpTask ( m_grp );
//		GRPLST_INSERT ( m_grp );
#endif // 0

		m_ef_zero = std::make_shared < GameGraphic > ();
		m_ef_zero->AddTexture_FromArchive ( U"Chara\\Tsukihibosi\\zero.png" );
		m_ef_zero->SetPos ( VEC2 ( 1280 - 320, 0 ) );
		m_ef_zero->SetZ ( Z_EFF );
		m_ef_zero->SetScalingCenter ( VEC2 ( 320, 0 ) );
		m_ef_zero->SetScaling ( VEC2 ( 2, 2 ) );
		AddpTask ( m_ef_zero );
		GRPLST_INSERT ( m_ef_zero );
		//m_ef_zero->On ();

		m_ef_siki = std::make_shared < GameGraphic > ();
		m_ef_siki->AddTexture_FromArchive ( U"Chara\\Tsukihibosi\\siki.png" );
		m_ef_siki->SetPos ( VEC2 ( 1280 - 320, 960 - 320 ) );
		m_ef_siki->SetZ ( Z_EFF );
		m_ef_siki->SetScalingCenter ( VEC2 ( 320, 320 ) );
		m_ef_siki->SetScaling ( VEC2 ( 2, 2 ) );
		AddpTask ( m_ef_siki );
		GRPLST_INSERT ( m_ef_siki );
		//m_ef_siki->On ();

		m_ef_ninn = std::make_shared < GameGraphic > ();
		m_ef_ninn->AddTexture_FromArchive ( U"Chara\\Tsukihibosi\\ninn.png" );
		m_ef_ninn->SetPos ( VEC2 ( 0, 0 ) );
		m_ef_ninn->SetZ ( Z_EFF );
		m_ef_ninn->SetScalingCenter ( VEC2 ( 0, 0 ) );
		m_ef_ninn->SetScaling ( VEC2 ( 2, 2 ) );
		AddpTask ( m_ef_ninn );
		GRPLST_INSERT ( m_ef_ninn );
		//m_ef_ninn->On ();

		m_ef_jutu = std::make_shared < GameGraphic > ();
		m_ef_jutu->AddTexture_FromArchive ( U"Chara\\Tsukihibosi\\jutu.png" );
		m_ef_jutu->SetPos ( VEC2 ( 0, 960 - 320 ) );
		m_ef_jutu->SetZ ( Z_EFF );
		m_ef_jutu->SetScalingCenter ( VEC2 ( 0, 320 ) );
		m_ef_jutu->SetScaling ( VEC2 ( 2, 2 ) );
		AddpTask ( m_ef_jutu );
		GRPLST_INSERT ( m_ef_jutu );
		//m_ef_jutu->On ();

		//On ();
		Off ();
	}

	EfString::~EfString ()
	{
	}

	void EfString::Load ()
	{
		TASK_VEC::Load ();
	}

	void EfString::Init ()
	{
		m_timer = 0;
		for ( int32 i = 0; i < 4; ++ i )
		{
			m_scaling [ i ] = 2.f;
		}
		m_ef_zero->SetScaling ( m_scaling [ 0 ], m_scaling [ 0 ] );
		m_ef_siki->SetScaling ( m_scaling [ 1 ], m_scaling [ 1 ] );
		m_ef_ninn->SetScaling ( m_scaling [ 2 ], m_scaling [ 2 ] );
		m_ef_jutu->SetScaling ( m_scaling [ 3 ], m_scaling [ 3 ] );

		Off ();
	}

	void EfString::Move ()
	{
		//停止時
		if ( m_timer == 0 )
		{
			return;
		}

		//終了条件
		if ( m_timer > 60 )
		{
			Off ();
			m_timer = 0;
			return;
		}

		//スタート時
		switch ( m_timer )
		{
		case  1: m_ef_zero->SetValid ( T ); break;
		case  7: m_ef_siki->SetValid ( T ); break;
		case 13: m_ef_ninn->SetValid ( T ); break;
		case 19: m_ef_jutu->SetValid ( T ); break;
		default: break;
		}

		switch ( m_timer )
		{
		case  1: SE(); break;
		case 10: SE(); break;
		case 19: SE(); break;
		case 28: SE(); break;
		default: break;
		}

		//稼働チェック
		if ( m_ef_zero->GetValid() )
		{
			if ( m_scaling [ 0 ] > 1.f )
			{
				m_ef_zero->SetScaling ( m_scaling [ 0 ], m_scaling [ 0 ] );
				m_scaling [ 0 ] += -0.1f;
			}
		}

		if ( m_ef_siki->GetValid() )
		{
			if ( m_scaling [ 1 ] > 1.f )
			{
				m_ef_siki->SetScaling ( m_scaling [ 1 ], m_scaling [ 1 ] );
				m_scaling [ 1 ] += -0.1f;
			}
		}

		if ( m_ef_ninn->GetValid() )
		{
			if ( m_scaling [ 2 ] > 1.f )
			{
				m_ef_ninn->SetScaling ( m_scaling [ 2 ], m_scaling [ 2 ] );
				m_scaling [ 2 ] += -0.1f;
			}
		}

		if ( m_ef_jutu->GetValid() )
		{
			if ( m_scaling [ 3 ] > 1.f )
			{
				m_ef_jutu->SetScaling ( m_scaling [ 3 ], m_scaling [ 3 ] );
				m_scaling [ 3 ] += -0.1f;
			}
		}


		++ m_timer;

		TASK_VEC::Move ();

#if 0

		m_ef_zero->SetPos ( VEC2 ( 1280 - 320, 0 ) );
		m_ef_siki->SetPos ( VEC2 ( 1280 - 320, 960 - 320 ) );
		m_ef_ninn->SetPos ( VEC2 ( 0, 0 ) );
		m_ef_jutu->SetPos ( VEC2 ( 0, 960 - 320 ) );

#endif // 0
	}

	void EfString::On ()
	{
		Init ();
	}

	void EfString::Off ()
	{
		m_ef_zero->SetValid ( F );
		m_ef_siki->SetValid ( F );
		m_ef_ninn->SetValid ( F );
		m_ef_jutu->SetValid ( F );
	}

	void EfString::SE ()
	{
		AUD_PLAY_ONESHOT_SE ( SE_Btl_Kattu );
	}

}
