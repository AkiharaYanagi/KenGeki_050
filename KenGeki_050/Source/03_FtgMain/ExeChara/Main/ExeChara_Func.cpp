//=================================================================================================
//
// エグゼキャラ　ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================
	//	関数群
	//================================================


	//================================================
	// フレーム毎に実行
	
	//バトルパラメータ入力処理
	void ExeChara::BtlPrm_Move_Input ()
	{
		//==========================================
		//◆ 自分・攻撃 -> 相手・くらい
		//ヒット発生(攻撃成立側)
		//==========================================
		//自分ノックバック処理
		
		//★★★ 剣撃対抗 (打撃時にいずれかの入力で距離離し)

		P_ExeChara pOther =  m_pOther.lock();

		//----------------------------------------------------------
		//バトルパラメータ入力
		m_btlPrm.Move_Input ();

		//----------------------------------------------------------
		// 向き

		//向き(右向きが真、左向きが偽)
		//　移動量も右が正、左が負
		bool bDirRight = m_btlPrm.GetDirRight ();
		
		//相手と離れる方向(裏当て対応)
		float myX = m_btlPrm.GetPos().x;
		float otherX = pOther->m_btlPrm.GetPos().x;
		bool bPosLeft = myX < otherX;
		//自身が左位置のとき、自分が離れるのは左(負)方向

		//少ないが同位置のとき、自分の向きで決定
		if ( myX == otherX ) { bPosLeft = ! bDirRight; }
		//----------------------------------------------------------


		//相手（くらい側のフラグチェック）
		bool bTimerTaikou = pOther->m_btlPrm.GetTmr_Taikou()->IsActive ();

		//ノックバック量を計算済みの値
		// 
		// ・方向はゲーム上の正負が左右になっている
		// ・スクリプトの値は正負が前後
		// 
		//バトルパラメータに保存し、CalcPos()で位置を計算し、０にリセットされる
		//剣撃対抗タイマ５フレ間、ヒットストップの間はたまたま保持されている
		float accRecoil = m_btlPrm.GetAccRecoil ();



		//----------------------------------------------------------
		// デバッグ表示用
		bool bt = bTimerTaikou;
		float ar0 = accRecoil;
		//----------------------------------------------------------



		//受付時間内の場合
		if ( bTimerTaikou )
		{
			//入力が合った場合
			if ( pOther->m_pCharaInput->PushSomething () )
			{
#if 0

				//@info 剣撃ゲージ消費で移項可能かチェック

				//現在値と比較
				const int COST = 500;
				int balance = pOther->m_btlPrm.GetBalance ();
				if ( balance < COST )
				{
					//足りないとき遷移しない
				}
				else
				{
					//必要量があれば消費して遷移する
					pOther->m_btlPrm.AddBalance ( -1 * COST );

					//成立時
					accRecoil *= 10;
					accRecoil += -10;

					//成立フラグ
					pOther->m_btlPrm.SetTaikou ( T );
					//フレーム最初にFalse、以降同一フレーム処理で判定に用いる
					//主にエフェクト発生

					//自身の受付時間を解除
					pOther->m_btlPrm.GetTmr_Taikou()->Clear ();;
				}

#endif // 0

				//アクセルゲージに変更

				//@info アクセルゲージ消費で移項可能かチェック


				//現在値と比較
				const int COST = 50;
				int accel = pOther->m_btlPrm.GetAccel ();
				if ( accel < ACCEL_MIN + 50 )
				{
					//足りないとき遷移しない
				}
				else
				{
					//アクセル値に必要量があれば消費して遷移する
					pOther->m_btlPrm.AddAccel ( -1 * COST );

					//成立時

					//accRecoil += -10;
					//移動量を向きに合わせる
					accRecoil += ( bPosLeft ) ? -1 : 1;

					accRecoil *= 10;

					//accRecoil += -10;
					//移動量を向きに合わせる
					accRecoil += ( bPosLeft ) ? -10 : 10;


					//成立フラグ
					pOther->m_btlPrm.SetTaikou ( T );
					//フレーム最初にFalse、以降同一フレーム処理で判定に用いる
					//主にエフェクト発生

					//自身の受付時間を解除
					pOther->m_btlPrm.GetTmr_Taikou()->Clear ();
				}


				//値を再保存
				m_btlPrm.SetAccRecoil ( accRecoil );
			}
		}

		float ar1 = m_btlPrm.GetAccRecoil ();
		if ( m_btlPrm.GetPlayerID () == PLAYER_ID_1 )
		{
			DBGOUT_WND_F ( DBGOUT_0, U"剣撃対抗 = {}"_fmt( bt ? 1 : 0 ) );
			DBGOUT_WND_F ( DBGOUT_1, U"計算前：accRecoil = {:.3f}"_fmt( ar0 ) );
			DBGOUT_WND_F ( DBGOUT_2, U"計算後：accRecoil = {:.3f}"_fmt( ar1 ) );
		}
		if ( m_btlPrm.GetPlayerID () == PLAYER_ID_2 )
		{
			DBGOUT_WND_F ( DBGOUT_3, U"剣撃対抗 = {}"_fmt( bt ? 1 : 0 ) );
			DBGOUT_WND_F ( DBGOUT_4, U"計算前：accRecoil = {:.3f}"_fmt( ar0 ) );
			DBGOUT_WND_F ( DBGOUT_5, U"計算後：accRecoil = {:.3f}"_fmt( ar1 ) );
		}
#if 0
#endif // 0
	}



}	//namespace GAME

