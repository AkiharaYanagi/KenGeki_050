//=================================================================================================
//
//	CharaSele_Stand
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Stand.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{


	const std::array < CHARA_NAME, CHARA_NAME_COUNT > CharaSele_Stand::chara_name =
	{
		CHARA_OUKA,			//鵯桜花
		CHARA_SAE,			//巴紗絵
		CHARA_RETSUDOU,		//烈火烈堂
		CHARA_GYAVADARUGA,	//ギャバダルガ
		CHARA_FERARIA,		//フェラリア
		CHARA_TSUKIHIBOSHI,	//月日星
		CHARA_REINA,		//レイナ
		CHARA_KISHI,		//忘れられた英雄
		CHARA_DOXTUKA,		//ドッカードボル
		CHARA_ENEMY_ZERO,	//エネミーゼロ
	};	//10個



	CharaSele_Stand::CharaSele_Stand ()
	{
		//キャラグラフィック
		m_chGrp = std::make_shared < CharaSele_CharaGrp > ();
		AddpTask ( m_chGrp );

		//最初の選択
		m_selectedIndex = 0;
	}

	CharaSele_Stand::~CharaSele_Stand ()
	{
	}

	void CharaSele_Stand::SetpParam ( P_Param p )
	{
		m_pParam = p;
		CHARA_NAME name = m_pParam->GetGameSetting ().GetCharaName ( m_id );
		if ( name == CHARA_NAME_NUM )
		{
			name = CHARA_OUKA;	//デフォルト
			m_pParam->GetGameSetting ().SetCharaName ( m_id, name );
		}
		//有効なキャラ名ならばインデックスを設定
		m_selectedIndex = static_cast < int > ( name );

		m_chGrp->SetpParam ( p );

	}

	void CharaSele_Stand::Load ()
	{
		TASK_VEC::Load ();
	}

	void CharaSele_Stand::Init ()
	{
		Assign ();
		TASK_VEC::Init ();
	}

	void CharaSele_Stand::Move ()
	{
		TASK_VEC::Move ();
	}


	void CharaSele_Stand::Next_Chara ()
	{
		const int N = 5;

		if ( N <= m_selectedIndex + 1 )
		{
			m_selectedIndex = 0;
		}
		else
		{
			++ m_selectedIndex;
		}

		//パラメータに保存
		CHARA_NAME name = static_cast < CHARA_NAME > ( m_selectedIndex );
		m_pParam->GetGameSetting().SetCharaName ( m_id, name );
		Assign ();
	}

	void CharaSele_Stand::Prev_Chara ()
	{
		const int N = 5;

		if ( m_selectedIndex < 1 )
		{
			m_selectedIndex = N - 1;
		}
		else
		{
			-- m_selectedIndex;
		}

		//パラメータに保存
		CHARA_NAME name = static_cast < CHARA_NAME > ( m_selectedIndex );
		m_pParam->GetGameSetting().SetCharaName ( m_id, name );
		Assign ();
	}

	void CharaSele_Stand::Next_Color ()
	{
		GameSettingFile & stg = m_pParam->GetGameSetting ();
		CHARA_COLOR clr = stg.GetCharaColor ( m_id );
		if ( CH_CLR_1 == clr )
		{
			clr = CH_CLR_2;
		}
		else if ( CH_CLR_2 == clr )
		{
			clr = CH_CLR_1;
		}
		stg.SetCharaColor ( m_id, clr );
		Assign ();
	}

	void CharaSele_Stand::Prev_Color ()
	{
		GameSettingFile & stg = m_pParam->GetGameSetting ();
		CHARA_COLOR clr = stg.GetCharaColor ( m_id );
		if ( CH_CLR_1 == clr )
		{
			clr = CH_CLR_2;
		}
		else if ( CH_CLR_2 == clr )
		{
			clr = CH_CLR_1;
		}
		stg.SetCharaColor ( m_id, clr );
		Assign ();
	}


	//グラフィックをパラメータに基づいて更新
	void CharaSele_Stand::Assign ( CHARA_NAME name, CHARA_COLOR clr )
	{
		m_chGrp->Assign ( name, clr );
	}

	void CharaSele_Stand::Assign ()
	{
		P_Param p = m_pParam;
		GameSettingFile& stg = p->GetGameSetting ();
		if ( PLAYER_ID_1 == m_id )
		{
			m_chGrp->Assign ( stg.GetCharaName1p (), stg.GetCharaColor1p () );
		}
		else if ( PLAYER_ID_2 == m_id )
		{
			m_chGrp->Assign ( stg.GetCharaName2p (), stg.GetCharaColor2p () );
		}
	}



#pragma region CONST

#pragma endregion


}	//namespace GAME

