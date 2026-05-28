//=================================================================================================
//
//	FtgMain ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "00_Core/Scene_lib.h"
//#include "Fighting/Fighting.h"
#include "00_Core/Menu/PauseMenu.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//前方宣言
	class Fighting; using P_FTG = std::shared_ptr < Fighting >;


	class FtgMain : public Scene_lib, public std::enable_shared_from_this < FtgMain >
	{
		//戦闘
		P_FTG			m_fighting;

		//ポーズメニュ
		P_PauseMenu		m_pauseMenu;
		//P_TrainingMenu		m_trainingMenu;

#if 0
		//ロード中
		P_PrmRect		m_rectLoad;
		UINT			m_wait;
		P_GrpStr		m_NowLoading;
#endif // 0


	public:
		FtgMain ();
		FtgMain ( const FtgMain & rhs ) = delete;
		~FtgMain ();

		void ParamInit ();
		void ParamReset () override;		//パラメータ再設定
		void Load ();
		void Move ();

		//--------------------------
		//状態遷移
		P_GameScene Transit ();
		//----------------------------------------
	private:
		//シーン移行
		P_CreateScene	mp_CreateResult;	//次のシーン
		P_CreateScene	mp_CreateCharaSele;	//次のシーン
		//----------------------------------------
	public:
		void SetpNext_Result ( P_CreateScene p ) { mp_CreateResult = p; }
		void Transit_Result () { SetpNextScene ( mp_CreateResult->Do() ); }
		void SetpNext_CharaSele ( P_CreateScene p ) { mp_CreateCharaSele = p; }
		void Transit_CharaSele () { SetpNextScene ( mp_CreateCharaSele->Do() ); }

		//--------------------------
#if 0
		//初期操作 プレイヤ/CPU 設定
		void Set_1P_vs_2P () { m_fighting->Set_1P_vs_2P (); }
		void Set_1P_vs_CPU () { m_fighting->Set_1P_vs_CPU (); }
		void Set_CPU_vs_CPU () { m_fighting->Set_CPU_vs_CPU (); }
#endif // 0
	};

	using P_FtgMain = std::shared_ptr < FtgMain >;


}	//namespace GAME


