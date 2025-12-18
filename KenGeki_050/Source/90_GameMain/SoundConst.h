//=================================================================================================
//
// SoundConst ファイル
//		BGMファイル指定用 定数
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	インクルードファイル
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//	定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	// 定数宣言
	//------------------------------------------

	//BGM
	constexpr char32_t BGM_NONE []		= U"BGM_NONE";
	constexpr char32_t BGM_GABA []		= U"BTL_BGM_00_GYAVA.wav";
	constexpr char32_t BGM_OUKA []		= U"BTL_BGM_01_OUKA.wav";
	constexpr char32_t BGM_SAE []		= U"BTL_BGM_02_SAE.wav";
	constexpr char32_t BGM_RETSU []		= U"BTL_BGM_03_RETSU.wav";
	constexpr char32_t BGM_FERA []		= U"BTL_BGM_04_FERA.wav";
	constexpr char32_t BGM_TSUKI []		= U"BTL_BGM_05_TSUKI.wav";
//	constexpr char32_t BGM_ENEMY0 []	= U"BTL_BGM_09_ENEMY0.wav";
	constexpr char32_t BGM_Title []		= U"SYS_BGM_00_Title.wav";
	constexpr char32_t BGM_CharaSele []	= U"SYS_BGM_01_CharaSele.wav";
	constexpr char32_t BGM_Result []	= U"SYS_BGM_02_Result.wav";

	//-------------------------------------------------------------------
	//@info バトルメインBGMを増やすとき、
	// 同時に画像「BGM名」を増やすことにも気をつける
	//-------------------------------------------------------------------
	
	//ID
	enum BGM_ID
	{
		BGM_ID_NONE,
		BGM_ID_GABA,
		BGM_ID_OUKA,
		BGM_ID_SAE,
		BGM_ID_RETSU,
		BGM_ID_FERA,
		BGM_ID_TSUKI,
	};


	//エイリアス
	using BGM_NAME = const char32_t *;

	//BGM_ID_TO_NAME	実体はSoundConsp.cpp
	extern BGM_NAME		BGM_ID_TO_NAME[];
}

