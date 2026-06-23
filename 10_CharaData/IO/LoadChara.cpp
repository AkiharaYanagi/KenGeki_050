//=================================================================================================
//
// LoadChara ソースファイル
//
//=================================================================================================
#include "10_CharaData/LoadChara.h"

//ライブラリ利用
#include "DebugOutTrace.h"
using namespace GAME;


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace CHARA
{
	using CLK = std::chrono::steady_clock;


	//----------------------------------
	void LoadChara::Load ( const s3d::String & filename, Chara & chara )
	{
		try
		{
			_Load_scp ( filename, chara );
		}
		catch ( s3d::Error err )
		{
			TRACE_F_S ( err );
		}
		catch ( LPCTSTR lpctstr )
		{
			TRACE_F ( lpctstr );
		}
		catch (...)
		{
			TRACE_F ( _T("Error LoadCharaBin_s3d.\n") );
		}
	}

	//------------------------------------------
	//	try用実行関数
	//------------------------------------------

	//scp
	//filename : "chara_name.scp"
	void LoadChara::_Load_scp ( const s3d::String & filename, Chara & chara )
	{
		std::filesystem::path current_path = std::filesystem::current_path();

		//ファイル存在確認
		if ( ! std::filesystem::exists  ( filename.str() ) ) { return; }

		//---------------------------------------------------------------------
		//ファイル読込
		s3d::BinaryReader br ( filename );

		//---------------------------------------------------------------------
		//バージョン
		UINT32 version = 0;
		br.read ( version );

		//---------------------------------------------------------------------
		//全体のサイズ
		UINT32 scriptSize = 0;
		br.read ( scriptSize );
		if ( scriptSize > 1000000000u ) { assert (0); };	//1[GB]以上はアサート

		//全体を一時読込
		UP_BYTE buffer = std::make_unique < byte [] > ( scriptSize );
		br.read ( buffer.get(), scriptSize );

		//------------------------------------------
		//キャラ読込
		UINT32 pos = 0;	//メモリポインタ

		//スクリプト
		m_func.LoadCharaScript ( std::move ( buffer ), pos, chara );
	}

}	//namespace GAME

