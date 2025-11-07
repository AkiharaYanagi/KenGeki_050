//=================================================================================================
//
//	CharaSele_Stage
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Stage.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	CharaSele_Stage::CharaSele_Stage ()
	{
		m_bg = std::make_shared < GameGraphic > ();
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );
		m_bg->SetZ ( Z_BG );

		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_hara_evening.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_hara_noon.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_hara_night.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_school_morning.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_school_night.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_school_noon.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_Taishou_morning.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_Taishou_night.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_Taishou_noon.png" );
	}

	CharaSele_Stage::~CharaSele_Stage ()
	{
	}


	void CharaSele_Stage::SetpParam ( P_Param p )
	{
		m_pParam = p;
		STAGE_NAME name = p->GetGameSetting ().GetStage_Name ();
		m_index = static_cast < INT32 > ( name );
		m_bg->SetIndexTexture ( m_index );
	}

	void CharaSele_Stage::Load ()
	{
		TASK_VEC::Load ();
	}

	void CharaSele_Stage::Move ()
	{
		TASK_VEC::Move ();
	}

	void CharaSele_Stage::Next ()
	{
		if ( m_index == STAGE_NUM - 1 )
		{
			m_index = 0;
		}
		else
		{
			++ m_index;
		}

		m_bg->SetIndexTexture ( m_index );

		//値の保存
		m_pParam->GetGameSetting ().SetStage_Name ( GetStageName () );
	}

	void CharaSele_Stage::Prev ()
	{
		if ( m_index == 0 )
		{
			m_index = STAGE_NUM - 1;
		}
		else
		{
			-- m_index;
		}

		m_bg->SetIndexTexture ( m_index );

		//値の保存
		m_pParam->GetGameSetting ().SetStage_Name ( GetStageName () );
	}


}	//namespace GAME

