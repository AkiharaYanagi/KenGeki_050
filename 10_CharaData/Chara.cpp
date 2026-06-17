//=================================================================================================
//
//	Chara ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "10_CharaData/Chara.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace CHARA
{

	Chara::Chara ()
	{
	}

	Chara::~Chara ()
	{
	}

#if 0

	//---------------------------------------------------
	void Chara::SetaCommand ( UP_AP_Cmd paCmd )
	{
		size_t size = paCmd->size ();
		ma_pCmd.clear ();
		ma_pCmd.resize ( size );
		for ( size_t i = 0; i < size; ++ i )
		{
			ma_pCmd [ i ] = (*paCmd) [ i ];
		}
	}

	void Chara::SetaBranch ( UP_AP_Brc paBrc )
	{
		size_t size = paBrc->size ();
		ma_pBrc.clear ();
		ma_pBrc.resize ( size );
		for ( size_t i = 0; i < size; ++ i )
		{
			ma_pBrc [ i ] = (*paBrc) [ i ];
		}
	}

	void Chara::SetaRoute ( UP_AP_Rut paRut )
	{
		size_t size = paRut->size ();
		ma_pRut.clear ();
		ma_pRut.resize ( size );
		for ( size_t i = 0; i < size; ++ i )
		{
			ma_pRut [ i ] = (*paRut) [ i ];
		}
	}

#endif // 0


}	//namespace GAME

