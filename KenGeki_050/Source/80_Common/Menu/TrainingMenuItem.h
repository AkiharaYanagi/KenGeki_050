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
#include "../../90_GameMain/Scene.h"
#include "YesNo_Menu.h"
#include "../../91_Param/Prm_Const.h"


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
		VEC2		m_posCursor { 0, 0 };	//親カーソル位置

		P_GrpStr	m_StrMain;		//見出し文字列
		P_PrmRect	m_Select;		//選択表示
		P_PrmRect	m_SelectBG;		//アクティブ中背景
		P_PrmRect	m_Cursor;		//アクティブ中選択カーソル

		P_PrmRect MakePrmRect ();
		P_PrmRect MakeSelectBGRect ();
		P_PrmRect MakeSelectRect ();
		P_PrmRect MakeCursorRect ();

	protected:
		P_GrpStr MakeStr ();
		P_GrpStr MakeStr ( LPCUSTR str, VEC2 pos );
		void SetStrMain ( LPCUSTR str, VEC2 pos );
		void SetSelectBGRect ( VEC2 pos, VEC2 size );
		void SetSelectRect ( VEC2 pos, VEC2 size );
		void SetCursorRect ( VEC2 pos, VEC2 size );


	public:
		TrainingMenuItem ();
		TrainingMenuItem ( const TrainingMenuItem & rhs ) = delete;
		~TrainingMenuItem ();

		void SetpParam ( P_Param p ) { m_pParam = p; }
		P_Param GetpParam () { return m_pParam; }
		void SetwpParentScene ( WP_Scene wp );
		void SetActive ( bool b ) override;

		void On () override;
		void Off () override;

		VEC2 GetPosCursor() const { return m_posCursor; }
		void SetPosCursor(VEC2 v) { m_posCursor = v; }

		void SetSelectPos ( VEC2 pos ) { m_Select->SetPos ( pos ); }
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
		~MenuItem_Ukemi ();

		void Init ();
		void Load ();
		void Move ();

		void Do() override;
		void SetActive(bool b) override;
		void On () override;
		void Off () override;

	private:
		//P_GrpStr MakeStr ( LPCUSTR str, VEC2 pos );
		void NextState ();
		void PrevState ();
		VEC2 GetPosFromState ( bool state );
	};

	using P_MenuItem_Ukemi = std::shared_ptr < MenuItem_Ukemi >;


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
		~MenuItem_Taikou ();

		void Init ();
		void Load ();
		void Move ();

		void Do() override;
		void SetActive(bool b) override;
		void On () override;
		void Off () override;

	private:
		//P_GrpStr MakeStr ( LPCUSTR str, VEC2 pos );
		void NextState ();
		void PrevState ();
		VEC2 GetPosFromState ( TaikouState state );
	};

	using P_MenuItem_Taikou = std::shared_ptr < MenuItem_Taikou >;


	//======================================================
	class MenuItem_CPU_LEVEL	: public TrainingMenuItem
	{
		P_PrmRect	m_SelectBG;		//選択中背景
		P_PrmRect	m_Cursor;		//選択カーソル

		P_GrpStr	m_StrCpuLevel;	//"CPUレベル"
//		P_GrpStr	m_StrDigit;	//数値

		s3d::Array < P_GrpStr >		m_aryLvStr;		//レベル文字列配列

		INT32		m_level { 0 };	//CPUレベル
		P_PrmRect	m_Select;		//選択表示

		WP_Scene	mwp_Scene;

	public:
		MenuItem_CPU_LEVEL ();
		MenuItem_CPU_LEVEL ( const MenuItem_CPU_LEVEL & rhs ) = delete;
		~MenuItem_CPU_LEVEL ();

		void Init ();
		void Load ();
		void Move ();

		void Do() override;
		void SetActive(bool b) override;
		void On () override;
		void Off () override;

		void SetwpParentScene ( WP_Scene wp );

	private:
		void SetLevel(INT32 level);
	};

	using P_MenuItem_CPU_LEVEL = std::shared_ptr < MenuItem_CPU_LEVEL >;

	//======================================================
	class MenuItem_ToTitle	: public TrainingMenuItem
	{
		P_GrpStr		m_StrToTitle;	//"タイトルに戻る"
		P_YesNo_Menu	m_YesNoMenu;	//確認メニュ

	public:
		MenuItem_ToTitle ();
		MenuItem_ToTitle ( const MenuItem_ToTitle & rhs ) = delete;
		~MenuItem_ToTitle ();

		void Load ();
		void Move ();
		void On () override;
		void Off () override;

		void Do() override;
		void Decide () override;

		void SetwpParentScene ( WP_Scene wp ) { m_YesNoMenu->SetwpParentScene ( wp ); }
	private:
		
	};

	using P_MenuItem_ToTitle = std::shared_ptr < MenuItem_ToTitle >;


	//======================================================

	//======================================================
	class MenuItem_Return	: public TrainingMenuItem
	{
		P_GrpStr	m_StrReturn;	//"戻る"
	public:
		MenuItem_Return ();
		MenuItem_Return ( const MenuItem_Return & rhs ) = delete;
		~MenuItem_Return ();

		void Load ();
		void Move ();
		void On () override;
		void Off () override;

		void Do() override;
		void Decide () override;
	private:
		
	};

	using P_MenuItem_Return = std::shared_ptr < MenuItem_Return >;


	//======================================================

}	//namespace GAME

