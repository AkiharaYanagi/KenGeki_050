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


		//相手（やられ側の受付時間チェック）
		bool bTimerTaikou = pOther->m_btlPrm.GetTmr_Taikou()->IsActive ();

		//受付時間ではないとき何もしない
		if ( ! bTimerTaikou )
		{
			return;
		}



		//---------------------------------------------
		//メニュー設定条件
		bool bAchieved = F;	//成立

		//CPU時、プレイヤ時、パラメータによる
		TaikouState tkStt = m_pParam->GetPrmResult().m_prp_Taikou.Get();
		switch ( tkStt )
		{
		//無効
		case GAME::TaikouState::None: bAchieved = F; break;

		case GAME::TaikouState::Normal:
			//相手の入力が合った場合
			bAchieved = pOther->m_pCharaInput->PushSomething ();
		break;

		case GAME::TaikouState::Random:
			bAchieved = s3d::Random ( 0, 1 ) == 0;
			//自身の受付時間を解除
			pOther->m_btlPrm.GetTmr_Taikou()->Clear ();
		break;

		//強制
		case GAME::TaikouState::ForcedOn: bAchieved = T; break;
		}

		//条件非成立時、何もしない
		if ( ! bAchieved )
		{
			return;
		}



		//-----------------------------------------------------
		//ゲージ処理
		

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

#if 0

		//アクセルゲージに変更

		//@info アクセルゲージ消費で移項可能かチェック
		//現在値と比較
		const int COST = 100;
		int accel = pOther->m_btlPrm.GetAccel ();

		//足りないとき何もしない
		if ( accel < ACCEL_MIN + COST )
		{
			return;
		}


		//アクセル値に必要量があれば消費して遷移する
		pOther->m_btlPrm.AddAccel ( -1 * COST );

#endif // 0

		//剣撃ゲージに変更
		//剣撃ゲージ消費で移項可能かチェック
		//現在値と比較
		const int COST = 1000;
		int balance = pOther->m_btlPrm.GetBalance ();

		//足りないとき何もしない
		if ( balance < COST )
		{
			return;
		}

		//アクセル値に必要量があれば消費して遷移する
		pOther->m_btlPrm.AddBalance ( -1 * COST );


		//超必殺技ゲージにプラス
		pOther->m_btlPrm.AddMana ( 1000 );


		//-----------------------------------------------------
		//成立時

		//---------------------------------------------
		//ノックバック量を計算済みの値
		// 
		// ・方向はゲーム上の正負が左右になっている
		// ・スクリプトの値は正負が前後
		// 
		//バトルパラメータに保存し、CalcPos()で位置を計算し、０にリセットされる
		//剣撃対抗タイマ５フレ間、ヒットストップの間はたまたま保持されている
		float accRecoil = m_btlPrm.GetAccRecoil ();
		float accRecoil_other = pOther->m_btlPrm.GetAccRecoil ();

		//----------------------------------------------------------
		// デバッグ表示用
		//bool bt = bTimerTaikou;
		//float ar0 = accRecoil;
		//----------------------------------------------------------
		

		//空中技に基礎ノックバックを設定
		if ( IsJump () || IsFloat () )
		{
			//空中技のとき、基礎ノックバックを設定
			accRecoil = ( bPosLeft ) ? -10.f : 10.f;
		}

		//0のとき初期値を設定する
		if ( accRecoil == 0 )
		{
			accRecoil = ( bPosLeft ) ? -10.f : 10.f;
		}

		//->両者の位置から方向を決める
		float dir = ( bPosLeft ) ? -1.f : 1.f;
		accRecoil = std::abs ( accRecoil ) * dir;

		//値を大きくする
		accRecoil *= 10;
		//accRecoil *= 5;

		//移動量を向きに合わせる
		//accRecoil += -10;
		accRecoil += ( bPosLeft ) ? -10 : 10;


		//成立フラグ
		pOther->m_btlPrm.SetTaikou ( T );
		//フレーム最初にFalse、以降同一フレーム処理で判定に用いる
		//主にエフェクト発生

		//受付時間を解除
		pOther->m_btlPrm.GetTmr_Taikou()->Clear ();


		//---------------------
		// 自分攻撃、相手剣撃対抗
		//自分が画面端の場合、相手に余剰分を返す

		//画面端
		float wall_L = (float)FIELD_EDGE + G_FTG()->GetWallLeft ();
		float wall_R = G_FTG()->GetWallRight () - (float)FIELD_EDGE;

		//位置
		float pos_x = m_btlPrm.GetPos ().x;
		float ax = pos_x + accRecoil;

		//左壁
		if ( ax < wall_L )
		{
			accRecoil_other = wall_L - ax;
		}
		//右壁
		if ( wall_R < ax )
		{
			accRecoil_other = - ( ax - wall_R );
		}

		//---------------------
		//値を再保存
		m_btlPrm.SetAccRecoil ( accRecoil );
		pOther->m_btlPrm.SetAccRecoil ( accRecoil_other );



#if 0
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
#endif // 0
	}



}	//namespace GAME

