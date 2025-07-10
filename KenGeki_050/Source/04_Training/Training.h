//=================================================================================================
//
//	Training ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../90_GameMain/Scene.h"



#if 0
#include "../FtgMain/Fighting/Fighting.h"
#include "../Menu/PauseMenu.h"
//#include "Training_Menu.h"
#endif // 0


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Training : public Scene, public std::enable_shared_from_this < Training >
	{
		//トレーニング表示
		P_Grp			m_training;
		P_Grp			m_training_Intro0;
		P_Grp			m_training_Intro1;

#if 0
		//戦闘
		P_FTG			m_fighting;
#endif // 0


#if 0
		//キー説明
		P_GrpAcv		m_keyIntro;

		//ロード中
		P_PrmRect		m_rectLoad;
		UINT			m_wait;
		P_GrpStr		m_NowLoading;

#endif // 0

#if 0

		//ポーズメニュ
		P_PauseMenu		m_pauseMenu;
//		P_Training_Menu		m_pauseMenu;

#endif // 0

		static const float	BX;
		static const float	BY;
		static const float	BX_KI;
		static const float	BY_KI;

	public:
		Training ();
		Training ( const Training & rhs ) = delete;
		~Training ();

		void ParamInit ();
		void Load ();
		void Init ();
		void Move ();

		P_GameScene Transit ();
	};


}	//namespace GAME


