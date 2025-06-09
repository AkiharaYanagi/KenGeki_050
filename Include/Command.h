//=================================================================================================
//
// Command ヘッダファイル
//	ゲーム入力キーの配列を特定の組み合わせで保持する
//	実際に入力されたものの記録と、スクリプト分岐の条件に用いる
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "Define_Siv3D.h"
#include "GameKeyCommand.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//定数
	enum Command_Const
	{
		LMT_DFLT = 16,	//入力受付初期値
	};

	using A_GKCMD = s3d::Array < GameKeyCommand >;	//判定用ゲームキーコマンド
	using UP_A_GKCMD = std::unique_ptr < A_GKCMD >;
	using A_GK = s3d::Array < GameKey >;	//記録用ゲームキー

	class Command
	{
		A_GKCMD		ma_Gkc;	//キー配列

	public:
		Command();
		Command(const Command& rhs) = delete;
		~Command();

		//Property
		Prp_Str			Name { U"Cmd" };		//名前
		Prp_UINT32		LimitTime { LMT_DFLT };	//入力受付時間


		//キー配列
		void AddGameKeyCmd ( GameKeyCommand gkc ) { ma_Gkc.push_back(gkc); }
//		void SetaGameKeyCmd ( GameKeyCommand gkca[], UINT32 size );
		void SetaGameKeyCmd ( const A_GKCMD & aGkc );

		//比較 (記録上のGameKeyからコマンド判定用のGameKeyCommandでの比較)
		bool Compare ( const V_GAME_KEY & vecGameKey, bool dirRight );
		bool Compare ( const A_GK & aGk, bool dirRight );
	};

	using P_Cmd = std::shared_ptr < Command >;
	using WP_Cmd = std::weak_ptr < Command >;		//循環参照用
	using AP_Cmd = s3d::Array < P_Cmd >;
	using UP_AP_Cmd = std::unique_ptr < AP_Cmd >;

}	//namespace GAME

