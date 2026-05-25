//=================================================================================================
//
// シーンヘッダ
//		ゲームシーンを用いた状態遷移
//		ゲーム内定義のパラメータ(Param)を共通で扱う
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "00_Core/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-----------------------------------------------
	//前方宣言
	class Scene_lib;
	using WP_Scene_lib = std::weak_ptr < Scene_lib >;
	using P_Scene_lib = std::shared_ptr < Scene_lib >;


	//-----------------------------------------------
	//ゲーム場面
	class Scene_lib : public GameScene //, public enable_shared_from_this < Scene >
	{
		//===========================================================
		//遷移先シーンポインタ
		//@info	thisを自身に保存すると循環参照となるのでweak_ptrを用いる
		WP_Scene_lib	mwp_This;
		P_Scene_lib		mp_Transit;		//遷移可能な次のシーン

		//===========================================================

	public:
		Scene_lib ();
		Scene_lib ( const Scene_lib & rhs ) = delete;
		~Scene_lib ();

		//==================================================
		//	Scene共通
		//==================================================

		//-----------------------------------------------
		//パラメータを用いた初期化インターフェース
		//パラメータの取得のあとの呼出1回保証 ( ParamInit(), Load(), Init() の順番 )
		//ParamInit()とは異なりデバイスリセットでも呼ばれない
		//Load()はデバイスリセットの度に呼ばれる
		//Init()は複数回呼ばれる可能性がある
		//virtual void ParamInit () = 0;
		
		//-----------------------------------------------
		//	※	継承先クラス宣言において
		//		, public enable_shared_from_this < ClassName >
		//		を多重継承しておく
		
		//-----------------------------------------------
		//	※	継承先
		//		Load ()内で shared_from_this()をScene側に登録する
		//		Scene::Load (); も呼ぶ
		void Load ();

		//-----------------------------------------------
		//	※	Transit () をオーバーライドするとき戻値を
		//			return Scene::Transit ();
		//		とする
		P_GameScene Transit ();

		//==================================================


		//共通パラメータ
		void SetpParam ( P_Param&& pParam )
		{
			GameScene::SetpParam ( pParam ); 
		}
		P_Param GetpParam ()
		{
			P_GameParam pgp = GameScene::GetpParam (); 
			P_Param pp = dynamic_pointer_cast < Param > ( pgp );
			return pp; 
		}

		//パラメータ再設定
		virtual void ParamReset () {}


		//遷移
		WP_Scene_lib GetwpThis () { return mwp_This; }
		void SetwpParentScene ( WP_Scene_lib wp ) { mwp_This = wp; }
		void SetwpThis ( WP_Scene_lib wp ) { mwp_This = wp; }

		//次のシーンを外部から設定
		void SetpNextScene ( P_Scene_lib p ) { mp_Transit = p; }
	};





}	//namespace GAME

