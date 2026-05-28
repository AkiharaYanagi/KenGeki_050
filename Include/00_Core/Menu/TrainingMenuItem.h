//=================================================================================================
//
//	TestMenuItem
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "00_Core/Scene_lib.h"
#include "00_Core/Param.h"
#include "00_Core/Prm_Const.h"
#include "YesNo_Menu.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//======================================================
	class TrainingMenuItem : public MenuItem
	{
		P_Param		m_pParam;				//共有パラメータ
		WP_Scene	mwp_Scene;				//大元シーンポインタ
		VEC2		m_posPrtCursor { 0, 0 };	//親カーソル位置

		P_GrpStr	m_StrMain;		//見出し文字列
		P_PrmRect	m_Select;		//選択表示
		P_PrmRect	m_SelectBG;		//アクティブ中背景
		P_PrmRect	m_Cursor;		//アクティブ中選択カーソル

		P_PrmRect MakePrmRect ( float Z );	//GRP_INSERTのときZ値を先に指定する
		P_PrmRect MakeSelectBGRect ();
		P_PrmRect MakeSelectRect ();
		P_PrmRect MakeCursorRect ();

		bool	m_bUseSelect { T };		//選択可能かどうか(非表示)


	protected:
		void SetbUseSelect ( bool b ) { m_bUseSelect = b; }

		void SetStrMain ( LPCUSTR str, VEC2 pos );

		void SetSelectBGRect ( VEC2 pos, VEC2 size );

		void SetSelectRect ( VEC2 pos, VEC2 size );
		void SetSelectPos ( VEC2 pos ) { m_Select->SetPos ( pos ); }
		void SetSelectWidth ( VEC2 size );

		void SetCursorRect ( VEC2 pos, VEC2 size );
		void SetCursorPos ( VEC2 pos ) { m_Cursor->SetPos ( pos ); }
		void SetCursorWidth ( VEC2 size );

		float m_y { 0 };	//基準Y座標
		void SetBasePos ( float y );
		void SetWidth ( float w );

		//新規作成用
		P_GrpStr MakeStr ();
		P_GrpStr MakeStr ( LPCUSTR str, VEC2 pos );

	public:
		TrainingMenuItem ();
		TrainingMenuItem ( const TrainingMenuItem & rhs ) = delete;
		virtual ~TrainingMenuItem () = default;

		void SetpParam ( P_Param p ) { m_pParam = p; }
		P_Param GetpParam () { return m_pParam; }

		void SetwpParentScene ( WP_Scene wp );
		WP_Scene GetwpParentScene () { return mwp_Scene; }

		void SetActive ( bool b ) override;

		void On () override;
		void Off () override;

		VEC2 GetPosPrtCursor() const { return m_posPrtCursor; }
		void SetPosPrtCursor(VEC2 v) { m_posPrtCursor = v; }
	};
	using P_TrainingMenuItem = std::shared_ptr < TrainingMenuItem >;


	//======================================================
	class MenuItem_Ukemi	: public TrainingMenuItem
	{
		bool m_ukemiState { F };	//対象の状態

		//選択項目
		P_GrpStr	m_StrOn;		//On
		P_GrpStr	m_StrOff;		//Off

	public:
		MenuItem_Ukemi ();
		MenuItem_Ukemi ( const MenuItem_Ukemi & rhs ) = delete;
		~MenuItem_Ukemi () = default;

		void Do() override;
		void On () override;
		void Off () override;

	private:
		void NextState ();
		void PrevState ();
		VEC2 GetPosFromState () const;
	};
	using P_MenuItem_Ukemi = std::shared_ptr < MenuItem_Ukemi >;


	//======================================================
	class MenuItem_Guard	: public TrainingMenuItem
	{
		//対象の状態
		GuardState	 m_guardState { GuardState::Normal };

		//選択項目
		P_GrpStr	m_StrNormal;	//Normal
		P_GrpStr	m_StrHit1;		//Hit1
		P_GrpStr	m_StrRandom;	//Random
		P_GrpStr	m_StrForced;	//ForcedOn

	public:
		MenuItem_Guard ();
		MenuItem_Guard ( const MenuItem_Guard & rhs ) = delete;
		~MenuItem_Guard () = default;

		void Do() override;
		void On () override;
		void Off () override;
		void Back ();

	private:
		void NextState ();
		void PrevState ();
		VEC2 GetPosFromState ();
	};
	using P_MenuItem_Guard = std::shared_ptr < MenuItem_Guard >;


	//======================================================
	class MenuItem_Taikou	: public TrainingMenuItem
	{
		//選択状態
		TaikouState m_taikouState { TaikouState::Normal };

		//選択項目
		P_GrpStr	m_StrNone;		//None
		P_GrpStr	m_StrNormal;	//Normal
		P_GrpStr	m_StrRandom;	//Random
		P_GrpStr	m_StrForced;	//ForcedOn

	public:
		MenuItem_Taikou ();
		MenuItem_Taikou ( const MenuItem_Taikou & rhs ) = delete;
		~MenuItem_Taikou () = default;

		void Do() override;
		void On () override;
		void Off () override;

		void Back ();

	private:
		void NextState ();
		void PrevState ();
		VEC2 GetPosFromState ();
	};
	using P_MenuItem_Taikou = std::shared_ptr < MenuItem_Taikou >;


	//======================================================
	class MenuItem_CPU_LEVEL	: public TrainingMenuItem
	{
		INT32		m_level { 0 };	//CPUレベル
		s3d::Array < P_GrpStr >		m_aryLvStr;		//レベル文字列配列

	public:
		MenuItem_CPU_LEVEL ();
		MenuItem_CPU_LEVEL ( const MenuItem_CPU_LEVEL & rhs ) = delete;
		~MenuItem_CPU_LEVEL () = default;

		void Do() override;
		void On () override;
		void Off () override;
		void Back ();

		void ResetBasePos ( float y );

	private:
		void SetLevel ( INT32 level );
		void NextLevel ();
		void PrevLevel ();
		VEC2 GetPosFromState ();
	};
	using P_MenuItem_CPU_LEVEL = std::shared_ptr < MenuItem_CPU_LEVEL >;


	//======================================================
	class MenuItem_ToTitle	: public TrainingMenuItem
	{
		P_YesNo_Menu	m_YesNoMenu;	//確認メニュ

	public:
		MenuItem_ToTitle ();
		MenuItem_ToTitle ( const MenuItem_ToTitle & rhs ) = delete;
		~MenuItem_ToTitle () = default;

		void Off () override { m_YesNoMenu->Off (); TrainingMenuItem::Off (); }
		void Decide () override;

		void SetwpEndMenu ( WP_GameMenu wp ) { m_YesNoMenu->SetwpEndMenu ( wp ); }
		void SetwpParentScene_YS ( WP_Scene wp ) { m_YesNoMenu->SetwpParentScene ( wp ); }

		void ResetBasePos ( float y );
	};
	using P_MenuItem_ToTitle = std::shared_ptr < MenuItem_ToTitle >;


	//======================================================
	class MenuItem_Return	: public TrainingMenuItem
	{
	public:
		MenuItem_Return ();
		MenuItem_Return ( const MenuItem_Return & rhs ) = delete;
		~MenuItem_Return () = default;

		void Decide () override;

		void ResetBasePos ( float y );
	};
	using P_MenuItem_Return = std::shared_ptr < MenuItem_Return >;


	//======================================================

}	//namespace GAME

