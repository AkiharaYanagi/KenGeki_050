//=================================================================================================
//
//	CharaSele_GrpSet
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "CharaSele_Grp.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//キャラごとのグラフィックまとめ

	class CharaSele_GrpSet	: public TASK_VEC
	{
		CHARA_NAME	m_name;		//キャラ名
		PLAYER_ID		m_id { _PLAYER_NUM };	//プレイヤID

		P_Grp		m_ch_stand_large;		//キャラ立ち絵(大)1p/2p
		P_Grp		m_ch_stand_small;		//キャラ立ち絵(小)1p/2p

		int			m_index { 0 };

		float		m_base_x { 0 };
		float		m_base_y { 0 };
		float		m_dx { 0 };
		float		m_vx { 0 };
		float		m_start_x { 0 };

		P_Grp		m_ch_name;		//キャラ名前
		float		m_angle0 { 0 };
		float		m_omega { 0 };
		float		m_theta { 0 };	//名前表示必要角度
		float		m_angle1 { 0 };

	public:
		CharaSele_GrpSet ();
		CharaSele_GrpSet ( const CharaSele_GrpSet & rhs ) = delete;
		~CharaSele_GrpSet ();

		void Load ();
		void Init ();
		void Move ();

		void SetName ( CHARA_NAME name );
		CHARA_NAME GetName () const { return m_name; }
		void SetpGrp ( P_ChSl_Grp p );
		void SetPlayerID ( PLAYER_ID id ) { m_id = id; }

		void SetNameTheta ( float f ) { m_theta = f; m_angle1 = -f; }

		void On ();
		void Off ();

		void NextColor ();
		void PrevColor ();

	private:
		P_Grp MakepGrp ();
	};

	using P_ChSl_GrpSet = std::shared_ptr < CharaSele_GrpSet >;


}	//namespace GAME

