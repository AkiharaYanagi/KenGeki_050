//=================================================================================================
//
//	CharaSele_PickFrame
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "00_Core/Param.h"
#include "00_Core/SelectArrow.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//キャラ立絵
	class CharaSele_PickFrame	: public TASK_VEC
	{
		PLAYER_ID		m_id { _PLAYER_NUM };	//プレイヤID

		//保存用共通パラメータ
		P_Param			m_pParam;


		//後ろ
		P_Grp		m_chara_pick_Back;		//背景
		P_Grp		m_C2;
		P_Grp		m_chara_pick_Frame2;		//枠
		P_Grp		m_chara_pick_Clr;		//色選択
		P_Grp		m_C1;
		P_Grp		m_C0;
		P_Grp		m_chara_pick_Frame0;		//枠
		//前


		//回転角
		float		m_angle2 { 0 };
		float		m_omega2 { -0.005f };

		float		m_angle1 { 0 };
		float		m_omega1 { 0.005f };

		float		m_angle0 { 0 };
		float		m_omega0 { -0.005f };

		enum Z
		{	//後
			Z_BACK,
			Z_C2,
			Z_F2,
			Z_Clr,
			Z_C1,
			Z_C0,
			Z_F0,
		};	//前


		P_SelectArrow		m_arrow;	//選択矢印

	public:
		CharaSele_PickFrame ();
		CharaSele_PickFrame ( const CharaSele_PickFrame & rhs ) = delete;
		~CharaSele_PickFrame ();
		void SetPlayerID ( PLAYER_ID id );

		void Load ();
		void Init ();
		void Move ();

		void SetpParam ( P_Param p );

		void Wait ();
		void Start ();
		void Decide ();

#pragma region CONST
	private:
		P_Grp MakepGrp ( const s3d::String & filename );


#pragma endregion
	};

	using P_ChSl_PickFrame = std::shared_ptr < CharaSele_PickFrame >;


}	//namespace GAME

