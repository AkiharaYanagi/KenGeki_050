//=================================================================================================
//
//	Generater
//		EF, SEなどの発生源。条件やグループチェックの値を持つ
//		共通・固有指定はそれぞれ配列を作る
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"
#include "10_CharaData/Chara_Const.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace CHARA
{
	using Prp_Gnrt_Cnd = Property < GENERATE_CONDITION >;


	class Generator
	{

	public:
		Generator () {}
		Generator ( const Generator & rhs )	//コピー可能
		{
			Name = rhs.Name;
			m_cnd = rhs.m_cnd;
			m_group = rhs.m_group;
			m_target_id = rhs.m_target_id;
		}
		~Generator () {}

		Prp_Str			Name { U"" };			//名前
		Prp_Gnrt_Cnd	m_cnd { GNRT_ALL };		//条件：　常時、ヒット時、ガード時、空振り時
		Prp_UINT32		m_group { 0 };			//グループID：同一アクション内で同一IDは１回のみ発生
		Prp_UINT32		m_target_id { 0 };		//対象ID
	};

	using P_Gnrt = std::shared_ptr < Generator >;

	using A_Gnrt = s3d::Array < Generator >;	//即値コピー可能


}	//namespace GAME

