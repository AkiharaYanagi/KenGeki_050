//=================================================================================================
//
// キャラレクト　ヘッダファイル
//		キャラにおける枠を監理する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "00_Core/FtgConst.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//クラス
	class CharaRect
	{
		//実効枠(スクリプトからキャラ位置等を加算した値)
		PV_RECT		m_pvCRect;	//接触枠
		PV_RECT		m_pvARect;	//攻撃枠
		PV_RECT		m_pvHRect;	//当り枠
		PV_RECT		m_pvORect;	//相殺枠

	public:
		CharaRect ();
		CharaRect ( const CharaRect & rhs ) = delete;
		~CharaRect ();

		//枠設定
		void ResetAllRect ();				//全実効枠のリセット

		void ResetCRect () { ZeroVecRect ( m_pvCRect ); }
		void ResetARect () { ZeroVecRect ( m_pvARect ); }
		void ResetHRect () { ZeroVecRect ( m_pvHRect ); }
		void ResetORect () { ZeroVecRect ( m_pvORect ); }

		//枠配列取得 ( size == ExeChara::CONST_CHARA::NUM_RECT )
		PV_RECT GetpvCRect () { return m_pvCRect; }
		PV_RECT GetpvARect () { return m_pvARect; }
		PV_RECT GetpvHRect () { return m_pvHRect; }
		PV_RECT GetpvORect () { return m_pvORect; }

		//スクリプトから実効枠へ設置
		void SetpvRect ( PV_RECT pvRectActual, PV_RECT pvRectScript, bool dir, VEC2 pos );
		void SetCRect ( PV_RECT crect, bool dir, VEC2 pos );
		void SetARect ( PV_RECT arect, bool dir, VEC2 pos );
		void SetHRect ( PV_RECT hrect, bool dir, VEC2 pos );
		void SetORect ( PV_RECT orect, bool dir, VEC2 pos );

#if 0
		//実効枠から表示枠へ設置
		void SetGrpRect ( PrmRect grpRect [], RECT rect [], float dispGameBaseX );
#endif // 0
		
	};

	using P_CharaRect = std::shared_ptr < CharaRect >;


}	//namespace GAME


