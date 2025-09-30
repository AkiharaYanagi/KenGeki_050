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
		CHARA_TEST,

		CHARA_OUKA,			//鵯桜花
		CHARA_SAE,			//巴紗絵
		CHARA_RETSUDOU,		//烈火烈堂
		CHARA_GABADARUGA,	//ギャバダルガ
		CHARA_FERARIA,		//フェラリア
		CHARA_TSUKIHIBOSHI,	//月日星
		CHARA_REINA,		//レイナ
		CHARA_KISHI,		//忘れられた英雄
		CHARA_DOXTUKA,		//ドッカードボル
		CHARA_ENEMY_ZERO,	//エネミーゼロ

		CHARA_RANDUM,
		CHARA_NAME_NUM,
	};

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

	//ステージ名
	enum STAGE_NAME
	{
		STAGE_ASAHINO_HARA,
		STAGE_YUUHINO_HARA,
		STAGE_YORUNO_HARA,
		STAGE_SCHOOL_MORNING,
		STAGE_SCHOOL_NOON,
		STAGE_SCHOOL_NIGHT,
		STAGE_TAISHOU_MORNING,
		STAGE_TAISHOU_NOON,
		STAGE_TAISHOU_NINGT,
	};

}

