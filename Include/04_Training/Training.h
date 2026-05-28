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
#include "00_Core/Scene_lib.h"
#include "00_Core/Menu/TrainingMenu.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//前方宣言
	class Fighting; using P_FTG = std::shared_ptr < Fighting >;


	class Training : public Scene_lib, public std::enable_shared_from_this < Training >
	{
		//トレーニング表示
		P_Grp			m_training;
		P_Grp			m_training_Intro0;
		P_Grp			m_training_Intro1;

		//戦闘
		P_FTG			m_fighting;

		//ポーズメニュ(トレーニング専用)
		P_TrainingMenu		m_trainingMenu;

		static const float	BX;
		static const float	BY;
		static const float	BX_KI;
		static const float	BY_KI;

	public:
		Training ();
		Training ( const Training & rhs ) = delete;
		~Training ();

		void ParamInit ();
		void ParamReset () override;		//パラメータ再設定
		void Load ();
		void Init ();
		void Move ();

		P_GameScene Transit ();
	};

	using P_Training = std::shared_ptr < Training >;


}	//namespace GAME


