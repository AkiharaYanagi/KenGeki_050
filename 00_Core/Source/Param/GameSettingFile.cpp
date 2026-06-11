//=================================================================================================
//
// 設定ファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "00_Core/GameSettingFile.h"
#include <fstream>


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//コンストラクタ
	GameSettingFile::GameSettingFile ()
	{
	}

	//コピーコンストラクタ
	GameSettingFile::GameSettingFile ( const GameSettingFile & rhs )
	{
		m_startMode		= rhs.m_startMode;
		m_demo			= rhs.m_demo;
		m_playerMode1p	= rhs.m_playerMode1p;
		m_playerMode2p	= rhs.m_playerMode2p;
		m_name1p		= rhs.m_name1p;
		m_name2p		= rhs.m_name2p;
		m_color1p		= rhs.m_color1p;
		m_color2p		= rhs.m_color2p;
		m_bgm_id		= rhs.m_bgm_id;
		m_stage_name	= rhs.m_stage_name;
	}

	void GameSettingFile::Load ()
	{
		try
		{
			//入力ストリームを生成
			std::ifstream ifstrm ( _T( "GameSettings.dat" ), std::ios::in | std::ios::binary );

			//見つからないときデフォルトの値を設定して終了
			if (!ifstrm) { SetDefault(); return; }

			byte tempMode = 0;
			ifstrm.read( (char*)&tempMode, sizeof( byte ) );
			m_startMode = (START_MODE)tempMode;

			byte demo = 0;
			ifstrm.read( (char*)&demo, sizeof( bool ) );
			m_demo = (bool)demo;

			byte tempInput1p = 0;
			byte tempInput2p = 0;
			ifstrm.read( (char*)&tempInput1p, sizeof( byte ) );
			ifstrm.read( (char*)&tempInput2p, sizeof( byte ) );
			m_playerMode1p = (PLAYER_MODE)tempInput1p;
			m_playerMode2p = (PLAYER_MODE)tempInput2p;

			byte tempName1p = 0;
			byte tempName2p = 0;
			ifstrm.read( (char*)&tempName1p, sizeof( byte ) );
			ifstrm.read( (char*)&tempName2p, sizeof( byte ) );
			m_name1p = (CHARA_NAME)tempName1p;
			m_name2p = (CHARA_NAME)tempName2p;

			byte tempColor1p = 0;
			byte tempColor2p = 0;
			ifstrm.read( (char*)&tempColor1p, sizeof( byte ) );
			ifstrm.read( (char*)&tempColor2p, sizeof( byte ) );
			m_color1p = (CHARA_COLOR)tempColor1p;
			m_color2p = (CHARA_COLOR)tempColor2p;

			byte bgm = 0;
			ifstrm.read( (char*)&bgm, sizeof( byte ) );
			m_bgm_id = (BGM_ID)bgm;

			byte stage = 0;
			ifstrm.read( (char*)&stage, sizeof( byte ) );
			m_stage_name = (STAGE_NAME)stage;

			//終了
			ifstrm.close();

		}
		catch (...)
		{
			SetDefault ();
		}
	}

	GameSettingFile::~GameSettingFile ()
	{
	}

	void GameSettingFile::Save() const
	{
		try
		{
			//入力ストリームを生成
			std::ofstream ofstrm ( _T("GameSettings.dat"), std::ios::out | std::ios::binary );
			
			ofstrm.write ( (char*)&m_startMode, sizeof(byte));
			ofstrm.write ( (char*)&m_demo, sizeof ( bool ) );
			ofstrm.write ( (char*)&m_playerMode1p, sizeof ( byte ) );
			ofstrm.write ( (char*)&m_playerMode2p, sizeof ( byte ) );
			ofstrm.write ( (char*)&m_name1p, sizeof ( byte ) );
			ofstrm.write ( (char*)&m_name2p, sizeof ( byte ) );
			ofstrm.write ( (char*)&m_color1p, sizeof ( byte ) );
			ofstrm.write ( (char*)&m_color2p, sizeof ( byte ) );
			ofstrm.write ( (char*)&m_bgm_id, sizeof ( byte ) );
			ofstrm.write ( (char*)&m_stage_name, sizeof ( byte ) );

			//終了
			ofstrm.close ();
		}
		catch (...)
		{
			//エラー時何もしない
		}
	}
	
	void GameSettingFile::SetDefault ()
	{
		m_startMode = START_BATTLE;
		m_demo = F;
		m_playerMode1p = MODE_PLAYER;
		m_playerMode2p = MODE_PLAYER;
		m_name1p = CHARA_OUKA;
		m_name2p = CHARA_OUKA;
		m_color1p = CH_CLR_1;
		m_color2p = CH_CLR_2;
		m_bgm_id = BGM_ID::GYAVA;
		m_stage_name = STAGE_YUUHINO_HARA;
	}


	//プレイヤ別　キャラ名
	CHARA_NAME GameSettingFile::GetCharaName ( PLAYER_ID pid ) const
	{
		if ( pid == PLAYER_ID_1 ) { return m_name1p; }
		if ( pid == PLAYER_ID_2 ) { return m_name2p; }
		return CHARA_NAME_NUM;
	}

	void GameSettingFile::SetCharaName ( PLAYER_ID pid, CHARA_NAME name )
	{
		if ( pid == PLAYER_ID_1 ) { m_name1p = name; }
		if ( pid == PLAYER_ID_2 ) { m_name2p = name; }
	}

	void GameSettingFile::SetCharaName_Rnd ()
	{
#if 0
		m_name1p = static_cast < CHARA_NAME > ( s3d::Random ( 0, 4 ) );
		m_name2p = static_cast < CHARA_NAME > ( s3d::Random ( 0, 4 ) );
#endif // 0

		//1p
		switch ( s3d::Random ( 0, 5 ) )
		{
		case 0: m_name1p = CHARA_OUKA; break;
		case 1: m_name1p = CHARA_SAE; break;
		case 2: m_name1p = CHARA_RETSUDOU; break;
		case 3: m_name1p = CHARA_GYAVADARUGA; break;
		case 4: m_name1p = CHARA_FERARIA; break;
		case 5: m_name1p = CHARA_TSUKIHIBOSHI; break;
		default: break;
		}

		//2p
		switch ( s3d::Random ( 0, 5 ) )
		{
		case 0: m_name2p = CHARA_OUKA; break;
		case 1: m_name2p = CHARA_SAE; break;
		case 2: m_name2p = CHARA_RETSUDOU; break;
		case 3: m_name2p = CHARA_GYAVADARUGA; break;
		case 4: m_name2p = CHARA_FERARIA; break;
		case 5: m_name2p = CHARA_TSUKIHIBOSHI; break;
		default: break;
		}
	}

	//プレイヤ別　キャラカラー
	CHARA_COLOR GameSettingFile::GetCharaColor ( PLAYER_ID pid ) const
	{
		if ( pid == PLAYER_ID_1 ) { return m_color1p; }
		if ( pid == PLAYER_ID_2 ) { return m_color2p; }
		return CH_CLR_1;
	}

	void GameSettingFile::SetCharaColor ( PLAYER_ID pid, CHARA_COLOR clr )
	{
		if ( pid == PLAYER_ID_1 ) { m_color1p = clr; }
		if ( pid == PLAYER_ID_2 ) { m_color2p = clr; }
	}

	void GameSettingFile::SetCharaClr_Rnd ()
	{
		m_color1p = static_cast < CHARA_COLOR > ( s3d::Random ( 0, 1 ) );
		m_color2p = static_cast < CHARA_COLOR > ( s3d::Random ( 0, 1 ) );
	}

	//BGM
	void GameSettingFile::SetBGM_Rnd ()
	{
		//NONEだけ弾く
		int i = s3d::Random ( 1, 5 );
		m_bgm_id = static_cast < BGM_ID > ( i );
	}

	void GameSettingFile::NextBGM ()
	{
		switch ( m_bgm_id  )
		{
		case BGM_ID::NONE:	m_bgm_id = BGM_ID::SAE; break;
		case BGM_ID::SAE :	m_bgm_id = BGM_ID::OUKA; break;
		case BGM_ID::OUKA:	m_bgm_id = BGM_ID::RETSU ; break;
		case BGM_ID::RETSU:	m_bgm_id = BGM_ID::GYAVA; break;
		case BGM_ID::GYAVA:	m_bgm_id = BGM_ID::FERA; break;
		case BGM_ID::FERA:	m_bgm_id = BGM_ID::TSUKI; break;
		case BGM_ID::TSUKI:	m_bgm_id = BGM_ID::REINA; break;
		case BGM_ID::REINA:	m_bgm_id = BGM_ID::NONE; break;
		}
	}

	void GameSettingFile::PrevBGM ()
	{
		switch ( m_bgm_id  )
		{
		case BGM_ID::NONE:	m_bgm_id = BGM_ID::REINA; break;
		case BGM_ID::SAE:	m_bgm_id = BGM_ID::NONE; break;
		case BGM_ID::OUKA:	m_bgm_id = BGM_ID::SAE; break;
		case BGM_ID::RETSU:	m_bgm_id = BGM_ID::OUKA; break;
		case BGM_ID::GYAVA:	m_bgm_id = BGM_ID::RETSU; break;
		case BGM_ID::FERA:	m_bgm_id = BGM_ID::GYAVA; break;
		case BGM_ID::TSUKI:	m_bgm_id = BGM_ID::FERA; break;
		case BGM_ID::REINA:	m_bgm_id = BGM_ID::TSUKI; break;
		}
	}

	//Stage
	void GameSettingFile::SetStage_Rnd ()
	{
		m_stage_name = static_cast < STAGE_NAME > ( s3d::Random ( 0, 8 ) );
	}


	//マッチモード(対戦上のプレイヤの組み合わせ)
	MUTCH_MODE GameSettingFile::GetMutchMode() const
	{
		MUTCH_MODE ret = MODE_PLAYER_PLAYER;
		PLAYER_MODE mode1p = m_playerMode1p;
		PLAYER_MODE mode2p = m_playerMode2p;

		if ( MODE_PLAYER == mode1p )
		{
				 if ( MODE_PLAYER == mode2p ) { ret = MODE_PLAYER_PLAYER; }
			else if ( MODE_CPU == mode2p ) { ret = MODE_PLAYER_CPU; }
			else if ( MODE_NETWORK == mode2p ) { ret = MODE_PLAYER_NETWORK; }
		}
		else if ( MODE_CPU == mode1p )
		{
				 if ( MODE_PLAYER == mode2p ) { ret = MODE_CPU_PLAYER; }
			else if ( MODE_CPU == mode2p ) { ret = MODE_CPU_CPU; }
		}

		return ret;
	}

	//マッチモード(対戦上のプレイヤの組み合わせ)
	void GameSettingFile::SetMutchMode( MUTCH_MODE mode )
	{
		switch ( mode )
		{
		case MODE_PLAYER_PLAYER:	SetPlayerMode ( MODE_PLAYER, MODE_PLAYER );	break;
		case MODE_PLAYER_CPU:		SetPlayerMode ( MODE_PLAYER, MODE_CPU );	break;
		case MODE_CPU_PLAYER:		SetPlayerMode ( MODE_CPU, MODE_PLAYER );	break;
		case MODE_CPU_CPU:			SetPlayerMode ( MODE_CPU, MODE_CPU );	break;
		case MODE_PLAYER_NETWORK:	SetPlayerMode ( MODE_PLAYER, MODE_NETWORK );	break;
		}
	}



}	//namespace GAME

