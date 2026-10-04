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

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const float DispBreak::BG_POS_X_1P = 30.f;
	const float DispBreak::BG_POS_X_2P = 1280 - BG_POS_X_1P;
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
		//ブレイクゲージ
		m_gaugeBreak = std::make_shared < GameGraphic > ();
		m_gaugeBreak->AddTexture_FromArchive ( U"brake_gauge.png" );
		m_gaugeBreak->SetZ ( Z_GAUGE_ACCEL );
		m_gaugeBreak->SetScalingCenter ( VEC2 ( 0, 128.f ) );
		AddpTask ( m_gaugeBreak );
		GRPLST_INSERT ( m_gaugeBreak );
	}

	DispBreak::~DispBreak ()
	{
	}

	void DispBreak::LoadPlayer ( PLAYER_ID playerID )
	{
		m_playerID = playerID;

		//プレイヤー別初期化位置
		if ( PLAYER_ID_1 == playerID )
		{
			m_gaugeBreak->SetPos ( BG_POS_X_1P, BG_POS_Y );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_gaugeBreak->SetScaling ( -1.f, 1.f );
			m_gaugeBreak->SetPos ( BG_POS_X_2P, BG_POS_Y );
		}
	}

	void DispBreak::Update ( int value )
	{
	}

	void DispBreak::On ()
	{
		m_gaugeBreak->SetValid ( T );
	}

	void DispBreak::Off ()
	{
		m_gaugeBreak->SetValid ( F );
	}



}	//namespace GAME

