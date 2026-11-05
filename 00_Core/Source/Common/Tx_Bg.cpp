//=================================================================================================
//
//	Tx　共通アセット 遅延読込
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "00_Core/Tx_Bg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	TxBg::TxBg ()
	{
		s3d::TextureAsset::Register ( U"BG_hara_evening",	U"Grp\\BG\\BG_hara_evening.png" );
		s3d::TextureAsset::Register ( U"BG_hara_noon",		U"Grp\\BG\\BG_hara_noon.png" );
		s3d::TextureAsset::Register ( U"BG_hara_night",		U"Grp\\BG\\BG_hara_night.png" );
		s3d::TextureAsset::Register ( U"BG_school_morning",	U"Grp\\BG\\BG_school_morning.png" );
		s3d::TextureAsset::Register ( U"BG_school_noon",	U"Grp\\BG\\BG_school_noon.png" );
		s3d::TextureAsset::Register ( U"BG_school_night",	U"Grp\\BG\\BG_school_night.png" );
		s3d::TextureAsset::Register ( U"BG_Taishou_morning",U"Grp\\BG\\BG_Taishou_morning.png" );
		s3d::TextureAsset::Register ( U"BG_Taishou_noon",	U"Grp\\BG\\BG_Taishou_noon.png" );
		s3d::TextureAsset::Register ( U"BG_Taishou_night",	U"Grp\\BG\\BG_Taishou_night.png" );

		m_hashBgName [ STAGE_ASAHINO_HARA ] = U"BG_hara_noon";
		m_hashBgName [ STAGE_YUUHINO_HARA ] = U"BG_hara_evening";
		m_hashBgName [ STAGE_YORUNO_HARA ] = U"BG_hara_night";
		m_hashBgName [ STAGE_SCHOOL_MORNING ] = U"BG_school_morning";
		m_hashBgName [ STAGE_SCHOOL_NOON ] = U"BG_school_noon";
		m_hashBgName [ STAGE_SCHOOL_NIGHT ] = U"BG_school_night";
		m_hashBgName [ STAGE_TAISHOU_MORNING ] = U"BG_Taishou_morning";
		m_hashBgName [ STAGE_TAISHOU_NOON ] = U"BG_Taishou_noon";
		m_hashBgName [ STAGE_TAISHOU_NIGHT ] = U"BG_Taishou_night";
	}

	TxBg::~TxBg ()
	{
	}

	s3d::Texture TxBg::GetTx ( STAGE_NAME stagename )
	{
		//@info const では[]演算子は使えない
		s3d::String sn = m_hashBgName.at ( stagename );
		
		LoadAsync ( sn );
		s3d::TextureAsset::Wait ( sn );

		return s3d::Texture { s3d::TextureAsset ( sn ) };
	}

	void TxBg::LoadAsync ( STAGE_NAME stagename )
	{
		//非同期読込
		s3d::TextureAsset::LoadAsync ( m_hashBgName.at ( stagename ) );
	}

	void TxBg::LoadAsync ( const s3d::String & assetname )
	{
		//非同期読込
		s3d::TextureAsset::LoadAsync ( assetname );
	}

}	//namespace GAME

