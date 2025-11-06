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
#include "../../91_Param/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class CharaSele_Name	: public TASK_VEC
	{
		//プレイヤID
		PLAYER_ID	m_id { _PLAYER_NUM };
		 
		//保存用共通パラメータ
		P_Param			m_pParam;

		//画像
		P_Grp		m_grp;
		P_Ob		m_pob0;
		P_Ob		m_pob1;

		//1つめ
		float		m_theta0 { 0 };
		float		m_omega { 0 };
		float		m_angle { 0 };	//名前表示必要角度

		//2つめ
		float		m_theta1 { 0 };

	public:
		CharaSele_Name ();
		CharaSele_Name ( const CharaSele_Name & rhs ) = delete;
		~CharaSele_Name ();

		void Load ();
		void Init ();
		void Move ();

		void SetPlayerID ( PLAYER_ID id ) { m_id = id; }
		void SetpParam ( P_Param p );
		 
		void Next ();
		void Prev ();

		void Assign ( CHARA_NAME name );

		//名前の輪っか表示幅
		static constexpr std::array < float, CHARA_NAME_COUNT > ARY_NAME_THETA = 
		{
			2.15f,		//鵯桜花
			1.45f,		//巴紗絵
			2.20f,		//烈火烈堂
			1.84f,		//ギャバダルガ
			1.38f,		//フェラリア
			1.52f,		//月日星
			0.6f,		//レイナ
			1.4f,		//忘れられた英雄
			1.6f,		//ドッカードボル
			1.3f,		//エネミーゼロ
		};

		void AngleInit ( CHARA_NAME name );
	};

	using P_ChSl_Nm = std::shared_ptr < CharaSele_Name >;


}	//namespace GAME

