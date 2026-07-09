//=================================================================================================
//
// エグゼキャラ　ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara.h"
//#include "../../Fighting/Fighting.h"
#include "00_Core/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#if 0
	const UINT32 ExeChara::CLR_LOOP [ 8 ] =
	{
		0xff0000ff,
		0xff2020ff,
		0xff4040ff,
		0xff6060ff,
		0xff8080ff,
		0xff6060ff,
		0xff4040ff,
		0xff2020ff,
	};
	#endif // 0

	//================================================
	//	特殊アクション指定処理
	//================================================
	void ExeChara::SpecialAction ()
	{
		//相手
		P_ExeChara pOther = m_pOther.lock ();

		//「相手」の、連続ヒット関連リセット
		//-----------------------------------------------------
		{
			//単純チェック
			bool bStand = IsNameAction ( U"立ち" );	//立ち状態でリセット
			bool bDamaged = ! IsDamaged ();			//ダメージでないときもリセット

			//次が立ちに戻る
			bool bName = m_pAction->NextName.Is ( U"立ち" );
			bool bEndScript = m_pAction->IsEndScript ( m_frame );	//最終スクリプト
			bool bNextStand = bName && bEndScript;

			//今までのヒット数が１以上
			UINT hitNum = pOther->m_btlPrm.GetChainHitNum ();

			//総合判定
			bool bChainReset = bStand || bDamaged || bNextStand;
			if ( bChainReset )
			{
				//連続ヒット途切れ ( N->0なので１回 )
				if ( hitNum > 0 )
				{
					//ガード設定もオンのとき
					bool bGuard = m_pParam->GetPrmResult ().m_prp_Guard.Is ( GuardState::Hit1 );
					if ( bGuard )
					{
						//自分
						//トレモ：連続ヒット途切れ、ガード開始 
						m_btlPrm.GetTmr_TrainingGuard()->Start ( 60 );
						m_btlPrm.GetTmr_TrainingGuard()->Move ();	//＋１
					}
				}

				//相手：連続ヒット関連リセット
				pOther->m_btlPrm.ChainReset ();
			}
#if 0

			//1p攻撃、2pやられ
			if ( IsPlayerID( PLAYER_ID_2 ) )
			{
				//タイマーは１からスタート
				UINT time = m_btlPrm.GetTmr_TrainingGuard ()->GetTime ();
				UINT limit = 60 - time;
				if ( time == 0 ) { limit = 0; }

				DBGOUT_WND_F( DBGOUT_7, U"{}連続ヒット途切れ、ガード開始 = {}"_fmt( hitNum, limit ) );
			}

#endif // 0
		}

		//-----------------------------------------------------
		//足払い追撃ヒット
		if ( IsNameAction ( U"ダウン" ) )
		{
			if ( m_pOther.lock()->IsNameAction ( U"足払い追撃ヒット" ) )
			{
				m_pOther.lock()->SetAction ( U"立ち" );
			}
		}

		//-----------------------------------------------------
		//起き上がり
		if ( IsNameAction ( U"起き上がり" ) )
		{
			//基準スタミナ回復
			//m_btlPrm.AddBalance ( 20 );
		}

		//-----------------------------------------------------
		//ダッシュ時
		if ( IsNameAction ( U"前ダッシュ" ) )
		{
			//ゲージ
#if 0
			int balance = m_btlPrm.GetBalance ();
			if ( 20 < balance )
			{
//				m_btlPrm.AddBalance ( -10 );	//スタミナマイナス
				m_btlPrm.AddBalance ( 10 );	//剣撃ゲージプラス
				m_btlPrm.AddMana ( 30 );	//超必殺プラス
			}
#endif // 0
			m_btlPrm.AddBalance ( 10 );	//剣撃ゲージプラス
			m_btlPrm.AddMana ( 10 );	//超必殺プラス
		}

		//-----------------------------------------------------
		//空中ダッシュ, 低空ダッシュ
		bool AirDash = IsNameAction ( U"空中ダッシュ" );
		bool LowAirDash = IsNameAction ( U"低空ダッシュ" );
		bool tsukihibosi_dash =
			   IsNameAction ( U"空中ダッシュ1" )
			|| IsNameAction ( U"空中ダッシュ2" )
			|| IsNameAction ( U"空中ダッシュ3" )
			|| IsNameAction ( U"空中ダッシュ4" )
			|| IsNameAction ( U"空中ダッシュ6" )
			|| IsNameAction ( U"空中ダッシュ7" )
			|| IsNameAction ( U"空中ダッシュ8" )
			|| IsNameAction ( U"空中ダッシュ9" );

		if ( AirDash || LowAirDash || tsukihibosi_dash )
		{
			if ( m_frame == 0 )
			{
				m_btlPrm.SetNAirDash ( 1 );
			}
			//回数リセットは "着地" 時
		}

		//-----------------------------------------------------
		//着地
		if ( IsNameActionFrame ( U"着地", 0 ) )
		{
#if 0

	void CHST_Main::PreScriptMove ()
	{
		P_ExeChara pExe = GetwpExeChara ().lock ();
		pExe->Input ();				//入力		


		pExe->PreMove_Effect ();	//エフェクト動作

		//ヒットストップ時は以降を飛ばす
		if ( pExe->IsHitStop () )
		{
			return;
		}

		pExe->TransitAction ();		//アクション遷移
		pExe->CalcPos ();			//位置計算
		pExe->SetCollisionRect ();	//接触枠設定
//		pExe->OverEfPart ();		//EfPart重なり
		pExe->Generate_Effect ();	//エフェクト生成
	}

#endif // 0

			//投げ無敵
			//m_btlPrm.GetcTmr_ThrowInv ()->Start ( 10 );

			//@info
			//ここではTransitAction中なので、着地[0]に遷移せず、
			// CalcPos()で着地判定と移行を行う	

		}


#if 0

		//@info DBGOUT_WND_F は　ExeChara中で用いると２P側で上書きされる
		if ( IsPlayerID( PLAYER_ID_1 ) )
		{
//			DBGOUT_WND_F( DBGOUT_8, U"AirDash = {}"_fmt( m_btlPrm.GetNAirDash() ) );
		}

#endif // 0


		//-----------------------------------------------------
//		bool bSouha = IsNameAction ( U"剣撃走破" );
		bool bSouha = IsNameAction ( U"剣撃走破_地上_発生" );
		bool bSouha_air = IsNameAction ( U"剣撃走破_空中_発生" );
		if ( bSouha || bSouha_air )
		{
			if ( m_pScript->Index.Is ( 1 ) )
			{
				//剣撃技は超必殺ゲージを直接増加
				m_btlPrm.AddMana ( 2000 );
			}

			//エフェクト発生
			if ( m_pScript->Index.Is ( 5 ) )
			{
				VEC2 pos = m_btlPrm.GetPos ();
				pos.y += -250;
				m_efSouha->On ( pos );
			}

		}

		bool bSouha_d = IsNameAction ( U"剣撃走破_地上_ダッシュ" );
		bool bSouha_air_d = IsNameAction ( U"剣剣撃走破_空中_ダッシュ" );
		if ( bSouha_d || bSouha_air_d )
		{
			//ダッシュ中はゲージ消費
			m_btlPrm.AddBalance ( -20 );
		}

		//-----------------------------------------------------
		//超必殺全般
		if ( IsOverdrive () )
		{
			//最終スクリプト
			if ( m_pAction->IsEndScript ( m_frame ) )
			{
				//補正は自分に係り、相手のダメージ時に参照される
				float rev = m_btlPrm.GetReviseOverDrive ();
				m_btlPrm.SetReviseOverDrive ( rev * 0.5f );
			}
		}

		//-----------------------------------------------------
		//紗絵
		if ( m_name == CHARA_SAE )
		{
			if ( IsNameActionFrame ( U"投げ成立0", 0 ) )
			{
				TopByZ ();
				SetPosEachOther ( VEC2 ( 250.f, 0 ) );
			}

			if ( IsNameActionFrame ( U"渦雷", 0 ) )
			{
				//ヒット時
				if ( 0 < m_btlPrm.GetChainHitNum () )
				{
					//位置固定
					SetPosEachOther ( VEC2 ( 100.f, -100.f ) );
				}
			}

	#if 0
			//カットイン
			if ( IsNameAction ( U"超雷電蹴_発生" ) )
			{
				if ( m_pScript->GetFrame () == 0 )
				{
					m_testCutIn->SetValid ( T );
				}
				if ( m_pAction->IsEndScript ( m_frame ) )
				{
					m_testCutIn->SetValid ( F );
				}

				if ( m_pScript->Index.Is ( 1 ) )
				{
					//カットイン
					m_pFtgGrp->SetOverDrive ( T );
				}
			}
	#endif // 0

			if ( IsNameAction ( U"超雷電蹴_持続" ) )
			{
				//補正解除
				m_btlPrm.SetReviseOverDrive ( 1.0f );
			}

			if ( IsNameAction ( U"雷嵐ヒット" ) )
			{
				//補正解除
				m_btlPrm.SetReviseOverDrive ( 1.0f );

				if ( m_pScript->Index.Is ( 0 ) )
				{
					//位置固定
					TopByZ ();
					SetPosEachOther ( VEC2 ( 200.f, 0 ) );
					//地上ヒット
					m_pOther.lock()->SetAction ( U"ダメージ大" );
				}
			}
		}

		//-----------------------------------------------------
		//桜花
		else if ( m_name == CHARA_OUKA )
		{
			if ( IsNameActionFrame ( U"波動必殺追加1", 0 ) )
			{
				SetPosEachOther ( VEC2 ( 100.f, 0 ) );
			}

			if ( IsNameAction ( U"投げ成立0" ) )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					TopByZ ();
					SetPosEachOther ( VEC2 ( 250.f, 0 ) );
				}
			}

			if ( IsNameAction ( U"超必殺技B成立" ) )
			{
				if ( m_pScript->Index.Is ( 2 ) )
				{
					m_pFtgGrp->StartWhiteOut ( 60 + 4 );
					m_dispChara->TurnShadow ( T );
					m_pOther.lock()->m_dispChara->TurnShadow ( T );
				}

				if ( ! m_pFtgGrp->IsActive_WhiteOut () )
				{
					m_dispChara->TurnShadow ( F );
					m_pOther.lock()->m_dispChara->TurnShadow ( F );
				}
			}

		}

		//-----------------------------------------------------
		//烈堂
		else if ( m_name == CHARA_RETSUDOU )
		{
			if ( IsNameAction ( U"投げ成立0" ) )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					TopByZ ();

					//位置調整用
					float bDir = m_btlPrm.GetDirRight () ? 1.f : -1.f;
					VEC2 my_pos = GetPos ();
					VEC2 pos_rev = { my_pos.x + ( bDir * 250 ), my_pos.y + 0 };

					m_pOther.lock()->SetPos ( pos_rev );	//位置同期
				}
			}

		}

		//-----------------------------------------------------
		//ギャバ
		else if ( m_name == CHARA_GYAVADARUGA )
		{
			if ( IsNameAction ( U"立ち" ) )
			{
				//投げ状態のロックを回避
				bool b0 = m_pOther.lock()->IsNameAction ( U"ギャバ_投げやられ持続" );
				bool b1 = m_pOther.lock()->IsNameAction ( U"ギャバ_昇竜投げやられ落下" );
				bool b2 = m_pOther.lock()->IsNameAction ( U"半回転投げやられ持続" );
				bool b3 = m_pOther.lock()->IsNameAction ( U"ギャバ_超必Bやられ持続" );
				bool bAll =  b0 || b1 || b2 || b3 ;

				if ( bAll )
				{
					m_pOther.lock()->SetAction ( U"ダウン" );
				}
			}

			if ( IsNameAction ( U"大攻撃2" ) )
			{
				if ( GetpScript()->Index.Is ( 0 ) )
				{
					m_pOther.lock()->TopByZ ();
					//位置調整用
					float bDir = m_btlPrm.GetDirRight () ? 1.f : -1.f;
					VEC2 my_pos = GetPos ();
					VEC2 pos_rev = { my_pos.x + ( bDir * 250 ), my_pos.y + 0 };

					m_pOther.lock()->SetPos ( pos_rev );	//位置同期
				}
			}

			if ( IsNameAction ( U"投げ成立0" ) )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					m_pOther.lock()->TopByZ ();
				}
			}

			//位置調整用
			float bDir = m_btlPrm.GetDirRight () ? 1.f : -1.f;
			VEC2 my_pos = GetPos ();
			VEC2 pos_rev = { my_pos.x + ( bDir * 250 ), my_pos.y + 0 };

			if ( IsNameAction ( U"昇竜投げ成立" ) )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					m_pOther.lock()->TopByZ ();	//表示前後
				}

				m_pOther.lock()->SetPos ( pos_rev );	//位置同期
			}

			if ( IsNameAction ( U"昇竜投げ落下" ) )
			{
				m_pOther.lock()->SetPos ( pos_rev );	//位置同期
			}

			if ( IsNameAction ( U"昇竜投げ着地" ) )
			{
				//終了待機またはタイムアップ待機のとき
				bool b_endwait = IsState_EndWait ();
				bool b_timeup = IsState_TimeUpWait ();
				if ( b_endwait || b_timeup )
				{
					//タイムアップ時にConduct_InDemoになるため直接指定
					if ( m_pScript->Index.Is ( 1 ) )
					{
						m_pOther.lock()->SetAction ( U"ギャバ_昇竜投げやられ着地" );
					}
				}
			}


			if ( IsNameAction ( U"半回転投げ成立" ) )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					//1p2p表示前後
					m_pOther.lock()->TopByZ ();

					//位置指定
					m_pOther.lock()->SetPos ( VEC2 ( my_pos.x + ( bDir * 250 ), GROUND_Y ) );
				}

				//終了待機またはタイムアップ待機のとき
				bool b_endwait = IsState_EndWait ();
				bool b_timeup = IsState_TimeUpWait ();
				if ( b_endwait || b_timeup )
				{
					//タイムアップ時にConduct_InDemoになるため直接指定
					if ( m_pScript->Index.Is ( 26 ) )
					{
						m_pOther.lock()->SetAction ( U"ギャバ_半回転投げやられ締め" );
					}
				}
			}

			bool b_ex0 = IsNameAction ( U"竜巻EX0" );
			bool b_ex1 = IsNameAction ( U"竜巻EX1" );
			bool b_ex2 = IsNameAction ( U"竜巻EX2" );

#if 0

			if ( b_ex0 )
			{
				//位置ロック
				if ( m_pScript->Index.Is ( 0 ) )
				{
					SetPosEachOther ( VEC2 ( 250.f, 0 ) );
				}
			}
#endif // 0


			if ( b_ex0 || b_ex1 || b_ex2 )
			{
				//スタミナ回復制限
				//最初
				if ( m_frame == 0 )
				{
					m_btlPrm.SetRecoveringStamina ( F );
				}
			}
			else
			{
				//それ以外は常に回復可能
				m_btlPrm.SetRecoveringStamina ( T );
			}

			//-------------------------------------------------------------------------
			if ( IsNameAction ( U"超必殺技B0" ) )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					//表示前後 (相手を手前に)
					m_pOther.lock()->TopByZ ();
				}

				if (m_pAction->IsEndScript(m_pScript->Index.Get()))
				{
					//位置指定
					//左右位置チェック
					if ( GetDirRight () )	//右向 → 左位置
					{
						SetPos ( VEC2 ( 960 - 200, GROUND_Y ) );
						m_pOther.lock()->SetPos ( VEC2 ( 960 + 200, GROUND_Y ) );
					}
					else
					{
						SetPos ( VEC2 ( 960 + 200, GROUND_Y ) );
						m_pOther.lock()->SetPos ( VEC2 ( 960 - 200, GROUND_Y ) );
					}
				}
			}

			if ( IsNameAction ( U"超必殺技B1" ) )
			{
#if 0
				if ( m_pScript->GetFrame () == 0 )
				{
					//位置指定
					SetPos ( VEC2 ( 960 - 20, GROUND_Y ) );
					m_pOther.lock()->SetPos ( VEC2 ( 960 + 20, GROUND_Y ) );
				}
#endif // 0

				//状態指定
				if ( m_pScript->Index.Is ( 10 ) )
				{
					//表示前後 (自身を手前に)
					TopByZ ();
				}
				//状態指定
				if ( m_pScript->Index.Is ( 121 ) )
				{
					m_pOther.lock()->SetAction ( U"ギャバ_超必Bやられダウン持続" );
				}
			}
			if ( IsNameAction ( U"超必殺技B2" ) )
			{
				//勝敗決定時
				if ( m_pOther.lock()->IsZeroLife() )
				{
					m_pOther.lock()->SetAction ( U"ギャバ_超必Bやられダウン持続" );
				}
			}
			if ( IsNameAction ( U"超必殺技B3" ) )
			{
				//勝敗決定時
				if ( m_pOther.lock()->IsZeroLife() )
				{
					m_pOther.lock()->SetAction ( U"ギャバ_超必Bやられダウン持続" );
				}

				//最終スクリプト
				if ( m_pAction->IsEndScript ( m_pScript->Index.Get () ) )
				{
					//勝敗決定時
					if ( m_pOther.lock()->IsZeroLife() )
					{
						//トレーニングモードを除く
						if ( m_pParam->IsTrainingMode () )
						{
							//戦闘続行
							m_pOther.lock()->SetAction ( U"ダウン" );
						}
						else
						{
							//状態指定でアクタを敗北時ダウンに移行
							m_pOther.lock()->Lose ();	
						}
					}
					else
					{
						//戦闘続行
						m_pOther.lock()->SetAction ( U"ダウン" );
					}
				}

				//終了待機またはタイムアップ待機のとき
				bool b_endwait = IsState_EndWait ();
				bool b_timeup = IsState_TimeUpWait ();
				if ( b_endwait || b_timeup )
				{
					//タイムアップ時にConduct_InDemoになるため直接指定
					m_pOther.lock()->SetAction ( U"ギャバ_超必Bやられダウン持続" );
				}
			}

			//----------------------------------------------------------
			if ( IsNameAction ( U"超必殺技AA1" ) )	//成立時
			{
				//補正解除
				m_btlPrm.SetReviseOverDrive ( 1.0f );
				//状態指定
				if ( m_pScript->Index.Is ( 0 ) )
				{
					OffShade ();		//影を消す
					m_pOther.lock()->OffShade ();		//影を消す
					TopByZ ();			//表示前後 (自身を手前に)

					//位置指定
					//左右位置チェック
					if ( GetDirRight () )	//右向 → 左位置
					{
						SetPos ( VEC2 ( 960 - 200, GROUND_Y ) );
						m_pOther.lock()->SetPos ( VEC2 ( 960 + 200, GROUND_Y ) );
					}
					else
					{
						SetPos ( VEC2 ( 960 + 200, GROUND_Y ) );
						m_pOther.lock()->SetPos ( VEC2 ( 960 - 200, GROUND_Y ) );
					}
				}
			}
			if ( IsNameAction ( U"超必殺技AA2" ) )
			{
				//補正解除
				m_btlPrm.SetReviseOverDrive ( 1.0f );
				//状態指定
				if ( m_pScript->Index.Is ( 15 ) )
				{
					//表示前後 (相手を手前に)
					m_pOther.lock()->TopByZ ();
				}
			}
			if ( IsNameAction ( U"超必殺技AA3" ) )
			{
				//補正解除
				m_btlPrm.SetReviseOverDrive ( 1.0f );
				//状態指定
				if ( m_pScript->Index.Is ( 15 ) )
				{
					OnShade ();		//影を表示する
					m_pOther.lock()->OnShade ();		//影を表示する
				}
			}
			//-------------------------------------------------------------------------


		}
		//-----------------------------------------------------
		//フェラリア
		else if ( m_name == CHARA_FERARIA )
		{
			//飛び道具
			//アクセルゲージを０に向かう方に
			int acl = m_btlPrm.GetAccel ();
			if ( IsNameActionFrame ( U"4弱", 0 ) )
			{
				if ( 0 < acl ) { m_btlPrm.AddAccel ( -100 ); } 
			}
			if ( IsNameActionFrame ( U"4中", 0 ) )
			{
				if ( 0 < acl ) { m_btlPrm.AddAccel ( -150 ); } 
			}
			if ( IsNameActionFrame ( U"4強", 0 ) )
			{
				if ( 0 < acl ) { m_btlPrm.AddAccel ( -200 ); } 
			}


			if ( IsNameAction ( U"投げ成立0" ) )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					TopByZ ();

					//位置調整用
					float bDir = m_btlPrm.GetDirRight () ? 1.f : -1.f;
					VEC2 my_pos = GetPos ();
					VEC2 pos_rev = { my_pos.x + ( bDir * 0 ), my_pos.y + 0 };
					SetPos ( pos_rev );	//位置同期(自分)

					VEC2 pos_rev_other = { my_pos.x + ( bDir * 100 ), my_pos.y + 0 };
					m_pOther.lock()->SetPos ( pos_rev_other );	//位置同期(相手)
				}
			}

			if ( IsNameAction ( U"カキャ・ムルチャ落下" ) )
			{
				//ガード時分岐
				if ( m_pOther.lock ()->IsGuard () )
				{
					SetAction ( U"カキャ・ムルチャ攻撃なし落下" );
				}
			}

#if 0
			if ( IsNameAction ( U"カキャ・ムルチャEX落下" ) )
			{
				//ガード時分岐
				if ( m_pOther.lock ()->IsGuard () )
				{
					SetAction ( U"カキャ・ムルチャEX攻撃なし落下" );
				}
			}
#endif // 0

			if ( IsNameAction ( U"トゥララ・コモタン成立1" ) )
			{
				//補正解除
				m_btlPrm.SetReviseOverDrive ( 1.0f );
			}
		}


		//-----------------------------------------------------
		//月日星
		else if ( m_name == CHARA_TSUKIHIBOSHI )
		{
			if ( IsNameAction ( U"投げ成立0" ) )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					TopByZ ();

					//位置調整用
					float bDir = m_btlPrm.GetDirRight () ? 1.f : -1.f;
					VEC2 my_pos = GetPos ();
					VEC2 pos_rev = { my_pos.x + ( bDir * 250 ), my_pos.y + 0 };

					m_pOther.lock()->SetPos ( pos_rev );	//位置同期
				}
			}

			if ( IsNameAction ( U"特大攻撃" ) )
			{
				//1Hit目以降
				if ( 0 < m_btlPrm.GetChainHitNum () )
				{
					SetAction ( U"コンボ特大攻撃" );
				}
			}

			//背景上部延長
			if ( IsNameAction ( U"エリアルジャンプ" ) )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					m_pFtgGrp->StartAerial ();
					G_FTG ()->SetScrollY ( T );
				}
			}

			//スクロール背景停止
			bool bA = m_pFtgGrp->IsAerial ();
			bool b0 = IsNameAction ( U"着地" );
			bool b1 = IsNameAction ( U"立ち" );
			if ( bA && (b0 || b1) )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					if ( ! m_pFtgGrp->IsAerialFade () )
					{
						m_pFtgGrp->EndAerial ();
						G_FTG ()->SetScrollY ( F );
					}
				}
			}

			//位置調整
			if ( IsNameAction ( U"竜巻成立" ) )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					TopByZ ();

					//位置調整用
					bool bDir = m_btlPrm.GetDirRight ();
					float dir = bDir ? 1.f : -1.f;
					VEC2 my_pos = GetPos ();
					VEC2 pos_rev = { my_pos.x + ( dir * 10 ), my_pos.y + 0 };
					m_pOther.lock()->SetPos ( pos_rev );	//位置同期
					m_pOther.lock()->SetDirRight ( ! bDir );	//向き同期
				}
			}
			if ( IsNameAction ( U"空中必殺技成立" ) )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					TopByZ ();

					//位置調整用
					bool bDir = m_btlPrm.GetDirRight ();
					float dir = bDir ? 1.f : -1.f;
					VEC2 my_pos = GetPos ();
					//my_pos.y = GROUND_Y;	//地上基準
					//SetPos ( my_pos );	//位置同期
					VEC2 pos_rev = { my_pos.x + ( dir * 100 ), my_pos.y + 0 };
					m_pOther.lock()->SetPos ( pos_rev );	//位置同期
					m_pOther.lock()->SetDirRight ( ! bDir );	//向き同期
				}
			}

			//超必殺　演出
			bool bA1 = IsNameAction ( U"超必殺技A1" );
			bool baA1 = IsNameAction ( U"空中超必殺技A発動" );
			if ( bA1 || baA1 )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					m_pFtgGrp->EfString_Start ();
				}
			}
			//ロック
			bool bA2h = IsNameAction ( U"超必殺技A2ヒット" );
			if ( bA2h )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					VEC2 my_pos = { GetPos().x, GROUND_Y };
					bool bDir = m_btlPrm.GetDirRight ();
					float dir_d = bDir ? 1.f : -1.f;
					VEC2 pos_rev = { my_pos.x + ( dir_d * 250 ), GROUND_Y };

					SetPos ( my_pos );
					m_pOther.lock()->SetPos ( pos_rev );
				}
			}

			bool baA2h = IsNameAction ( U"空中超必殺技A2_1ヒット" );
			if ( baA2h )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					VEC2 my_pos = GetPos();
					bool bDir = m_btlPrm.GetDirRight ();
					float dir_d = bDir ? 1.f : -1.f;
					VEC2 pos_rev = { my_pos.x + ( dir_d * 250 ), GetPos().y };
					m_pOther.lock()->SetPos ( pos_rev );
				}
			}

			//----------------------------------------------------
			if ( IsNameActionFrame ( U"超必殺技B1", 0 ) )
			{
				m_pFtgGrp->EfString_Start ();
			}

			if ( IsNameActionFrame ( U"超必殺技B3", 48 ) )
			{
				m_pFtgGrp->StartAllBlack ();
			}
			if ( IsNameActionEnd ( U"超必殺技B3" ) )
			{
				m_pFtgGrp->EndAllBlack ();
			}

			if ( IsNameActionFrame ( U"超必殺技B4", 0 ) )
			{
				//補正解除
				m_btlPrm.SetReviseOverDrive ( 1.0f );
			}
			if ( IsNameActionFrame ( U"超必殺技B4", 34 ) )
			{
				m_pFtgGrp->EfMandara_On ();
			}
			if ( IsNameActionEnd ( U"超必殺技B4" ) )
			{

				m_pFtgGrp->EfMandara_Off ();
			}
			//----------------------------------------------------
		}

		//-----------------------------------------------------
		//レイナ
		else if ( m_name == CHARA_REINA )
		{
			if ( IsNameActionFrame ( U"投げ成立0", 0 ) )
			{
				TopByZ ();
				SetPosEachOther ( VEC2 ( 200, 0 ) );	//位置同期
			}

			if ( IsNameActionFrame ( U"ヴェンガンサ1", 0 ) )
			{
				SetPosEachOther ( VEC2 ( 200, -200 ) );	//位置同期
			}

			if ( IsNameAction ( U"ヴォルデーリャ成立1" ) )
			{
				if ( m_pScript->Index.Is ( 0 ) )
				{
					TopByZ ();

					//距離で速度を指定
					VEC2 my_pos = GetPos ();
					VEC2 other_pos = pOther->GetPos ();
					float distance = my_pos.x - other_pos.x;
					distance = distance + ( GetDirRight () ? - 100 : 100 );
					distance = distance * ( GetDirRight () ? -1.f : 1.f );
					float vel = distance / 43;	//43[F]

					m_btlPrm.SetReinaOdVx ( vel );
				}
			}

			if ( IsNameActionFrame ( U"ヴォルデーリャ成立2", 0 ) )
			{
				//超必殺技補正解除
				m_btlPrm.SetReviseOverDrive ( 1.0f );
			}

			bool bni0 = IsNameAction ( U"ヴニベルソ0" );
			bool bni1 = IsNameAction ( U"ヴニベルソ1" );
			bool bni2 = IsNameAction ( U"ヴニベルソ2" );
			bool bni3 = IsNameAction ( U"ヴニベルソ3" );
			bool bni4 = IsNameAction ( U"ヴニベルソ4" );
			if ( bni0 || bni1 || bni2 || bni3 || bni4 )
			{
				//補正解除
				m_btlPrm.SetReviseOverDrive ( 1.0f );
			}

			if ( IsNameAction ( U"ヴニベルソ0" ) )
			{
				//ヒット時のロック
				if ( m_pScript->Index.Is ( 1 ) )
				{
					SetPosEachOther ( VEC2 ( 300, 0 ) );	//位置同期
				}
			}

			if ( IsNameAction ( U"ヴニベルソ3" ) )
			{
				UINT32 i = m_pScript->Index.Get ();

				if ( 27 < i && i < 37 ) 
				{
					SetPosEachOther ( VEC2 ( 150.f - (i-27) * 50, 0 ) );	//位置同期
				}
			}
		}



		//-----------------------------------------------------
		//全キャラ


		//喰らい側から相打ち時のロック回避
		if ( IsNameAction ( U"ギャバ_半回転投げやられ" ) )
		{
			//ギャバダルガが成立ではないとき（相打ちなど）
			if ( ! m_pOther.lock()->IsNameAction ( U"半回転投げ成立" ) )
			{
				SetAction ( U"ダウン" );
			}
		}


		//-----------------------------------------------------
		if ( IsNameAction ( U"勝利" ) )
		{
			if ( m_pScript->Index.Is ( 0 ) )
			{
				//表示前後 (自分を手前に)
				TopByZ ();
			}
		}


		//-----------------------------------------------------
		//アクセル増減　 ：　アクション中のアクセル値を利用
		int accel_value = m_pAction->Accel.Get ();
		if ( 0 == accel_value ) //スクリプト中で指定なし(==0)
		{
			//カテゴリ一括
			if ( IsAttacking () ) {	m_btlPrm.AddAccel ( 3 ); }	//通常攻撃
			else if ( IsSpecial () ) {	m_btlPrm.AddAccel ( 5 ); }	//必殺技
			else if ( IsOverdrive () ) {	m_btlPrm.AddAccel ( 10 ); }	//超必殺技
			else 
			{
				//０：基本状態は沈静化
				m_btlPrm.DirZeroAccel ( 3 );	//アクセル 沈静化
			}
		}
		else if ( 0 < accel_value ) //プラス時
		{
			m_btlPrm.AddAccel ( accel_value );
		}
		else //マイナス時
		{
			//０：基本状態は沈静化
			//m_btlPrm.DirZeroAccel ( 3 );	//アクセル 沈静化

			//マイナス分
			m_btlPrm.AddAccel ( accel_value - 3 );
		}



#if 0

		//-----------------------------------------------------
		//足払い追撃終了
//		if ( IsNameAction ( _T ( "足払い追撃ヒット" ) ) )
		if ( IsNameAction ( _T ( "ホーミング" ) ) )
//		if ( IsNameAction ( _T ( "テスト" ) ) )
		{
			if ( m_frame == 0 )
			{
				G_FTG()->SetWallMove ( T );
			}

//			if ( m_pAction->IsOverScript ( m_frame ) )
			if ( m_pAction->IsEndScript ( m_pScript->GetFrame() ) )
			{
//				G_FTG()->SetWallMove ( F );
			}
		}
		if ( IsNameAction ( _T ( "位置リセット着地" ) ) )
		{
			if ( m_frame == 0 )
			{
				G_FTG()->SetWallMove ( F );
			}
		}



		if ( IsNameAction ( _T ( "空中ダッシュ小攻撃" ) ) 
			||  IsNameAction ( _T ( "空中ダッシュ中攻撃" ) ) 
			||  IsNameAction ( _T ( "空中ダッシュ大攻撃" ) ) 
			)
		{
			//攻撃成立時
			if ( m_btlPrm.GetHitEst () )
			{
				m_btlPrm.SetHitDrop ( 2.5 );
			}
		}

#if 0
		//-----------------------------------------------------
		//バランスアウト
		if ( m_btlPrm.GetBalance () <= 0 )
		{
			//			SetAction ( _T ( "Dotty" ) );
			SetAction ( _T ( "立ち" ) );
		}
#endif // 0

		//=====================================================
		// キャラ別分岐
		
		//-----------------------------------------------------
		//壁まで吹き飛び
		if ( IsNameAction ( _T ( "小攻撃" ) ) )
		{
			if ( m_frame == 0 )
			{
				int i = 0;
			}
		}

		//-----------------------------------------------------
		//壁まで吹き飛び
		if ( IsNameAction ( _T ( "壁まで吹き飛び" ) ) )
		{
			if ( m_frame == 0 )
			{
			}

			//カラー遷移
			static UINT32 index = 0;
			if ( index >= CLR_LOOP_NUM )
			{
				index = 0;
			}
			m_btlPrm.SetColor ( CLR_LOOP [ index ++ ] );
		}

		//-----------------------------------------------------
		//壁割り発生
		if ( IsNameAction ( _T ( "壁張り付き" ) ) )
		{
			if ( m_frame == 0 )
			{
#if 0
				if ( m_btlPrm.GetDirRight () )
				{
					mwp_fighting.lock()->WallBreak_L ();
				}
				else
				{
					mwp_fighting.lock()->WallBreak_R ();
				}

				//相手を強制的に"壁割り後の走り"に移行する
				
				G_FTG()->SetNewWall ( T );
#endif // 0
				m_btlPrm.SetColor ( 0xffffffff );
			}
		}

		//-----------------------------------------------------
		//必殺技A
		if ( IsNameAction ( _T ( "必殺技A" ) ) )
		{
			//相手色変更
			m_pOther.lock ()->m_btlPrm.SetColor ( 0xff0000ff );
		}

		//-----------------------------------------------------
		//超必殺背景演出
		if ( IsNameAction ( _T ( "超必Bヒット後" ) ) )
		{
			if ( m_frame == 0 )
			{
				//ライフ判定
				if ( m_pOther.lock()->GetLife () < 3000 )
				{
					//倒しきり時分岐
					SetAction ( _T ( "超必B_特殊勝利" ) );
				}

				//背景白転　キャラ影演出
				m_dispChara->TurnShadow ( T );
				m_btlPrm.SetWhiteOut ( T );
				m_pOther.lock()->m_dispChara->TurnShadow ( T );
			}
		}

		if (	IsNameAction ( _T ( "超必Bヒット終了" ) ) 
			||	IsNameAction ( _T ( "超必B_特殊勝利終了" ) ) 
		)
		{
			if ( m_frame == 0 )
			{
				//演出解除
				m_dispChara->TurnShadow ( F );
				m_pOther.lock()->m_dispChara->TurnShadow ( F );
			}
		}
#endif // 0

	}

	void ExeChara::SetSpPos ( float mx, float my, float ox, float oy )
	{
		SetPos ( VEC2 ( mx, my ) );
		m_pOther.lock()->SetPos ( VEC2 ( ox, oy ) );
	}


	//名前とフレーム
	bool ExeChara::IsNameActionFrame ( s3d::String name, uint32 frame ) const
	{
		bool bName = IsNameAction ( name );
		bool bFrame = m_pScript->Index.Is ( frame );
		return bName && bFrame;
	}
	bool ExeChara::IsNameActionEnd ( s3d::String name ) const
	{
		bool bName = IsNameAction ( name );
		bool bEnd = IsEndScript ();
		return bName && bEnd;
	}

	//投げなどで、相手との位置をロックする
	void ExeChara::SetPosEachOther ( VEC2 pos )
	{
		//位置調整用
		bool bDir = m_btlPrm.GetDirRight ();
		float dir = bDir ? 1.f : -1.f;
		VEC2 my_pos = GetPos ();
		VEC2 pos_rev = { my_pos.x + ( dir * pos.x ), my_pos.y + pos.y };

		m_pOther.lock()->SetPos ( pos_rev );	//位置同期
		m_pOther.lock()->SetDirRight ( ! bDir );	//向き同期
	}



}	//namespace GAME

