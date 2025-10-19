//=================================================================================================
//
//	DispGaugeテスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispGauge.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{


	DispGauge::DispGauge ()
	{
		//総合ゲージ背景
		m_gauge_all_bg = std::make_shared < GameGraphic > ();
		m_gauge_all_bg->AddTexture_FromArchive ( U"Battle\\gauge_all.png" );
		m_gauge_all_bg->SetZ ( Z_SHADOW );
		GRPLST_INSERT ( m_gauge_all_bg );
		AddpTask ( m_gauge_all_bg );

		//ライフ
 		m_life_value = std::make_shared < GameGraphic > ();
//		m_life_value->AddTexture_FromArchive ( U"Battle\\life_value.png" );
		m_life_value->SetZ ( Z_SHADOW - 0.01f );
		m_life_value->SetbPlgnMask ( T );		//ポリゴンマスク使用
		GRPLST_INSERT ( m_life_value );
		AddpTask ( m_life_value );

		//剣撃ゲージ
		m_stamina_value = std::make_shared < GameGraphic > ();
		//m_stamina_value->AddTexture_FromArchive ( U"Battle\\stumina_value.png" );
		m_stamina_value->SetZ ( Z_SHADOW - 0.01f );
		m_stamina_value->SetbPlgnMask ( T );		//ポリゴンマスク使用
		GRPLST_INSERT ( m_stamina_value );
		AddpTask ( m_stamina_value );

		//必殺
 		m_hissatsu_value = std::make_shared < GameGraphic > ();
//		m_hissatsu_value->AddTexture_FromArchive ( U"Battle\\life_value.png" );
		m_hissatsu_value->SetZ ( Z_SHADOW - 0.01f );
		m_hissatsu_value->SetbPlgnMask ( T );		//ポリゴンマスク使用
		GRPLST_INSERT ( m_hissatsu_value );
		AddpTask ( m_hissatsu_value );

		//アクセル
 		m_accel_value = std::make_shared < GameGraphic > ();
//		m_accel_value->AddTexture_FromArchive ( U"Battle\\life_value.png" );
		m_accel_value->SetZ ( Z_SHADOW - 0.01f );
		m_accel_value->SetbPlgnMask ( T );		//ポリゴンマスク使用
		GRPLST_INSERT ( m_accel_value );
		AddpTask ( m_accel_value );
	}

	DispGauge::~DispGauge ()
	{
	}

	//プレイヤ側で初期化
	void DispGauge::LoadPlayer ( PLAYER_ID playerID )
	{
		m_playerID = playerID;


		//プレイヤー別初期化位置
		if (PLAYER_ID_1 == playerID)
		{
			m_gauge_all_bg->SetPos(POS_FRAME_ALL_1P);
			m_gauge_all_bg->SetScaling ( -1.f, 1.f );


			//2pが正方向なので水平反転
			//画像からイメージを作成し、それを反転してからテクスチャを作成する

			//-----------------------------------------------------------------
			//ライフ
			m_life_value->SetPos ( POS_LIFE_VALUE_1P );
			//Size ( 320, 20 ) //上辺310
			//const VEC2 DispFrontEnd_all::POS_LIFE_VALUE_1P ( WND_CNT - 151, 62 );
#if 0
			double x0 = 640 - 151 - 10 - 310;	//169
			double x1 = 640 - 151 - 10;			//479
			double x2 = 640 - 151;				//489
			double x3 = 640 - 151 - 310;		//179
#endif // 0
			s3d::Array < s3d::Vec2 > aryVec_life{ {169, 62}, {479, 62}, {489, 82}, {179, 82} };
			m_life_mask = std::make_shared < s3d::Polygon > ( aryVec_life );
			m_life_value->SetPosInMask ( VEC2 (169, 62) );
			m_life_value->SetpPolygon ( m_life_mask );
			m_life_value->AddTexture_FromArchive_mrr ( U"Battle\\life_value.png" );

			//-----------------------------------------------------------------
			//剣撃ゲージ
			//Size ( 309, 16 ) //上辺299
			//const VEC2 DispFrontEnd_all::POS_STAMINA_VALUE_1P ( WND_CNT - 141, 86 );
#if 0
			double x0 = 640 - 141 - 10 - 299;	//179
			double x1 = 640 - 141 - 10;			//489
			double x2 = 640 - 141;				//499
			double x3 = 640 - 141 - 299;		//189
#endif // 0
			s3d::Array < s3d::Vec2 > aryVec_stamina{ {179, 86}, {489 , 86}, {499, 102}, {189, 102} };
			m_stamina_mask = std::make_shared < s3d::Polygon > ( aryVec_stamina );
			m_stamina_value->SetPosInMask ( VEC2 (189, 86) );
			m_stamina_value->SetpPolygon ( m_stamina_mask );
			m_stamina_value->AddTexture_FromArchive_mrr ( U"Battle\\stumina_value.png" );


			//-----------------------------------------------------------------
			//超必殺技ゲージ
			//Size ( 202, 32 )
			//const VEC2 DispFrontEnd_all::POS_HISSATSU_VALUE_1P ( WND_CNT - 243, 105 );
#if 0
			double x0 = 640 - 243 - 10 - 192;	//195
			double x1 = 640 - 243 - 10;			//387
			double x2 = 640 - 243;				//397
			double x3 = 640 - 243 - 192;		//205
#endif // 0
			s3d::Array < s3d::Vec2 > aryVec_hissatsu{ {195, 105}, {387, 105}, {397, 137}, {205, 137} };
			m_hissatsu_mask = std::make_shared < s3d::Polygon > ( aryVec_hissatsu );
			m_hissatsu_value->SetPosInMask ( VEC2 (195, 105) );
			m_hissatsu_value->SetpPolygon ( m_hissatsu_mask );
			m_hissatsu_value->AddTexture_FromArchive_mrr ( U"Battle\\hissatsu_value.png" );

			//-----------------------------------------------------------------
			//アクセルゲージ
			//Size ( 80, 139 )
			//const VEC2 DispGauge::POS_ACCEL_VALUE_1P ( 0 - 3, 27 ); //86-80
			double r = 220;
			double x0 = 0;
			double y0 = 27 + 139;
			double x1 = x0 - r;
			double y1 = y0 - r;
			double x2 = x0 - r;
			double y2 = y0;
			s3d::Array < s3d::Vec2 > aryVec_accel{ {x0, y0}, {x2, y2}, {x1, y1} };
			m_accel_mask = std::make_shared < s3d::Polygon > ( aryVec_accel );
			m_accel_value->SetPosInMask ( POS_ACCEL_VALUE_1P );
			m_accel_value->SetpPolygon ( m_accel_mask );
			m_accel_value->AddTexture_FromArchive_mrr ( U"Battle\\accel_value.png" );
//			m_accel_value->SetPos ( POS_ACCEL_VALUE_1P );
		}
		else if (PLAYER_ID_2 == playerID)
		{
			m_gauge_all_bg->SetPos(POS_FRAME_ALL_2P);


			//-----------------------------------------------------------------
			//ライフ
			m_life_value->SetPos ( POS_LIFE_VALUE_2P );
			//Size ( 320, 20 ) //上辺310
			//const VEC2 DispFrontEnd_all::POS_LIFE_VALUE_2P ( WND_CNT + 151, 62 );
			s3d::Array < s3d::Vec2 > aryPlgn_life{ {801, 62}, {801 + 310, 62}, {791 + 310, 82}, {791, 82} };
			m_life_mask = std::make_shared < s3d::Polygon > ( aryPlgn_life );
			m_life_value->SetPosInMask ( VEC2 (791, 62) );
			m_life_value->SetpPolygon ( m_life_mask );
			m_life_value->AddTexture_FromArchive ( U"Battle\\life_value.png" );

			//-----------------------------------------------------------------
			//剣撃ゲージ
			//Size ( 309, 16 )
			//const VEC2 DispFrontEnd_all::POS_STAMINA_VALUE_2P ( WND_CNT + 141, 86 );
			s3d::Array < s3d::Vec2 > aryVec_stamina{ {791, 86}, {791 + 299 , 86}, {781 + 299, 102}, {781, 102} };
			m_stamina_mask = std::make_shared < s3d::Polygon > ( aryVec_stamina );
			m_stamina_value->SetPosInMask ( VEC2 (781, 86) );
			m_stamina_value->SetpPolygon ( m_stamina_mask );
			m_stamina_value->AddTexture_FromArchive ( U"Battle\\stumina_value.png" );

			//-----------------------------------------------------------------
			//超必殺技ゲージ
			//Size ( 202, 32 )
			//const VEC2 DispFrontEnd_all::POS_HISSATSU_VALUE_2P ( WND_CNT + 243, 105 );
			s3d::Array < s3d::Vec2 > aryVec_hissatsu{ {883+10, 105}, {883+202+10, 105}, {883+202-10, 137}, {883-10, 137} };
			m_hissatsu_mask = std::make_shared < s3d::Polygon > ( aryVec_hissatsu );
			m_hissatsu_value->SetPosInMask ( VEC2 (883, 105) );
			m_hissatsu_value->SetpPolygon ( m_hissatsu_mask );
			m_hissatsu_value->AddTexture_FromArchive ( U"Battle\\hissatsu_value.png" );


			//-----------------------------------------------------------------
			//アクセルゲージ
			//Size ( 80, 139 )
			//const VEC2 DispGauge::POS_ACCEL_VALUE_2P ( 1280 - 75 - 11, 27 );	//(1194,27)
			double r = 220;
			double x0 = 1194 - 80;
			double y0 = 27 + 139;
			double x1 = x0 + r;
			double y1 = y0 - r;
			double x2 = x0 + r;
			double y2 = y0;
			s3d::Array < s3d::Vec2 > aryVec_accel{ {x0, y0}, {x1, y1}, {x2, y2} };
			m_accel_mask = std::make_shared < s3d::Polygon > ( aryVec_accel );
			m_accel_value->SetPosInMask ( POS_ACCEL_VALUE_2P );
			m_accel_value->SetpPolygon ( m_accel_mask );
			m_accel_value->AddTexture_FromArchive ( U"Battle\\accel_value.png" );

		}
	}

	void DispGauge::Move()
	{
		//----------------
		//	更新
		//----------------

		//体力ゲージ
		int32 LIFE_MAX = 10000;
		m_life = m_life + m_dir_life * 50;
		if (m_life < 0) { m_dir_life = 1; }
		if (LIFE_MAX < m_life) { m_dir_life  = - 1;}


		//（ 最大幅 * 値 / 最大値 ）
		float width_life = 310.f * m_life /(float)LIFE_MAX;

		if ( PLAYER_ID_1 == m_playerID )
		{
			double x0 = 640 - 151 - 10 - width_life;
			double x1 = 640 - 151 - 10;
			double x2 = 640 - 151;
			double x3 = 640 - 151 - width_life;

			s3d::Array < s3d::Vec2 > aryVec_life{ {x0, 62}, {x1, 62}, {x2, 82}, {x3, 82} };
			m_life_mask = std::make_shared < s3d::Polygon > ( aryVec_life );
			m_life_value->SetpPolygon ( m_life_mask );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			double x1 = 801 + width_life;
			double x2 = 791 + width_life;
			s3d::Array < s3d::Vec2 > aryVec{ {801, 62}, {x1, 62}, {x2, 82}, {791, 82} };
			m_life_mask = std::make_shared < s3d::Polygon > ( aryVec );
			m_life_value->SetpPolygon ( m_life_mask );
		}


		//剣撃ゲージ
		int32 BALANCE_MAX = 10000;
		m_stamina = m_stamina + m_dir_stamina * 50;
		if (m_stamina < 0) { m_dir_stamina = 1; }
		if (BALANCE_MAX < m_stamina) { m_dir_stamina  = - 1;}

		//（ 最大幅 * 値 / 最大値 ）
		float width_stamina = 299.f * m_stamina /(float)BALANCE_MAX;

		if ( PLAYER_ID_1 == m_playerID )
		{
			double x0 = 640 - 141 - 10 - width_stamina;
			double x1 = 640 - 141 - 10;
			double x2 = 640 - 141;
			double x3 = 640 - 141 - width_stamina;
			//剣撃ゲージ
			s3d::Array < s3d::Vec2 > aryVec_stamina{ {x0, 86}, {x1, 86}, {x2, 102}, {x3, 102} };
			m_stamina_mask = std::make_shared < s3d::Polygon > ( aryVec_stamina );
			m_stamina_value->SetpPolygon ( m_stamina_mask );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			double x1 = 791 + width_stamina;
			double x2 = 781 + width_stamina;
			s3d::Array < s3d::Vec2 > aryVec_stamina{ {791, 86}, {x1, 86}, {x2, 102}, {781, 102} };
			m_stamina_mask = std::make_shared < s3d::Polygon > ( aryVec_stamina );
			m_stamina_value->SetpPolygon ( m_stamina_mask );
		}


		//超必殺技ゲージ
		int32 MANA_MAX = 10000;
		m_hissatsu = m_hissatsu + m_dir_hissatsu * 50;
		if (m_hissatsu < 0) { m_dir_hissatsu = 1; }
		if (MANA_MAX < m_stamina) { m_dir_hissatsu  = - 1;}


		//（ 最大幅 * 値 / 最大値 ）
		float width_hissatsu = (202.f - 10) * m_hissatsu /(float)MANA_MAX;

		if ( PLAYER_ID_1 == m_playerID )
		{
			double x0 = 640 - 243 - width_hissatsu - 20;		//195
			double x1 = 640 - 243 - 10;						//387
			double x2 = 640 - 243 + 10;							//397
			double x3 = 640 - 243 - width_hissatsu;		//205
			s3d::Array < s3d::Vec2 > aryVec_hissatsu{ {x0, 105}, {x1, 105}, {x2, 137}, {x3, 137} };
			m_hissatsu_mask = std::make_shared < s3d::Polygon > ( aryVec_hissatsu );
			m_hissatsu_value->SetpPolygon ( m_hissatsu_mask );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			double x0 = 640 + 243 + 10;		//893
			double x1 = 640 + 243 + width_hissatsu + 20;
			double x2 = 640 + 243 + width_hissatsu;
			double x3 = 640 + 243 - 10;		//873
			s3d::Array < s3d::Vec2 > aryVec_hissatsu{ {x0, 105}, {x1, 105}, {x2, 137}, {x3, 137} };
			m_hissatsu_mask = std::make_shared < s3d::Polygon > ( aryVec_hissatsu );
			m_hissatsu_value->SetpPolygon ( m_hissatsu_mask );
		}

		//-----------------------------------------------------------------
		//アクセルゲージ
		if ( PLAYER_ID_1 == m_playerID )
		{
			double r = 220;
			double x0 = 0 + 75 + 12 + 80;
			double y0 = 27 + 139;
			double x2 = x0 - r;
			double y2 = y0;
		
			m_accel += m_dir_accel * 100;
			if (m_accel < 0) { m_dir_accel = 1; }
			if ( 10000 < m_accel ) { m_dir_accel = -1; }

			double theta = mapRange ( m_accel, 0, 10000, 0, D3DX_PI_BY4 );
			double x = r * std::cos ( theta );
			double y = r * std::sin ( theta );

			s3d::Array < s3d::Vec2 > aryVec_accel{ {x2, y2}, {x0 - x, y0 - y}, {x0, y0} };
			m_accel_mask = std::make_shared < s3d::Polygon > ( aryVec_accel );
			m_accel_value->SetpPolygon ( m_accel_mask );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			double r = 220;
			double x0 = 1194 - 80;
			double y0 = 27 + 139;
//			double x1 = x0 + r;
//			double y1 = y0 - r;
			double x2 = x0 + r;
			double y2 = y0;
		
			m_accel += m_dir_accel * 100;
			if (m_accel < 0) { m_dir_accel = 1; }
			if ( 10000 < m_accel ) { m_dir_accel = -1; }

			double theta = mapRange ( m_accel, 0, 10000, 0, D3DX_PI_BY4 );
			double x = r * std::cos ( theta );
			double y = r * std::sin ( theta );

			s3d::Array < s3d::Vec2 > aryVec_accel{ {x0, y0}, {x0 + x, y0 - y}, {x2, y2} };
//			s3d::Array < s3d::Vec2 > aryVec_accel{ {x0, y0}, {x1, y1}, {x2, y2} };
			m_accel_mask = std::make_shared < s3d::Polygon > ( aryVec_accel );
			m_accel_value->SetpPolygon ( m_accel_mask );

#if 0
#endif // 0
		}


		TASK_VEC::Move ();
	}


	enum
	{
		WND_CNT = 640,
	};


#pragma region CONST
	//定数
	//2pが正方向, 1p側は(右端が基準点)

	//全体枠
	//Size ( 516, 172 )
	const VEC2 DispGauge::POS_FRAME_ALL_1P ( 0 + 516, 10 );
	const VEC2 DispGauge::POS_FRAME_ALL_2P ( 1280 - 516 - 0, 10 );

	//体力ゲージ
	//Size ( 320, 20 )
	const VEC2 DispGauge::POS_LIFE_VALUE_1P ( WND_CNT - 151, 62 );
	const VEC2 DispGauge::POS_LIFE_VALUE_2P ( WND_CNT + 151, 62 );

	//剣撃ゲージ
	//Size ( 309, 16 )
	const VEC2 DispGauge::POS_STAMINA_VALUE_1P ( WND_CNT - 141, 86 );
	const VEC2 DispGauge::POS_STAMINA_VALUE_2P ( WND_CNT + 141, 86 );

	//超必殺技ゲージ
	//Size ( 202, 32 )
	const VEC2 DispGauge::POS_HISSATSU_VALUE_1P ( WND_CNT - 243, 105 );
	const VEC2 DispGauge::POS_HISSATSU_VALUE_2P ( WND_CNT + 243, 105 );

	//アクセルゲージ
	//Size ( 90, 139 )
	const VEC2 DispGauge::POS_ACCEL_VALUE_1P ( 0 - 3, 27 );
	const VEC2 DispGauge::POS_ACCEL_VALUE_2P ( 1280 - 75 - 12, 27 );

#pragma endregion


}	//namespace GAME

