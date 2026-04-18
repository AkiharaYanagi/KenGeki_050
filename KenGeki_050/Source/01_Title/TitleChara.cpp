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

		m_vx1 = 50.f;
		m_vx2 = 0.15f;

		//タイマ
		m_tmr1 = std::make_shared < Timer > ( 15 );
		AddpTask ( m_tmr1 );
		m_tmr2 = std::make_shared < Timer > ( 60 * 4 );
		AddpTask ( m_tmr2 );
	}

	TitleChara::~TitleChara ()
	{
	}

	void TitleChara::SetpParam ( P_Param p )
	{
		m_pParam = p;
		const GameSettingFile& stg = p->GetGameSetting ();

		//最初はパラメータに保存されている選択キャラ
		CHARA_NAME name1p = stg.GetCharaName1p ();
		CHARA_COLOR clr1p = stg.GetCharaColor1p ();
		CHARA_NAME name2p = stg.GetCharaName2p ();
		CHARA_COLOR clr2p = stg.GetCharaColor2p ();
		SetChara ( name1p, clr1p, name2p, clr2p );

#if 0

		CHARA_NAME name1p = stg.GetCharaName1p ();
		CHARA_COLOR clr1p = stg.GetCharaColor1p ();
		P_Tx ptx1p = p->GetpChara_TxSet()->GetpTx_CutIn ( name1p, clr1p );
		m_chara_1p->AssignpTexture ( ptx1p );
		m_revX1 = m_posAdjustMap.at ( name1p );
		m_x1 = START_X_1P + m_revX1;

		CHARA_NAME name2p = stg.GetCharaName2p ();
		CHARA_COLOR clr2p = stg.GetCharaColor2p ();
		P_Tx ptx2p = p->GetpChara_TxSet()->GetpTx_CutIn ( name2p, clr2p );
		m_chara_2p->AssignpTexture ( ptx2p );
		m_revX2 = m_posAdjustMap.at ( name2p );
		m_x2 = START_X_2P - m_revX2;

#endif // 0
	}

	void TitleChara::Load ()
	{
		TASK_VEC::Load ();
	}

	void TitleChara::Init ()
	{
		//RandomStartChara ();
		m_tmr1->Start ();

		TASK_VEC::Init ();
	}

	void TitleChara::Move ()
	{
		if ( m_tmr1->IsActive () )
		{
			m_x1 += m_vx1;
			m_x2 -= m_vx1;

			if ( m_tmr1->IsLast () )
			{
				m_tmr1->Stop ();
				m_tmr2->Start ();
			}
		}

		if ( m_tmr2->IsActive () )
		{
			m_x1 += m_vx2;
			m_x2 -= m_vx2;
			if ( m_tmr2->IsLast () )
			{
				RandomStartChara ();
				m_tmr1->Start ();
				m_tmr2->Stop ();
			}
		}


#if 0

		if ( m_tmr1->IsActive () )
		{
			if ( m_x1 > TARGET_X_1P + m_vx + m_revX1 )
			{
				//m_x1 = TARGET_X_1P;
				m_active1 = F;
			}
			else
			{
				m_x1 += m_vx;
			}
		}
		else
		{
			m_x1 += m_vx1;
		}

		if ( m_active2 )
		{
			if ( m_x2 < TARGET_X_2P - m_vx - m_revX2 )
			{
				//m_x2 = TARGET_X_2P;
				m_active2 = F;
			}
			else
			{
				m_x2 -= m_vx;
			}
		}
		else
		{
			m_x2 -= m_vx1;
		}

#endif // 0

		m_chara_1p->SetPosX ( m_x1 );
		m_chara_2p->SetPosX ( m_x2 );


		//test 手動変更
		if ( CFG_PUSH_KEY_12 ( PLY_BTN5 ) )
		{
			RandomStartChara ();
			m_tmr1->Start ();
		}

#if 0
#endif // 0


		TASK_VEC::Move ();
	}

	void TitleChara::RandomStartChara ()
	{
		//m_active1 = T;
		//m_active2 = T;

		CHARA_NAME name1p = GetRandomCharaName ();
		CHARA_COLOR clr1p = static_cast < CHARA_COLOR > ( s3d::Random(0,1) );
		CHARA_NAME name2p = GetRandomCharaName ();
		CHARA_COLOR clr2p = static_cast < CHARA_COLOR > ( s3d::Random(0,1) );
		SetChara ( name1p, clr1p, name2p, clr2p );
	}


	void TitleChara::SetChara ( CHARA_NAME name1, CHARA_COLOR clr1, CHARA_NAME name2, CHARA_COLOR clr2 )
	{
		//@info const は[]でのアクセス不可なのでat()で取得
		if ( ! m_posAdjustMap.contains ( name1 ) )
		{
			name1 = GetRandomCharaName ();
		}
		if ( ! m_posAdjustMap.contains ( name2 ) )
		{
			name2 = GetRandomCharaName ();
		}

		P_Tx ptx1p = m_pParam->GetpChara_TxSet()->GetpTx_CutIn ( name1, clr1 );
		m_chara_1p->AssignpTexture ( ptx1p );
		m_revX1 = m_posAdjustMap.at ( name1 );
		m_x1 = START_X_1P + m_revX1;

		P_Tx ptx2p = m_pParam->GetpChara_TxSet()->GetpTx_CutIn ( name2, clr2 );
		m_chara_2p->AssignpTexture ( ptx2p );
		m_revX2 = m_posAdjustMap.at ( name2 );
		m_x2 = START_X_2P - m_revX2;

		//パラメータにも記録
		GameSettingFile& stg = m_pParam->GetGameSetting ();
		stg.SetCharaName ( PLAYER_ID_1, name1 );
		stg.SetCharaName ( PLAYER_ID_2, name2 );
		stg.SetCharaColor ( PLAYER_ID_1, clr1 );
		stg.SetCharaColor ( PLAYER_ID_2, clr2 );
	}

	CHARA_NAME TitleChara::GetRandomCharaName () const
	{
		//タイトルカットイン対象のキャラのみ
#if 0
		const CHARA_NAME name[] = {
			CHARA_OUKA,
			CHARA_SAE,
			CHARA_RETSUDOU,
			CHARA_GYAVADARUGA,
			CHARA_FERARIA,
		};
#endif // 0

		CHARA_NAME name = CHARA_OUKA;
		int rnd = s3d::Random ( 0, 4 );

		switch ( rnd )
		{
		case 0: name = CHARA_OUKA; break;
		case 1: name = CHARA_SAE; break;
		case 2: name = CHARA_RETSUDOU; break;
		case 3: name = CHARA_GYAVADARUGA; break;
		case 4: name = CHARA_FERARIA; break;
		default: break;
		}

		return name;
	}


#pragma region CONST
	const float TitleChara::TX_W = 950;
	const float TitleChara::START_X_1P = - 1000;
	const float TitleChara::START_X_2P = 1280 - TX_W + 1000;
	const float TitleChara::TARGET_X_1P = - 400;
	const float TitleChara::TARGET_X_2P = 1280 - TX_W + 400;

#pragma endregion


}	//namespace GAME

