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
#include <array>


//-------------------------------------------------------------------------------------------------
//	定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	// 定数宣言
	//------------------------------------------

	//BGMファイル名
#if 0

	constexpr char32_t BGM_NONE []		= U"BGM_NONE";
	constexpr char32_t BGM_SAE []		= U"00_BGM_SAE.wav";
	constexpr char32_t BGM_OUKA []		= U"01_BGM_OUKA.wav";
	constexpr char32_t BGM_RETSU []		= U"02_BGM_RETSU.wav";
	constexpr char32_t BGM_GYAVA []		= U"03_BGM_GYAVA.wav";
	constexpr char32_t BGM_FERA []		= U"04_BGM_FERA.wav";
	constexpr char32_t BGM_TSUKI []		= U"05_BGM_TSUKI.wav";
	constexpr char32_t BGM_REINA []		= U"06_BGM_REINA.wav";
	constexpr char32_t BGM_EIYUU []		= U"07_BGM_EIYUU.wav";
	constexpr char32_t BGM_DOXT []		= U"08_BGM_DOXT.wav";
	constexpr char32_t BGM_ENEMY0 []	= U"09_BGM_ENEMY0.wav";
	constexpr char32_t BGM_Title []		= U"10_BGM_Title.wav";
	constexpr char32_t BGM_CharaSele []	= U"11_BGM_CharaSele.wav";
	constexpr char32_t BGM_Result []	= U"12_BGM_Result.wav";

	constexpr char32_t BGM_NONE []		= U"BGM_NONE";
	constexpr char32_t BGM_SAE []		= U"00_BGM_SAE.opus";
	constexpr char32_t BGM_OUKA []		= U"01_BGM_OUKA.opus";
	constexpr char32_t BGM_RETSU []		= U"02_BGM_RETSU.opus";
	constexpr char32_t BGM_GYAVA []		= U"03_BGM_GYAVA.opus";
	constexpr char32_t BGM_FERA []		= U"04_BGM_FERA.opus";
	constexpr char32_t BGM_TSUKI []		= U"05_BGM_TSUKI.opus";
	constexpr char32_t BGM_REINA []		= U"06_BGM_REINA.opus";
	constexpr char32_t BGM_EIYUU []		= U"07_BGM_EIYUU.opus";
	constexpr char32_t BGM_DOXT []		= U"08_BGM_DOXT.opus";
	constexpr char32_t BGM_ENEMY0 []	= U"09_BGM_ENEMY0.opus";
	constexpr char32_t BGM_Title []		= U"10_BGM_Title.opus";
	constexpr char32_t BGM_CharaSele []	= U"11_BGM_CharaSele.opus";
	constexpr char32_t BGM_Result []	= U"12_BGM_Result.opus";
#endif // 0
	constexpr char32_t BGM_NONE []		= U"BGM_NONE";
	constexpr char32_t BGM_SAE []		= U"00_BGM_SAE.ogg";
	constexpr char32_t BGM_OUKA []		= U"01_BGM_OUKA.ogg";
	constexpr char32_t BGM_RETSU []		= U"02_BGM_RETSU.ogg";
	constexpr char32_t BGM_GYAVA []		= U"03_BGM_GYAVA.ogg";
	constexpr char32_t BGM_FERA []		= U"04_BGM_FERA.ogg";
	constexpr char32_t BGM_TSUKI []		= U"05_BGM_TSUKI.ogg";
	constexpr char32_t BGM_REINA []		= U"06_BGM_REINA.ogg";
	constexpr char32_t BGM_EIYUU []		= U"07_BGM_EIYUU.ogg";
	constexpr char32_t BGM_DOXT []		= U"08_BGM_DOXT.ogg";
	constexpr char32_t BGM_ENEMY0 []	= U"09_BGM_ENEMY0.ogg";
	constexpr char32_t BGM_Title []		= U"10_BGM_Title.ogg";
	constexpr char32_t BGM_CharaSele []	= U"11_BGM_CharaSele.ogg";
	constexpr char32_t BGM_Result []	= U"12_BGM_Result.ogg";


	//ID
	enum class BGM_ID
	{
		NONE,
		SAE,
		OUKA,
		RETSU,
		GYAVA,
		FERA,
		TSUKI,
		REINA,
		EIYUU,
		DOXT,
		ENEMY0,
		Count,
	};


	//BGM_ID_TO_NAME
//	extern BGM_NAME		BGM_ID_TO_NAME[];


	//BGMファイル名 エイリアス
	using BGM_NAME = const char32_t *;

	//型エイリアス intergral_constant
	//size_t型の値 static_cast < size_t > ( BGM_ID::Count ) を持つ型
	//::valueで値を取得できる
	using BGM_Count = std::integral_constant < size_t, static_cast < size_t > ( BGM_ID::Count ) >;


	//IDからファイル名への変換
	extern const std::array < BGM_NAME, BGM_Count::value > BGM_ID_TO_NAME;

}

