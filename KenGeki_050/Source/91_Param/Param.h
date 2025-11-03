//=================================================================================================
//
// シーンパラメータ ヘッダ
//		シーン間の共通で用いる値
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameSettingFile.h"
#include "../90_GameMain/GameConst.h"
#include "../90_GameMain/SoundConst.h"
#include "../80_Common/Chara_TxSet.h"

#include "Chara.h"
#include "Prm_Chara.h"
#include "Prm_Result.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Param	: public GameParam
	{
		//戦闘（対戦種類：メイン, トレーニング) モード
		//(現在値なのでファイルには保存しない)
		FTG_MODE		m_FtgMode;

		//ゲーム設定 ( 外部ファイル読込 )
		GameSettingFile		m_setting;

		//キャラデータ（外部読込）
		Prm_Chara_all	m_prmChara_all;

		//リザルト用(内部のみ)
		Prm_Result		m_prmResult;

		//共通キャラテクスチャ
		P_Ch_TxSet		m_chTxSet;

	public:
		Param ();
		Param ( const Param & rhs );	//コピー可能
		~Param ();

		void Load ();


		//内部設定
		void SetFtgMode ( FTG_MODE mode ) { m_FtgMode = mode; }
		FTG_MODE GetFtgMode () const { return m_FtgMode; }


		//ゲーム設定 ( 外部ファイル読込 )
		GameSettingFile & GetGameSetting () { return m_setting; }
		void SetSettingFile ( const GameSettingFile & stg ) { m_setting = stg; }

		//設定ファイルにも記録
		BGM_ID Get_BGM_ID () const { return m_setting.GetBGM_ID (); }
		void Set_BGM_ID ( BGM_ID id ) { m_setting.SetBGM_ID ( id ); }

		//Chara
		Prm_Chara_all& GetPrmCharaAll () { return m_prmChara_all; }

		//キャラデータ事前読込
		void LoadCharaData_All ();

		//キャラ指定データ取得
		P_Chara GetpChara ( CHARA_NAME name, PLAYER_ID pl_id );

		//Result用
		Prm_Result&	GetPrmResult () { return m_prmResult; }

		//共通キャラテクスチャ
		void SetpChara_TxSet ( P_Ch_TxSet p );
		P_Ch_TxSet GetpChara_TxSet ();
	};

	using P_Param = std::shared_ptr < Param >;


}	//namespace GAME

