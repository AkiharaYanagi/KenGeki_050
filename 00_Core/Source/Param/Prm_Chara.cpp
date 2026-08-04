//=================================================================================================
//
//	Prm_Chara
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "00_Core/Prm_Chara.h"
#include "LoadCharaBin_s3d.h"
#include "LoadImgFile.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#pragma region FILE_NAME

	//キャラメインデータファイル .scp
	//キャライメージファイル bhv 1p/2p .atls
	//キャラエフェクトイメージファイル gns.atls

	constexpr char32_t CHARA_SCP_OUKA []	= U"chara\\Ouka.scp";
	constexpr char32_t CHARA_ATLS1_OUKA []	= U"Chara\\Ouka_1p_bhv.atls";
	constexpr char32_t CHARA_ATLS2_OUKA []	= U"Chara\\Ouka_2p_bhv.atls";
	constexpr char32_t CHARA_ATLS_EF_OUKA []	= U"Chara\\Ouka_gns.atls";

	constexpr char32_t CHARA_SCP_SAE []		= U"Chara\\Sae.scp";
	constexpr char32_t CHARA_ATLS1_SAE []	= U"Chara\\Sae_1p_bhv.atls";
	constexpr char32_t CHARA_ATLS2_SAE []	= U"Chara\\Sae_2p_bhv.atls";
	constexpr char32_t CHARA_ATLS_EF_SAE []	= U"Chara\\Sae_gns.atls";

	constexpr char32_t CHARA_SCP_RETSU []	= U"Chara\\Retsudou.scp";
	constexpr char32_t CHARA_ATLS1_RETSU []	= U"Chara\\Retsudou_1p_bhv.atls";
	constexpr char32_t CHARA_ATLS2_RETSU []	= U"Chara\\Retsudou_2p_bhv.atls";
	constexpr char32_t CHARA_ATLS_EF_RETSU []	= U"Chara\\Retsudou_gns.atls";

	constexpr char32_t CHARA_SCP_GYAVA []	= U"Chara\\Gabadaruga.scp";
	constexpr char32_t CHARA_ATLS1_GYAVA []	= U"Chara\\Gabadaruga_1p_bhv.atls";
	constexpr char32_t CHARA_ATLS2_GYAVA []	= U"Chara\\Gabadaruga_2p_bhv.atls";
	constexpr char32_t CHARA_ATLS_EF_GYAVA []	= U"Chara\\Gabadaruga_gns.atls";

	constexpr char32_t CHARA_SCP_FERA []	= U"Chara\\Ferallia.scp";
	constexpr char32_t CHARA_ATLS1_FERA []	= U"Chara\\Ferallia_1p_bhv.atls";
	constexpr char32_t CHARA_ATLS2_FERA []	= U"Chara\\Ferallia_2p_bhv.atls";
	constexpr char32_t CHARA_ATLS_EF_FERA []	= U"Chara\\Ferallia_gns.atls";

	constexpr char32_t CHARA_SCP_TUKI []	= U"Chara\\Tsukihibosi.scp";
	constexpr char32_t CHARA_ATLS1_TUKI []	= U"Chara\\Tsukihibosi_1p_bhv.atls";
	constexpr char32_t CHARA_ATLS2_TUKI []	= U"Chara\\Tsukihibosi_2p_bhv.atls";
	constexpr char32_t CHARA_ATLS_EF_TUKI []	= U"Chara\\Tsukihibosi_gns.atls";

	constexpr char32_t CHARA_ATLS2_REINA []	= U"Chara\\Reina_2p_bhv.atls";
	constexpr char32_t CHARA_ATLS1_REINA []	= U"Chara\\Reina_1p_bhv.atls";
	constexpr char32_t CHARA_SCP_REINA []	= U"Chara\\Reina.scp";
	constexpr char32_t CHARA_ATLS_EF_REINA []	= U"Chara\\Reina_gns.atls";

	constexpr char32_t CHARA_ATLS2_EIYUU []	= U"Chara\\Eiyuu_2p_bhv.atls";
	constexpr char32_t CHARA_ATLS1_EIYUU []	= U"Chara\\Eiyuu_1p_bhv.atls";
	constexpr char32_t CHARA_SCP_EIYUU []	= U"Chara\\Eiyuu.scp";
	constexpr char32_t CHARA_ATLS_EF_EIYUU []	= U"Chara\\Eiyuu_gns.atls";




#pragma endregion



	void Prm_Chara::Load ()
	{
		//既に読み込んでいる場合、何もしない
		if ( m_pChara != nullptr ) { return; }

		//---------------------------------------------------
		//スクリプト　
		PRINT_F_S( U"スクリプト" );
		m_pChara = std::make_shared < Chara > ();	//キャラデータ実体
		LoadCharaBin_s3d lcb;
		lcb.Load ( m_filename_scp, * m_pChara );
		PRINT_F_S( U"OK" );


		//---------------------------------------------------
		//アトラス
		PRINT_F_S( U"アトラス：メインイメージ" );

		m_atlas_clr1 = LoadAtlasFilePng ( m_filename_atls_1p );
		m_atlas_clr2 = LoadAtlasFilePng ( m_filename_atls_2p );

		//キャラに設置(初期値1p)
		m_pChara->GetBehavior ().SetpAtlas ( m_atlas_clr1 );

		PRINT_F_S( U"OK" );


		PRINT_F_S( U"アトラス：Efイメージ" );

		m_atlas_ef = LoadAtlasFilePng ( m_filename_atls_ef );

		//キャラに設置(初期値1p)
		m_pChara->GetGarnish ().SetpAtlas ( m_atlas_ef );

		PRINT_F_S( U"OK" );
	
	}


	//個別キャラデータを取得 (未ロード時はロードしてから取得)
	P_Chara Prm_Chara::GetpChara ( CHARA_COLOR clr )
	{
		PRINT_F_S( U"スクリプト" );
		//スクリプト部
		if ( nullptr == m_pChara )
		{
			m_pChara = std::make_shared < Chara > ();	//キャラデータ実体
			LoadCharaBin_s3d lcb;
			lcb.Load ( m_filename_scp, * m_pChara );
		}
		PRINT_F_S( U"OK" );

		//---------------------------------------------------
		//アトラス
		PRINT_F_S( U"アトラス：メイン" );

		//カラー別
		//既に読込済みなら飛ばす
		if ( CH_CLR_1 == clr )
		{
			if ( m_atlas_clr1 == nullptr )
			{
				m_atlas_clr1 = LoadAtlasFilePng ( m_filename_atls_1p );
			}
			m_pChara->GetBehavior ().SetpAtlas ( m_atlas_clr1 );
		}
		else if ( CH_CLR_2 == clr )
		{
			if ( m_atlas_clr2 == nullptr )
			{
				m_atlas_clr2 = LoadAtlasFilePng ( m_filename_atls_2p );
			}
			m_pChara->GetBehavior ().SetpAtlas ( m_atlas_clr2 );
		}
		PRINT_F_S( U"OK" );
	

		PRINT_F_S( U"アトラス：EF" );

		m_atlas_ef = LoadAtlasFilePng ( m_filename_atls_ef );
		m_pChara->GetGarnish ().SetpAtlas ( m_atlas_ef );

		PRINT_F_S( U"OK" );


		return m_pChara;
	}

	//-----------------------------------------

	Prm_Chara_all::Prm_Chara_all ()
	{
		m_Ouka.SetStrScp	( CHARA_SCP_OUKA );
		m_Sae.SetStrScp	( CHARA_SCP_SAE );
		m_Retsu.SetStrScp ( CHARA_SCP_RETSU );
		m_Gyava.SetStrScp	( CHARA_SCP_GYAVA );
		m_Fera.SetStrScp	( CHARA_SCP_FERA );
		m_Tsuki.SetStrScp ( CHARA_SCP_TUKI );
		m_Reina.SetStrScp ( CHARA_SCP_REINA );
		m_Eiyuu.SetStrScp ( CHARA_SCP_EIYUU );

		m_Ouka.SetStrAtls ( CHARA_ATLS1_OUKA, CHARA_ATLS2_OUKA, CHARA_ATLS_EF_OUKA );
		m_Sae.SetStrAtls ( CHARA_ATLS1_SAE, CHARA_ATLS2_SAE, CHARA_ATLS_EF_SAE );
		m_Retsu.SetStrAtls ( CHARA_ATLS1_RETSU, CHARA_ATLS2_RETSU, CHARA_ATLS_EF_RETSU );
		m_Gyava.SetStrAtls ( CHARA_ATLS1_GYAVA, CHARA_ATLS2_GYAVA, CHARA_ATLS_EF_GYAVA );
		m_Fera.SetStrAtls ( CHARA_ATLS1_FERA, CHARA_ATLS2_FERA, CHARA_ATLS_EF_FERA );
		m_Tsuki.SetStrAtls ( CHARA_ATLS1_TUKI, CHARA_ATLS2_TUKI, CHARA_ATLS_EF_TUKI );
		m_Reina.SetStrAtls ( CHARA_ATLS1_REINA, CHARA_ATLS2_REINA, CHARA_ATLS_EF_REINA );
		m_Eiyuu.SetStrAtls ( CHARA_ATLS1_EIYUU, CHARA_ATLS2_EIYUU, CHARA_ATLS_EF_EIYUU );
	}


	Prm_Chara_all::~Prm_Chara_all ()
	{
		//非同期タスク開放
#if 0
		if ( m_task.isValid () )
		{
			m_abort = true;
			m_task.wait ();
		}
#endif // 0

		if ( m_asyncLoad_Ouka.isValid () ) { m_asyncLoad_Ouka.wait (); }
		if ( m_asyncLoad_Sae_.isValid () ) { m_asyncLoad_Sae_.wait (); }
		if ( m_asyncLoad_Retu.isValid () ) { m_asyncLoad_Retu.wait (); }
		if ( m_asyncLoad_Gaba.isValid () ) { m_asyncLoad_Gaba.wait (); }
		if ( m_asyncLoad_Fera.isValid () ) { m_asyncLoad_Fera.wait (); }
		if ( m_asyncLoad_Tuki.isValid () ) { m_asyncLoad_Tuki.wait (); }
		if ( m_asyncLoad_Rein.isValid () ) { m_asyncLoad_Rein.wait (); }
		if ( m_asyncLoad_Eiyu.isValid () ) { m_asyncLoad_Eiyu.wait (); }
	}


	//すべて読込(非同期処理)
	void Prm_Chara_all::LoadAll_Async ()
	{
		PRINT_F_S ( U"Prm_Chara_all::LoadAll_Async" );

		m_asyncLoad_Ouka = s3d::Async ( _Load_Ouka, this );
		m_asyncLoad_Sae_ = s3d::Async ( _Load_Sae_, this );
		m_asyncLoad_Retu = s3d::Async ( _Load_Retu, this );
		m_asyncLoad_Gaba = s3d::Async ( _Load_Gaba, this );
		m_asyncLoad_Fera = s3d::Async ( _Load_Fera, this );
		m_asyncLoad_Fera = s3d::Async ( _Load_Tuki, this );
		m_asyncLoad_Rein = s3d::Async ( _Load_Rein, this );
	}

	//すべて読込(同期処理)
	void Prm_Chara_all::LoadAll_Sync ()
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_LoadAll_Sync" );


		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Ouka" );
		m_Ouka.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Ouka" );

		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Sae_" );
		m_Sae.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Sae_" );

		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Retu" );
		m_Retsu.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Retu" );

		PRINT_F_S ( U"Start Prm_Chara_all::_Load_m_Gaba" );
		m_Gyava.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_m_Gaba" );

		PRINT_F_S ( U"Start Prm_Chara_all::_Load_m_Fera" );
		m_Fera.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_m_Fera" );

		PRINT_F_S ( U"Start Prm_Chara_all::_Load_m_Fera" );
		m_Tsuki.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_m_Fera" );

		PRINT_F_S ( U"Start Prm_Chara_all::_Load_m_Reina" );
		m_Reina.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_m_Reina" );

		PRINT_F_S ( U"Start Prm_Chara_all::_Load_m_Eiyuu" );
		m_Eiyuu.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_m_Eiyuu" );


		PRINT_F_S ( U"End Prm_Chara_all::_LoadAll_Sync" );
	}


	//すべて読込
	void Prm_Chara_all::_LoadAll ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_LoadAll" );
		pThis->m_Ouka.Load ();
		pThis->m_Sae.Load ();
		pThis->m_Retsu.Load ();
		pThis->m_Gyava.Load ();
		pThis->m_Fera.Load ();
		pThis->m_Tsuki.Load ();
		pThis->m_Reina.Load ();
		pThis->m_Reina.Load ();
		pThis->m_Eiyuu.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_LoadAll" );
	}

	void Prm_Chara_all::_Load_Ouka ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Ouka" );
		pThis->m_Ouka.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Ouka" );
	}

	void Prm_Chara_all::_Load_Sae_ ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Sae_" );
		pThis->m_Sae.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Sae_" );
	}

	void Prm_Chara_all::_Load_Retu ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Retu" );
		pThis->m_Retsu.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Retu" );
	}

	void Prm_Chara_all::_Load_Gaba ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Gaba" );
		pThis->m_Gyava.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Gaba" );
	}

	void Prm_Chara_all::_Load_Fera ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Fera" );
		pThis->m_Fera.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Fera" );
	}

	void Prm_Chara_all::_Load_Tuki ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Fera" );
		pThis->m_Tsuki.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Fera" );
	}

	void Prm_Chara_all::_Load_Rein ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Reina" );
		pThis->m_Reina.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Reina" );
	}

	void Prm_Chara_all::_Load_Eiyu ( Prm_Chara_all * pThis )
	{
		PRINT_F_S ( U"Start Prm_Chara_all::_Load_Eiyuu" );
		pThis->m_Eiyuu.Load ();
		PRINT_F_S ( U"End Prm_Chara_all::_Load_Eiyuu" );
	}


	//キャラ名とカラーからデータポインタを取得
	P_Chara Prm_Chara_all::GetpChara ( CHARA_NAME name, CHARA_COLOR clr )
	{
		switch ( name )
		{
		case CHARA_OUKA:
			PRINT_F_S ( U"GetpChara ( CHARA_OUKA, CLR_{} )"_fmt((int32)clr) );
			if ( m_asyncLoad_Ouka.isValid () )
			{
				m_asyncLoad_Ouka.wait ();
			}
			return m_Ouka.GetpChara ( clr );

		case CHARA_SAE:
			PRINT_F_S ( U"GetpChara ( CHARA_SAE, CLR_{} )"_fmt((int32)clr) );
			if ( m_asyncLoad_Sae_.isValid () ) { m_asyncLoad_Sae_.wait (); }
			return m_Sae.GetpChara ( clr );

		case CHARA_RETSUDOU:
			PRINT_F_S ( U"GetpChara ( CHARA_RETSUDOU, CLR_{} )"_fmt((int32)clr) );
			if ( m_asyncLoad_Retu.isValid () ) { m_asyncLoad_Retu.wait (); }
			return m_Retsu.GetpChara ( clr );

		case CHARA_GYAVADARUGA:
			PRINT_F_S ( U"GetpChara ( CHARA_GABADARUGA, CLR_{} )"_fmt((int32)clr) );
			if ( m_asyncLoad_Gaba.isValid () ) { m_asyncLoad_Gaba.wait (); }
			return m_Gyava.GetpChara ( clr );

		case CHARA_FERARIA:
			PRINT_F_S ( U"GetpChara ( CHARA_FERARIA, CLR_{} )"_fmt((int32)clr) );
			if ( m_asyncLoad_Fera.isValid () ) { m_asyncLoad_Fera.wait (); }
			return m_Fera.GetpChara ( clr );

		case CHARA_TSUKIHIBOSHI:
			PRINT_F_S ( U"GetpChara ( CHARA_TSUKIHIBOSHI, CLR_{} )"_fmt((int32)clr) );
			if ( m_asyncLoad_Tuki.isValid () ) { m_asyncLoad_Tuki.wait (); }
			return m_Tsuki.GetpChara ( clr );

		case CHARA_REINA:
			PRINT_F_S ( U"GetpChara ( CHARA_REINA, CLR_{} )"_fmt((int32)clr) );
			if ( m_asyncLoad_Rein.isValid () ) { m_asyncLoad_Rein.wait (); }
			return m_Reina.GetpChara ( clr );

		case CHARA_EIYUU:
			PRINT_F_S ( U"GetpChara ( CHARA_EIYUU, CLR_{} )"_fmt((int32)clr) );
			if ( m_asyncLoad_Eiyu.isValid () ) { m_asyncLoad_Eiyu.wait (); }
			return m_Eiyuu.GetpChara ( clr );
		}

		return m_Ouka.GetpChara ( clr );
	}


}	//namespace GAME

