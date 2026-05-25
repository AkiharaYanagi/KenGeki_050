//=================================================================================================
//
// シーンパラメータ ソース
//		シーン間の共通で用いる値
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Param.h"
#include "LoadCharaBin_s3d.h"
#include "LoadImgFile.h"

#include "../Const/FtgConst.h"
//#include "../GameMain/DebugDisp.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Param::Param ()
	{
	}

	//コピーコンストラクタ
	Param::Param ( const Param & rhs )
	{
		m_setting = rhs.m_setting;
//		m_prmChara_all = rhs.m_prmChara_all;
		m_prmResult = rhs.m_prmResult;
	}

	Param::~Param ()
	{
	}

	void Param::Load()
	{
		m_setting.Load ();		//ゲーム設定ファイル読込
//		PRINT_F_S ( U"Param::Load{} Start_Mode = {}"_fmt ( m_setting.GetStartMode() ) );
	}

	//-----------------------------------------------------------------
	//各キャラの読込


	//全キャラ先に読込
	void Param::LoadCharaData_All ()
	{
		//非同期処理
//		m_prmChara_all.LoadAll_Async ();

		//同期処理
		m_prmChara_all.LoadAll_Sync ();
	}


	//-----------------------------------------------------------------
	//	テスト用バトルから開始時は各使用キャラのみ


	//キャラ指定データ取得
	P_Chara Param::GetpChara(CHARA_NAME name, PLAYER_ID pl_id)
	{
		PRINT_F_S(U"Load {}P : name = {}"_fmt( (int32)pl_id, (int32)name ));

		//プレイヤ側でカラー番号を取得
		CHARA_COLOR clr = m_setting.GetCharaColor ( pl_id );
		return m_prmChara_all.GetpChara ( name, clr );
	}


	//共通キャラテクスチャ
	void Param::SetpChara_TxSet ( P_Ch_TxSet p )
	{
		m_chTxSet = p;
	}

	P_Ch_TxSet Param::GetpChara_TxSet ()
	{
		if ( ! m_chTxSet )
		{
			//未作成なら作成
			P_Ch_TxSet p = std::make_shared < Chara_TxSet > ();
			p->Load ();
			m_chTxSet = p;
		}
		return m_chTxSet;
	}



}	//namespace GAME

