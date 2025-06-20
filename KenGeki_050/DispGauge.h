//=================================================================================================
//
//	テスト
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "LocalDefine.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DispGauge	: public TASK_VEC
	{
		PLAYER_ID	m_playerID;			//プレイヤによる表示側
		P_Grp		m_gauge_all_bg;		//総合ゲージ背景

		P_Grp		m_life_value;		//体力
		P_Grp		m_stamina_value;	//剣撃
		P_Grp		m_hissatsu_value;	//必殺
		P_Grp		m_accel_value;		//アクセル

		P_Plgn		m_life_mask;		//ポリゴンマスク 体力
		P_Plgn		m_stamina_mask;		//ポリゴンマスク 剣撃
		P_Plgn		m_hissatsu_mask;	//ポリゴンマスク 必殺
		P_Plgn		m_accel_mask;		//ポリゴンマスク アクセル

		int32		m_life { 10000 };	//実行値
		int32		m_stamina { 10000 };	//実行値
		int32		m_hissatsu { 10000 };	//実行値
		int32		m_accel { 1000 };	//実行値

		int32		m_dir_life{ 1 };
		int32		m_dir_stamina{ 1 };
		int32		m_dir_hissatsu{ 1 };
		int32		m_dir_accel{ 1 };

	public:
		DispGauge ();
		DispGauge ( const DispGauge & rhs ) = delete;
		~DispGauge ();

		void LoadPlayer ( PLAYER_ID plyaerID );

		void Move ();

	private:

#pragma region CONST
		//定数

		static const VEC2 POS_FRAME_ALL_1P;		//全体枠
		static const VEC2 POS_FRAME_ALL_2P;
		static const VEC2 POS_LIFE_VALUE_1P;	//ライフ
		static const VEC2 POS_LIFE_VALUE_2P;
		static const VEC2 POS_STAMINA_VALUE_1P;	//スタミナ
		static const VEC2 POS_STAMINA_VALUE_2P;
		static const VEC2 POS_HISSATSU_VALUE_1P;	//必殺
		static const VEC2 POS_HISSATSU_VALUE_2P;
		static const VEC2 POS_ACCEL_VALUE_1P;	//アクセル
		static const VEC2 POS_ACCEL_VALUE_2P;

#pragma endregion
	};

	using P_DispGauge = std::shared_ptr < DispGauge >;


}	//namespace GAME

