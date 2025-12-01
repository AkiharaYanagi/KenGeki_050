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

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//======================================================
	class TrainingMenuItem : public MenuItem
	{
		VEC2	m_posCursor { 0, 0 };	//親カーソル位置

	public:
		TrainingMenuItem (){}
		TrainingMenuItem ( const TrainingMenuItem & rhs ) = delete;
		~TrainingMenuItem(){}

		VEC2 GetPosCursor() const { return m_posCursor; }
		void SetPosCursor(VEC2 v) { m_posCursor = v; }
	};

	using P_TrainingMenuItem = std::shared_ptr < TrainingMenuItem >;


	//======================================================
	class MenuItem_Taikou	: public TrainingMenuItem
	{
		P_PrmRect	m_SelectBG;		//選択中背景
		P_PrmRect	m_Cursor;		//選択カーソル

		P_GrpStr	m_StrTaikou;	//剣撃対抗
		P_GrpStr	m_StrOn;	//ON
		P_GrpStr	m_StrOff;	//OFF

		bool		m_state{ F };	//対象の状態
		P_PrmRect	m_Select;		//選択表示

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

		bool GetState() const { return m_state; }
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

	private:
		void SetLevel(INT32 level);
	};

	using P_MenuItem_CPU_LEVEL = std::shared_ptr < MenuItem_CPU_LEVEL >;

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
	private:
		
	};

	using P_MenuItem_Return = std::shared_ptr < MenuItem_Return >;


	//======================================================

	//======================================================
	class MenuItem_Title	: public TrainingMenuItem
	{
		P_GrpStr	m_StrReturn;	//"戻る"
	public:
		MenuItem_Title ();
		MenuItem_Title ( const MenuItem_Title & rhs ) = delete;
		~MenuItem_Title ();

		void Load ();
		void Move ();
		void On () override;
		void Off () override;

		void Do() override;
	private:
		
	};

	using P_MenuItem_Title = std::shared_ptr < MenuItem_Title >;


	//======================================================

}	//namespace GAME

