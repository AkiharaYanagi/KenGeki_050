//=================================================================================================
//
// DispBreak ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispBreak.h"
#include "DispChara_Const.h"
#include "03_FtgMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const float DispBreak::BG_POS_X_1P = 30.f;
	const float DispBreak::BG_POS_X_2P = 1280 - 300 -BG_POS_X_1P;
	const float DispBreak::BG_POS_Y = 835.f;

	const float DispBreak::HND_POS_X_1P = 72.f + 8.f;
	const float DispBreak::HND_POS_X_2P = 1280 - HND_POS_X_1P;
	const float DispBreak::HND_POS_Y = BG_POS_Y - 3;

	const float DispBreak::HND_ROT_X = 8.f;
	const float DispBreak::HND_ROT_Y = 64.f;

//	const float DispBreak::Z_GAUGE_ACCEL = Z_EFF + 0.08f;	//他ゲージより後ろ
	const float DispBreak::Z_GAUGE_ACCEL = Z_EFF;



	DispBreak::DispBreak ()
	{
		//-----------------------------------------
		//円形表示
		m_ccl = std::make_shared < GamePrimitiveCircle > ();
		m_ccl->SetOuterThickness ( 20 );
		m_ccl->SetZ ( Z_EFF );
		m_ccl->SetValid ( F );
		AddpTask ( m_ccl );
		GRPLST_INSERT ( m_ccl );

		//-----------------------------------------
		//値
		m_strValue = std::make_shared < GrpStr > ();
		m_strValue->SetSize ( G_Font::SIZE_40 );
		m_strValue->SetZ ( Z_EFF - 0.01f );
		m_strValue->SetValid ( T );
		AddpTask ( m_strValue );
		GRPLST_INSERT ( m_strValue );
	}

	DispBreak::~DispBreak ()
	{
	}

	void DispBreak::LoadPlayer ( PLAYER_ID playerID )
	{
		m_playerID = playerID;

		//プレイヤー別初期化位置
		if ( PLAYER_ID_1 == m_playerID )
		{
			m_strValue->SetPos ( VEC2 ( BG_POS_X_1P, 400 ) );
			m_strValue->SetStr ( U"P1_Break" );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			m_strValue->SetPos ( VEC2 ( 1000, 400 ) );
			m_strValue->SetStr ( U"P2_Break" );
		}
	}

	void DispBreak::Update ( const BtlParam & btlPrm )
	{
		//超必殺のときOFF
		
		//非稼働状態は非表示
		if ( ! btlPrm.GetbBreak () )
		{
			int32_t value = btlPrm.GetBreak ();
			m_strValue->SetStr ( U"{}"_fmt( value ) );
			m_ccl->SetValid ( F );
			return; 
		}


		//表示
		m_ccl->SetValid ( T );

		//値
		int32_t value = btlPrm.GetBreak ();
		m_strValue->SetStr ( U"{}"_fmt( value ) );


		float bx = G_BASE_POS ().x;	//基準位置

		//キャラ位置から円形
		const float r = 250.f;
		VEC2 pos = btlPrm.GetPos();
		float x = pos.x + bx;
		
		//画面端で補正
		const float margin = r + 20.f;
		if ( x < margin )
		{
			x = margin;
		}
		if ( x > 1280 - margin )
		{
			x = 1280 - margin;
		}
		
		m_ccl->SetCircle ( s3d::Circle { x, pos.y - 250, r } );


		//色
		if ( btlPrm.GetbBreakOn () ) //初回
		{
			m_ccl->SetColor0 ( _CLR( 1.0f, 1.0f, 1.0f, 1.0f ) );
			m_ccl->SetColor1 ( _CLR( 1.0f, 1.0f, 1.0f, 1.0f ) );
		}
		else
		{
			if ( value < 0 )
			{
				m_ccl->SetColor0 ( _CLR( 1.0f, 1.0f, 1.0f, 0.5f ) );
				m_ccl->SetColor1 ( _CLR( 1.0f, 0.5f, 0.5f, 0.8f ) );
			}
			else
			{
				m_ccl->SetColor0 ( _CLR( 0.8f, 0.8f, 1.0f, 0.5f ) );
				m_ccl->SetColor1 ( _CLR( 0.5f, 0.5f, 1.0f, 0.8f ) );
			}
		}

		//値から角度に変換
		double theta = MapRange ( value, 0, 10000, 0_deg, 360_deg );

		//角度を反映
		
		//ブレイク状態
		if ( value < 0 )
		{
			//向きで反転
			if ( btlPrm.GetDirRight () )
			{
				m_ccl->SetStartAngle ( 360_deg - theta );
				m_ccl->SetAngle ( theta );
			}
			else
			{
				m_ccl->SetStartAngle ( 0 );
				m_ccl->SetAngle ( theta );
			}
		}
		else //通常状態
		{
			//向きで反転
			if ( btlPrm.GetDirRight () )
			{
				m_ccl->SetStartAngle ( 360_deg - theta );
				m_ccl->SetAngle ( theta );
			}
			else
			{
				m_ccl->SetStartAngle ( 0 );
				m_ccl->SetAngle ( theta );
			}
		}
	}

	void DispBreak::On ()
	{
	}

	void DispBreak::Off ()
	{
	}



}	//namespace GAME

