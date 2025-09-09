//=================================================================================================
//
//	Chara ヘッダファイル
//		キャラクタのデータを管理する
//		イメージ、スクリプト、コマンド
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//ライブラリ利用
#include "Define_Siv3D.h"

//本プロジェクト利用
#include "Chara_Const.h"
#include "Compend.h"
#include "Command.h"
#if 0
#include "Chara_Define.h"
#include "Action.h"
#include "Effect.h"
#include "Behavior.h"
#endif // 0


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//==================================================================================
	//	キャラ 実行上データ ver 050
	//	
	//	キャラ
	//		┣コンペンド	ビヘイビア
	//		┣コンペンド	ガーニッシュ
	//		┣[]コマンド
	//		┣[]ブランチ
	//		┣[]ルート
	// 
	//	コンペンド	
	//		┣[]スクリプト
	//			┣[]ルート
	//			┣[]Efジェネレート
	//
	//==================================================================================
	//
	// ->  サウンド（ボイス）をコンペンドが保持する
	// ->  アクションとエフェクトを同一化する
	// ->  共通アクション
	// ->  他スクリプト項目の増減
	//
	//==================================================================================
	//	キャラ 編集上データ ver 050
	// 
	//	キャラ
	//		┣キャラセット		コモン(共通)	
	//		┣キャラセット		パーソナル(個別)
	// 
	//	キャラセット
	//		┣コンペンド	ビヘイビア
	//		┣コンペンド	ガーニッシュ
	// 
	// ->編集時に分割(名前で分類)し、実行上は統合(ID)する
	// //IDでも、名前指定でも、共通と固有を同列で並べ、参照時に分岐する
	//==================================================================================

	class Chara
	{
		Compend		behavior;
		Compend		garnish;
#if 0

//		Behavior		m_bhvMain;		//メイン スクリプト
		PAP_Tx			mpap_txMain;	//メインイメージ テクスチャ配列
		PAP_Action		mpap_Action;	//アクション配列

//		Garnish			m_bhvEf;		//EF スクリプト
		PAP_Tx			mpap_txEf;		//EFイメージ テクスチャ配列
		PAP_Effect		mpap_Ef;		//エフェクト配列
#endif // 0

		AP_Cmd		ma_pCmd;	//コマンド配列
		AP_Brc		ma_pBrc;	//ブランチ配列
		AP_Rut		ma_pRut;	//ルート配列

	public:
		Chara ();
		Chara ( const Chara & rhs ) = delete;
		~Chara ();

		void Clear ();


		Compend & GetBehavior () { return behavior; }
		Compend & GetGarnish  () { return garnish; }

#if 0

		//アクション配列にまとめて設定
		void SetpAction ( UP_AP_Sqc papAction );
//		void AddpSequence ( std::shared_ptr < P_Sqc [] > arypSequence, rsize_t size );
//		void AddpSequence ( const std::vector < P_Sqc > & arypSequence, rsize_t size );P_Sqc

		//エフェクト配列にまとめて設定
		void SetpEffect ( UP_AP_Sqc papEffect );

#endif // 0


		//テクスチャ配列の設定
		void SetpapTx_Main ( PAP_Tx paptx ) { behavior.SetpapTx_Main ( paptx ); }
		void SetpapTx_Ef ( PAP_Tx paptx ) { garnish.SetpapTx_Main ( paptx ); }

#if 0
		//-----------------------------------------------------------------
		//メインイメージ テクスチャ配列ポインタ
//		PVP_TxBs GetpvpMainTexture () const { return m_pvpTxMain; }
		PAP_Tx GetpapTxMain () const { return mpap_txMain; }

		//メインイメージ テクスチャ配列に追加
		void AddpMainTexture ( P_Tx pTexture ) { mpap_txMain->push_back ( pTexture ); }

		//メインイメージ テクスチャポインタの取得
		P_Tx GetpMainTexture ( UINT32 index ) const { return mpap_txMain->at ( index ); }

		//テクスチャ配列の設定
		void SetpapTx_Main ( PAP_Tx paptx ) { mpap_txMain = paptx; }


		//-----------------------------------------------------------------
		//アクション配列ポインタを取得
		PAP_Action GetpvpAction () const { return mpap_Action; }

		//アクション配列に追加
		void AddpAction ( P_Action pAction ) { mpap_Action->push_back ( pAction ); }

		//アクション配列にまとめて追加
		void AddpAction ( std::unique_ptr < P_Action [] > arypAction, rsize_t size );
		void AddpAction ( std::shared_ptr < P_Action [] > arypAction, rsize_t size );
		void AddpAction ( const std::vector < P_Action > & arypAction, rsize_t size );

		//---------------------------------------------------------------------
		//名前からアクションIDを取得する(無いときはNO_ACTION(0x7FFF0001)を返す)
		UINT32 GetActionID ( const s3d::String & name ) const;

		//指定アクション名が存在するかどうか
		bool ExistAction ( const s3d::String & name ) const;

		//アクションポインタを取得
		P_Action GetpAction ( UINT32 index ) const { return mpap_Action->at ( index ); }
		P_Action GetpAction ( const s3d::String & name ) const { return GetpAction ( GetActionID ( name ) ); }

		//---------------------------------------------------------------------
		//スクリプトポインタを取得
		P_Script GetpScript ( UINT32 indexAction, UINT32 indexScript ) { return mpap_Action->at ( indexAction )->GetpScript( indexScript ); }

		//次スクリプトが存在するかどうか
		bool IsNextScript ( UINT32 indexAction, UINT32 indexScript ) const
		{
			return mpap_Action->at ( indexAction )->IsNextScript( indexScript );
		}

		//-----------------------------------------------------------------
		//Efイメージ テクスチャ配列ポインタ
		PAP_Tx GetpapEfTexture () const { return mpap_txEf; }

		//Efイメージ テクスチャ配列に追加
		void AddpEfTexture ( P_Tx pTexture ) { mpap_txEf->push_back ( pTexture ); }

		//エフェクト配列にまとめて追加
		void AddpEffect ( std::unique_ptr < P_Effect [] > arypEffect, rsize_t size );
		void AddpEffect ( const std::vector < P_Effect > & arypEffect, rsize_t size );

		//指定エフェクト名が存在するかどうか
		bool ExistEffect ( const s3d::String & name ) const;

		//Efイメージ テクスチャポインタの取得
		P_Tx GetpEfTexture ( UINT32 index ) { return mpap_txEf->at ( index ); }

		//テクスチャ配列の設定
		void SetpapTx_Ef ( PAP_Tx paptx ) { mpap_txEf = paptx; }

		//-----------------------------------------------------------------
		//エフェクト配列に追加
		void AddpEffect ( P_Effect pEffect ) { mpap_Ef->push_back ( pEffect ); }

		//エフェクト配列ポインタを取得
		PAP_Effect GetpvpEffect () { return mpap_Ef; }

		//エフェクトポインタを取得
		P_Effect GetpEffect ( UINT32 index ) { return mpap_Ef->at ( index ); }
#endif // 



		//---------------------------------------------------------------------
		//コマンド配列に追加
		void AddpCommand ( P_Cmd pCmd ) { ma_pCmd.push_back ( pCmd ); }
		void SetaCommand ( UP_AP_Cmd paCmd );

		//ブランチ配列に追加
		void AddpBranch ( P_Brc pBrc ) { ma_pBrc.push_back ( pBrc ); }
		void SetaBranch ( UP_AP_Brc paBrc );

		//ルート配列に追加
		void AddpRoute ( P_Rut pRut ) { ma_pRut.push_back ( pRut ); }
		void SetaRoute ( UP_AP_Rut paRut );

#if 0
		//---------------------------------------------------------------------
		//コマンド配列に追加
		void AddpCommand ( P_Command pCommand ) { m_vpCommand.push_back ( pCommand ); }
		void AddaCommand ( std::unique_ptr < P_Command [] > aryCmd, UINT32 size );

		//コマンドを取得
		P_Command GetpCommand ( UINT32 indexCommand ) const { return m_vpCommand[indexCommand]; }
		const VP_Command & GetvpCommand () const { return m_vpCommand; }


		//ブランチ配列に追加
		void AddpBranch ( P_Branch pBranch ) { m_vpBranch.push_back ( pBranch ); }
		void AddaBranch ( std::unique_ptr < P_Branch [] > aryBrc, UINT32 size );

		//ブランチを取得
		P_Branch GetpBranch ( UINT32 indexBranch ) const { return m_vpBranch[indexBranch]; }
		const VP_Branch & GetvpBranch () const { return m_vpBranch; }


		//ルート配列に追加
		void AddpRoute ( P_Route pRoute ) { m_vpRoute.push_back ( pRoute ); }
		void AddaRoute ( std::unique_ptr < P_Route [] > aryRut, UINT32 size );

		//ルートを取得
		P_Route GetpRoute ( UINT32 indexRoute ) const { return m_vpRoute[indexRoute]; }
		const VP_Route & GetvpRoute () const { return m_vpRoute; }

#endif // 0
	};

	using P_Chara = std::shared_ptr < Chara >;
	using VP_Chara = std::vector < P_Chara >;
	using PVP_Chara = std::shared_ptr < VP_Chara >;


}	//namespace GAME


