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
	constexpr size_t VERSATILE_ARY_SIZE = 16;


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
		m_pvpEfGnrt = std::make_shared < AP_EfGnrt >();
		m_versatile = A_INT32 ( VERSATILE_ARY_SIZE, 0 );
	}

	void Frame::Rele()
	{
		m_pvCRect->clear(); m_pvCRect.reset();
		m_pvHRect->clear(); m_pvCRect.reset();
		m_pvARect->clear(); m_pvCRect.reset();
		m_pvORect->clear(); m_pvCRect.reset();
		m_pvpEfGnrt->clear(); m_pvpEfGnrt.reset();
		m_versatile.clear();
	}

	void Frame::SetRouteID ( UPA_UINT32 up_aryUint, UINT size )
	{
		ma_RouteID.clear();
		ma_RouteID.resize(size);
		for (UINT i = 0; i < size; ++i)
		{
			ma_RouteID[i] = (*up_aryUint)[i];
		}
	}


}	//namespace GAME

