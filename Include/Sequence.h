﻿//=================================================================================================
//
//	Sequence ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"

//#include "Script.h"
#include "Frame.h"



//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-----------------------------------------------------------------
	//		フレームの一連、アクションとエフェクトに派生
	//-----------------------------------------------------------------
	class Sequence
	{
		s3d::String		m_name { U"new_sequence" };			//名前
		PAP_Frame		m_papFrame;		//フレーム配列
		UINT			m_next { 0 };		//次シークエンスID
		s3d::String		m_nextName { U"next_sequence" };		//次シークエンス名

	public:
		Sequence();
		Sequence(const Sequence& rhs) = delete;
		virtual ~Sequence();

		void Rele();

		//-----------------------------------------------------------------
		//フレームの追加
		void AddpFrame ( P_Frame pFrame ) { m_papFrame->push_back(pFrame); }

		//フレーム配列にまとめて追加
		void AddaFrame ( UP_AP_Script arypFrame, rsize_t size );

		//フレーム配列サイズの取得
		size_t SizeFrame() const { return m_papFrame->size(); }

		//フレーム配列ポインタを取得
		PAP_Frame GetpvpScript() { return m_papFrame; }

		//フレームの取得
		P_Frame GetpScript(UINT index) { return m_papFrame->at(index); }

		//次フレームが存在するかどうか
		bool IsNextScript(UINT index) const { return (index < m_papFrame->size() - 1); }

		//最終フレームかどうか
		bool IsEndScript(UINT index) const { return (index == m_papFrame->size() - 1); }

		//オーバーフレームかどうか
		bool IsOverScript(UINT index) const { return (index > m_papFrame->size() - 1); }

#if 0

//		tstring			m_name { _T("new_sequence") };			//名前
		s3d::String		m_name { U"new_sequence" };			//名前

		PVP_Script		m_pvpScript;		//スクリプト配列
//		PAP_Script		mpap_Script;		//スクリプト配列

		UINT			m_next { 0 };		//次シークエンスID
//		tstring			m_nextName { _T("next_sequence") };		//次シークエンス名
		s3d::String		m_nextName { U"next_sequence" };		//次シークエンス名

	public:
		Sequence ();
		Sequence ( const Sequence & rhs ) = delete;
		virtual ~Sequence ();

		void Rele ();

		//-----------------------------------------------------------------
		//名前
//		void SetName ( tstring name ) { m_name.assign ( name ); }
//		tstring GetName () const { return m_name; }
//		bool IsName ( tstring name ) const { return m_name == name; }
		void SetName ( const s3d::String & name ) { m_name.assign ( name ); }
		const s3d::String & GetcrName () const { return m_name; }
		s3d::String GetName () const { return m_name; }
		bool IsName ( const s3d::String & name ) const { return m_name == name; }

		//-----------------------------------------------------------------
		//スクリプトの追加
		void AddpScript ( P_Script pScript ) { m_pvpScript->push_back ( pScript ); }

		//スクリプト配列にまとめて追加
		void AddaScript ( std::unique_ptr < P_Script[] > arypScript, rsize_t size );

		//スクリプト配列サイズの取得
		size_t SizeScript () const { return m_pvpScript->size(); }

		//スクリプト配列ポインタを取得
		PVP_Script GetpvpScript () { return m_pvpScript; }

		//スクリプトの取得
		P_Script GetpScript ( UINT index ) { return m_pvpScript->at ( index ); }

		//次スクリプトが存在するかどうか
		bool IsNextScript ( UINT index ) const { return ( index < m_pvpScript->size() - 1 ); }

		//最終スクリプトかどうか
		bool IsEndScript ( UINT index ) const { return ( index == m_pvpScript->size () - 1 ); }

		//オーバースクリプトかどうか
		bool IsOverScript ( UINT index ) const { return ( index > m_pvpScript->size () - 1 ); }

		//次シークエンスID
		UINT GetNextID () const { return m_next; }
		void SetNextID (UINT id) { m_next = id; }

		//次シークエンス名
//		tstring GetNextName () const { return m_nextName; }
//		void SetNextName ( tstring tstr ) { m_nextName = tstr; }
		s3d::String GetNextName () const { return m_nextName; }
		void SetNextName ( s3d::String tstr ) { m_nextName = tstr; }

#endif // 0
	};

	using WP_Sqc = std::weak_ptr < Sequence >;
	using P_Sqc = std::shared_ptr < Sequence >;
	using AP_Sqc = s3d::Array < P_Sqc >;
	using PAP_Sqc = std::shared_ptr < AP_Sqc >;


}	//namespace GAME


