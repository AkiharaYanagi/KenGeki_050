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
#include "CharaSele_Grp.h"
#include "CharaSele_GrpSet.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using AP_ChGrp = s3d::Array < P_ChSl_GrpSet >;
	constexpr size_t CHARA_NAME_COUNT = 10;


	//キャラ立ち絵

	class CharaSele_Stand	: public TASK_VEC
	{
		PLAYER_ID		m_id { _PLAYER_NUM };	//プレイヤID
		bool			m_initialized { F };	//初期化済フラグ

		P_ChSl_Grp		m_grp;	//キャラテクスチャセット

		AP_ChGrp		map_ChGrp;		//各キャラ
		P_ChSl_GrpSet	selectedCh;		//選択
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
			for ( P_ChSl_GrpSet p : map_ChGrp )
			{
				p->SetPlayerID ( id );
			}
		}
		bool IsInit () const { return m_initialized; }

		void Next_Chara ();
		void Prev_Chara ();

		void Next_Color ();
		void Prev_Color ();

		void GrpAll_Off ();


#pragma region CONST
	private:

		//名前の輪っか表示幅
		static constexpr std::array < float, CHARA_NAME_COUNT > ARY_NAME_THETA = 
		{
			1.95f,		//鵯桜花
			1.45f,		//巴紗絵
			2.10f,		//烈火烈堂
			1.74f,		//ギャバダルガ
			1.38f,		//フェラリア
			1.52f,		//月日星
			0.6f,		//レイナ
			1.4f,		//忘れられた英雄
			1.6f,		//ドッカードボル
			1.3f,		//エネミーゼロ
		};

#pragma endregion
	};

	using P_ChSl_Std = std::shared_ptr < CharaSele_Stand >;


}	//namespace GAME

