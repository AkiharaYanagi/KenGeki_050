//=================================================================================================
//
//	Branch ヘッダファイル
//		スクリプト遷移条件の入力コマンドと遷移先シークエンス
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "Define.h"
#include "Chara_Const.h"
#include "Command.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//---------------------------------------------------------------
	//前方宣言
	class Sequence;
	using WP_Sqc = std::weak_ptr < Sequence >;		//循環参照

	using Prp_Brc_Cnd = Property < BRANCH_CONDITION >;	//プロパティ

	//---------------------------------------------------------------
	class Branch
	{

	public:
		Branch();
		Branch( const Branch& rhs ) = delete;
		~Branch();

		//Property
		Prp_Str			Name;			//名前
		Prp_Brc_Cnd		Condition;		//分岐条件

		Prp_UINT32		IndexCommand;	//条件コマンド配列添字
		Prp_Str			NameCommand{ U"cmd_name" };	//条件コマンド名前
		WP_Cmd			m_pCmd;			//条件コマンドポインタ
		WP_Cmd GetpCommand () const { return m_pCmd; }

		Prp_UINT32		IndexSequence;//遷移先シークエンス添字
		Prp_Str			NameSequence{ U"sqc_name" };	//遷移先シークエンス名前
		WP_Sqc			m_pSqc;			//遷移先シークエンスポインタ
		WP_Sqc GetpSequence () const { return m_pSqc; }

		Prp_UINT32		IndexFrame;		//遷移先スクリプト位置
		Prp_bool		Other;			//同一シークエンスで遷移可能かどうか
	};

	using P_Brc = std::shared_ptr < Branch >;
	using AP_Brc = s3d::Array < P_Brc >;
	using PAP_Brc = std::shared_ptr < AP_Brc >;
	using UP_AP_Brc = std::unique_ptr < AP_Brc >;

}	//namespace GAME

