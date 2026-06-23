//=================================================================================================
//
// エグゼキャラ　ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara.h"
//#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================
	//	外部からの状況起因関数
	//================================================

	//---------------------------------------------
	//	イベント
	//---------------------------------------------

	//ダッシュ相殺
	void ExeChara::OnDashOffset ()
	{
		m_btlPrm.AddBalance ( -1000 );
		TransitAction_Condition_I ( BRC_DASH, F );	//ダッシュ相殺・自分
	}

	//----------------------------------------------
	//相殺発生//自分：Attack, 相手：Offset
	void ExeChara::OnOffset_AO ()
	{
		m_btlPrm.OnOffset_AO ();

		//共通
		OnOffset_Common ();
	}

	//相殺発生	//自分：Offset, 相手：Attack
	void ExeChara::OnOffset_OA ()
	{
		m_btlPrm.OnOffset_OA ();

		//共通
		OnOffset_Common ();
	}

	//相殺発生	//自分：Attack, 相手：Attack
	void ExeChara::OnOffset_AA ()
	{
		//相手のパラメータで増減
		P_Frame scp = m_pOther.lock ()->GetpScript ();
		int balance_e = scp->Get_FP_B().Balance_E.Get();
		m_btlPrm.AddBalance ( balance_e );

#if 0
		//バランスアウト
		if ( m_btlPrm.GetBalance () <= 0 )
		{
			//			SetAction ( _T ( "Dotty" ) );
			SetAction ( _T ( "立ち" ) );
		}
#endif // 0

		//パラメータ
		m_btlPrm.OnOffset_AA ();

		//共通
		OnOffset_Common ();
	}

	//相殺発生
	void ExeChara::OnOffset_Common ()
	{
		//全体振動
		m_pFtgGrp->StartVibration ( 10 );


		//剣撃走破時はバランス増加無し
		bool bSouha_g = IsNameAction ( U"剣撃走破_地上_発生" );
		bool bSouha_air = IsNameAction ( U"剣撃走破_空中_発生" );
		bool bSouha_d = IsNameAction ( U"剣撃走破_地上_ダッシュ" );
		bool bSouha_air_d = IsNameAction ( U"剣剣撃走破_空中_ダッシュ" );

		bool bSouha = bSouha_g || bSouha_air || bSouha_d || bSouha_air_d;
		int addBalance = bSouha ? 0: 500;

		//ゲージ増加
		m_btlPrm.AddAccel ( 100 );
		m_btlPrm.AddBalance ( addBalance );
		m_btlPrm.AddMana ( 500 );


		//@todo 相殺２撃目にアサート（名前指定？）


		//キャラの持つルート,ブランチの参照
		const AP_Rut vpRoute = m_pChara->GetvpRoute ();
		const AP_Brc vpBranch = m_pChara->GetvpBranch ();

		//スクリプトの持つルートリスト
		for ( UINT indexRoute : m_pScript->GetcaRouteID () )
		{
			//ルートの取得
			P_Rut pRut = vpRoute [ indexRoute ];
			const V_UINT32 vBranchID = vpRoute [ indexRoute ]->GetcaIDBranch ();

			//対象のブランチリスト
			for ( UINT indexBranch : vBranchID )
			{
				//ブランチの取得
				P_Brc pBrc = vpBranch [ indexBranch ];

				//"条件：相殺時" 以外は飛ばす
				if ( BRC_FLG_0 != pBrc->Condition.Get () ) { continue; }

				//対象アクションに移行
				UINT id = vpBranch [ indexBranch ]->IndexSequence.Get ();
				SetAction ( id );
			}
		}

		//相殺キャンセル　タイマー開始
		m_btlPrm.GetTmr_OfstCncl()->Start ( OFST_CNCL );


		//===================================================================
		//キャラ毎 特殊処理
		//-----------------------------------------------------
		//桜花
		if ( m_name == CHARA_OUKA )
		{
			if ( IsNameAction ( U"竜巻必殺技" ) )
			{
				P_ExeChara pOther = m_pOther.lock();

				//相手の技によって効果が変わる

				//超必殺技
				if ( pOther->IsOverdrive () )
				{
					SetAction ( U"天照燕・暗転刹" );
				}
				//必殺技
				else if ( pOther->IsSpecial () )
				{
					bool bDir = GetDirRight ();
					SetDirRight ( ! bDir );		//向きを反転
					SetAction ( U"波動必殺追加2" );
				}
				//通常技
				else if ( pOther->IsNormalAttack () )
				{
					//後ろ反動　追加
					float vRcl = pOther->m_btlPrm.GetVelRecoil ();
					pOther->m_btlPrm.SetVelRecoil ( vRcl + 50 );

					//アクション内ヒット数を上限にして攻撃判定を消去
					UINT hitnum = m_pAction->HitNum.Get();
					m_btlPrm.SetHitNum ( hitnum );
				}
			}
		}

	}


	//----------------------------------------------


	//==========================================
	//◆ 自分・攻撃 -> 相手・くらい
	//ヒット発生(攻撃成立側)
	//==========================================
	void ExeChara::OnHit ()
	{
		m_OnHit.OnHit ();
	}


	void ExeChara::OnEfHit()
	{
		m_OnHit.OnEfHit ();
	}

	P_ExEf ExeChara::GetpExEf ()
	{
		PLP_ExEf plpExEf1 = m_oprtEf->GetplpExEf ();

		//エフェクトリストのヒットチェック
		for ( P_ExEf pexef1 : (*plpExEf1) )
		{
			if ( pexef1->GetHit () )
			{
				return pexef1;
			}
		}
		return nullptr;
	}


#if 0
	//エフェクトヒット発生(攻撃成立側)
	void ExeChara::OnEfHit ()
	{
		m_btlPrm.SetHitEst ( true );		//攻撃成立フラグ
//		m_tmrHitstop->Start ();		//エフェクトはヒットストップしない
		m_btlPrm.GetTmr_HitPitch ()->Start ();
	}
#endif // 0


	//投げられ判定
	bool ExeChara::CanBeThrown () const 
	{
		P_Sequence pAct = m_pAction;

		//指定アクションのとき　「不可」
		if ( pAct->Name.Is ( U"投げやられ" ) ) { return F; }

		//アクション態勢が"AP_JUMP"は「不可」
		if ( Is_AP_Jump () ) { return F; }

		//アクション属性が"AC_DAMAGED"は「不可」
		if ( IsDamaged () ) { return F; }

		//アクション属性が"AC_GUARD"は「不可」
		if ( IsGuard () ) { return F; }

		//特殊タイマー：投げ無敵（やられ状態からの戻りフレーム）
		if ( m_btlPrm.GetcTmr_ThrowInv ()->IsActive () ) { return F; }


		//それ以外は「可能」
		return T;
	}

	
	//投げ判定
	bool ExeChara::IsThrowAction () const
	{
		//状態遷移に「投げ」を条件に持つものがあるとき true を返す
		UINT i = Check_TransitAction_Condition ( BRC_THR_I );
		UINT e = Check_TransitAction_Condition ( BRC_THR_E );

		return ( i != NO_COMPLETE ) || ( e != NO_COMPLETE );
	}


	//相殺しない判定
	bool ExeChara::IsNotOffset () const
	{
		//投げ
		if ( IsThrowAction () ) { return T; }
#if 0
		//超必殺
		P_Sequence pAct = m_pAction;
		if ( pAct->IsName ( _T("超必殺発動") ) ) { return T; }
		if ( pAct->IsName ( _T("超必B発動") ) ) { return T; }
#endif // 0

		return F;
	}

	//受身可能かどうか	
	bool ExeChara::CanUkemi () const
	{
		//現在スクリプトのルートから「空中受身」がある場合
		// 
		//キャラの持つルート,ブランチ,コマンドの参照
		const AP_Rut& vpRoute = m_pChara->GetvpRoute ();

		//スクリプトの持つルートリスト
		for ( UINT indexRut : m_pScript->GetcaRouteID () )
		{
			const P_Rut pRut = vpRoute [ indexRut ];
			if ( pRut->Name.Is ( U"空中受身" ) )
			{
				return T;
			}
		}
		return F;
	}

	//==========================================
	//◆ 相手・攻撃 → 自分・くらい
	//くらい状態・ダメージ処理
	//==========================================
	void ExeChara::OnDamaged ()
	{
		m_OnDamaged.OnDamaged ();
	}

	void ExeChara::OnEfDamaged ()
	{
		m_OnDamaged.OnEfDamaged ();



		//特殊処理
		//相手側
		if ( m_pOther.lock()->m_name == CHARA_FERARIA )
		{
			if ( IsNameAction ( U"投げ成立0" ) )
			{
			}
		}

		m_btlPrm.DecisionWhiteDamage ();
	}


	//相手ダメージ処理の後
	void ExeChara::OnDamaged_After ()
	{
		P_ExeChara pOther = m_pOther.lock ();		//相手
		bool bGuard = pOther->IsGuard ();


		//ガード時
		if ( bGuard )
		{

		}
		//ヒット時
		else
		{
#if 0

			//キャラ別特殊
			//紗絵
			if ( GetCharaName() == CHARA_SAE )
			{
				if ( IsNameAction ( U"雷嵐ヒット" ) )
				{
					//位置固定
					//SetPosEachOther ( VEC2 ( 200.f, 0 ) );

					//地上ヒット
					pOther->SetAction ( U"ダメージ大" );
				}
			}

#endif // 0
		}


		//-----------------------------------------------------
		//特殊アクションカテゴリ指定
		if ( IsSpecial () || IsOverdrive () || IsThrow () )
		{
			//必殺・超必殺時に相手の白ダメージ確定
			//ver 0.13 投げを追加
			m_pOther.lock()->m_btlPrm.DecisionWhiteDamage ();
		}

	}


}	//namespace GAME

