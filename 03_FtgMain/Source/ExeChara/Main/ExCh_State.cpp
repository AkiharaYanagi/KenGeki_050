//=================================================================================================
//
//	ExeChara ステート
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExCh_State.h"
#include "ExeChara.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------
	// ※凡例
	//■	：他ステートと比較して外してある項目
 	//------------------------------------------------
	//
	// 
	//=====================================================
	//共通：入力なしPreScriptMove
	void ExeChara_State::PreScriptMove_NoInput ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		//■		pExe->Input ();				//入力		
		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
		pExe->SetCollisionRect ();	//接触枠設定
		pExe->Generate_Effect ();	//エフェクト生成
		pExe->PreMove_Effect ();	//エフェクト動作
	}

	//共通：ライフ判定なしPostScriptMove
	void ExeChara_State::PostScriptMove_NoLifeCheck ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->PostMove_Effect ();		//エフェクト生成と動作
		//■		pExe->CheckLife ();		//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
		pExe->SoundPlay ();		//音の再生
//		pExe->SE_Play ();			//SEの再生
//		pExe->VC_Play ();			//VCの再生

		pExe->MoveTimer ();		//タイマ稼働
		pExe->SetFirstSE ( F );		//SE再生フラグ
		pExe->SetFirstVC ( F );		//VC再生フラグ
	}

	//=====================================================

	//------------------------------------------------
	//開始時挨拶
	void CHST_Greeting::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照

		//アクション・スクリプト初期化
		pExe->SetAction ( U"開幕" );
	}

	void CHST_Greeting::PreScriptMove ()
	{
		PreScriptMove_NoInput ();
	}

	void CHST_Greeting::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}


	//------------------------------------------------
	//準備
	void CHST_GetReady::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照

		//アクション・スクリプト初期化
		pExe->SetAction ( U"開幕待機" );
	}

	void CHST_GetReady::PreScriptMove ()
	{
		//入力不可
		PreScriptMove_NoInput ();

#if 0
		//@info 入力は可能

		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->Input ();				//入力		
		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
//■		pExe->SetCollisionRect ();	//接触枠設定
		pExe->Generate_Effect ();	//エフェクト生成
		pExe->PreMove_Effect ();	//エフェクト動作

#endif // 0
	}

	void CHST_GetReady::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}


	//------------------------------------------------
	//バトル　メイン状態
	void CHST_Main::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->Init ();
		//アクション・スクリプト初期化
		pExe->SetAction ( U"立ち" );



		m_time.clear ();
		m_ave.clear ();
		for ( int i = 0; i < 10; ++i )
		{
			m_time.push_back ( 0 );
			m_ave.push_back ( 0 );
		}

	}

	void CHST_Main::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		PLAYER_ID pid = pExe->GetBtlPrm().GetPlayerID ();
		m_sw.restart ();


		//P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->Input ();				//入力		


		m_time [ 1 ] += m_sw.msF ();
		if ( m_count == 60 ) { m_ave[1] = m_time [ 1 ] / 60.0; }
		DBGOUT_WND_F ( DBGOUT_1, U"{:2.4f}[ms] pExe->Input ();"_fmt( m_ave[1] ) );
		m_sw.restart ();


		pExe->PreMove_Effect ();	//エフェクト動作

	
		m_time [ 2 ] += m_sw.msF ();
		if ( m_count == 60 ) { m_ave[2] = m_time [ 2 ] / 60.0; }
		DBGOUT_WND_F ( DBGOUT_2, U"{:2.4f}[ms] pExe->PreMove_Effect ();"_fmt( m_ave[2] ) );
		m_sw.restart ();


		//ヒットストップ時は以降を飛ばす
		if ( pExe->IsHitStop () )
		{
			return;
		}

		pExe->TransitAction ();		//アクション遷移

	
		m_time [ 3 ] += m_sw.msF ();
		if ( m_count == 60 ) { m_ave[3] = m_time [ 3 ] / 60.0; }
		DBGOUT_WND_F ( DBGOUT_3, U"{:2.4f}[ms] pExe->TransitAction ();"_fmt( m_ave[3] ) );
		m_sw.restart ();



		pExe->CalcPos ();			//位置計算

	
		m_time [ 4 ] += m_sw.msF ();
		if ( m_count == 60 ) { m_ave[4] = m_time [ 4 ] / 60.0; }
		DBGOUT_WND_F ( DBGOUT_4, U"{:2.4f}[ms] pExe->CalcPos ();"_fmt( m_ave[4] ) );
		m_sw.restart ();



		pExe->SetCollisionRect ();	//接触枠設定

	
		m_time [ 5 ] += m_sw.msF ();
		if ( m_count == 60 ) { m_ave[5] = m_time [ 5 ] / 60.0; }
		DBGOUT_WND_F ( DBGOUT_5, U"{:2.4f}[ms] pExe->SetCollisionRect ();"_fmt( m_ave[5] ) );
		m_sw.restart ();




//		pExe->OverEfPart ();		//EfPart重なり




		pExe->Generate_Effect ();	//エフェクト生成


	
		m_time [ 6 ] += m_sw.msF ();
		if ( m_count == 60 ) { m_ave[6] = m_time [ 6 ] / 60.0; }
		DBGOUT_WND_F ( DBGOUT_6, U"{:2.4f}[ms] pExe->Generate_Effect ();"_fmt( m_ave[6] ) );
		m_sw.restart ();

	}

	void CHST_Main::RectMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->SetRect ();		//枠設定
	}

	void CHST_Main::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();

	
		m_time [ 7 ] += m_sw.msF ();
		if ( m_count >= 60 ) { m_ave[7] = m_time [ 7 ] / 60.0; }
		DBGOUT_WND_F ( DBGOUT_7, U"{:2.4f} [ms] CHST_Main::PostScriptMove ()"_fmt( m_ave[7] ) );
		m_sw.restart ();




		//追加
		pExe->BtlPrm_Move_Input();					//バトルパラメータの入力処理
		pExe->PostMove_Effect ();	//エフェクト動作
		pExe->CheckLife ();			//ライフ判定


		m_time [ 0 ] += m_sw.msF ();
		if ( m_count == 60 ) 
		{ 
			m_ave[0] = m_time [ 0 ] / 60.0;
		}
		DBGOUT_WND_F ( DBGOUT_0, U"{:2.4f}[ms] pExe->UpdateGraphic ();"_fmt( m_ave[0]));
		m_sw.restart ();


		pExe->UpdateGraphic ();		//グラフィックの更新
		pExe->SoundPlay ();			//音の再生
//		pExe->SE_Play ();			//SEの再生
//		pExe->VC_Play ();			//VCの再生
	

		m_time [ 8 ] += m_sw.msF ();
		if ( m_count >= 60 ) { m_ave[8] = m_time [ 8 ] / 60.0; }
		DBGOUT_WND_F ( DBGOUT_8, U"{:2.4f}[ms] pExe->PostMove_Effect ();"_fmt( m_ave[8] ) );
		m_sw.restart ();


		pExe->MoveTimer ();			//タイマ稼働
		pExe->SetFirstSE ( F );		//SE再生フラグ
		pExe->SetFirstVC ( F );		//VC再生フラグ
	

		m_time [ 9 ] += m_sw.msF ();
		if ( m_count >= 60 ) { m_ave[9] = m_time [ 9 ] / 60.0; }
		DBGOUT_WND_F ( DBGOUT_9, U"{:2.4f}[ms] pExe->MoveTimer ();"_fmt( m_ave[9] ) );
		m_sw.restart ();

		//カウント
		if ( m_count >= 60 )
		{
			m_count = 0;
			for ( int i = 0; i < 10; ++i )
			{
				m_time [ i ] = 0;
			}
		}
		++ m_count;
	}

	void CHST_Main::NextScript ()
	{
//		GetwpExeChara ().lock()->EndScript ();
	}


	//------------------------------------------------
	//バトル　一時停止

	void CHST_ScpStop::Start ()
	{
		WP_ExeChara wpExeCh = GetwpExeChara ();
		UINT stop = wpExeCh.lock()->GetBtlPrm ().GetScpStop ();
		m_timer.Start ( stop );
	}

	void CHST_ScpStop::PreScriptMove ()
	{
		//タイマ
		m_timer.Move ();
		if ( m_timer.IsLast () )
		{
			m_timer.Clear ();

			//終了時に通常バトルにシフト
			GetwpActor ().lock()->ShiftFightingMain_PreScriptMove ();
			return;
		}

		//一連処理
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->Input ();				//入力		
		//■ 	pExe->TransitAction ();		//アクション遷移
		//■		pExe->CalcPos ();			//位置計算
		//■		pExe->SetCollisionRect ();	//接触枠設定

		//エフェクト生成のみ１回だけ、動作は毎回
		pExe->Generate_Effect_once ();	//エフェクト生成
		pExe->PreMove_Effect ();	//エフェクト動作
	}

	void CHST_ScpStop::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->PostMove_Effect ();	//エフェクト動作
		//■		pExe->CheckLife ();			//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新

		//SEは再生してフラグを続投（通常時にOFF）
		pExe->SoundPlay ();			//音の再生
//		pExe->SE_Play ();			//SEの再生
//		pExe->VC_Play ();			//VCの再生
		pExe->GetBtlPrm().SetFirstSE ( T );		//SE再生フラグ
		pExe->GetBtlPrm().SetFirstVC ( T );		//VC再生フラグ

		//■		pExe->MoveTimer ();			//タイマ稼働
	}

	//------------------------------------------------
	//バトル　壁割

	void CHST_WallBreak::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->Input ();				//入力		
		//■ 	pExe->TransitAction ();		//アクション遷移
		//■		pExe->CalcPos ();			//位置計算
		pExe->SetCollisionRect ();	//接触枠設定

		pExe->Generate_Effect ();	//エフェクト生成
		pExe->PreMove_Effect ();	//エフェクト動作
	}

	void CHST_WallBreak::PostScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->PostMove_Effect ();	//エフェクト動作
		//■		pExe->CheckLife ();			//ライフ判定
		pExe->UpdateGraphic ();		//グラフィックの更新
		pExe->SoundPlay ();		//音の再生
//		pExe->SE_Play ();			//SEの再生
//		pExe->VC_Play ();			//VCの再生

		//■		pExe->MoveTimer ();			//タイマ稼働
		pExe->SetFirstSE ( F );		//SE再生フラグ
		pExe->SetFirstVC ( F );		//VC再生フラグ
	}

	//------------------------------------------------
	//バトル　スロウスキップ状態(スロウ時に飛ばすフレーム処理のとき)

	void CHST_Slow_Skip::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->Input ();				//入力		

		//ヒットストップ時は以降を飛ばす
		if ( pExe->IsHitStop () ) { return; }

		pExe->TransitAction ();		//アクション遷移
		//■		pExe->CalcPos ();			//位置計算
		pExe->SetCollisionRect ();	//接触枠設定
		pExe->Generate_Effect ();	//エフェクト生成
		//■		pExe->PreMove_Effect ();	//エフェクト動作
	}

	void CHST_Slow_Skip::RectMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->SetRect ();		//枠設定
	}

	void CHST_Slow_Skip::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}

	//------------------------------------------------
	//終了待機
	void CHST_EndWait::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->ClearInput ();
	}

	void CHST_EndWait::PreScriptMove ()
	{
		PreScriptMove_NoInput ();
	}

	void CHST_EndWait::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}

	//------------------------------------------------
	//敗北ダウン状態
	void CHST_Down::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->ClearInput ();
		pExe->SetLose ();

		//アクション・スクリプト初期化
		pExe->SetAction ( U"敗北ダウン浮き" );
	}

	void CHST_Down::PreScriptMove ()
	{
		PreScriptMove_NoInput ();
	}

	void CHST_Down::Do ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		//アクション・スクリプト初期化
		pExe->IsNameAction ( U"敗北ダウン" );
	}

	void CHST_Down::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}

	//------------------------------------------------
	//勝者表示
	void CHST_Win::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		//アクション指定移行
		pExe->SetAction ( U"勝利" );
	}

	void CHST_Win::PreScriptMove ()
	{
		PreScriptMove_NoInput ();
	}

	void CHST_Win::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}

	//------------------------------------------------
	//タイムアップ
	void CHST_TimeUp::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->ClearInput ();
	}

	void CHST_TimeUp::PreScriptMove ()
	{
		PreScriptMove_NoInput ();
	}

	void CHST_TimeUp::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}

	//------------------------------------------------
	//タイムアップ待機
	void CHST_TimeUpWait::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->ClearInput ();
	}

	void CHST_TimeUpWait::PreScriptMove ()
	{
		PreScriptMove_NoInput ();
	}

	void CHST_TimeUpWait::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}

	//------------------------------------------------
	//時間切れ敗北
	void CHST_TimeUpLose::Start ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();		//一時参照
		pExe->ClearInput ();

		//アクション指定移行
		pExe->SetAction ( U"時間切れ敗北" );
	}

	void CHST_TimeUpLose::PreScriptMove ()
	{
		PreScriptMove_NoInput ();
	}

	void CHST_TimeUpLose::PostScriptMove ()
	{
		PostScriptMove_NoLifeCheck ();
	}


}	//namespace GAME

