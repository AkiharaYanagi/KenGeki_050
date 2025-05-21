//=================================================================================================
//
//	Frame ヘッダ
//		1[F]内のパラメータを保持するクラス
//		( 旧 Script )
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"
#include "Rect.h"

#include "Chara_Const.h"
#include "Route.h"
#include "EffectGenerate.h"
#include "Frame_Param_Battle.h"
#include "Frame_Param_Staging.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Frame
	{
		Prp_UINT32		m_index { 0 };		//自身の該当フレーム数
		Prp_UINT32		m_imageIndex { 0 };	//イメージID
		Property < VEC2 >		m_pos;		//画像表示位置

		PV_RECT		m_pvCRect;		//接触枠リスト
		PV_RECT		m_pvHRect;		//当り枠リスト
		PV_RECT		m_pvARect;		//攻撃枠リスト
		PV_RECT		m_pvORect;		//相殺枠リスト

		A_UINT32	ma_RouteID;		//ルートIDリスト
		PAP_EfGnrt	m_pvpEfGnrt;	//Efジェネレートリスト

		//値
		Frame_Param_Battle		m_prmBattle;	//戦闘パラメータ
		Frame_Param_Staging		m_prmStaging;	//演出パラメータ
		A_INT32		m_versatile;	//汎用パラメータ

	public:
		Frame();
		Frame( const Frame& rhs ) = delete;
		~Frame();

		void Make ();
		void Rele ();

		//ルート
		void AddRouteID ( UINT i ) { ma_RouteID.push_back ( i ); }
		void SetRouteID ( UPA_UINT32 up_aryUint, UINT size );
		const A_UINT32 & GetcaRouteID () const { return ma_RouteID; }
		A_UINT32 & GetaRouteID () { return ma_RouteID; }

	};

	using P_Frame = std::shared_ptr < Frame >;
	using AP_Frame = s3d::Array < P_Frame >;
	using PAP_Frame = std::shared_ptr < AP_Frame >;
	using UP_AP_Script = std::unique_ptr < P_Frame[] >;


}	//namespace GAME

