//=================================================================================================
//
//	Frame ソース
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Frame.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Frame::Frame()
	{
		Make ();
	}

	Frame::~Frame()
	{
		Rele ();
	}

	void Frame::Make()
	{
		m_pvCRect = std::make_shared < V_RECT >();
		m_pvHRect = std::make_shared < V_RECT >();
		m_pvARect = std::make_shared < V_RECT >();
		m_pvORect = std::make_shared < V_RECT >();
		m_papEfGnrt = std::make_shared < AP_EfGnrt >();
		m_versatile = A_INT32 ( VERSATILE_ARY_SIZE, 0 );
	}

	void Frame::Rele()
	{
		if ( m_pvCRect ) { m_pvCRect->clear(); m_pvCRect.reset(); }
		if ( m_pvHRect ) { m_pvHRect->clear(); m_pvCRect.reset(); }
		if ( m_pvARect ) { m_pvARect->clear(); m_pvCRect.reset(); }
		if ( m_pvORect ) { m_pvORect->clear(); m_pvCRect.reset(); }
		if ( m_papEfGnrt ) { m_papEfGnrt->clear(); m_papEfGnrt.reset(); }
		m_versatile.clear();
	}

	void Frame::SetRouteID ( UPA_UINT32 up_aryUint, UINT32 size )
	{
		ma_RouteID.clear();
		ma_RouteID.resize(size);
		for (UINT32 i = 0; i < size; ++i)
		{
			ma_RouteID[i] = (*up_aryUint)[i];
		}
	}

	void Frame::Set_Versatile ( const A_INT32 & ver )
	{
		for ( UINT32 i = 0; i < VERSATILE_ARY_SIZE; ++ i )
		{
			m_versatile [ i ] = ver [ i ];
		}
	}


	//Staging Generate

	//対象が存在するかどうか
	bool Frame::AGnrt_Exist ( const A_Gnrt & aGnrt, const s3d::String & name ) const
	{
		for (Generator gnrt : aGnrt)
		{
			if ( gnrt.Name.Is ( name ) ) { return T; }
		}
		return F;
	}


	//空欄かどうかチェックする
	bool Frame::AGnrt_Blank ( const A_Gnrt & aGnrt ) const
	{
		for (Generator gnrt : aGnrt)
		{
			//１つでも空白以外ならF
			if ( ! gnrt.Name.Is ( U"" ) ) { return F; }
		}

		//すべて空白ならT
		return T;
	}


	//対象が存在するかどうか
//	bool Frame::EF_Exist ( const s3d::String & name ) { return AGnrt_Exist ( ma_EF, name ); }
	bool Frame::SE_Exist ( const s3d::String & name ) { return AGnrt_Exist ( ma_SE, name ); }
	bool Frame::VC_Exist ( const s3d::String & name ) { return AGnrt_Exist ( ma_VC, name ); }


	//空欄かどうかチェックする
//	bool Frame::EF_Blank () const { return AGnrt_Blank ( ma_EF ); }
	bool Frame::SE_Blank () const { return AGnrt_Blank ( ma_SE ); }
	bool Frame::VC_Blank () const { return AGnrt_Blank ( ma_VC ); }


}	//namespace GAME

