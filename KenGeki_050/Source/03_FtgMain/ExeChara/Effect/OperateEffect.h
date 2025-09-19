//=================================================================================================
//
// OperateEffect ヘッダファイル
//		Effectを０〜複数個で実行する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "ExeEffect.h"
#include "../BtlParam.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class OperateEffect : public TASK_VEC
	{
		P_Chara			m_pChara;			//キャラ
		PLP_ExEf		m_plpExeEffect;		//エフェクトの実行リスト(GameMain中に動的に生成・解放する)

		PAP_Tx			m_pvpEfTexture;		//エフェクトイメージのテクスチャリスト
		AP_Brc		m_vpBranch;			//エフェクトの分岐
		AP_Rut		m_vpRoute;			//ルート

		//生成フラグ 時間停止などで生成を１回のみ実行する
		bool			m_bStop { F };
		bool			m_bGenerate { F };

	public:
		OperateEffect ();
		OperateEffect ( const OperateEffect & rhs ) = delete;
		~OperateEffect ();

		void Init ();
		void Rele ();

		void Disp ();	//復旧時表示のみ

		//エフェクト事前生成
		void MakeEfList ( P_Chara p );

		//エフェクトリスト取得
		PLP_ExEf GetplpExEf () { return m_plpExeEffect; }

		//エフェクト全体のオペレート
		void Generate ( P_Frame pScp, BtlParam & btlPrm );
		void PreMove ( P_Frame pScp, BtlParam & btlPrm );
		void PostMove ( BtlParam & btlPrm );

		//-----------------------------
		// エフェクト生成
		void GenerateEffect ( P_Frame pScp, const BtlParam & btlPrm );
		
		//エフェクトリストに追加
		void AddListEffect ( P_Sequence pEffect, P_EfGnrt pEfGnrt, VEC2 ptChara, bool dirRight );

		//オブジェクトからExeEfを取得
		P_ExEf GetpExEf ( P_Sequence p ) const;

		//オブジェクトが実行中かどうか
		bool IsActive ( P_Sequence p ) const { return GetpExEf ( p )->IsActive (); }

		//オブジェクトによる稼働開始
		void DriveEffect ( P_Sequence p ) { GetpExEf ( p )->Drive (); }

		//オブジェクトによる稼働停止
		void StopEffect ( P_Sequence p ) { GetpExEf ( p )->Stop (); }


		//一時停止中
		void SetbStop ( bool b ) { m_bStop = b; }

		//生成済みフラグ
		void SetbGnrt ( bool b ) { m_bGenerate = b; }

		//---------------------------------------------------------------
	private:
		void SynchroScript ( VEC2 ptChara );

		//特定エフェクト処理
		void Generate_Special ( P_ExEf pExeEffect, P_Sequence pEffect, P_EfGnrt pEfGnrt, VEC2 ptChara, bool dirRight );

	public:

		//攻撃判定付きのエフェクトの先頭を取得
		s3d::String GetpExeEf_BrcHitE ();

		//---------------------------------------------------------------
		//Rect
		void OnDispRect ();
		void OffDispRect ();
	};

	using P_OprEf = std::shared_ptr < OperateEffect >;


}	//namespace GAME


