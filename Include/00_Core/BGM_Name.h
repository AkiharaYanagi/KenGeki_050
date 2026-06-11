//=================================================================================================
//
//	BGM_Name
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//BGM表示の共通テクスチャを保持する

	class BGM_Name
	{
		//BGM名
		P_Grp	m_bgmName;

		//位置
		VEC2	m_pos { VEC2 ( 0, 0 ) };

	public:
		BGM_Name ();
		BGM_Name ( const BGM_Name & rhs ) = delete;
		~BGM_Name ();

		void Load ();

		void SetPos ( VEC2 v ) { m_pos = v; }
		P_Grp GetpGrp () const { return m_bgmName; }

		void SetBGM ( BGM_ID bgm )
		{
			if ( bgm < BGM_ID::HERO )
			{
				m_bgmName->SetIndexTexture ( static_cast < int32 > ( bgm ) );
			}
		}

		//定数
		static const float BGM_X;
		static const float BGM_Y;
	};

	using P_BGM_Name = std::shared_ptr < BGM_Name >;


}	//namespace GAME

