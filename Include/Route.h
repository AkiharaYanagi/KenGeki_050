//=================================================================================================
//
//	Route
//		ブランチの集合
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "Branch.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Route
	{
		A_UINT32	ma_IdBranch;	//ブランチIDリスト

	public:
		Route() {}
		Route(const Route& rhs) = delete;
		~Route() {}

		//Property
		Prp_Str		Name;			//名前

		//データ設定
		void SetaIdBranch ( UPA_UINT32 paId, UINT32 size)
		{
			ma_IdBranch.clear();
			ma_IdBranch.resize(size);
			for (UINT32 i = 0; i < size; ++i)
			{
				ma_IdBranch[i] = (*paId)[i];
			}
		}

		void Clear () { ma_IdBranch.clear(); }
		void AddBranchID ( UINT32 branchId ) { ma_IdBranch.push_back ( branchId ); }

		const A_UINT32 & GetcaIDBranch () const { return ma_IdBranch; }
		A_UINT32 & GetaIDBranch () { return ma_IdBranch; }
	};

	using P_Rut = std::shared_ptr < Route >;
	using AP_Rut = s3d::Array < P_Rut >;
	using PAP_Rut = std::shared_ptr < AP_Rut >;
	using UP_AP_Rut = std::unique_ptr < AP_Rut >;


}	//namespace GAME

