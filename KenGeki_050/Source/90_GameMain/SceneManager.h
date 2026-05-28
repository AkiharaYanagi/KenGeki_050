//=================================================================================================
//
// シーンマネージャ ヘッダ
//		ゲームシーンを管理
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "00_Core/Scene_lib.h"
#include "00_Core/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==================================================================
	//生成関数
	class CreateTitle : public CreateScene { public: P_Scene_lib Do (); };
	class CreateCharaSele : public CreateScene { public: P_Scene_lib Do (); };
	class CreateFtgMain : public CreateScene { public: P_Scene_lib Do (); };
	class CreateTraining : public CreateScene { public: P_Scene_lib Do (); };
	class CreateResult : public CreateScene { public: P_Scene_lib Do (); };


	//==================================================================
	//ゲーム状態遷移管理
	class SceneManager_lib	: public GameSceneManager
	{
		P_Param		m_pParam;	//シーン共通パラメータ

	public:
		SceneManager_lib ();
		SceneManager_lib ( const SceneManager_lib& rhs ) = delete;
		~SceneManager_lib ();

		void Load ();
		void Start ();

		//シーン共通パラメータ
		void SetpParam ( P_Param&& pParam ) { m_pParam = std::move ( pParam ); }
		P_Param GetpParam () { return m_pParam; }

	private:
		P_Scene_lib MakeTitle ();
		P_Scene_lib MakeCharaSele ();
		P_Scene_lib MakeFtgMain ();
		P_Scene_lib MakeTraining ();
		P_Scene_lib MakeResult ();
	};

	//==================================================================


}	//namespace GAME

