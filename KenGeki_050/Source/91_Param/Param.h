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

#if 0

		//内部設定
		GAME_MODE		m_gameMode { MODE_TRAINING };
		MUTCH_MODE		m_mutchMode { MODE_PLAYER_PLAYER };
		CHARA_NAME		m_chara_name_1p { CHARA_NAME_NUM };
		CHARA_NAME		m_chara_name_2p { CHARA_NAME_NUM };
		STAGE_NAME		m_stage_name { STAGE_YUUHINO_HARA };

#endif // 0


		//キャラデータ（外部読込）
		Prm_Chara_all	m_prmChara_all;

		//リザルト用(内部のみ)
#if 0
		PLAYER_ID		m_winner { PLAYER_ID_1 };		//勝者
		int32		m_n_life_1p { 0 };		//残ライフ
		int32		m_n_life_2p { 0 };		//
		int32		m_n_input_1p { 0 };		//入力数
		int32		m_n_input_2p { 0 };		//
		int32		m_n_act_1p { 0 };		//アクション回数
		int32		m_n_act_2p { 0 };		//
		int32		m_n_offset { 0 };		//相殺数
		int32		m_n_max_chain_1p { 0 };		//連撃数
		int32		m_n_max_chain_2p { 0 };		//
		int32		m_n_max_damege_1p { 0 };		//最大連撃力
		int32		m_n_max_damege_2p { 0 };		//
#endif // 0
		Prm_Result	m_prmResult;


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

#if 0

		void SetMutchMode ( MUTCH_MODE mode );
		void SetMutchMode ( PLAYER_MODE mode1p, PLAYER_MODE mode2p );
		MUTCH_MODE GetMutchMode () const { return m_mutchMode; }

		PLAYER_MODE GetPlayerMode ( PLAYER_ID id ) const;

		void SetCharaName1p ( CHARA_NAME name )
		{
			m_setting.SetCharaName1p ( name );	//ファイルにも記録
			m_chara_name_1p = name;
		}
		CHARA_NAME GetCharaName1p () const { return m_chara_name_1p; }
		void SetCharaName2p ( CHARA_NAME name )
		{
			m_setting.SetCharaName2p ( name );	//ファイルにも記録
			m_chara_name_2p = name;
		}
		CHARA_NAME GetCharaName2p () const { return m_chara_name_2p; }
		CHARA_NAME GetCharaName ( PLAYER_ID id )
		{
			if ( PLAYER_ID_1 == id ) { return m_chara_name_1p; }
			else if ( PLAYER_ID_2 == id ) { return m_chara_name_2p; }
			return CHARA_NAME_NUM;
		}
		void SetRandomChara ();

//		GET_SET ( STAGE_NAME, GetStageName, SetStageName, m_stage_name	)		//bgm

		//設定ファイルにも記録
		BGM_ID Get_BGM_ID () const { return m_setting.GetBGM_ID (); }
		void Set_BGM_ID ( BGM_ID id ) { m_setting.SetBGM_ID ( id ); }

		STAGE_NAME GetStage_Name () const { return m_setting.GetStage_Name (); }
		void SetStage_Name ( STAGE_NAME stage ) { m_setting.SetStage_Name ( stage ); }

		bool GetDemo () const { return m_setting.GetDemo (); }
		void SetDemo ( bool b ) { m_setting.SetDemo ( b ); }


		//キャラデータ事前読込
		void LoadCharaData_All ();

		//キャラ指定データ取得
		P_Chara GetpChara ( CHARA_NAME name, PLAYER_ID player );

		//プレイヤ別　カラー取得
		CHARA_COLOR GetCharaColor ( PLAYER_ID pl_id ) const { return m_setting.GetColor ( pl_id ); }

		//カラー設定
		//void SetCharaColor ();
		void SetCharaColor1p ( CHARA_COLOR clr ) { m_setting.SetCharaColor1p ( clr ); }
		void SetCharaColor2p ( CHARA_COLOR clr ) { m_setting.SetCharaColor2p ( clr ); }

#endif // 0

		//Chara
		Prm_Chara_all& GetPrmCharaAll () { return m_prmChara_all; }

		//キャラ指定データ取得
		P_Chara GetpChara ( CHARA_NAME name, PLAYER_ID pl_id );

#if 0
		P_Chara GetpChara_Ouka ();
		P_Chara GetpChara_Sae ();
		P_Chara GetpChara_Retsudou ();
		P_Chara GetpChara_Gabadaruga ();
		bool IsReadChara () const { return m_read_chara; }

		//プレイヤ指定
		P_Chara GetpChara_Ouka ( PLAYER_ID player );
		P_Chara GetpChara_Sae ( PLAYER_ID player );
		P_Chara GetpChara_Retsudou ( PLAYER_ID player );
		P_Chara GetpChara_Gabadaruga ( PLAYER_ID player );

		//プレイヤ側でカラー番号を取得
		CHARA_COLOR GetClr ( PLAYER_ID id ) const;

		//キャラカラー
		void SetCharaColor1p ( CHARA_COLOR clr ) { m_setting.SetCharaColor1p ( clr ); }
		CHARA_COLOR GetCharaColor1p () const { return m_setting.GetColor1p (); }
		void SetCharaColor2p ( CHARA_COLOR clr ) { m_setting.SetCharaColor2p ( clr ); }
		CHARA_COLOR GetCharaColor2p () const { return m_setting.GetColor2p (); }

		//キャラとプレイヤ側でカラー番号別テクスチャ配列の参照
		PAP_Tx & GetPAP_Tx ( CHARA_NAME name, PLAYER_ID id );
		//キャラ名とプレイヤ側とカラー番号で読込ファイル名を取得
		LPCUSTR GetImgFileName ( CHARA_NAME name, PLAYER_ID id ) const;
		//ファイル名とキャラポインタで、指定カラー番号のテクスチャ配列を設置
		void SetImgClr ( P_Chara r_pch, CHARA_NAME name, PLAYER_ID id );

		//キャラとカラーを指定して事前読込
		void LoadCharaColor ( CHARA_NAME name, CHARA_COLOR clr );
		void SetPAP_Clr ( LPCUSTR filename, PAP_Tx & tgtPapBhv, PAP_Tx & tgtPapGns );
#endif // 0

		//Result用
		Prm_Result&	GetPrmResult () { return m_prmResult; }

#if 0

		void ResetBattleParam ();

		void UpdateIfMAX_DMG ( PLAYER_ID id, int n );
		void UpdateIfMax_Chain ( PLAYER_ID id, int n );
#endif // 0

	};

	using P_Param = std::shared_ptr < Param >;


}	//namespace GAME

