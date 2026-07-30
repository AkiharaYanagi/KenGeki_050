//=================================================================================================
//
//	パラメータ　キャラ
//		事前読込やカラー指定のため保持するポインタ類
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameConst.h"
#include "Chara.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	
	//-----------------------------------------
	//キャラ個別データ
	class Prm_Chara
	{
		//キャラポインタ
		P_Chara		m_pChara { nullptr };

		//スクリプトファイル名
		LPCUSTR		m_filename_scp { U"" };

#if 0
		//キャラカラー
		PAP_Tx		m_papTx_clr1 { nullptr };
		PAP_Tx		m_papTx_clr2 { nullptr };

		//共通エフェクト
		PAP_Tx		m_papTx_gns { nullptr };

		//イメージファイル名
		LPCUSTR		m_filename_img_1p { U"" };
		LPCUSTR		m_filename_img_2p { U"" };

		//エフェクトイメージファイル名
		LPCUSTR		m_filename_gns { U"" };
#endif // 0


		//アトラスファイル名
		LPCUSTR		m_filename_atls_1p { U"" };	
		LPCUSTR		m_filename_atls_2p { U"" };	
		LPCUSTR		m_filename_atls_ef { U"" };	

		//atlas
		P_Atlas		m_atlas_clr1 { nullptr };
		P_Atlas		m_atlas_clr2 { nullptr };
		P_Atlas		m_atlas_ef   { nullptr };

	public:
		Prm_Chara ();
		Prm_Chara ( const Prm_Chara & rhs );	//コピー可能
		~Prm_Chara ();

		//すべて読込
		void Load ();

		//個別キャラデータを取得 (未ロード時はロードしてから取得)
		P_Chara GetpChara ( CHARA_COLOR clr );


		//スクリプトファイル名を設定
		void SetStrScp ( LPCUSTR pStr ) { m_filename_scp = pStr; }

#if 0

		//イメージファイル名を設定
		void SetStrImg_1p ( LPCUSTR pStr ) { m_filename_img_1p = pStr; }
		void SetStrImg_2p ( LPCUSTR pStr ) { m_filename_img_2p = pStr; }

		//エフェクトイメージファイル名を設定
		void SetStrGns ( LPCUSTR pStr ) { m_filename_gns = pStr; }

		//すべてのファイル名設定
		void SetFileName ( LPCUSTR SCP, LPCUSTR IMG1, LPCUSTR IMG2, LPCUSTR GNS );

#endif // 0

		//アトラスファイル名を設定
		void SetStrAtls_1p ( LPCUSTR pStr ) { m_filename_atls_1p = pStr; }
		void SetStrAtls_2p ( LPCUSTR pStr ) { m_filename_atls_2p = pStr; }
		void SetStrAtls_ef ( LPCUSTR pStr ) { m_filename_atls_ef = pStr; }
		void SetStrAtls ( LPCUSTR pStr1p, LPCUSTR pStr2p, LPCUSTR pStref )
		{
			m_filename_atls_1p = pStr1p; 
			m_filename_atls_2p = pStr2p; 
			m_filename_atls_ef = pStref; 
		}
	};


	//-----------------------------------------
	//全キャラ分
	class Prm_Chara_all
	{
		//非同期処理
		s3d::AsyncTask < void >	m_asyncLoad_Ouka;
		s3d::AsyncTask < void >	m_asyncLoad_Sae_;
		s3d::AsyncTask < void >	m_asyncLoad_Retu;
		s3d::AsyncTask < void >	m_asyncLoad_Gaba;
		s3d::AsyncTask < void >	m_asyncLoad_Fera;
		s3d::AsyncTask < void >	m_asyncLoad_Tuki;
		s3d::AsyncTask < void >	m_asyncLoad_Rein;

		//終了ミューテックス
		std::mutex				m_mutex;

		//中断フラグ
		std::atomic < bool >	m_abort { F };


		//キャラデータ
		Prm_Chara		m_Ouka;
		Prm_Chara		m_Sae;
		Prm_Chara		m_Retsu;
		Prm_Chara		m_Gyava;
		Prm_Chara		m_Fera;
		Prm_Chara		m_Tsuki;
		Prm_Chara		m_Reina;


	public:
		Prm_Chara_all ();
		//Prm_Chara_all ( const Prm_Chara_all & rhs );	//コピー可能
		Prm_Chara_all ( const Prm_Chara_all & rhs ) = delete;	//コピー不可
		~Prm_Chara_all ();


		//すべて読込
		void LoadAll_Async ();
		void LoadAll_Sync ();

		//キャラ名とカラーからデータポインタを取得
		P_Chara GetpChara ( CHARA_NAME name, CHARA_COLOR clr );


	private:
		static void _LoadAll ( Prm_Chara_all * pThis );

		static void _Load_Ouka ( Prm_Chara_all * pThis );
		static void _Load_Sae_ ( Prm_Chara_all * pThis );
		static void _Load_Retu ( Prm_Chara_all * pThis );
		static void _Load_Gaba ( Prm_Chara_all * pThis );
		static void _Load_Fera ( Prm_Chara_all * pThis );
		static void _Load_Tuki ( Prm_Chara_all * pThis );
		static void _Load_Rein ( Prm_Chara_all * pThis );
	};


}	//namespace GAME

