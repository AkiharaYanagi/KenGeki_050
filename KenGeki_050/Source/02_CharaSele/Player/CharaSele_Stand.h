//=================================================================================================
//
//	CharaSele_Stand
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "CharaSele_CharaGrp.h"
#include "../../91_Param/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//キャラ立絵
	class CharaSele_Stand	: public TASK_VEC
	{
		PLAYER_ID		m_id { _PLAYER_NUM };	//プレイヤID

		//保存用共通パラメータ
		P_Param			m_pParam;

		P_ChSl_ChGrp	m_chGrp;	//キャラグラフィック
		int				m_selectedIndex{0};	//選択インデックス

	public:
		CharaSele_Stand ();
		CharaSele_Stand ( const CharaSele_Stand & rhs ) = delete;
		~CharaSele_Stand ();

		void Load ();
		void Init ();
		void Move ();

		void SetPlayerID ( PLAYER_ID id )
		{
			m_id = id;
			m_chGrp->SetPlayerID ( id );
		}
		void SetpParam ( P_Param p );

		void Next_Chara ();
		void Prev_Chara ();

		void Next_Color ();
		void Prev_Color ();

		void Assign_Color ( CHARA_COLOR clr );


		//グラフィックを直接指定
		void Assign ( CHARA_NAME name, CHARA_COLOR clr );

		//グラフィックをパラメータに基づいて更新
		void Assign ();

#pragma region CONST
	private:
		const static int CH_NUM;
		const static std::array < CHARA_NAME, CHARA_NAME_COUNT > chara_name;


#pragma endregion
	};

	using P_ChSl_Std = std::shared_ptr < CharaSele_Stand >;


}	//namespace GAME

