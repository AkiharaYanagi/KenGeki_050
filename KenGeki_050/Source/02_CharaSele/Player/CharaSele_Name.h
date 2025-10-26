//=================================================================================================
//
//	CharaSele_Name
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../90_GameMain/GameConst.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class CharaSele_Name	: public TASK_VEC
	{
		//プレイヤID
		PLAYER_ID	m_id { _PLAYER_NUM };
		 
		//画像
		P_Grp		m_grp;

		float		m_angle0 { 0 };
		float		m_omega { 0 };
		float		m_theta { 0 };	//名前表示必要角度
		float		m_angle1 { 0 };

	public:
		CharaSele_Name ();
		CharaSele_Name ( const CharaSele_Name & rhs ) = delete;
		~CharaSele_Name ();

		void Load ();
		void Init ();
		void Move ();

		void SetPlayerID ( PLAYER_ID id ) { m_id = id; }

		void Next ();
		void Prev ();
	};

	using P_ChSl_Nm = std::shared_ptr < CharaSele_Name >;


}	//namespace GAME

