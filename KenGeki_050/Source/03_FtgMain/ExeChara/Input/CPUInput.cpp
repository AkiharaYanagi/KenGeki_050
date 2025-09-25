//=================================================================================================
//
// CPUInput ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Branch.h"
#include "Action.h"
#include "CPUInput.h"
#include "GameKey.h"
#include "../Main/ExeChara.h"

#include <array>


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//CPU_AIの外部ファイル化

	//※ 乱数配分 の部分のみを外部ファイルにする

	// テキストファイル
	//	[n%] [行動ID]
	//	[m%] [行動ID]
	//	……

	//先頭から読んで、確率(%)が100以上で打ち切り

	//近 [%][ID]
	//中 [%][ID]
	//遠 [%][ID]

	//３種類

	CPUInput::CPUInput ( WP_ExeChara p, WP_ExeChara pOther )
	: m_pExeChara ( p ), m_pExeCharaOther ( pOther )
	, m_vGameKeyNum ( CPU_INPUT_GAMEKEY_NUM ), m_playerID ( PLAYER_ID_1 )
	, m_bAct ( false ), m_act ( CPU_NEUTRAL ), m_actTime ( 0 ), m_timer ( 0 )
	, m_testAct ( 0 )
	, m_actNear { 0 }, m_actMiddle{ 0 }, m_actFar{ 0 }
	, m_randomKeyNear { CPU_NEUTRAL }, m_randomKeyMiddle{ CPU_NEUTRAL }, m_randomKeyFar{ CPU_NEUTRAL }
	{
		//ゲームキーを規定数だけ確保
		for ( UINT i = 0; i < CPU_INPUT_GAMEKEY_NUM; ++ i )
		{
			GameKey gameKey;
			m_vGameKey.push_back ( gameKey );
		}
	}

	void CPUInput::Load ()
	{
		//---------------------------------------------------------------------
		//	※ 乱数配分
		//
		for ( UINT i = 0; i < CENT; ++ i )
		{
			m_randomKeyNear[i] = CPU_NEUTRAL;
			if		( i < 2  ) { m_randomKeyNear[i] = CPU_FRONT; }
			else if ( i < 4  ) { m_randomKeyNear[i] = CPU_BACK;	}
			else if ( i < 6  ) { m_randomKeyNear[i] = CPU_FRONT_DASH; }
			else if ( i < 8  ) { m_randomKeyNear[i] = CPU_BACK_DASH;	}
			else if ( i < 40 ) { m_randomKeyNear[i] = CPU_L; }
			else if ( i < 55 ) { m_randomKeyNear[i] = CPU_Ma; }
			else if ( i < 70 ) { m_randomKeyNear[i] = CPU_Mb; }
			else if ( i < 99 ) { m_randomKeyNear[i] = CPU_H; }

			m_randomKeyMiddle[i] = CPU_NEUTRAL;
			if		( i < 5  ) { m_randomKeyMiddle[i] = CPU_FRONT; }
			else if ( i < 10 ) { m_randomKeyMiddle[i] = CPU_BACK;	}
			else if ( i < 15 ) { m_randomKeyMiddle[i] = CPU_FRONT_DASH; }
			else if ( i < 20 ) { m_randomKeyMiddle[i] = CPU_BACK_DASH;	}
			else if ( i < 25 ) { m_randomKeyMiddle[i] = CPU_L; }
			else if ( i < 30 ) { m_randomKeyMiddle[i] = CPU_Ma; }
			else if ( i < 35 ) { m_randomKeyMiddle[i] = CPU_Mb; }
			else if ( i < 60 ) { m_randomKeyMiddle[i] = CPU_H; }

			m_randomKeyFar[i] = CPU_NEUTRAL;
			if		( i < 15 ) { m_randomKeyFar[i] = CPU_FRONT; }
			else if ( i < 17 ) { m_randomKeyFar[i] = CPU_BACK;	}
			else if ( i < 25 ) { m_randomKeyFar[i] = CPU_FRONT_DASH; }
			else if ( i < 27 ) { m_randomKeyFar[i] = CPU_BACK_DASH;	}
			else if ( i < 30 ) { m_randomKeyFar[i] = CPU_L; }
			else if ( i < 33 ) { m_randomKeyFar[i] = CPU_Ma; }
			else if ( i < 38 ) { m_randomKeyFar[i] = CPU_Mb; }
			else if ( i < 40 ) { m_randomKeyFar[i] = CPU_H; }
		}
		//
		//	※ 乱数配分 ここまで
		//---------------------------------------------------------------------

		//外部ファイル読込
		tifstream tifStrm;
		//エラー時はデフォルト値を使用して続行
		try
		{
			tifStrm.open ( _T("CPU_ACT.txt") );
			if ( ! tifStrm ) { throw std::runtime_error(" ! tifStrm"); }
			if ( ! tifStrm.is_open () ) { throw std::runtime_error(" ! tifStrm.is_open ()");  }
			if (   tifStrm.fail () ) { throw std::runtime_error("   tifStrm.fail ()");  }

			std::array < int, CPU_ACT_NUM * 3 > iBuf = { 0 };
			UINT index = 0;

			//ファイル末尾まで読込
			while ( ! tifStrm.eof() )
			{
				//1行読込
				tstring tstr = _T("");
				tifStrm >> tstr;

				//1文字ずつ処理
				bool bComp = false;
				UINT i = 0;
				TCHAR tchNum[2] = { 0 };	//10進数2桁 (0〜99)
				while ( tstr.size() != i )
				{
					TCHAR tch = tstr[i];

					// '['や改行は終了
					if ( '[' == tch || '\n' == tch ) { break; }

					tchNum [ i ] = tch;
					++i;
					if ( i == 2 ) { bComp = T; }
				}

				//完成時数値に変換
				if ( bComp )
				{
					iBuf[index] = ::_ttoi ( tchNum );
					++index;
					bComp = false;
				}
			}

			//保存
			for ( UINT i = 0; i < CPU_ACT_NUM; ++i )
			{
				m_actNear[i] = iBuf[ i ];
			}
			for ( UINT i = 0; i < CPU_ACT_NUM; ++i )
			{
				m_actMiddle[i] = iBuf[ CPU_ACT_NUM + i ];
			}
			for ( UINT i = 0; i < CPU_ACT_NUM; ++i )
			{
				m_actFar[i] = iBuf[ CPU_ACT_NUM * 2 + i];
			}

			for ( int i = 0; i < CENT; ++ i )
			{
				SetCPU_Act ( i, m_actNear, m_randomKeyNear [ i ] );
				SetCPU_Act ( i, m_actMiddle, m_randomKeyMiddle [ i ] );
				SetCPU_Act ( i, m_actFar, m_randomKeyFar [ i ] );
			}
		}
		catch ( ... )
		{
			TRACE_F ( _T("CPU_ACT:読込エラー\n") );
		}

//		DBGOUT_WND->SetPos ( 0, 100, 400 );
//		DBGOUT_WND->SetPos ( 1, 400, 400 );
		srand ( (UINT) time ( nullptr ) );
	}

	CPUInput::~CPUInput ()
	{
	}

	//更新
	void CPUInput::Update ( bool dirRight )
	{
		if ( dirRight ) { int i = 0; ++ i; }

		//今回の入力をゲームキーに直して保存
		//  (ゲームキー保存は右方向共通で、コマンド入力側で向きを反映している)
		GameKey gameKey;

		VEC2 pos = m_pExeChara.lock()->GetPos ();
		VEC2 posOther = m_pExeCharaOther.lock()->GetPos ();

		//行動未決定ならば
		if ( ! m_bAct ) 
		{
			int r = ::rand() % 100;

			//距離別で行動を取得
			float distance = fabsf ( pos.x - posOther.x );
			if ( distance < 200 )
			{
				m_act = m_randomKeyNear[r];
			}
			else if ( distance < 300 )
			{
				m_act = m_randomKeyMiddle[r];
			}
			else 
			{
				m_act = m_randomKeyFar[r];
			}
			
			//行動決定
			switch ( m_act )
			{
			case CPU_NEUTRAL:					break;
			case CPU_FRONT:		m_actTime = 20;	break;
			case CPU_BACK:		m_actTime = 20;	break;
			case CPU_FRONT_DASH:m_actTime = 20; break;
			case CPU_BACK_DASH:	m_actTime = 20; break;
			case CPU_L:			m_actTime = 6;	break;
			case CPU_Ma:		m_actTime = 6;	break;
			case CPU_Mb:		m_actTime = 6;	break;
			case CPU_H:			m_actTime = 6;	break;
			case CPU_POISED:	m_actTime = 20;	break;
			default:							break;
			};
			m_bAct = T;
		}

		//行動決定済
		if ( m_bAct )
		{
			switch ( m_act )
			{
			case CPU_FRONT: gameKey.SetLvr ( GameKey::LVR_6, T );	break;
			case CPU_BACK: gameKey.SetLvr ( GameKey::LVR_4, T );	break;
			case CPU_FRONT_DASH:
				switch ( m_timer )
				{
				case 0: gameKey.SetLvr ( GameKey::LVR_6, T ); 	break;
				case 1:	gameKey.SetLvrOff (); break;
				default: 
					gameKey.SetLvr ( GameKey::LVR_6, T );
					//ダッシュを維持しつつ攻撃をランダムで行う
					switch ( ::rand() % 10 )
					{
					case 0: gameKey.SetBtn ( GameKey::BTN_0, T ); 	break;
					case 1: gameKey.SetBtn ( GameKey::BTN_1, T ); 	break;
					case 2: gameKey.SetBtn ( GameKey::BTN_2, T ); 	break;
					case 3: gameKey.SetBtn ( GameKey::BTN_3, T ); 	break;
					default: break;
					}

					break;
				}
				break;
			case CPU_BACK_DASH:
				switch ( m_timer )
				{
				case 0: gameKey.SetLvr ( GameKey::LVR_4, T ); break;
				case 1:	gameKey.SetLvrOff (); break;
				default: gameKey.SetLvr ( GameKey::LVR_4, T ); break;
				}
				break;
			case CPU_L:	gameKey.SetBtn ( GameKey::BTN_0, T );	break;
			case CPU_Ma:gameKey.SetBtn ( GameKey::BTN_1, T );	break;
			case CPU_Mb:gameKey.SetBtn ( GameKey::BTN_2, T );	break;
			case CPU_H: gameKey.SetBtn ( GameKey::BTN_3, T );	break;
			case CPU_POISED: gameKey.SetBtn ( GameKey::BTN_3, T );		break;
			case CPU_NEUTRAL:	break;
			default:	break;
			};

			if ( m_timer == m_actTime )
			{
				m_timer = 0;
				m_actTime = 0;
				m_bAct = false;
			}
			else
			{
				++m_timer;
			}
		}

		//前回のキーを今回にも保存する
		gameKey.ReservePrevious ( m_vGameKey[ 0 ] );

		//ゲーム入力を更新しながら現在フレーム分を保存
		for ( int i = m_vGameKeyNum - 1; i >= 1; --i )
		{
			m_vGameKey[i] = m_vGameKey[i - 1];
		}
		m_vGameKey[0] = gameKey;


		//親クラスに反映
		CharaInput::SetGameKey ( m_vGameKey );
	}

	//ブランチリストをチェックして
	//コマンド条件が達成されていたら遷移先のアクションIDを返す
	UINT CPUInput::GetTransitID ( PAP_Brc pvpBranch, bool dirRight )
	{
		AP_Brc::iterator it = pvpBranch->begin ();
		AP_Brc::iterator it_end = pvpBranch->end ();
		for ( ; it != it_end; ++it )
		{
			P_Cmd pCommand = (*it)->GetpCommand().lock ();
			
			if ( pCommand->Compare ( m_vGameKey, dirRight ) )
			{
				return (*it)->IndexSequence.Get ();
			}
		}
		return (UINT)NO_COMPLETE;
	}

	void CPUInput::SetCPU_Act ( int index, ARY_INT act, CPU_ACT& cpu_act )
	{
		cpu_act = CPU_NEUTRAL;
		if		( index < act[1] ) { cpu_act = CPU_FRONT; }
		else if ( index < act[2] ) { cpu_act = CPU_BACK;	}
		else if ( index < act[3] ) { cpu_act = CPU_FRONT_DASH; }
		else if ( index < act[4] ) { cpu_act = CPU_BACK_DASH;	}
		else if ( index < act[5] ) { cpu_act = CPU_L; }
		else if ( index < act[6] ) { cpu_act = CPU_Ma; }
		else if ( index < act[7] ) { cpu_act = CPU_Mb; }
		else if ( index < act[8] ) { cpu_act = CPU_H; }
		else if ( index < act[9] ) { cpu_act = CPU_POISED; }
	}


}	//namespace GAME

