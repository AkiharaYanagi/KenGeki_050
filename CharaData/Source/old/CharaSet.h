﻿//=================================================================================================
//
//	CharaSet ヘッダ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"
#include "Compend.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class CharaSet
	{
		Compend		behavior;
		Compend		garnish;

	public:
		CharaSet();
		CharaSet( const CharaSet& rhs ) = delete;
		~CharaSet();

		void Load ();
	};

	using P_CharaSet = std::shared_ptr < CharaSet >;


}	//namespace GAME

