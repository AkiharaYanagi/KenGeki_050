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
		s3d::String		m_name;			//名前
		V_UINT32		m_vIdBranch;	//ブランチIDリスト

	public:
		Route();
		Route(const Route& rhs) = delete;
		~Route();


		//名前
		s3d::String GetName() const { return m_name; }
		void SetName(s3d::String name) { m_name.assign(name); }

		//データ設定
		void SetaIdBranch(std::unique_ptr < UINT32[] > aryId, UINT32 size)
		{
			m_vIdBranch.clear();
			m_vIdBranch.resize(size);
			for (UINT i = 0; i < size; ++i)
			{
				m_vIdBranch[i] = aryId[i];
			}
		}

		void Clear ();

		void AddBranchID ( UINT32 branchId );

		const V_UINT32 & GetcvIDBranch () const { return m_vIdBranch; }
		V_UINT32 & GetvIDBranch () { return m_vIdBranch; }
	};

	using P_Route = std::shared_ptr < Route >;
	using VP_Route = std::vector < P_Route >;
	using PVP_Route = std::shared_ptr < VP_Route >;

	using AUP_P_Route = std::unique_ptr < P_Route[] >;


}	//namespace GAME

