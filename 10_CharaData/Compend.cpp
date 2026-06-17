//=================================================================================================
//
//	Compend
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Compend.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Compend::Compend()
	{
		mpap_Tx = std::make_shared < AP_Tx > ();
		mpap_Sqc = std::make_shared < AP_Sqc > ();
	}

	Compend::~Compend()
	{
	}

	void Compend::SetpSqc ( UP_AP_Sqc papSqc )
	{
		size_t size = papSqc->size ();
		mpap_Sqc->clear ();
		mpap_Sqc->resize ( size );
		for ( size_t i = 0; i < size; ++ i )
		{
			(*mpap_Sqc) [ i ] = (*papSqc) [ i ];
		}
	}

	bool Compend::ExistSqc ( const s3d::String & name ) const
	{
		for ( auto p : * mpap_Sqc )
		{
			const s3d::String & actionName = p->Name.Get();
			if ( 0 == name.compare ( actionName ) )
			{
				return T;
			}
		}
		return F;
	}


	//---------------------------------------------------
	UINT32 Compend::GetSqcID ( const s3d::String & name ) const
	{
		UINT32 index = 0;
		for ( P_Sqc pSqc : * mpap_Sqc )
		{
#if 0
			s3d::String actionName = p->Name.Get (); 
			if ( 0 == name.compare ( actionName ) )
			{
				return index;
			}
#endif // 0
			if ( pSqc->Name.Is ( name ) )
			{
				return index;
			}

			++index;
		}
		return NO_ACTION;
	}


}	//namespace GAME

