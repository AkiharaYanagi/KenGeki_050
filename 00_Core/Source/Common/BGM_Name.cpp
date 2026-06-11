//=================================================================================================
//
//	BGM_Name
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "00_Core/BGM_Name.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	BGM_Name::BGM_Name ()
	{
		//BGM名
		m_bgmName = std::make_shared < GameGraphic > ();
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM\\BGM_NAME_NoBGM.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM\\BGM_NAME_Sae.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM\\BGM_NAME_Ouka.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM\\BGM_NAME_Retsudou.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM\\BGM_NAME_GYAVA.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM\\BGM_NAME_FERARIA.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM\\BGM_NAME_TSUKI.png" );
		m_bgmName->AddTexture_FromArchive ( U"Battle\\BGM\\BGM_NAME_REINA.png" );

		GRPLST_INSERT ( m_bgmName );

		//初期位置(バトルメイン)
		m_bgmName->SetPos ( VEC2 ( BGM_X, BGM_Y ) );
	}

	BGM_Name::~BGM_Name ()
	{
	}

	void BGM_Name::Load ()
	{
		m_bgmName->SetPos ( m_pos );
		m_bgmName->SetZ ( Z_BG - 0.01f );
	}

	const float BGM_Name::BGM_X = 640 - (303 / 2);
	const float BGM_Name::BGM_Y = 920;



}	//namespace GAME

