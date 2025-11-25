//=================================================================================================
//
// ExeEffect ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeEffect.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//@Later	いずれEffectにEfGnrtを統合
	//------------------------------------------

	ExeEffect::ExeEffect ( P_Sequence pEffect, P_Chara pChara, P_EfGnrt pEfGnrt, VEC2 ptChara, bool dirRight )
	 :	  m_active ( true ), m_end ( false ), m_frame ( 0 )
		, m_ptEffect ( VEC2 ( 0, 0 ) ), m_dirRight ( dirRight )
		, m_vel ( VEC2 ( 0, 0 ) ), m_acc ( VEC2 ( 0, 0 ) )
		, m_pEffect ( pEffect ), m_pScript ( nullptr ) 
		, m_bDispRect ( true )
		, m_offset ( false ), m_hit ( false )
	{
		SetpEfGnrt ( pEfGnrt );
		m_pScript = m_pEffect->GetpScript ( 0 );

		m_pChara = pChara;
		m_vpBranch = pChara->GetvpBranch ();
		m_vpRoute = pChara->GetvpRoute ();

		//初期位置 (キャラ位置+エフェクト発生位置)
		m_ptEffect = ptChara + Dir ( m_ptGnrt );
		m_target = ptChara + VEC2 ( (dirRight ? 1.f : -1.f) * 1000, 0 );

		//枠
		m_charaRect = std::make_shared < CharaRect > ();

		//表示
		m_dispEffect = std::make_shared < DispEffect > ( pChara->GetGarnish().GetpapTx(), pEfGnrt->Z.Get() );
		m_dispEffect->SetpChara ( pChara );
		AddpTask ( m_dispEffect );
		m_dispEffect->SetpCharaRect ( m_charaRect );
	}

	ExeEffect::~ExeEffect ()
	{
	}

	void ExeEffect::SetpEfGnrt ( P_EfGnrt p )
	{
		m_pEfGnrt = p;
		m_ptGnrt = p->Pos.Get ();
		m_gnrt = p->Gnrt.Get ();
		m_loop = p->Loop.Get ();
		m_sync = p->Sync.Get ();
	}

	void ExeEffect::Init ()
	{
		m_active = F;
		m_end = F;
		m_frame = 0;
		m_ptEffect = VEC2 ( 0, 0 );
		m_vel = VEC2 ( 0, 0 );
		m_acc = VEC2 ( 0, 0 );
		m_dispEffect->SetValid ( F );
		m_offset = F;
		m_hit = F;

		m_loop_count = 0;
		//m_loopなど
		//生成時パラメータから取得する値は初期化しない

		TASK_VEC::Init ();
	}


	void ExeEffect::Disp ()
	{
		//表示更新
		m_dispEffect->Update ( m_pScript, m_ptEffect, m_dirRight );

		//枠表示
		if ( m_bDispRect )
		{
			m_dispEffect->Update ( m_pScript, m_ptEffect, m_dirRight );
		}
	}


	void ExeEffect::Rele ()
	{
		m_dispEffect->Rele ();
		m_dispEffect.reset ();
	}


	void ExeEffect::PreScriptMove ()
	{
		//スクリプトを取得
		m_pScript = m_pEffect->GetpScript ( m_frame );

		//エフェクト終了条件
		//画面外のとき終了
		if ( m_ptEffect.x < 0 - 100 || GAME_WIDTH + 100 < m_ptEffect.x )
		{
			m_end = true;
		}

		//エフェクト移項用
		UINT sqcID = 0;

		//現在エフェクトが最終フレームならば
		if ( m_pEffect->IsEndScript ( m_frame ) )
		{
			bool bBranch = false;

			//スクリプト分岐条件から

			//ルートのチェック
			A_UINT32 vec_RouteID = m_pScript->GetcaRouteID ();
			for ( UINT indexRoute : vec_RouteID )
			{
				//ブランチのチェック
				V_UINT32 vBranchID = m_vpRoute[indexRoute]->GetcaIDBranch ();
				for ( UINT indexBranch : vBranchID )
				{
					//終了時以外は飛ばす
					if ( BRC_END == m_vpBranch[indexBranch]->Condition.Get () )
					{
						//次シークエンスID
						sqcID = m_vpBranch[indexBranch]->IndexSequence.Get ();
						bBranch = true;
					}
				}
			}
			
			if ( bBranch )
			{
				//@todo シークエンス(エフェクト)内でエフェクトの移項
				m_pEffect = m_pChara->GetGarnish().GetpSqc ( sqcID );
				m_frame = 0;
			}
			else
			{
				INT32 loop = m_pEfGnrt->Loop.Get();

				//ループ数が０は無限
				if ( 0 == loop )
				{
					//何もしない
				}
				else if ( loop > m_loop_count )
				{
					//ループ回数カウント
					++ m_loop_count;
					m_frame = 0;	//ループ
				}
				else
				{
					m_end = true;	//終了
				}
			}
		}
		else
		{
			++ m_frame;	//続行
		}


		//特定エフェクト処理
		PreMove_Special ();
	}

	void ExeEffect::PostScriptMove ( BtlParam & btlprm )
	{
		//ゲーム位置計算 (表示位置はDispで計算する)
		//@info Exeでゲーム位置を計算し、Dispで画面位置補正を加算する

		VEC2 ptChara = btlprm.GetPos ();
		bool dirRight = btlprm.GetDirRight ();


		//判定後ヒット時or相殺時に消滅
		if ( ! m_immortal )
		{
			if ( m_hit || m_offset )
			{
				m_end = true;
				return;
			}
		}

		//エフェクト基準位置
		if ( m_sync )		//キャラ同期フラグで分岐
		{
			//エフェクト位置 = キャラ位置 + 発生位置
			m_ptEffect = ptChara + Dir ( m_ptGnrt );

			//向き
			m_dirRight = dirRight;
		}

		//速度計算
		//m_ptEffect += Dir ( m_pScript->m_prmBattle.Vel );
		CalcPos ();


		//特定エフェクト処理
		PostMove_Special ();

			 



		//枠設定
		m_charaRect->SetARect ( m_pScript->GetpvARect (), m_dirRight, m_ptEffect );

		//表示
		Disp ();
	}

	void ExeEffect::SynchroScript ( VEC2 ptChara )
	{
		m_ptEffect = ptChara;
	}


	void ExeEffect::CalcPos ()
	{
		//自前で計算する
		if ( m_calc_Off ) { return; }



		//スクリプトを取得
		P_Frame pScp = m_pScript;
		VEC2 vel = pScp->Get_FP_B().Vel.Get();
		VEC2 acc = pScp->Get_FP_B().Acc.Get();
		float dir = m_dirRight ? 1.f : -1.f;		//向き

		//------------------------
		//計算種類で分岐
		CLC_ST clcSt = pScp->Get_FP_B().CalcState.Get();
		switch ( clcSt )
		{
		case CLC_MAINTAIN: 	//持続
			m_acc = acc;

			m_vel.x += m_acc.x;		//加速度
			m_ptEffect.x += dir * m_vel.x;		//速度
			//m_ptEffect.x += dir * m_inertial.x;		//慣性

			m_vel.y += m_acc.y;		//加速度
			m_ptEffect.y += m_vel.y;		//速度
			//m_ptEffect.y += m_inertial.y;		//慣性

			break;

		case CLC_SUBSTITUDE:	//代入

			m_vel.x = vel.x;
			m_acc.x = acc.x;
			m_ptEffect.x += dir * m_vel.x;		//速度
			//m_ptEffect.x += dir * m_inertial.x;		//慣性

			//m_vg += m_g;
			//m_vel.y = vel.y + m_vg;
			m_acc.y = acc.y;
			m_ptEffect.y += m_vel.y;		//速度
			//m_ptEffect.y += m_inertial.y;		//慣性

			break;

		case CLC_ADD:	//加算

			m_vel.x += vel.x;
			m_acc.x += acc.x;
			m_ptEffect.x += dir * m_vel.x;		//速度
			//m_ptEffect.x += dir * m_inertial.x;		//慣性

			m_vel.y += vel.y;
			m_acc.y += acc.y;
			m_ptEffect.y += m_vel.y;		//速度
			//m_ptEffect.y += m_inertial.y;		//慣性

			break;

		default: break;
		}

	}


}	//namespace GAME

