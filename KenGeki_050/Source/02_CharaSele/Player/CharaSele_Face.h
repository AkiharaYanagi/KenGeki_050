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

		//メイン画像
		P_Grp		m_grp;

		//位置保存
		s3d::Array < VEC2 >		m_aryPos;

		//回転
		bool		m_turn { F };
		//回転位置
		int			m_pos_turn { 0 };

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

		void SetPos ( int pos_turn );

		void ResetPos ();
		void Assign ( CHARA_NAME name );

	private:
		//選択位置からキャラ名
		CHARA_NAME POS_CHARA;

		//選択キャラ名から前後の表示用キャラ名
		struct PN_CHARA
		{
			CHARA_NAME prev;
			CHARA_NAME next;
			CHARA_NAME next2;
		};
	};

	using P_ChSl_Fc = std::shared_ptr < CharaSele_Face >;


}	//namespace GAME

