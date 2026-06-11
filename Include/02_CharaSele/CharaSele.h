//=================================================================================================
//
//	CharaSele ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

#include "00_Core/Scene_lib.h"
#include "00_Core/Param.h"
#include "00_Core/BattleTime.h"
#include "00_Core/BGM_Name.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//----------------------------------------
	//前方宣言
	class CharaSele_Stage; using P_CharaSele_Stage = std::shared_ptr < CharaSele_Stage >;
	class CharaSele_Menu; using P_CharaSele_Menu = std::shared_ptr < CharaSele_Menu >;
	class CharaSele_Player_Actor; using P_ChSl_Plr_Actor = std::shared_ptr < CharaSele_Player_Actor >;

	//----------------------------------------


	class CharaSele : public Scene_lib, public std::enable_shared_from_this < CharaSele >
	{
		//----------------------------------------
		//シーン移行
		P_CreateScene	mp_CreateTitle;		//次のシーン
		P_CreateScene	mp_CreateFighting;	//次のシーン
		P_CreateScene	mp_CreateTraining;	//次のシーン
		//----------------------------------------

		//背景
		P_CharaSele_Stage	m_stage;


		//上部メニュ
		P_CharaSele_Menu	m_menu;


		//開戦ボタン
		P_Grp		m_center_button;
		P_Grp		m_KaiSen;

		//1P,2P,CPU表示
		P_Grp		m_playerInput;
		P_Ob		m_pl_1p;
		P_Ob		m_pl_2p;

		//操作位置1P,2P
		P_Grp		m_input_pos;
		P_Ob		m_ob_input_1p;
		P_Ob		m_ob_input_2p;

		//トレーニング表示
		P_Grp		m_training;


		//アクタ・ステート
		P_ChSl_Plr_Actor	m_plrActor_1p;
		P_ChSl_Plr_Actor	m_plrActor_2p;


		//タイマ
		P_BattleTime		m_battleTime;

		//BGM名表示
#if 0
		P_Grp	m_bgmName;
#endif // 0
		P_BGM_Name		m_bgmName;

		//保存用共通パラメータ
		P_Param			m_pParam;

		//フェード (シーン移行フラグを兼ねる)
		P_FadeRect		m_fade_in;
		P_FadeRect		m_fade_toTitle;
		P_FadeRect		m_fade_toFighting;
		uint32			m_plus_wait { 0 };

	public:
		CharaSele ();
		CharaSele ( const CharaSele & rhs ) = delete;
		~CharaSele ();

		void ParamInit () override;
		void Load ();
		void Move ();

		P_GameScene Transit () override;


		void SetpNext_Fighting ( P_CreateScene p ) { mp_CreateFighting = p; }
		void Transit_Fighting () { Scene_lib::SetpNextScene ( mp_CreateFighting->Do() ); }

		void SetpNext_Training ( P_CreateScene p ) { mp_CreateTraining = p; }
		void Transit_Training () { Scene_lib::SetpNextScene ( mp_CreateTraining->Do() ); }

		void SetpNext_Title ( P_CreateScene p ) { mp_CreateTitle = p; }
		void Transit_Title () { Scene_lib::SetpNextScene ( mp_CreateTitle->Do() ); }


		//指定アクタがどちらの操作か取得
		PLAYER_ID GetInputPlayer ( PLAYER_ID id );

		bool IsWait ( PLAYER_ID id ) const;
		//入力開始
		void StartInput ( PLAYER_ID id );

		//メニュー移動
		void Menu_Next ();
		void Menu_Prev ();

	private:
		P_Grp MakepGrp ( const s3d::String & filename, float z );
		void Input ();
		void Save ();

		void SwitchMode ();

		//両者同一キャラ同一カラーか
		void PrimalColor1p2p ();	//カラー優先チェック
		bool SameCharaSameColor () const;


#pragma region CONST
		static const uint32 FADE_IN_T;
		static const uint32 FADE_OUT_T;

		static const UINT32 PL_INDEX_1P;
		static const UINT32 PL_INDEX_2P;
		static const UINT32 PL_INDEX_CPU;

		static const float PL_1P_X;
		static const float PL_2P_X;
		static const float PL_Y;

		static const float INPUT_1P_X;
		static const float INPUT_2P_X;
		static const float INPUT_Y;
#pragma endregion
	};

	using P_ChSl = std::shared_ptr < CharaSele >;


}	//namespace GAME


