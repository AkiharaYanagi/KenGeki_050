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
	protected:
		P_Param		m_pParam;				//共有パラメータ
		WP_Scene	mwp_Scene;				//大元シーンポインタ
		VEC2		m_posCursor { 0, 0 };	//親カーソル位置

		P_PrmRect	m_SelectBG;		//選択中背景
		P_PrmRect	m_Select;		//選択表示
		P_PrmRect	m_Cursor;		//選択カーソル

		P_PrmRect MakeSelectBGRect ( VEC2 pos, VEC2 size );
		P_PrmRect MakeSelectRect ( VEC2 pos, VEC2 size );
		P_PrmRect MakeCursorRect ( VEC2 pos, VEC2 size );


	public:
		TrainingMenuItem ();
		TrainingMenuItem ( const TrainingMenuItem & rhs ) = delete;
		~TrainingMenuItem ();

		void SetpParam ( P_Param p ) { m_pParam = p; }
		void SetwpParentScene ( WP_Scene wp );

		void On () override;
		void Off () override;

		VEC2 GetPosCursor() const { return m_posCursor; }
		void SetPosCursor(VEC2 v) { m_posCursor = v; }

	};

	using P_TrainingMenuItem = std::shared_ptr < TrainingMenuItem >;


	//======================================================
	class MenuItem_Ukemi	: public TrainingMenuItem
	{
		P_GrpStr	m_StrUkemi;		//受け身
		P_GrpStr	m_StrOn;		//On
		P_GrpStr	m_StrOff;		//Off


		bool m_ukemiState { F };

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

		//bool GetState() const { return m_state; }

	private:
		P_GrpStr MakeStr ( LPCUSTR str, VEC2 pos );
		void NextState ();
		void PrevState ();
		VEC2 GetPosFromState ( bool state );
	};

	using P_MenuItem_Ukemi = std::shared_ptr < MenuItem_Ukemi >;


	//======================================================
	class MenuItem_Taikou	: public TrainingMenuItem
	{
		P_PrmRect	m_SelectBG;		//選択中背景
		P_PrmRect	m_Cursor;		//選択カーソル

		P_GrpStr	m_StrTaikou;	//剣撃対抗
		P_GrpStr	m_StrNone;		//None
		P_GrpStr	m_StrNormal;	//Normal
		P_GrpStr	m_StrRandom;	//Random
		P_GrpStr	m_StrForced;	//ForcedOn

//		bool		m_state{ F };	//対象の状態
		P_PrmRect	m_Select;		//選択表示

		WP_Scene	mwp_Scene;

		TaikouState m_taikouState { TaikouState::Normal };

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

		//bool GetState() const { return m_state; }

		void SetwpParentScene ( WP_Scene wp );

	private:
		P_GrpStr MakeStr ( LPCUSTR str, VEC2 pos );
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

