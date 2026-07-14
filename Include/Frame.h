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
#include "SoundGenerate.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	constexpr size_t VERSATILE_ARY_SIZE = 16;


	class Frame
	{
		PV_RECT		m_pvCRect;		//接触枠リスト
		PV_RECT		m_pvHRect;		//当り枠リスト
		PV_RECT		m_pvARect;		//攻撃枠リスト
		PV_RECT		m_pvORect;		//相殺枠リスト

		A_UINT32	ma_RouteID;		//ルートIDリスト
		PAP_EfGnrt	m_papEfGnrt;	//Efジェネレートリスト

		//Staging Generator
		//A_Gnrt		ma_EF;			//EF(0-99)共通 (100-)固有
		A_Gnrt		ma_SE;			//SE(0-99)共通 (100-)固有
		A_Gnrt		ma_VC;			//VC(0-99)共通 (100-)固有

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

		//---------------------------------------------------
		//Property
		Prp_UINT32	Index { 0 };		//自身の該当フレーム数
		Prp_UINT32	ImageIndex { 0 };	//イメージID
		Prp_VEC2	Pos;				//画像表示位置

		//---------------------------------------------------
		//ルート
		void AddRouteID ( UINT32 i ) { ma_RouteID.push_back ( i ); }
		void SetRouteID ( UPA_UINT32 up_aryUint, UINT32 size );
		const A_UINT32 & GetcaRouteID () const { return ma_RouteID; }
		A_UINT32 & GetaRouteID () { return ma_RouteID; }


		//EfGnrtリスト
		PAP_EfGnrt GetpapEfGnrt () const { return m_papEfGnrt; }

		//EfGnrtリストに追加
		void AddpEfGnrt ( P_EfGnrt pEfGnrt ) { m_papEfGnrt->push_back ( pEfGnrt ); }

		//接触枠, 攻撃枠, 当り枠, 相殺枠
		PV_RECT GetpvCRect () const { return m_pvCRect; }
		PV_RECT GetpvARect () const { return m_pvARect; }
		PV_RECT GetpvHRect () const { return m_pvHRect; }
		PV_RECT GetpvORect () const { return m_pvORect; }
		void AddCRect ( RECT crect ) { m_pvCRect->push_back ( crect ); }
		void AddARect ( RECT arect ) { m_pvARect->push_back ( arect ); }
		void AddHRect ( RECT hrect ) { m_pvHRect->push_back ( hrect ); }
		void AddORect ( RECT orect ) { m_pvORect->push_back ( orect ); }

		//Staging Generate
		//A_Gnrt & GetaEF () { return ma_EF; }
		A_Gnrt & GetaSE () { return ma_SE; }
		A_Gnrt & GetaVC () { return ma_VC; }

		bool AGnrt_Exist ( const A_Gnrt & aGnrt, const s3d::String & name ) const;
		//bool EF_Exist ( const s3d::String & name );
		bool SE_Exist ( const s3d::String & name );
		bool VC_Exist ( const s3d::String & name );

		bool AGnrt_Blank ( const A_Gnrt & aGnrt ) const;
		//bool EF_Blank () const; 
		bool SE_Blank () const; 
		bool VC_Blank () const; 


		//パラメータ
		void Set_FP_B ( Frame_Param_Battle fpb ) { m_prmBattle = fpb; }
		Frame_Param_Battle & Get_FP_B () { return m_prmBattle; }
		
		void Set_FP_S ( Frame_Param_Staging fps ) { m_prmStaging = fps; }
		Frame_Param_Staging & Get_FP_S () { return m_prmStaging; }

		void Set_Versatile ( const A_INT32 & ver );
		A_INT32 & GetaVersatile () { return m_versatile; }

	};

	using P_Frame = std::shared_ptr < Frame >;
	using AP_Frame = s3d::Array < P_Frame >;
	using PAP_Frame = std::shared_ptr < AP_Frame >;
	using UP_AP_Frame = std::unique_ptr < AP_Frame >;





#if 0
	//================================================================
	//	◆スクリプト		キャラにおけるアクションの１フレームの値
	//		┣フレーム数
	//		┣イメージID
	//		┣画像表示位置
	//		┣計算状態(持続/代入/加算)
	//		┣[]ルート
	//		┣[]接触枠
	//		┣[]攻撃枠
	//		┣[]当り枠
	//		┣[]相殺枠
	//		┣[]エフェクト発生
	//
	//================================================================

	//クラス
	class Script
	{
		UINT	m_frame {0};		//自身の該当フレーム数
		UINT	m_imageIndex {0};	//イメージID
		VEC2	m_pos {0, 0};		//画像表示位置

		PV_RECT	m_pvCRect;		//接触枠リスト
		PV_RECT	m_pvARect;		//攻撃枠リスト
		PV_RECT	m_pvHRect;		//当り枠リスト
		PV_RECT	m_pvORect;		//相殺枠リスト

		V_UINT32		m_vRouteID;		//ルートリスト
		PVP_EfGnrt	m_pvpEfGnrt;	//Efジェネレートリスト

	public:

		//値
		ScriptParam_Battle		m_prmBattle;	//戦闘パラメータ
		ScriptParam_Staging		m_prmStaging;	//演出パラメータ
		s3d::Array < int >		m_versatile;	//汎用パラメータ


		Script ();
		Script ( const Script & rhs ) = delete;
		~Script ();

		void Make ();
		void Rele ();

		//該当フレーム数
		void SetFrame ( UINT frame ) { m_frame = frame; }
		UINT GetFrame () const { return m_frame; }

		//イメージID
		void SetImageIndex ( UINT index ) { m_imageIndex = index; }
		UINT GetImageIndex () const { return m_imageIndex; }

		//画像表示位置
		void SetPos ( VEC2 pos ) { m_pos = pos; }
		VEC2 GetPos () const { return m_pos; }

		//ルート
		void AddRouteID ( UINT i ) { m_vRouteID.push_back ( i ); }
		void SetRouteID ( std::unique_ptr < UINT[] > up_aryUint, UINT size );
		const V_UINT32 & GetcvRouteID () const { return m_vRouteID; }
		V_UINT32 & GetvRouteID () { return m_vRouteID; }

		//EfGnrtリスト
		PVP_EfGnrt GetpapEfGnrt () const { return m_pvpEfGnrt; }

		//EfGnrtリストに追加
		void AddpEfGnrt ( P_EfGnrt pEfGnrt ) { m_pvpEfGnrt->push_back ( pEfGnrt ); }

		//接触枠, 攻撃枠, 当り枠, 相殺枠
		PV_RECT GetpvCRect () const { return m_pvCRect; }
		PV_RECT GetpvARect () const { return m_pvARect; }
		PV_RECT GetpvHRect () const { return m_pvHRect; }
		PV_RECT GetpvORect () const { return m_pvORect; }
		void AddCRect ( RECT crect ) { m_pvCRect->push_back ( crect ); }
		void AddARect ( RECT arect ) { m_pvARect->push_back ( arect ); }
		void AddHRect ( RECT hrect ) { m_pvHRect->push_back ( hrect ); }
		void AddORect ( RECT orect ) { m_pvORect->push_back ( orect ); }
	};


	using P_Frame = std::shared_ptr < Script >;
	using VP_Script = std::vector < P_Frame >;
	using PVP_Script = std::shared_ptr < VP_Script >;

	//P_Frameの配列
	using AUP_P_Script = std::unique_ptr < P_Frame [] >;


	//s3d
	using Ary_Scp = s3d::Array < Script >;
	using AP_Scp = s3d::Array < P_Frame >;
	using PAP_Scp = std::shared_ptr < AP_Scp >;


#endif // 0

}	//namespace GAME

