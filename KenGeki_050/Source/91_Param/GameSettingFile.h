//=================================================================================================
//
// ゲーム設定ファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../90_GameMain/GameConst.h"
#include "../90_GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{
	//ゲーム内設定
	class GameSettingFile
	{
		START_MODE		m_startMode { START_BATTLE };	//開始シーン指定
		bool			m_demo { F };			//デモモード(自動CPU_VS_CPU繰返)

		PLAYER_MODE		m_playerMode1p { MODE_PLAYER };	//１P操作
		PLAYER_MODE		m_playerMode2p { MODE_PLAYER };	//２P操作

		CHARA_NAME		m_name1p { CHARA_NAME_NUM };		//選択キャラ
		CHARA_NAME		m_name2p { CHARA_NAME_NUM };

		CHARA_COLOR		m_color1p { CH_CLR_1 };
		CHARA_COLOR		m_color2p { CH_CLR_2 };

		BGM_ID			m_bgm_id { BGM_ID_GABA };			//BGM_ID
		STAGE_NAME		m_stage_name { STAGE_YUUHINO_HARA };	//STAGE_NAME


	public:
		GameSettingFile ();
		GameSettingFile ( const GameSettingFile & rhs );	//コピー可能
		~GameSettingFile ();

		//読込
		void Load ();

		//保存
		void Save() const;

		//-----------------------------------------
		//値の取得

		//ゲームモード
		START_MODE GetStartMode () const { return m_startMode; }
	
		//プレイヤの種類
		PLAYER_MODE GetPlayerMode ( PLAYER_ID pid ) const
		{
			if ( pid == PLAYER_ID_1 ) { return m_playerMode1p; }
			if ( pid == PLAYER_ID_2 ) { return m_playerMode2p; }
			return MODE_PLAYER;
		}
		void SetPlayerMode ( PLAYER_MODE mode1p, PLAYER_MODE mode2p )
		{
			m_playerMode1p = mode1p;
			m_playerMode2p = mode2p;
		}
		PLAYER_MODE GetPlayerMode1p () const { return m_playerMode1p; }
		PLAYER_MODE GetPlayerMode2p () const { return m_playerMode2p; }
		void SetPlayerMode1p ( PLAYER_MODE mode ) { m_playerMode1p = mode; }
		void SetPlayerMode2p ( PLAYER_MODE mode ) { m_playerMode2p = mode; }

		//マッチモード(対戦上のプレイヤの組み合わせ)
		MUTCH_MODE GetMutchMode () const;
		void  SetMutchMode ( MUTCH_MODE mode );


		//キャラ名
		CHARA_NAME GetCharaName ( PLAYER_ID pid ) const;
		CHARA_NAME GetCharaName1p () const { return m_name1p; }
		CHARA_NAME GetCharaName2p () const { return m_name2p; }
		void SetCharaName ( PLAYER_ID pid, CHARA_NAME name );
		void SetCharaName1p ( CHARA_NAME name ) { m_name1p = name; }
		void SetCharaName2p ( CHARA_NAME name ) { m_name2p = name; }

		void SetCharaName_Rnd();

		//キャラカラー
		CHARA_COLOR GetCharaColor ( PLAYER_ID pid ) const;
		CHARA_COLOR GetCharaColor1p() const { return m_color1p; }
		CHARA_COLOR GetCharaColor2p() const { return m_color2p; }
		void SetCharaColor ( PLAYER_ID pid, CHARA_COLOR clr );
		void SetCharaColor1p ( CHARA_COLOR clr ) { m_color1p = clr; }
		void SetCharaColor2p ( CHARA_COLOR clr ) { m_color2p = clr; }

		void SetCharaClr_Rnd();

		//デモ (設定ファイルにも記録)
		GET_SET ( bool, GetDemo, SetDemo, m_demo )
		 
		//BGM
		GET_SET ( BGM_ID, GetBGM_ID, SetBGM_ID, m_bgm_id )

		void SetBGM_Rnd ();
		void NextBGM ();
		void PrevBGM ();
		 
		//Stage
		GET_SET ( STAGE_NAME, GetStage_Name, SetStage_Name, m_stage_name )
		 
		void SetStage_Rnd();
		 
		//-----------------------------------------

		//初期値
		void	SetDefault ();
	};

}	//namespace GAME

