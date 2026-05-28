//=================================================================================================
//
// DispGauge_all ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispGauge_all.h"
#include "DispChara_Const.h"
#include "03_FtgMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

constexpr float D3DX_PI_BY4 = 0.7853981635f;


inline double mapRange
	( double value, double inMin, double inMax, double outMin, double outMax )
{
	if ( inMax == inMin ) { return outMin; }	// 範囲がゼロの場合、出力範囲の最小値を返す
	return outMin + (outMax - outMin) * ((value - inMin) / (inMax - inMin));
}



	DispGauge_all::DispGauge_all ()
	{
		//総合ゲージ背景
		m_gauge_all_bg = std::make_shared < GameGraphic > ();
		m_gauge_all_bg->AddTexture_FromArchive ( U"Battle\\gauge_all.png" );
		m_gauge_all_bg->SetZ ( Z_SHADOW );
		GRPLST_INSERT ( m_gauge_all_bg );
		AddpTask ( m_gauge_all_bg );

		//ゲージ類
		m_life_red_value = MakepGrp (); 	//ライフゲージ 赤
		m_life_white_value = MakepGrp ();	//ライフゲージ 白
		m_life_value = MakepGrp ();			//ライフゲージ 緑
		m_stamina_value = MakepGrp ();		//剣撃ゲージ
		m_hissatsu_value = MakepGrp ();		//必殺ゲージ
		m_accel_value = MakepGrp ();		//アクセルゲージ

		//必殺マーク
		m_hissatsu_mark = MakepGrp ();	//必殺円形
		m_hissatsu_mark->SetbPlgnMask ( F );		//ポリゴンマスク不使用
		m_hissatsu_mark->AddTexture_FromArchive ( U"Battle\\hissatsu_mark.png" );
		m_hissatsu_mark->SetRotationCenter(VEC2(79*0.5f, 72*0.5f));

		//必殺回転円型
		m_hissatsu_ring = MakepGrp ();	//必殺円形
		m_hissatsu_ring->SetbPlgnMask ( F );		//ポリゴンマスク不使用
		m_hissatsu_ring->AddTexture_FromArchive ( U"Battle\\hissatsu_ring.png" );
		m_hissatsu_ring->SetRotationCenter(VEC2(79*0.5f, 72*0.5f));

		m_omega = D3DX_PI_TWICE / 90.f;


		//剣撃ゲージ分割線
		m_kengeki_split = std::make_shared < GameGraphic > ();
		m_kengeki_split->AddTexture_FromArchive ( U"Battle\\gauge_split.png" );
		m_kengeki_split->SetZ ( Z_SHADOW - 0.02f );
		GRPLST_INSERT ( m_kengeki_split );
		AddpTask ( m_kengeki_split );

	}

	//グラフィック確保
	P_Grp DispGauge_all::MakepGrp ()
	{
		P_Grp pGrp = std::make_shared < GameGraphic > ();
		pGrp->SetZ ( Z_SHADOW - 0.01f );
		pGrp->SetbPlgnMask ( T );		//ポリゴンマスク使用
		GRPLST_INSERT ( pGrp );
		AddpTask ( pGrp );
		return pGrp;
	}

	DispGauge_all::~DispGauge_all ()
	{
	}


	void DispGauge_all::Load ()
	{
		TASK_VEC::Load ();
	}

	//パラメータ初期化
	void DispGauge_all::ParamInit ( P_Param pParam )
	{
		(void)pParam;
	}

	//プレイヤ側で初期化
	void DispGauge_all::LoadPlayer ( PLAYER_ID playerID )
	{
		//プレイヤ側保存
		m_playerID = playerID;

		//-----------------------------------------------------------------
		//背景
		if ( PLAYER_ID_1 == playerID )
		{
			m_gauge_all_bg->SetPos ( POS_FRAME_ALL_1P );
			m_gauge_all_bg->SetScaling ( -1.f, 1.f );	//2pが正方向なので水平反転

			m_hissatsu_mark->SetPos ( POS_HISSATSU_1P );
			m_hissatsu_ring->SetPos ( POS_HISSATSU_1P );

			m_kengeki_split->SetPos ( POS_KENGEKI_SPLIT_1P );
			m_kengeki_split->SetScaling ( -1.f, 1.f );	//2pが正方向なので水平反転
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			m_gauge_all_bg->SetPos ( POS_FRAME_ALL_2P );
			m_hissatsu_mark->SetPos ( POS_HISSATSU_2P );
			m_hissatsu_ring->SetPos ( POS_HISSATSU_2P );
			m_kengeki_split->SetPos ( POS_KENGEKI_SPLIT_2P );
		}
		//-----------------------------------------------------------------


		//-----------------------------------------------------------------
		//ゲージ値初期化

		//ライフゲージ(緑、白、赤)
		InitGauge_Life ( m_life_value, U"Battle\\life_value.png" );
		InitGauge_Life ( m_life_white_value, U"Battle\\life_white.png" );
		InitGauge_Life ( m_life_red_value, U"Battle\\life_damage.png" );

		//他ゲージ
		if ( PLAYER_ID_1 == playerID )
		{
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
			P_Plgn m_stamina_mask = std::make_shared < s3d::Polygon > ( aryVec_stamina );
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
			P_Plgn m_hissatsu_mask = std::make_shared < s3d::Polygon > ( aryVec_hissatsu );
			m_hissatsu_value->SetPosInMask ( VEC2 (195, 105) );
			m_hissatsu_value->SetpPolygon ( m_hissatsu_mask );
			m_hissatsu_value->AddTexture_FromArchive_mrr ( U"Battle\\hissatsu_value.png" );


			//-----------------------------------------------------------------
			//アクセルゲージ
			//Size ( 90, 139 )
			//const VEC2 DispGauge::POS_ACCEL_VALUE_1P ( 0 - 3, 27 ); //86-80
			double r = 220;
			double x0 = 0;
			double y0 = 27 + 139;
			double x1 = x0 - r;
			double y1 = y0 - r;
			double x2 = x0 - r;
			double y2 = y0;
			s3d::Array < s3d::Vec2 > aryVec_accel{ {x0, y0}, {x2, y2}, {x1, y1} };
			P_Plgn m_accel_mask = std::make_shared < s3d::Polygon > ( aryVec_accel );
			m_accel_value->SetPosInMask ( POS_ACCEL_VALUE_1P );
			m_accel_value->SetpPolygon ( m_accel_mask );
			m_accel_value->AddTexture_FromArchive_mrr ( U"Battle\\accel_value.png" );
		}
		else if ( PLAYER_ID_2 == playerID )
		{
			//-----------------------------------------------------------------
			//剣撃ゲージ
			//Size ( 309, 16 )
			//const VEC2 DispFrontEnd_all::POS_STAMINA_VALUE_2P ( WND_CNT + 141, 86 );
			s3d::Array < s3d::Vec2 > aryVec_stamina{ {791, 86}, {791 + 299 , 86}, {781 + 299, 102}, {781, 102} };
			P_Plgn m_stamina_mask = std::make_shared < s3d::Polygon > ( aryVec_stamina );
			m_stamina_value->SetPosInMask ( VEC2 (781, 86) );
			m_stamina_value->SetpPolygon ( m_stamina_mask );
			m_stamina_value->AddTexture_FromArchive ( U"Battle\\stumina_value.png" );

			//-----------------------------------------------------------------
			//超必殺技ゲージ
			//Size ( 202, 32 )
			//const VEC2 DispFrontEnd_all::POS_HISSATSU_VALUE_2P ( WND_CNT + 243, 105 );
			s3d::Array < s3d::Vec2 > aryVec_hissatsu{ {883+10, 105}, {883+202+10, 105}, {883+202-10, 137}, {883-10, 137} };
			P_Plgn m_hissatsu_mask = std::make_shared < s3d::Polygon > ( aryVec_hissatsu );
			m_hissatsu_value->SetPosInMask ( VEC2 (883, 105) );
			m_hissatsu_value->SetpPolygon ( m_hissatsu_mask );
			m_hissatsu_value->AddTexture_FromArchive ( U"Battle\\hissatsu_value.png" );

			//-----------------------------------------------------------------
			//アクセルゲージ
			//Size ( 90, 139 )
			//const VEC2 DispGauge::POS_ACCEL_VALUE_2P ( 1280 - 75 - 11, 27 );	//(1194,27)
			double r = 220;
			double x0 = 1194 - 80;
			double y0 = 27 + 139;
			double x1 = x0 + r;
			double y1 = y0 - r;
			double x2 = x0 + r;
			double y2 = y0;
			s3d::Array < s3d::Vec2 > aryVec_accel{ {x0, y0}, {x1, y1}, {x2, y2} };
			P_Plgn m_accel_mask = std::make_shared < s3d::Polygon > ( aryVec_accel );
			m_accel_value->SetPosInMask ( POS_ACCEL_VALUE_2P );
			m_accel_value->SetpPolygon ( m_accel_mask );
			m_accel_value->AddTexture_FromArchive ( U"Battle\\accel_value.png" );
		}

	}

	//------------------------
	//更新

	//ゲージ
	void DispGauge_all::UpdateGauge ( const BtlParam & btlPrm )
	{
		//体力ゲージ
		int32 life = btlPrm.GetLife ();
		UpdateGauge_Life ( m_life_value, life );

		//体力ゲージ 白
		int32 whiteDamage = btlPrm.GetWhiteDamage ();
		int32 white = whiteDamage + life;	//表示幅はライフとの合計
		UpdateGauge_Life ( m_life_white_value, white );

		//体力ゲージ 赤
		int32 redDamage = btlPrm.GetRedDamage ();
		int32 red = redDamage + life;	//表示幅はライフとの合計
		UpdateGauge_Life ( m_life_red_value, red );


		//剣撃ゲージ
		int32 stamina = btlPrm.GetBalance() ;
		//（ 最大幅 * 値 / 最大値 ）
		float width_stamina = 299.f * stamina /(float)BALANCE_MAX;

		if ( PLAYER_ID_1 == m_playerID )
		{
			double x0 = 640 - 141 - 10 - width_stamina;
			double x1 = 640 - 141 - 10;
			double x2 = 640 - 141;
			double x3 = 640 - 141 - width_stamina;
			//剣撃ゲージ
			s3d::Array < s3d::Vec2 > aryVec_stamina{ {x0, 86}, {x1, 86}, {x2, 102}, {x3, 102} };
			P_Plgn m_stamina_mask = std::make_shared < s3d::Polygon > ( aryVec_stamina );
			m_stamina_value->SetpPolygon ( m_stamina_mask );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			double x1 = 791 + width_stamina;
			double x2 = 781 + width_stamina;
			s3d::Array < s3d::Vec2 > aryVec_stamina{ {791, 86}, {x1, 86}, {x2, 102}, {781, 102} };
			P_Plgn m_stamina_mask = std::make_shared < s3d::Polygon > ( aryVec_stamina );
			m_stamina_value->SetpPolygon ( m_stamina_mask );
		}


		//超必殺技ゲージ
		int32 hissatsu = btlPrm.GetMana () ;
		//（ 最大幅 * 値 / 最大値 ）
		float width_hissatsu = (202.f - 10) * hissatsu /(float)MANA_MAX;

		if ( PLAYER_ID_1 == m_playerID )
		{
			double x0 = 640 - 243 - width_hissatsu - 20;		//195
			double x1 = 640 - 243 - 10;						//387
			double x2 = 640 - 243 + 10;							//397
			double x3 = 640 - 243 - width_hissatsu;		//205
			s3d::Array < s3d::Vec2 > aryVec_hissatsu{ {x0, 105}, {x1, 105}, {x2, 137}, {x3, 137} };
			P_Plgn m_hissatsu_mask = std::make_shared < s3d::Polygon > ( aryVec_hissatsu );
			m_hissatsu_value->SetpPolygon ( m_hissatsu_mask );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			double x0 = 640 + 243 + 10;		//893
			double x1 = 640 + 243 + width_hissatsu + 20;
			double x2 = 640 + 243 + width_hissatsu;
			double x3 = 640 + 243 - 10;		//873
			s3d::Array < s3d::Vec2 > aryVec_hissatsu{ {x0, 105}, {x1, 105}, {x2, 137}, {x3, 137} };
			P_Plgn m_hissatsu_mask = std::make_shared < s3d::Polygon > ( aryVec_hissatsu );
			m_hissatsu_value->SetpPolygon ( m_hissatsu_mask );
		}


		//-----------------------------------------------------------------
		//アクセルゲージ
		int32 accel = btlPrm.GetAccel () ;

		if ( PLAYER_ID_1 == m_playerID )
		{
			double r = 220;
			double x0 = 0 + 75 + 12 + 80;
			double y0 = 27 + 139;
			double x2 = x0 - r;
			double y2 = y0;

			double theta = mapRange ( accel, ACCEL_MIN, ACCEL_MAX, 0, D3DX_PI_BY4 );
			double x = r * std::cos ( theta );
			double y = r * std::sin ( theta );

			s3d::Array < s3d::Vec2 > aryVec_accel{ {x2, y2}, {x0 - x, y0 - y}, {x0, y0} };
			P_Plgn m_accel_mask = std::make_shared < s3d::Polygon > ( aryVec_accel );
			m_accel_value->SetpPolygon ( m_accel_mask );

			DBGOUT_WND_F ( DBGOUT_6, U"accel {}, x={}, y={}"_fmt( accel, x, y ) );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			double r = 220;
			double x0 = 1194 - 80;
			double y0 = 27 + 139;
			double x2 = x0 + r;
			double y2 = y0;

			double theta = mapRange ( accel, ACCEL_MIN, ACCEL_MAX, 0, D3DX_PI_BY4 );
			double x = r * std::cos ( theta );
			double y = r * std::sin ( theta );

			s3d::Array < s3d::Vec2 > aryVec_accel{ {x0, y0}, {x0 + x, y0 - y}, {x2, y2} };
			P_Plgn m_accel_mask = std::make_shared < s3d::Polygon > ( aryVec_accel );
			m_accel_value->SetpPolygon ( m_accel_mask );
		}

		//必殺マーク
		//必殺ゲージが満タンで点灯回転
		if ( MANA_MAX == hissatsu )
		{
			m_hissatsu_mark->SetValid ( T );
			m_hissatsu_ring->SetValid ( T );
			m_theta += m_omega;
			m_hissatsu_ring->SetRadian ( m_theta );
		}
		else
		{
			m_hissatsu_mark->SetValid ( F );
			m_hissatsu_ring->SetValid ( F );
		}
	}



	//ライフゲージ表示初期化
	void DispGauge_all::InitGauge_Life ( const P_Grp & pGrp, const s3d::String & filename )
	{
		UpdateGauge_Life ( pGrp, LIFE_MAX );

		VEC2 pos { 0, 0 };
		if (m_playerID == PLAYER_ID_1)
		{
			pos = VEC2 (169, 62 );
			pGrp->AddTexture_FromArchive_mrr ( filename );
		}
		else if (m_playerID == PLAYER_ID_2)
		{
			pos = VEC2 (791, 62);
			pGrp->AddTexture_FromArchive ( filename );
		}
		pGrp->SetPosInMask ( pos );

	}


	//ライフゲージ表示
	void DispGauge_all::UpdateGauge_Life ( const P_Grp & pGrp, int32 value )
	{
		//（ 最大幅 * 値 / 最大値 ）
		float width = 310.f * value /(float)LIFE_MAX;

		//体力ゲージ
		//Size ( 320, 20 ) //上辺310
		//const VEC2 DispFrontEnd_all::POS_LIFE_VALUE_1P ( WND_CNT - 151, 62 );
#if 0
		double x0 = 640 - 151 - 10 - 310;	//169
		double x1 = 640 - 151 - 10;			//479
		double x2 = 640 - 151;				//489
		double x3 = 640 - 151 - 310;		//179
#endif // 0

		if ( PLAYER_ID_1 == m_playerID )
		{
			double x0 = 640 - 151 - 10 - width;
			double x1 = 640 - 151 - 10;
			double x2 = 640 - 151;
			double x3 = 640 - 151 - width;

			s3d::Array < s3d::Vec2 > aryVec{ {x0, 62}, {x1, 62}, {x2, 82}, {x3, 82} };
			P_Plgn mask = std::make_shared < s3d::Polygon > ( aryVec );
			pGrp->SetpPolygon ( mask );
		}
		else if ( PLAYER_ID_2 == m_playerID )
		{
			double x1 = 801 + width;
			double x2 = 791 + width;
			s3d::Array < s3d::Vec2 > aryVec{ {801, 62}, {x1, 62}, {x2, 82}, {791, 82} };
			P_Plgn mask = std::make_shared < s3d::Polygon > ( aryVec );
			pGrp->SetpPolygon ( mask );
		}
	}



#pragma region CONST
	//定数
	//2pが正方向, 1p側は(右端が基準点)

	//全体枠
	//Size ( 516, 172 )
	const VEC2 DispGauge_all::POS_FRAME_ALL_1P ( 0 + 516, 10 );
	const VEC2 DispGauge_all::POS_FRAME_ALL_2P ( 1280 - 516 - 0, 10 );

	//体力ゲージ
	//Size ( 320, 20 )
	const VEC2 DispGauge_all::POS_LIFE_VALUE_1P ( WND_CNT - 151, 62 );
	const VEC2 DispGauge_all::POS_LIFE_VALUE_2P ( WND_CNT + 151, 62 );

	//剣撃ゲージ
	//Size ( 309, 16 )
	const VEC2 DispGauge_all::POS_STAMINA_VALUE_1P ( WND_CNT - 141, 86 );
	const VEC2 DispGauge_all::POS_STAMINA_VALUE_2P ( WND_CNT + 141, 86 );

	//超必殺技ゲージ
	//Size ( 202, 32 )
	const VEC2 DispGauge_all::POS_HISSATSU_VALUE_1P ( WND_CNT - 243, 105 );
	const VEC2 DispGauge_all::POS_HISSATSU_VALUE_2P ( WND_CNT + 243, 105 );

	//アクセルゲージ
	//Size ( 90, 139 )
	const VEC2 DispGauge_all::POS_ACCEL_VALUE_1P ( 0 - 3, 27 );
	const VEC2 DispGauge_all::POS_ACCEL_VALUE_2P ( 1280 - 75 - 11, 27 );

	//必殺マーク
	const VEC2 DispGauge_all::POS_HISSATSU_1P ( 0 -79 + 218, 115 );
	const VEC2 DispGauge_all::POS_HISSATSU_2P ( 1280 - 218, 115 );

	//剣撃分割線
	const VEC2 DispGauge_all::POS_KENGEKI_SPLIT_1P ( WND_CNT - 141, 86 );
	const VEC2 DispGauge_all::POS_KENGEKI_SPLIT_2P ( WND_CNT + 141, 86 );


#pragma endregion



}	//namespace GAME

