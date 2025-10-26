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
#include "CharaSele_TxSet.h"
#include "CharaSele_CharaGrp.h"
#include "../../91_Param/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
//	using AP_ChGrp = s3d::Array < P_ChSl_ChGrp >;


	//キャラ立絵
	class CharaSele_Stand	: public TASK_VEC
	{
		PLAYER_ID		m_id { _PLAYER_NUM };	//プレイヤID

		//保存用共通パラメータ
		P_Param			m_pParam;

//		bool			m_initialized { F };	//初期化済フラグ

//		P_ChSl_TxSet	m_grp;	//キャラテクスチャセット
//		AP_ChGrp		map_ChGrp;		//各キャラ
//		P_ChSl_ChGrp	selectedCh;		//選択

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
//		bool IsInit () const { return m_initialized; }
		void SetpParam ( P_Param p );

		void Next_Chara ();
		void Prev_Chara ();

		void Next_Color ();
		void Prev_Color ();

//		void GrpAll_Off ();

		//グラフィックをパラメータに基づいて更新
		void Assign ();

#pragma region CONST
	private:
		const static std::array < CHARA_NAME, CHARA_NAME_COUNT > chara_name;


#pragma endregion
	};

	using P_ChSl_Std = std::shared_ptr < CharaSele_Stand >;


}	//namespace GAME

