//=================================================================================================
//
// CPUInput ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaInput.h"
#include <array>


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#if 0
#endif // 0
	//前方宣言
	class ExeChara;
	using P_ExeChara = std::shared_ptr < ExeChara >;
	using WP_ExeChara = std::weak_ptr < ExeChara >;

	//CPU行動種類
	enum CPU_ACT
	{
		CPU_NEUTRAL = 0,
		CPU_FRONT = 1,
		CPU_BACK = 2,
		CPU_FRONT_DASH = 3,
		CPU_BACK_DASH = 4,
		CPU_L = 5,
		CPU_Ma = 6,
		CPU_Mb = 7,
		CPU_H = 8,
		CPU_POISED = 9,
		CPU_ACT_NUM = 10,
	};
	using ARY_CPU_ACT = std::array < CPU_ACT, CENT >;
	using ARY_INT = std::array < int, CPU_ACT_NUM >;


	//-------
	class CPUInput : public CharaInput
	{
		const UINT		m_vGameKeyNum;		//キー入力の保存フレーム数
		V_GAME_KEY		m_vGameKey;			//キー入力保存
		PLAYER_ID		m_playerID;			//プレイヤーID
		WP_ExeChara		m_pExeChara;		//自身の参照
		WP_ExeChara		m_pExeCharaOther;	//相手の参照

		ARY_CPU_ACT		m_randomKeyNear;	//近距離
		ARY_CPU_ACT		m_randomKeyMiddle;	//中距離
		ARY_CPU_ACT		m_randomKeyFar;		//遠距離

		bool		m_bAct;		//行動決定済
		CPU_ACT		m_act;
		UINT		m_timer;
		UINT		m_actTime;

		int m_testAct;

		//外部読込
		ARY_INT		m_actNear;
		ARY_INT		m_actMiddle;
		ARY_INT		m_actFar;

	public:
		CPUInput ( WP_ExeChara p, WP_ExeChara pOther );
		CPUInput ( const CPUInput & rhs ) = delete;
		~CPUInput ();

		//初期化
		void Load ();

		//設定
		void SetPlayer ( PLAYER_ID id ) { m_playerID = id; }
//		void SetpExeChara ( WP_ExeChara p ) { m_pExeChara = p; }
//		void SetpExeCharaOther ( WP_ExeChara p ) { m_pExeCharaOther = p; }

		//フレーム毎の更新
		void Update ( bool dirRight );

		//ブランチリストをチェックして
		//コマンド条件が達成されていたら遷移先のアクションIDを返す
		UINT GetTransitID ( PAP_Brc pvpBranch, bool dirRight );

		void SetCPU_Act ( int index, ARY_INT act, CPU_ACT& cpu_act );
	};

	using P_CPUInput = std::shared_ptr < CPUInput >;



}	//namespace GAME


