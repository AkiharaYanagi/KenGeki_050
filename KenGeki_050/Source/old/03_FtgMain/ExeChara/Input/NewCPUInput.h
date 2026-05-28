//=================================================================================================
//
// NewCPUInput ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaInput.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class NewCPUInput : public CharaInput
	{
		//重み定数
		static const std::vector < double > weights;

		//重み付き確率
		std::discrete_distribution <>	m_dist_lvr;		//レバー

		//ランダムデバイス
		std::random_device	m_rnd_dev;

		//メルセンヌ・ツイスタ
		std::mt19937 m_gen;


		//キー
		//重み定数
		static const std::vector < double > weights_key;

		//重み付き確率
		std::discrete_distribution <>	m_dist_btn;		//ボタン


		//Level		休符間隔で行動量を調整
		int32		m_level { 7 };	//1~8(0-7)
		int32		m_count_interval { 0 };


	public:
		NewCPUInput ();
		NewCPUInput ( const NewCPUInput & rhs ) = delete;
		~NewCPUInput ();

		void Load ();
		void Update ( bool dirRight );

		void SetLevel ( int32 level ) { m_level = level; }

	private:
		int32 Interval ();
	};

	using P_NewCPUInput = std::shared_ptr < NewCPUInput >;


}	//namespace GAME


