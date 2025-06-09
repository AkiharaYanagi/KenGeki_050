//=================================================================================================
//
//	Command
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Command.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Command::Command()
	{
	}

	Command::~Command()
	{
		ma_Gkc.clear();
	}


	//キー配列
	void Command::SetaGameKeyCmd ( const A_GKCMD & aGkc )
	{
		size_t size = aGkc.size ();
		ma_Gkc.clear ();
		ma_Gkc.resize ( size );

		for ( UINT32 i = 0; i < size; ++ i )
		{
			ma_Gkc [ i ] = aGkc [ i ];	//代入可能
		}
	}

	//比較
	bool Command::Compare( const A_GK & aGk, bool dirRight )
	{
		//キー配列長さか、コマンド受付時間の短い方で検索
		UINT32 len = (UINT32)ma_Gkc.size();
		UINT32 lmt_tm = LimitTime.Get();
		UINT32 frame = ( lmt_tm < len ) ? lmt_tm: len;

		//完成入力数（カウントダウン）(判定は-1まで用いる)
		int comp = (int)ma_Gkc.size() - 1;

		//---------------------------------------------------
		//@info 遡って検索すると毎フレーム成立状態を保持しなくて良い
		//---------------------------------------------------
		//フレームを遡って検索
		for ( UINT32 i = 0; i < frame; ++ i )
		{
			//対象キーが成立しているかどうか
			if ( ma_Gkc [ comp ].CompareTarget( aGk [ i ], dirRight ) )
			{
				-- comp;
			}

			//コマンド内のすべてが成立していればtrueを返す
			if ( 0 > comp ) { return true; }
		}

		//非 成立状態
		return false;
	}

#if 0

	void Command::SetaGameKey(GameKeyCommand gkca[], UINT32 size)
	{
		m_vecGameKey.clear();
		m_vecGameKey.resize(size);
		for (UINT32 i = 0; i < size; ++i)
		{
			m_vecGameKey[i] = gkca[i];
		}
	}

	bool Command::Compare(const V_GAME_KEY& vecGameKey, bool dirRight)
	{
		//キー配列長さか、コマンド受付時間の短い方で検索
		UINT32 len = (UINT32)vecGameKey.size();
		UINT32 lmt_tm = LimitTime.Get();
		UINT32 frame = ( lmt_tm < len ) ? lmt_tm: len;

		//完成入力数（カウントダウン）(判定は-1まで用いる)
		int comp = (int)m_vecGameKey.size() - 1;

		//---------------------------------------------------
		//@info 遡って検索すると毎フレーム成立状態を保持しなくて良い
		//---------------------------------------------------
		//フレームを遡って検索
		for (UINT32 i = 0; i < frame; ++i)
		{
			//対象キーが成立しているかどうか
			if (m_vecGameKey[comp].CompareTarget(vecGameKey[i], dirRight))
			{
				--comp;
			}

			//コマンド内のすべてが成立していればtrueを返す
			if (0 > comp) { return true; }
		}

		//非 成立状態
		return false;
	}

#endif // 0

}	//namespace GAME

