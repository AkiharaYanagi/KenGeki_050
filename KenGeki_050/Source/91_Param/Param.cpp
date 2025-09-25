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

#include "../03_FtgMain/FtgConst.h"
//#include "../GameMain/DebugDisp.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Param::Param ()
	{
#if 0
		//ゲーム設定ファイル開始
		m_setting.Load ();

		m_chara_name_1p = m_setting.GetName1p ();
		m_chara_name_2p = m_setting.GetName2p ();

#endif // 0

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
	}

#if 0

	void Param::SetMutchMode ( MUTCH_MODE mode )
	{
		m_mutchMode = mode; 

		switch ( mode )
		{
		case MODE_PLAYER_PLAYER:	m_setting.SetPlayerMode ( MODE_PLAYER, MODE_PLAYER );	break;
		case MODE_PLAYER_CPU:		m_setting.SetPlayerMode ( MODE_PLAYER, MODE_CPU );	break;
		case MODE_CPU_PLAYER:		m_setting.SetPlayerMode ( MODE_CPU, MODE_PLAYER );	break;
		case MODE_CPU_CPU:			m_setting.SetPlayerMode ( MODE_CPU, MODE_CPU );	break;
		case MODE_PLAYER_NETWORK:	m_setting.SetPlayerMode ( MODE_PLAYER, MODE_NETWORK );	break;
		}
	}

	void Param::SetMutchMode ( PLAYER_MODE mode1p, PLAYER_MODE mode2p )
	{
		if ( MODE_PLAYER == mode1p )
		{
			if ( MODE_PLAYER == mode2p ) { m_mutchMode = MODE_PLAYER_PLAYER; }
			if ( MODE_CPU == mode2p ) { m_mutchMode = MODE_PLAYER_CPU; }
			if ( MODE_NETWORK == mode2p ) { m_mutchMode = MODE_PLAYER_NETWORK; }
		}
		else if ( MODE_CPU == mode1p )
		{
			if ( MODE_PLAYER == mode2p ) { m_mutchMode = MODE_CPU_PLAYER; }
			if ( MODE_CPU == mode2p ) { m_mutchMode = MODE_CPU_CPU; }
		}
	}

	PLAYER_MODE Param::GetPlayerMode ( PLAYER_ID id ) const
	{
		PLAYER_MODE pm = MODE_PLAYER;
		if ( id == PLAYER_ID_1 )
		{
			switch ( m_mutchMode )
			{
			case MODE_PLAYER_PLAYER:	pm = MODE_PLAYER;	break;
			case MODE_PLAYER_CPU:		pm = MODE_PLAYER; 	break;
			case MODE_CPU_PLAYER:		pm = MODE_CPU;	  	break;
			case MODE_CPU_CPU:			pm = MODE_CPU;	  	break;
			case MODE_PLAYER_NETWORK:	pm = MODE_PLAYER; 	break;
			default: break;
			}
		}
		if ( id == PLAYER_ID_2 )
		{
			switch ( m_mutchMode )
			{
			case MODE_PLAYER_PLAYER:	pm = MODE_PLAYER;	break;
			case MODE_PLAYER_CPU:		pm = MODE_CPU;	  	break;
			case MODE_CPU_PLAYER:		pm = MODE_PLAYER; 	break;
			case MODE_CPU_CPU:			pm = MODE_CPU;	  	break;
			case MODE_PLAYER_NETWORK:	pm = MODE_NETWORK; 	break;
			default: break;
			}
		}
		return pm;
	}

	void Param::SetRandomChara ()
	{
	}

	//-----------------------------------------------------------------
	//各キャラの読込


	//	タイトルから開始時は全キャラ先に読込
	void Param::LoadCharaData_All ()
	{
		//非同期処理
//		m_prmChara_all.LoadAll ();

		//同期処理
		m_prmChara_all._LoadAll ();
	}


	//-----------------------------------------------------------------
	//	テスト用バトルから開始時は各使用キャラのみ

#endif // 0

	//キャラ指定データ取得
	P_Chara Param::GetpChara(CHARA_NAME name, PLAYER_ID pl_id)
	{
		PRINT_F_S(U"Load {}P : name = {}\n"_fmt( (int32)pl_id, (int32)name ));

		//プレイヤ側でカラー番号を取得
		CHARA_COLOR clr = m_setting.GetColor ( pl_id );
		return m_prmChara_all.GetpChara ( name, clr );
	}

#if 0
	//-----------------------------------------------------------------
	void Param::ResetBattleParam ()
	{
		m_prmResult.Reset ();
	}

	//最大だったら更新する
	void Param::UpdateIfMAX_DMG ( PLAYER_ID id, int n )
	{
		m_prmResult.UpdateIfMAX_DMG ( id, n );
	}

	void Param::UpdateIfMax_Chain ( PLAYER_ID id, int n )
	{
		m_prmResult.UpdateIfMax_Chain ( id, n );
	}
#endif // 0


}	//namespace GAME

