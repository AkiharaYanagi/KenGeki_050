//=================================================================================================
//
//	Chara
//
//=================================================================================================
#pragma once


//-------------------------------------------------------------------------------------------------
//	ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Compend.h"
#include "Command.h"
#include "Branch.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace CHARA
{
	class Chara
	{
		Compend		behavior;
		Compend		garnish;

		AP_Cmd		ma_pCmd;	//コマンド配列
		AP_Brc		ma_pBrc;	//ブランチ配列
		AP_Rut		ma_pRut;	//ルート配列

		s3d::Array < s3d::String >		ma_SE;	//SE名配列
		s3d::Array < s3d::String >		ma_VC;	//VC名配列

	public:
		Chara ();
		Chara ( const Chara & rhs ) = delete;
		~Chara ();

		void Clear ();


		Compend & GetBehavior () { return behavior; }
		Compend & GetGarnish  () { return garnish; }

		//---------------------------------------------------------------------
		//コマンド配列に追加
		void AddpCommand ( P_Cmd pCmd ) { ma_pCmd.push_back ( pCmd ); }
		void SetaCommand ( UP_AP_Cmd paCmd );
		const AP_Cmd & GetvpCommand () const { return ma_pCmd; }

		//ブランチ配列に追加
		void AddpBranch ( P_Brc pBrc ) { ma_pBrc.push_back ( pBrc ); }
		void SetaBranch ( UP_AP_Brc paBrc );
		const AP_Brc & GetvpBranch () const { return ma_pBrc; }

		//ルート配列に追加
		void AddpRoute ( P_Rut pRut ) { ma_pRut.push_back ( pRut ); }
		void SetaRoute ( UP_AP_Rut paRut );
		const AP_Rut & GetvpRoute () const { return ma_pRut; }

		//---------------------------------------------------------------------
		s3d::Array < s3d::String > & GetaSE () { return ma_SE; }
		s3d::Array < s3d::String > & GetaVC () { return ma_VC; }
	};


	using P_Chara = std::shared_ptr < Chara >;

}

