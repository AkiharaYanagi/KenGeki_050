//=================================================================================================
//
//	CharaSele
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele::CharaSele ()
	{
	}

	CharaSele::~CharaSele ()
	{
	}


	void CharaSele::ParamInit ()
	{
#if 0
		P_Param p = GetpParam ();
		m_player_1p->ParamInit ( p );
		m_player_2p->ParamInit ( p );

		m_stage->SetStage ( p->GetStage_Name () );
#endif // 0
	}


	void CharaSele::Load ()
	{
		//==================================================
		//	Scene共通
		//==================================================
		//遷移先を自身に設定
		//	(コンストラクタでは shared_from_this() が使えないため、Load() で呼び出す)
		Scene::SetwpThis ( shared_from_this () );
		//==================================================

		Scene::Load ();
	}


	P_GameScene CharaSele::Transit ()
	{
#if 0
		//タイトルに移行
		if ( m_fade_toTitle->IsLast () )
		{
			Save ();
			SND_STOP_ALL_BGM();
			Scene::Transit_Title ();
		}
#endif // 0

#if 0
		//戦闘に移行
		if ( m_fade_toFighting->IsLast () )
		{
			Save ();
			SND_STOP_ALL_BGM ();

			m_fade_toFighting->ShiftTargetColor ();

			//通常戦闘かトレーニングの分岐
			P_Param pPrm = Scene::GetpParam ();
			if ( MODE_MAIN == pPrm->GetGameMode () )
			{
				Scene::Transit_Fighting ();
			}
			else if ( MODE_TRAINING == pPrm->GetGameMode () )
			{
				Scene::Transit_Training ();
			}
		}
#endif // 0

		//通常時は自身を返す
//		return shared_from_this ();
		//他のシーンが確保されたなら遷移する
		return Scene::Transit (); 
	}

}	//namespace GAME

