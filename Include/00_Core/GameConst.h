//=================================================================================================
//
// GameConst ファイル
//		ゲーム内共通定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	インクルードファイル
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
//	定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	// 定数宣言
	//------------------------------------------

	//キャラ名
	enum CHARA_NAME
	{
		CHARA_OUKA,			//鵯桜花
		CHARA_SAE,			//巴紗絵
		CHARA_RETSUDOU,		//烈火烈堂
		CHARA_GYAVADARUGA,	//ギャバダルガ
		CHARA_FERARIA,		//フェラリア
		CHARA_TSUKIHIBOSHI,	//月日星
		CHARA_REINA,		//レイナ
		CHARA_EIYUU,		//忘れられた英雄
		CHARA_DOXTUKA,		//ドッカードボル
		CHARA_ENEMY_ZERO,	//エネミーゼロ
//		CHARA_RANDUM,
		CHARA_NAME_NUM,		//10
	};
	constexpr size_t CHARA_NAME_COUNT = 10;


	//カラー指定
	enum CHARA_COLOR
	{
		CH_CLR_1,
		CH_CLR_2,
		CH_CLR_NUM,
	};

	//開始状態
	enum START_MODE
	{
		START_TITLE,
		START_INTRO,
		START_CHARA_SELE,
		START_BATTLE,
		START_RESULT,
		START_TRAINING,
		TEST_VOID,
	};

	//シーン種類
	enum class SCENE_TYPE
	{
		TITLE,
		CHARA_SELE,
		FTG_MAIN,
		TRAINING,
		RESULT,
	};


	//戦闘（対戦種類：メイン, トレーニング) モード
	enum class FTG_MODE
	{
		MODE_FTG_MAIN,	//対人(メイン)
		MODE_TRAINING,	//トレーニング
	};

	//ステージ名
	enum STAGE_NAME
	{
		STAGE_YUUHINO_HARA,
		STAGE_ASAHINO_HARA,
		STAGE_YORUNO_HARA,
		STAGE_SCHOOL_MORNING,
		STAGE_SCHOOL_NOON,
		STAGE_SCHOOL_NIGHT,
		STAGE_TAISHOU_MORNING,
		STAGE_TAISHOU_NOON,
		STAGE_TAISHOU_NINGT,
	};

}

