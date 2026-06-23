//=================================================================================================
//
// LoadChara_Utl ヘッダファイル
//
//=================================================================================================
#pragma once
#include "Define.h"
#include "Define_Siv3D.h"
#include "Rect.h"
using namespace GAME;


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace CHARA
{
	//------------------------------------------------------------
	//	LoadChara_Funcで用いる関数群
	//------------------------------------------------------------
	class LoadChara_Utl
	{
	public:
		LoadChara_Utl ();
		LoadChara_Utl ( const LoadChara_Utl & rhs ) = delete;
		~LoadChara_Utl () = default;

		//----------------------------------------------------------
		s3d::String LoadS3dString ( CUPR_BYTE buf, UINT32 & pos );
		bool LoadBool ( CUPR_BYTE buf, UINT32 & pos );
		byte LoadByte ( CUPR_BYTE buf, UINT32 & pos );
		int LoadInt ( CUPR_BYTE buf, UINT32 & pos );
		UINT32 LoadUInt ( CUPR_BYTE buf, UINT32 & pos );
		float LoadFloat ( CUPR_BYTE buf, UINT32 & pos );
		VEC2 LoadVec2 ( CUPR_BYTE buf, UINT32 & pos );
		VEC2 LoadVec2_Dev10F ( CUPR_BYTE buf, UINT32 & pos );
		RECT LoadRect ( CUPR_BYTE buf, UINT32 & pos );
		void LoadListRect ( CUPR_BYTE buf, UINT32 & pos, PV_RECT pvRect );

		L_UINT LoadAryUint ( CUPR_BYTE buf, UINT32 & pos, UINT32 & refLength );
		void LoadAryUint ( CUPR_BYTE buf, UINT32 & pos, V_UINT32 & refAryUint );
		void LoadAryUint ( CUPR_BYTE buf, UINT32 & pos, A_UINT32 & refAryUint );

		void LoadAryInt ( CUPR_BYTE buf, UINT32 & pos, A_INT32 & refAryInt );
	};


}	//namespace CHARA


