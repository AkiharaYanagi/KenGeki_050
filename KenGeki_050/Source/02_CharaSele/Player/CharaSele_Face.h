//=================================================================================================
//
//	CharaSele_Face
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

	class CharaSele_Face	: public TASK_VEC
	{
		//プレイヤID
		PLAYER_ID	m_id { _PLAYER_NUM };
		 
		//配置個数
		const static int CHARA_NUM { 10 };
		const static int USE_CHARA_NUM { 6 };

		//メイン画像
		P_Grp		m_grp;

		//位置保存
		s3d::Array < VEC2 >		m_aryPos;

		//回転中かどうか
		bool		m_turn { F };

		//回転位置
		//int			m_pos_turn { 0 };
		CHARA_NAME		m_pos_turn { CHARA_NAME_NUM };

	public:
		CharaSele_Face ();
		CharaSele_Face ( const CharaSele_Face & rhs ) = delete;
		~CharaSele_Face ();

		void Load ();
		void Init ();
		void Move ();

		void Next ();
		void Prev ();

		void SetPlayerID ( PLAYER_ID id );

		//void SetPos ( int pos_turn );

		void ResetPos ();
		void Assign ( CHARA_NAME name );

	private:

		//選択キャラ名から前後の表示用キャラ名
		struct PN_CHARA
		{
			CHARA_NAME prev;
			CHARA_NAME next;
		};

		//保存用
		std::map < CHARA_NAME, PN_CHARA > m_map_pn_chara;
	};

	using P_ChSl_Fc = std::shared_ptr < CharaSele_Face >;


}	//namespace GAME

