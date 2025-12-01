//=================================================================================================
//
//	TrainingMenuItem
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "TrainingMenuItem.h"
#include "PauseMenu.h"
#include "PauseMenu_Const.h"
#include "../../90_GameMain/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=========================================================


	//--------------------------------------------------------------
	//剣撃対抗 (オン/オフ)
	PMI_Taikou::PMI_Taikou ()
	{
		Menu::SetBG_use ( F );
		m_grpStr = std::make_shared < MenuString > ();
		m_grpStr->SetStr ( U"剣撃対抗：" );
		m_grpStr->SetPos ( 200, 600 );
		m_grpStr->SetZ ( Z_MENU_STR );
		AddpTask ( m_grpStr );
		GRPLST_INSERT ( m_grpStr );
	}

	PMI_Taikou::~PMI_Taikou ()
	{
	}

	void PMI_Taikou::Do ()
	{
		PauseMenuItem::Do ();
	}

	void PMI_Taikou::Decide ()
	{
		AUD_PLAY_ONESHOT_SE(SE_select_Cancel);
	}

	void PMI_Taikou::Off ()
	{
		m_grpStr->SetValid ( F );
	}

	void PMI_Taikou::On ()
	{
		m_grpStr->SetValid ( T );
	}

	//=========================================================

}	//namespace GAME

