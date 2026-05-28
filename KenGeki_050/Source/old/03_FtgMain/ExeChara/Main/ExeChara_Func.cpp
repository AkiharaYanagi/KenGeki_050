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
		
		//==========================================
		//★★★ 剣撃対抗 (打撃時にいずれかの入力で距離離し)
		//==========================================

		P_ExeChara pOther =  m_pOther.lock();

		//----------------------------------------------------------
		//バトルパラメータ入力
		m_btlPrm.Move_Input ();

		//----------------------------------------------------------
		//特定技は剣撃対抗が不可能になる
		// ->IsRefused_Taikou()に移項
#if 0

		//全キャラ投げ
		if ( IsNameAction ( U"投げ発生") ) { return; }
		if ( IsNameAction ( U"投げ成立0") ) { return; }

		//特定キャラ
		if ( m_name == CHARA_OUKA )
		{
		}
		if ( m_name == CHARA_SAE )
		{
			if ( IsNameAction ( U"投げ成立1") ) { return; }
			if ( IsNameAction ( U"投げ成立2") ) { return; }
			if ( IsNameAction ( U"投げ成立3") ) { return; }
			if ( IsNameAction ( U"投げ成立4") ) { return; }
			if ( IsNameAction ( U"万雷弱派生") ) { return; }
			if ( IsNameAction ( U"万雷弱派生_成立") ) { return; }
			if ( IsNameAction ( U"万雷弱派生_起き上がり") ) { return; }
		}
		if ( m_name == CHARA_RETSUDOU )
		{
		}
		if ( m_name == CHARA_GYAVADARUGA )
		{
		}
		if ( m_name == CHARA_FERARIA )
		{
		}
		if ( m_name == CHARA_TSUKIHIBOSHI )
		{
			//月日星の特定技
			if ( IsNameAction ( U"小攻撃") )
			{
				uint32 i = m_pScript->Index.Get();
				if ( 3 <= i && i <= 8 )
				{ return; }
			}
			if ( IsNameAction ( U"中攻撃") )
			{
				uint32 i = m_pScript->Index.Get();
				if ( 3 <= i && i <= 8 )
				{ return; }
			}
			if ( IsNameAction ( U"大攻撃") )
			{
				uint32 i = m_pScript->Index.Get();
				if ( 3 <= i && i <= 8 )
				{ return; }
			}
		}

#endif // 0
		
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
		P_CharaInput pChInp = pOther->GetpCharaInput();
#if 0

		//---------------------------------------------
		//上下の判定
		bool bLvr8 = pChInp->IsLvr8 ();	// 上方向が入力されているとき

		if ( bLvr8 )
		{
			//空中やられに状態を変更して終了
			pOther->SetAction ( U"空中やられ" );
			pOther->GetBtlPrm ().SetVel ( VEC2 ( 0, -200 ) );	//上昇

			//成立フラグ
			pOther->m_btlPrm.SetTaikou ( T );
			//フレーム最初にFalse、以降同一フレーム処理で判定に用いる
			//主にエフェクト発生

			//受付時間を解除
			pOther->m_btlPrm.GetTmr_Taikou()->Clear ();

			return;
		}

		bool bLvr2 = pChInp->IsLvr2 ();	// 下方向が入力されているとき
		if ( bLvr2 )
		{
			//相手が空中( GROUND_Y < pos_y )
			float e_pos_y = m_pOther.lock()->GetPos().y;
			if ( e_pos_y < (float)GROUND_Y )
			{
				pOther->GetBtlPrm ().SetVel ( VEC2 ( 0, 200 ) );	//下降
			}
			else
			{
				//地上ならバウンド状態にして終了
				pOther->SetAction ( U"バウンド(追打)" );
			}

			//成立フラグ
			pOther->m_btlPrm.SetTaikou ( T );
			//フレーム最初にFalse、以降同一フレーム処理で判定に用いる
			//主にエフェクト発生

			//受付時間を解除
			pOther->m_btlPrm.GetTmr_Taikou()->Clear ();

			return;
		}

#endif // 0

		//--------------------------------------------------------------------
		bool bInputBack = F;	//後ろ入力
		bool bLvr4 = pChInp->IsLvr4 ();	// 後	方向が入力されているとき
		bool bLvr6 = pChInp->IsLvr6 ();	// 前	方向が入力されているとき
		//P_CharaInputは、キャラの向きに合わせて前が右、後ろが左になるように入力を変換している
		//位置で修正する

		//向きによらず相手と逆向き
		float mx = GetPos ().x;
		float ox = pOther->GetPos ().x;

		//ほぼ同位置のときは向きは両方
		if ( std::abs ( mx - ox ) < 5 )
		{
			bInputBack = bLvr4 || bLvr6;
		}
		//距離が離れた通常時
		else
		{
			//自分左：相手右
			if ( mx < ox )
			{
				//相手右向
				if ( pOther->GetDirRight () )
				{
					bInputBack = bLvr6;
				}
				//相手左向
				else
				{
					bInputBack = bLvr4;	//自分と逆
				}
			}
			//相手左：自分右
			else if ( ox < mx )
			{
				//相手右向
				if ( pOther->GetDirRight () )
				{
					bInputBack = bLvr4;	//自分と逆
				}
				//相手左向
				else
				{
					bInputBack = bLvr6;
				}
			}
		}


		//---------------------------------------------
		//成立タイマ開始
		pOther->m_btlPrm.GetTmr_TaikouOn()->Start ( 20 );

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

		if ( bInputBack )
		{
			//後ろ対抗：相手自身が下がる(方向逆)
			m_btlPrm.SetAccRecoil ( -1.f * accRecoil_other );
			pOther->m_btlPrm.SetAccRecoil ( -1.f * accRecoil );
		}
		else
		{
			m_btlPrm.SetAccRecoil ( accRecoil );
			pOther->m_btlPrm.SetAccRecoil ( accRecoil_other );
		}

#if 0
		//==========================================
		//◆ 自分・攻撃 -> 相手・くらい
		//ヒット発生(攻撃成立側)
		//==========================================
		//自分ノックバック処理

		//y方向移動量を水平に固定
		VEC2 inertial = pOther->m_btlPrm.GetInertial ();
		inertial.y = 0;
		pOther->m_btlPrm.SetInertial ( inertial );

		VEC2 vel = pOther->m_btlPrm.GetVel ();
		vel.y = 0;
		pOther->m_btlPrm.SetVel ( vel );

		VEC2 acc = pOther->m_btlPrm.GetAcc ();
		acc.y = 0;
		pOther->m_btlPrm.SetAcc ( acc );


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

