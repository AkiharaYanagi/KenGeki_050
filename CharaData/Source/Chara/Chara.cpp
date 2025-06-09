//=================================================================================================
//
//	Chara ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Chara.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Chara::Chara ()
	{
	}

	Chara::~Chara ()
	{
	}

#if 0

	//---------------------------------------------------
	//アクション配列にまとめて追加
	void Chara::SetpAction ( UP_AP_Sqc papAction )
	{
		behavior.SetpSqc ( std::move ( papAction ) );

	}

	//エフェクト配列にまとめて追加
	void Chara::SetpEffect ( UP_AP_Sqc papEffect )
	{
		garnish.SetpSqc ( std::move ( papEffect ) );

	}

#endif // 0


#if 0
	Chara::Chara ()
	{
//		m_pvpTxMain = std::make_shared < VP_TxBs > ();
		mpap_txMain = std::make_shared < AP_Tx > ();
		mpap_Action = std::make_shared < AP_Action > ();
//		m_pvpTxEf = std::make_shared < VP_TxBs > ();
		mpap_txEf = std::make_shared < AP_Tx > ();
		mpap_Ef = std::make_shared < AP_Effect > ();
	}

	Chara::~Chara ()
	{
	}

	void Chara::Clear ()
	{
#if 0
		//再読込時はCharaごと行う
		for ( auto p : * m_pvpTxMain ) { p->Rele (); } m_pvpTxMain->clear (); m_pvpTxMain.reset ();
		for ( auto p : * m_pvpAction ) { p->Rele (); } m_pvpAction->clear (); m_pvpAction.reset ();
		for ( auto p : * m_pvpTxEf ) { p->Rele (); } m_pvpTxEf->clear (); m_pvpTxEf.reset ();
		for ( auto p : * m_pvpEf ) { p->Rele (); } m_pvpEf->clear (); m_pvpEf.reset ();
#endif // 0
	}

	//---------------------------------------------------
	//アクション配列にまとめて追加
	void Chara::AddpAction ( AUP_P_Action arypAction, rsize_t size )
	{
		mpap_Action->clear ();
		mpap_Action->resize ( size );
		for ( UINT32 i = 0; i < size; ++ i )
		{
			( *mpap_Action ) [ i ] = arypAction [ i ];
		}
	}
	void Chara::AddpAction ( std::shared_ptr < P_Action [] > arypAction, rsize_t size )
	{
		if ( ! mpap_Action ) { return; }

		mpap_Action->clear ();
		mpap_Action->resize ( size );
		for ( UINT32 i = 0; i < size; ++ i )
		{
			( *mpap_Action ) [ i ] = arypAction [ i ];
		}
	}
	void Chara::AddpAction ( const std::vector < P_Action > & arypAction, rsize_t size )
	{
		if ( ! mpap_Action ) { return; }

		mpap_Action->clear ();
		mpap_Action->resize ( size );
		for ( UINT32 i = 0; i < size; ++ i )
		{
			(*mpap_Action) [ i ] = arypAction [ i ];
		}
	}

	//---------------------------------------------------
	//エフェクト配列にまとめて追加
	void Chara::AddpEffect ( std::unique_ptr < P_Effect [] > arypEffect, rsize_t size )
	{
		if ( ! mpap_Ef ) { return; }

		mpap_Ef->clear ();
		mpap_Ef->resize ( size );
		for ( UINT32 i = 0; i < size; ++ i )
		{
			mpap_Ef->at ( i ) = arypEffect [ i ];
		}
	}
	void Chara::AddpEffect ( const std::vector < P_Effect > & arypEffect, rsize_t size )
	{
		if ( ! mpap_Ef ) { return; }

		mpap_Ef->clear ();
		mpap_Ef->resize ( size );
		for ( UINT32 i = 0; i < size; ++ i )
		{
			mpap_Ef->at ( i ) = arypEffect [ i ];
		}
	}

#endif // 0

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

#if 0
	//---------------------------------------------------
	UINT32 Chara::GetActionID ( const s3d::String & name ) const
	{
		UINT32 index = 0;
		for ( auto p : *mpap_Action )
		{
			s3d::String actionName = p->GetName (); 
			if ( 0 == name.compare ( actionName ) )
			{
				return index;
			}
			++index;
		}
		return NO_ACTION;
	}

	bool Chara::ExistAction ( const s3d::String & name ) const
	{
		for ( auto p : * mpap_Action )
		{
			const s3d::String & actionName = p->GetcrName ();
			if ( 0 == name.compare ( actionName ) )
			{
				return T;
			}
		}
		return F;
	}

	bool Chara::ExistEffect ( const s3d::String & name ) const
	{
		for ( auto p : * mpap_Ef )
		{
			s3d::String effectName = p->GetName ();
			if ( 0 == name.compare ( effectName ) )
			{
				return T;
			}
		}
		return F;
	}

#endif // 0


}	//namespace GAME

