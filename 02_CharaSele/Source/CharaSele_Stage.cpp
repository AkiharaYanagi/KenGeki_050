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
		m_bg->SetZ ( Z_BG );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );

		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_hara_evening.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_hara_noon.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_hara_night.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_school_morning.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_school_noon.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_school_night.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_Taishou_morning.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_Taishou_noon.png" );
		m_bg->AddTexture_FromArchive ( U"CharaSele\\BG\\BG_Taishou_night.png" );
	}

	CharaSele_Stage::~CharaSele_Stage ()
	{
	}


	void CharaSele_Stage::SetpParam ( P_Param p )
	{
		m_pParam = p;
		STAGE_NAME name = p->GetGameSetting ().GetStage_Name ();
		m_bg->SetIndexTexture ( GetStageIndex ( name ) );
	}

	void CharaSele_Stage::Next ()
	{
		STAGE_NAME stageName = m_pParam->GetGameSetting().GetStage_Name ();
		switch ( stageName )
		{
		case STAGE_ASAHINO_HARA:	stageName = STAGE_YUUHINO_HARA;		break;
		case STAGE_YUUHINO_HARA:	stageName = STAGE_YORUNO_HARA;		break;
		case STAGE_YORUNO_HARA :	stageName = STAGE_SCHOOL_MORNING;	break;
		case STAGE_SCHOOL_MORNING:	stageName = STAGE_SCHOOL_NOON;		break;
		case STAGE_SCHOOL_NOON:		stageName = STAGE_SCHOOL_NIGHT;		break;
		case STAGE_SCHOOL_NIGHT:	stageName = STAGE_TAISHOU_MORNING;	break;
		case STAGE_TAISHOU_MORNING:	stageName = STAGE_TAISHOU_NOON;		break;
		case STAGE_TAISHOU_NOON:	stageName = STAGE_TAISHOU_NINGT;	break;
		case STAGE_TAISHOU_NINGT:	stageName = STAGE_ASAHINO_HARA;		break;
		}

		//表示の更新
		m_bg->SetIndexTexture ( GetStageIndex ( stageName ) );

		//値の保存
		m_pParam->GetGameSetting ().SetStage_Name ( stageName );
	}

	void CharaSele_Stage::Prev ()
	{
		STAGE_NAME stageName = m_pParam->GetGameSetting().GetStage_Name ();
		switch ( stageName )
		{
		case STAGE_ASAHINO_HARA:	stageName = STAGE_TAISHOU_NINGT;	break;
		case STAGE_YUUHINO_HARA:	stageName = STAGE_ASAHINO_HARA;		break;
		case STAGE_YORUNO_HARA :	stageName = STAGE_YUUHINO_HARA;		break;
		case STAGE_SCHOOL_MORNING:	stageName = STAGE_YORUNO_HARA;		break;
		case STAGE_SCHOOL_NOON:		stageName = STAGE_SCHOOL_MORNING;	break;
		case STAGE_SCHOOL_NIGHT:	stageName = STAGE_SCHOOL_NOON;		break;
		case STAGE_TAISHOU_MORNING:	stageName = STAGE_SCHOOL_NIGHT;		break;
		case STAGE_TAISHOU_NOON:	stageName = STAGE_TAISHOU_MORNING;	break;
		case STAGE_TAISHOU_NINGT:	stageName = STAGE_TAISHOU_NOON;		break;
		}

		//表示の更新
		m_bg->SetIndexTexture ( GetStageIndex ( stageName ) );

		//値の保存
		m_pParam->GetGameSetting ().SetStage_Name ( stageName );
	}

	void CharaSele_Stage::Rand ()
	{
		STAGE_NAME stageName = m_pParam->GetGameSetting().GetStage_Name ();

		int startID = static_cast < int > ( STAGE_NAME::STAGE_ASAHINO_HARA );
		int endID = static_cast < int > ( STAGE_NAME::STAGE_TAISHOU_NINGT );
		int i = s3d::Random ( startID, endID );
		stageName = static_cast < STAGE_NAME > ( i );

		//表示の更新
		m_bg->SetIndexTexture ( GetStageIndex ( stageName ) );

		//値の保存
		m_pParam->GetGameSetting ().SetStage_Name ( stageName );
	}


}	//namespace GAME

