//=================================================================================================
//
//	CharaSele_Color
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class CharaSele_Color : public TASK_VEC
	{
		PLAYER_ID		m_id { _PLAYER_NUM };	//プレイヤID

		//カラー表示
		P_Grp		m_color;		//カラー
		float		m_color_bx{0};	//基準位置


		P_Grp		m_arrow;		//矢印

		//矢印振動
		float		m_arrow_bx{0};	//基準位置
		float		m_arrow_by{0};	//基準位置
		float		m_arrow_frq{0};		//周波数
		float		m_arrow_time{0};	//時間
		float		m_arrow_w{0};	//幅

	public:
		CharaSele_Color ();
		CharaSele_Color ( const CharaSele_Color & rhs ) = delete;
		~CharaSele_Color ();

		void Load ();
		void Init ();
		void SetPlayerID ( PLAYER_ID id );
		void Move ();

		void Next ();
		void Prev ();
	};

	using P_CharaSele_Color = std::shared_ptr < CharaSele_Color >;


}	//namespace GAME

