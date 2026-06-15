//=================================================================================================
//
// ExeEffect ヘッダファイル
//		Effect１つにつき１個のオブジェクトを生成し実行する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Chara.h"
#include "DispEffect.h"
#include "../Rect/CharaRect.h"
#include "../BtlParam.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class ExeEffect : public TASK_VEC
	{
		//------------------------------------------------
		P_Sequence		m_pEffect;		//実効エフェクトポインタ

		P_EfGnrt		m_pEfGnrt;		//エフェクト生成ポインタ

		P_Chara			m_pChara;		//キャラ
		AP_Brc			m_vpBranch;		//エフェクトの分岐
		AP_Rut			m_vpRoute;		//ルート

		//------------------------------------------------
		P_DispEffect	m_dispEffect;	//表示項目管理
		bool			m_bDispRect;	//枠表示

		//------------------------------------------------
		//パラメータ
		bool		m_active;		//有効フラグ
		bool		m_end;			//終了フラグ

		UINT		m_frame;		//実効内部フレーム(スクリプトID)
		P_Frame		m_pScript;		//実効スクリプトポインタ
		VEC2		m_ptEffect;		//エフェクト位置

		VEC2		m_ptGnrt;		//エフェクト発生位置
		bool		m_gnrt;			//生成

		INT32		m_loop{1};			//繰返
		INT32		m_loop_count{0};		//カウント

		bool		m_sync;			//同期

		bool		m_dirRight;	//エフェクトの向き
		VEC2		m_vel;	//速度
		VEC2		m_acc;	//加速度

		P_CharaRect		m_charaRect;	//枠

		bool		m_offset{F};		//相殺
		bool		m_hit{F};			//ヒット


		bool		m_immortal{F};		//相殺やヒットで終了しない
		bool		m_full_display{F};	//画面全体描画(固定位置)
		bool		m_full_display_x{F};	//画面全体描画　Xのみ(固定位置)
		bool		m_out_display{F};	//画面外で消える	

	public:
		ExeEffect ( P_Sequence pEffect, P_Chara pChara, P_EfGnrt pEfGnrt, VEC2 ptChara, bool dirRight );
		ExeEffect ( const ExeEffect & rhs ) = delete;
		~ExeEffect ();

		void Init ();

		void Disp ();	//復旧時表示のみ

		void Rele ();	//手動解放

		//---------------------------------------------
		//枠取得
		P_CharaRect GetpCharaRect () { return m_charaRect; }
		//---------------------------------------------

		void SetpEfGnrt ( P_EfGnrt p );
		P_EfGnrt GetpEfGnrt () const { return m_pEfGnrt; }

		P_Sequence GetpEffect () const { return m_pEffect; }
		bool Compare ( P_Sequence p ) { return ( p == m_pEffect); }

		bool IsActive () const { return m_active; }
		bool IsEnd () const { return m_end; }

		P_Frame GetpScript ()
		{
			return m_pEffect->GetpScript ( m_frame );
		}

		//稼働開始
		void Drive () { m_active = true; }

		//稼働停止
		void Stop ()
		{
			m_active = false;
			m_dispEffect->SetValid ( false );
		}

		void PreScriptMove ();
		void PostScriptMove ( BtlParam & btlprm );
		void SynchroScript ( VEC2 ptChara );

		//値の設定
//		void SetZ ( float z ) { m_dispEffect.SetZ ( z ); }
		void SetShader ( bool b ) { m_dispEffect->SetShader ( b ); }

#if 0
		//相殺
		void SetOffset ( bool b ) { m_offset = b; }
		bool GetOffset () const { return m_offset; }

		//ヒット
		void SetHit ( bool b ) { m_hit = b; }
		bool GetHit () const { return m_hit; }

#endif // 0
		GET_SET ( VEC2, GetPt, SetPt, m_ptEffect )	//位置
		GET_SET ( VEC2, GetPtGnrt, SetPtGnrt, m_ptGnrt )	//エフェクト発生位置
		GET_SET ( bool, GetOffset, SetOffset, m_offset )	//相殺
		GET_SET ( bool, GetHit, SetHit, m_hit )				//ヒット
		GET_SET ( bool, GetImmortal, SetImmortal, m_immortal )		//不滅
		GET_SET ( bool, GetOutDisplay, SetOutDisplay, m_out_display )	//画面外で消える


		//---------------------------------------------------------------
		//Rect
		void OnDispRect() { m_bDispRect = true; m_dispEffect->OnRect(); }
		void OffDispRect() { m_bDispRect = false; m_dispEffect->OffRect(); }


		//---------------------------------------------------------------
		//描画位置指定フラグ
		void SetFullDisplay ( bool b ) { m_full_display = b; }
		void SetFullDisplay_X ( bool b ) { m_full_display_x = b; }

	private :
		//xだけ向きを反映する
		VEC2 Dir ( VEC2 v ) const
		{
			if ( m_dirRight ) { return v; }
			return VEC2 ( -v.x, v.y );
		}

		void CalcPos ();

		//特定エフェクト処理
		void Generate_Special ();
		void PreMove_Special ();
		void PostMove_Special ();

	//====================================================
	//フェラリア4M
	private :
		bool		m_calc_Off { F };
		VEC2		m_target;
		INT32		m_count { 0 };
	public :
		void SetCalcOff ( bool b ) { m_calc_Off = b; }
		void SetVel ( VEC2 vel ) { m_vel = vel; }
	//====================================================
	};

	//型別定義 エイリアス
	using ExEf = ExeEffect;
	using P_ExEf = std::shared_ptr < ExEf >;

	using VP_ExEf = std::vector < P_ExEf >;
	using PVP_ExEf = std::shared_ptr < VP_ExEf >;

	using LP_ExEf = std::list < P_ExEf >;
	using PLP_ExEf = std::shared_ptr < LP_ExEf >;


}	//namespace GAME


