//=================================================================================================
//
//	CharaSele_Name
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Name.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_Name::CharaSele_Name ()
	{
		m_grp = std::make_shared < GameGraphic > ();
		m_grp->AddTexture();	//空を１つ確保
		m_grp->SetZ ( Z_EFB - 0.01f * 3 + 0.005f );	//Z値はGRPLST_INSERTより先
		AddpTask ( m_grp );
		GRPLST_INSERT ( m_grp );
		m_pob0 = m_grp->GetpObject(0);

		m_grp->AddObject ();
		m_pob1 = m_grp->GetpObject(1);
		m_pob1->SetColor ( 0xffa0a0a0 );
	}

	CharaSele_Name::~CharaSele_Name ()
	{
	}

	void CharaSele_Name::SetpParam ( P_Param p )
	{
		m_pParam = p;
	}

	void CharaSele_Name::Load ()
	{
		TASK_VEC::Load ();
	}

	void CharaSele_Name::Init ()
	{
		//初期キャラ
		CHARA_NAME name = m_pParam->GetGameSetting ().GetCharaName ( m_id );
		Assign ( name );

		//位置の設定
		if ( PLAYER_ID_1 == m_id )
		{
			m_pob0->SetPos ( 0 - 0.5f - 715 / 2, 960 + 0.5f -36 - 715 / 2 );
			m_pob0->SetRotationCenter ( VEC2 { - 0.5f + 715 / 2, 0.5f + 715 / 2 } );
			m_pob1->SetPos ( 0 - 0.5f - 715 / 2, 960 + 0.5f -36 - 715 / 2 );
			m_pob1->SetRotationCenter ( VEC2 { 0.5f + 715 / 2, 0.5f + 715 / 2 } );
			m_omega = 0.01f;
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			m_pob0->SetPos ( 1280 + 0.5f - 715 / 2, 960 + 0.5f -36 - 715 / 2 );
			m_pob0->SetRotationCenter ( VEC2 { 0.5f + 715 / 2, 0.5f + 715 / 2 } );
			m_pob1->SetPos ( 1280 + 0.5f - 715 / 2, 960 + 0.5f -36 - 715 / 2 );
			m_pob1->SetRotationCenter ( VEC2 { 0.5f + 715 / 2, 0.5f + 715 / 2 } );
			m_omega = -0.01f;
		}

		TASK_VEC::Init ();
	}


	void CharaSele_Name::Move ()
	{
#if 0
		//名前角度を手動で確認
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


		if ( PLAYER_ID_1 == m_id )
		{
			//1つ目
			m_theta0 += m_omega;	//正数方向
			if ( m_theta0 > D3DX_PI )
			{
				m_theta0 -= 2 * m_angle;	//２周めはtheta2つ分戻ってからスタート
			}

			//２つ目
			m_theta1 += m_omega;	//正数方向
			if ( m_theta1 > D3DX_PI  )
			{
				m_theta1 -= 2 * m_angle;	//２周めはtheta2つ分戻ってからスタート
			}
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			//1つ目
			m_theta0 += m_omega;	//負数方向
			if ( m_theta0 < - m_angle )
			{
				m_theta0 += 2 * m_angle;	//２周めはm_angle 2つ分戻ってからスタート
			}

			//２つ目
			m_theta1 += m_omega;	//負数方向
			if ( m_theta1 < - m_angle )
			{
				m_theta1 += 2 * m_angle;	//２周めはm_angle 2つ分戻ってからスタート
			}
		}
		m_pob0->SetRadian ( m_theta0 );
		m_pob1->SetRadian ( m_theta1 );


		//DBGOUT_WND_F ( DBGOUT_0, U"theta0 = {}"_fmt( m_theta0 ) );
		//DBGOUT_WND_F ( DBGOUT_1, U"theta1 = {}"_fmt( m_theta1 ) );


		TASK_VEC::Move ();
	}

	void CharaSele_Name::Next ()
	{
	}

	void CharaSele_Name::Prev ()
	{
	}

	void CharaSele_Name::Assign ( CHARA_NAME name )
	{
		//共通テクスチャ
		P_Ch_TxSet ptxSet = m_pParam->GetpChara_TxSet ();
		//===============================================================
		//@info AssignpTexture ( PTx pTx )
		//		２つ目以降のObjectは最初のテクスチャサイズを持っていて、
		//		Draw時にサイズ０ではないとき、前のサイズ（範囲）で描画してしまう。
		// ->描画範囲を手動で０にした
		//	いずれかのタイミングでサイズ０リセットする
		//  サイズが０のときテクスチャサイズのすべてを描画する
		//===============================================================
		m_grp->AssignpTexture ( ptxSet->GetpTx_Name ( name ) );
		m_pob1->SetRectF ( RectF { 0, 0, 0, 0 } );

		AngleInit ( name );
	}


	void CharaSele_Name::AngleInit ( CHARA_NAME name )
	{
		//名前から２つの角度差と初期位置の設定
		if ( PLAYER_ID_1 == m_id )
		{
			//速度
			m_omega = 0.01f;
			//角度定数
			m_angle = ARY_NAME_THETA [ static_cast < int > ( name ) ];
			//初期位置
			m_theta0 = D3DX_PI - m_angle;
			m_theta1 = m_theta0 - m_angle;
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			//速度
			m_omega = -0.01f;
			//角度定数
			m_angle = ARY_NAME_THETA [ static_cast < int > ( name ) ];
			//初期位置
			m_theta0 = 0;
			m_theta1 = m_theta0 - m_angle;
		}
	}

}	//namespace GAME

