//=================================================================================================
//
// LoadCharaBinUtl ヘッダファイル
//
//=================================================================================================
#pragma once
//#include "Game.h"
#include "Chara.h"
#include "Define_Siv3D.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------
	//	LoadCharaBinで用いる関数群
	//------------------------------------------------------------
	class LoadCharaBinUtl
	{
	public:
		LoadCharaBinUtl ();
		LoadCharaBinUtl ( const LoadCharaBinUtl & rhs ) = delete;
		~LoadCharaBinUtl () = default;

		//----
//		tstring LoadText ( UP_BYTE buf, UINT32 & pos );
		s3d::String LoadS3dString ( CUPR_BYTE buf, UINT32 & pos );
		bool LoadBool ( CUPR_BYTE buf, UINT32 & pos );
		byte LoadByte ( CUPR_BYTE buf, UINT32 & pos );
		int LoadInt ( CUPR_BYTE buf, UINT32 & pos );
		UINT32 LoadUInt ( CUPR_BYTE buf, UINT32 & pos );
		VEC2 LoadVec2 ( CUPR_BYTE buf, UINT32 & pos );
		VEC2 LoadVec2_Dev10F ( CUPR_BYTE buf, UINT32 & pos );
		RECT LoadRect ( CUPR_BYTE buf, UINT32 & pos );
		void LoadListRect ( CUPR_BYTE buf, UINT32 & pos, PV_RECT pvRect );

		L_UINT LoadAryUint ( CUPR_BYTE buf, UINT32 & pos, UINT32 & refLength );
		void LoadAryUint ( CUPR_BYTE buf, UINT32 & pos, V_UINT32 & refAryUint );
		void LoadAryUint ( CUPR_BYTE buf, UINT32 & pos, A_UINT32 & refAryUint );

		void LoadAryInt ( CUPR_BYTE buf, UINT32 & pos, A_INT32 & refAryInt );
	};


}	//namespace GAME


