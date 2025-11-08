//=================================================================================================
//
//	TitleChara
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TitleChara.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	TitleChara::TitleChara ()
	{
		m_chara_1p = std::make_shared < GameGraphic > ();
		m_chara_1p->AddTexture ();	//テクスチャ指定のため１つ確保
		AddpTask ( m_chara_1p );
		GRPLST_INSERT ( m_chara_1p );
		m_chara_1p->SetPos ( START_X_1P, 0 );


		m_chara_2p = std::make_shared < GameGraphic > ();
		m_chara_2p->AddTexture ();	//テクスチャ指定のため１つ確保
		AddpTask ( m_chara_2p );
		GRPLST_INSERT ( m_chara_2p );

		m_chara_2p->SetPos ( START_X_2P, 0 );
		m_chara_2p->SetScalingCenter ( VEC2 ( TX_W/2, 1000/2 ) );
		m_chara_2p->SetScaling ( VEC2 ( -1, 1 ) );

		m_vx = 50.f;

		//タイマ
		m_tmr = std::make_shared < Timer > ( 60 * 5 );
		AddpTask ( m_tmr );
	}

	TitleChara::~TitleChara ()
	{
	}

	void TitleChara::SetpParam ( P_Param p )
	{
		m_pParam = p;
		const GameSettingFile stg = p->GetGameSetting ();

		//最初は選択キャラ
		CHARA_NAME name1p = stg.GetCharaName1p ();
		CHARA_COLOR clr1p = stg.GetCharaColor1p ();
		P_Tx ptx1p = p->GetpChara_TxSet()->GetpTx_CutIn ( name1p, clr1p );
		m_chara_1p->AssignpTexture ( ptx1p );

		CHARA_NAME name2p = stg.GetCharaName2p ();
		CHARA_COLOR clr2p = stg.GetCharaColor2p ();
		P_Tx ptx2p = p->GetpChara_TxSet()->GetpTx_CutIn ( name2p, clr2p );
		m_chara_2p->AssignpTexture ( ptx2p );
	}

	void TitleChara::Load ()
	{
		TASK_VEC::Load ();
	}

	void TitleChara::Init ()
	{
		ResetChara ();
		TASK_VEC::Init ();
	}

	void TitleChara::Move ()
	{
		if ( m_active1 )
		{
			if ( m_x1 > TARGET_X_1P + m_vx )
			{
				m_x1 = TARGET_X_1P;
				m_active1 = F;
			}
			else
			{
				m_x1 += m_vx;
			}
		}

		if ( m_active2 )
		{
			if ( m_x2 < TARGET_X_2P - m_vx )
			{
				m_x2 = TARGET_X_2P;
				m_active2 = F;
			}
			else
			{
				m_x2 -= m_vx;
			}
		}

		m_chara_1p->SetPosX ( m_x1 );
		m_chara_2p->SetPosX ( m_x2 );


		//test 手動変更
		if ( CFG_PUSH_KEY_12 ( PLY_BTN5 ) )
		{
			CHARA_NAME name1p = static_cast < CHARA_NAME > ( s3d::Random(0,4) );
			CHARA_COLOR clr1p = static_cast < CHARA_COLOR > ( s3d::Random(0,1) );
			P_Tx ptx1p = m_pParam->GetpChara_TxSet()->GetpTx_CutIn ( name1p, clr1p );
			m_chara_1p->AssignpTexture ( ptx1p );

			CHARA_NAME name2p = static_cast < CHARA_NAME > ( s3d::Random(0,4) );
			CHARA_COLOR clr2p = static_cast < CHARA_COLOR > ( s3d::Random(0,1) );
			P_Tx ptx2p = m_pParam->GetpChara_TxSet()->GetpTx_CutIn ( name2p, clr2p );
			m_chara_2p->AssignpTexture ( ptx2p );
		}

#if 0
#endif // 0

		//タイマでリセット
		if ( m_tmr->IsLast () )
		{
			ResetChara ();
			m_tmr->Start ();
		}


		TASK_VEC::Move ();
	}

	void TitleChara::ResetChara ()
	{
		m_x1 = START_X_1P;
		m_active1 = T;
		CHARA_NAME name1p = static_cast < CHARA_NAME > ( s3d::Random(0,4) );
		CHARA_COLOR clr1p = static_cast < CHARA_COLOR > ( s3d::Random(0,1) );
		P_Tx ptx1p = m_pParam->GetpChara_TxSet()->GetpTx_CutIn ( name1p, clr1p );
		m_chara_1p->AssignpTexture ( ptx1p );

		m_x2 = START_X_2P;
		m_active2 = T;
		CHARA_NAME name2p = static_cast < CHARA_NAME > ( s3d::Random(0,4) );
		CHARA_COLOR clr2p = static_cast < CHARA_COLOR > ( s3d::Random(0,1) );
		P_Tx ptx2p = m_pParam->GetpChara_TxSet()->GetpTx_CutIn ( name2p, clr2p );
		m_chara_2p->AssignpTexture ( ptx2p );

		m_tmr->Start ();

	}



#pragma region CONST
	const float TitleChara::TX_W = 950;
	const float TitleChara::START_X_1P = - 1000;
	const float TitleChara::START_X_2P = 1280 - TX_W + 1000;
	const float TitleChara::TARGET_X_1P = - 400;
	const float TitleChara::TARGET_X_2P = 1280 - TX_W + 400;

#pragma endregion


}	//namespace GAME

