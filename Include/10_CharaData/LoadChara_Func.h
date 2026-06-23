//=================================================================================================
//
// LoadChara_Func ヘッダファイル
//
//=================================================================================================
#pragma once

#include "Define.h"
using namespace GAME;

#include "10_CharaData/Chara.h"
#include "10_CharaData/LoadChara_Utl.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace CHARA
{
	//------------------------------------------------------------
	//	LoadCharaで用いる関数群
	//------------------------------------------------------------
	class LoadChara_Func
	{
		LoadChara_Utl		m_utl;

	public:
		LoadChara_Func () = default;
		LoadChara_Func ( const LoadChara_Func & rhs ) = delete;
		~LoadChara_Func () = default;

		void LoadChara ( CUPR_BYTE buf, UINT32 & pos, Chara & ch );
		void LoadCharaScript ( CUPR_BYTE buf, UINT32 & pos, Chara & ch );
		void LoadCharaImage ( CUPR_BYTE buf, UINT32 & pos, Chara & ch );

		void LoadCompend ( CUPR_BYTE buf, UINT32 & pos, Compend & cmpd );

		void LoadCommand ( CUPR_BYTE buf, UINT32 & pos, Chara & ch );
		void LoadBranch ( CUPR_BYTE buf, UINT32 & pos, Chara & ch );
		void LoadRoute ( CUPR_BYTE buf, UINT32 & pos, Chara & ch );

		void LoadFrame ( CUPR_BYTE buf, UINT32 & pos, Frame & frm );
		void LoadFrmPrm_Btl ( CUPR_BYTE buf, UINT32 & pos, Frame & frm );
		void LoadFrmPrm_Stg ( CUPR_BYTE buf, UINT32 & pos, Frame & frm );

//		void LoadImg ( CUPR_BYTE buf, UINT32 & pos, PAP_Tx pvp_tx );

		void LoadListName ( CUPR_BYTE buf, UINT32 & pos, A_STR & aStr );
	};


}	//namespace GAME


