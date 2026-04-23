//=================================================================================================
//
// OperateEffect ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "OperateEffect.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//特定エフェクト処理
	void OperateEffect::Generate_Special
	(
		P_ExEf pExeEffect, P_Sequence pEffect, P_EfGnrt pEfGnrt,
		VEC2 ptChara, bool dirRight
	)
	{
		(void)ptChara;

		//----------------------------------
		//	Ef個別指定
		//----------------------------------
		if ( pEffect->Name.Is ( U"空中竜巻_鞘" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"HitLine0" ) ) { /* pExeEffect->SetShader ( F ); */ }
		if ( pEffect->Name.Is ( U"HitLine1" ) ) { /* pExeEffect->SetShader ( F ); */ }
		if ( pEffect->Name.Is ( U"HitSmoke" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"HitSmoke1" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"DustCloud" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"Guard" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"地面" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"Ukemi" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"EX" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"暁0" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"暁1" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"颯0" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"颯1" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"贐" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"極" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"万雷発生" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"万雷中派生" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"OD_A_R" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"OD_A_L" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"OD_A_G" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"Ef_テル・プム" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"Ef_ニャムヒー" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"空中飛び道具" ) ) { pExeEffect->SetShader ( F ); }
		if ( pEffect->Name.Is ( U"Aura" ) ) { pExeEffect->SetShader ( F ); }


		//全部オフ
		//pExeEffect->SetShader ( F );
#if 0
#endif // 0

		//画面全体
		//float x0 = G_FTG()->GetCharaCenterX () - (float)GAME_WIDTH_HALF;
		if ( pEffect->Name.Is ( U"地割れキャラ前" ) )
		{
			pExeEffect->SetFullDisplay ( T );
		}
		if ( pEffect->Name.Is ( U"地割れキャラ後ろ" ) )
		{
			pExeEffect->SetFullDisplay ( T );
		}

		if ( pEffect->Name.Is ( U"画面全体" ) )
		{
			pExeEffect->SetFullDisplay ( T );
		}


		//相殺やヒットで消えない
//		if ( pEffect->Name.Is ( U"空中竜巻_鞘" ) ) { pExeEffect->SetImmortal ( T ); }
		//@todo 攻撃判定が残るのをどうするか

		if ( pEffect->Name.Is ( U"4L_Shot" ) )
		{
			pExeEffect->GetpEfGnrt()->Loop.Set ( 0 );
			pExeEffect->SetShader ( F );
		}

		if ( pEffect->Name.Is ( U"4H_Shot" ) )
		{
			//pExeEffect->GetpEfGnrt()->Loop.Set ( 0 );
			pExeEffect->SetImmortal ( T );
		}


		//特殊
		if ( pEffect->Name.Is ( U"4M_Shot" ) )
		{
			int x = (int)pEfGnrt->Pos.Get().x;

			if (dirRight)
			{
				switch ( x )
				{
				case  100: pExeEffect->SetVel ( VEC2{  6.0, -10.5 } ); break;
				case   80: pExeEffect->SetVel ( VEC2{  7.0, -10.5 } ); break;
				case   60: pExeEffect->SetVel ( VEC2{  8.0, -10.5 } ); break;
				case -140: pExeEffect->SetVel ( VEC2{ -8.0, -10.5 } ); break;
				case -150: pExeEffect->SetVel ( VEC2{ -7.0, -10.5 } ); break;
				case -160: pExeEffect->SetVel ( VEC2{ -6.0, -10.5 } ); break;
				default: break;
				}
			}
			else
			{
				switch ( x )
				{
				case  100: pExeEffect->SetVel ( VEC2{ -6.0, -10.5 } ); break;
				case   80: pExeEffect->SetVel ( VEC2{ -7.0, -10.5 } ); break;
				case   60: pExeEffect->SetVel ( VEC2{ -8.0, -10.5 } ); break;
				case -140: pExeEffect->SetVel ( VEC2{  8.0, -10.5 } ); break;
				case -150: pExeEffect->SetVel ( VEC2{  7.0, -10.5 } ); break;
				case -160: pExeEffect->SetVel ( VEC2{  6.0, -10.5 } ); break;
				default: break;
				}
			}


			//pExeEffect->SetImmortal ( T );
			pExeEffect->SetOutDisplay ( T );
			pExeEffect->GetpEfGnrt()->Loop.Set ( 0 );
			pExeEffect->SetCalcOff ( T );
			pExeEffect->SetShader ( F );

		}
	}


}	//namespace GAME

