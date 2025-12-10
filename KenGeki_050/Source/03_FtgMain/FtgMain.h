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
#include "../90_GameMain/Scene.h"
#include "Fighting/Fighting.h"
//#include "../80_Common/Menu/PauseMenu.h"
#include "../80_Common/Menu/TrainingMenu.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class FtgMain : public Scene, public std::enable_shared_from_this < FtgMain >
	{
		//戦闘
		P_FTG			m_fighting;

		//ポーズメニュ
		//P_PauseMenu		m_pauseMenu;
		P_TrainingMenu		m_trainingMenu;

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


