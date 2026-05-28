//=================================================================================================
//
//	CharaSele_CharaGrp
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "00_Core/GameConst.h"
#include "00_Core/Param.h"
#include "CharaSele_Name.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//キャラごとのグラフィックまとめ

	class CharaSele_CharaGrp	: public TASK_VEC
	{
		PLAYER_ID	m_id { _PLAYER_NUM };	//プレイヤID

		//保存用共通パラメータ
		P_Param		m_pParam;

		P_Grp		m_ch_stand_large;		//キャラ立ち絵(大)1p/2p
		P_Grp		m_ch_stand_small;		//キャラ立ち絵(小)1p/2p

		int			m_index { 0 };

		float		m_base_x { 0 };
		float		m_base_y { 0 };
		float		m_dx { 0 };
		float		m_vx { 0 };
		float		m_start_x { 0 };

		//キャラ名前表示（円形）
		P_ChSl_Nm	m_name;

	public:
		CharaSele_CharaGrp ();
		CharaSele_CharaGrp ( const CharaSele_CharaGrp & rhs ) = delete;
		~CharaSele_CharaGrp ();

		void SetpParam ( P_Param p );
		void Load ();
		void Init ();
		void Move ();

		void SetPlayerID ( PLAYER_ID id ) { m_id = id; m_name->SetPlayerID ( id ); }

#if 0
		void SetNameTheta ( float f ) { m_theta = f; m_angle1 = -f; }
		void SetName ( CHARA_NAME name );
		CHARA_NAME GetName () const { return m_name; }
		void SetpGrp ( P_ChSl_TxSet p );
#endif // 0

		void Assign ( CHARA_NAME name, CHARA_COLOR clr );

#if 0
		void NextColor ();
		void PrevColor ();

#endif // 0

	private:
		P_Grp MakepGrp ( float z );

		const static UINT32 CLR_0 {0};
		const static UINT32 CLR_1 {1};

#if 0

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

#endif // 0
	};

	using P_ChSl_ChGrp = std::shared_ptr < CharaSele_CharaGrp >;


}	//namespace GAME

