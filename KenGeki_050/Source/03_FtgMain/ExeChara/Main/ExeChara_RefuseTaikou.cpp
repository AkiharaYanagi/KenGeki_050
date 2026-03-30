//=================================================================================================
//
// 剣撃対抗不可　アクション判定　ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ExeChara.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//剣撃対抗は特定技のとき不成立
	//T:成立しない, F:成立する
	bool ExeChara::IsRefused_Taikou () const
	{
		//==========================================
		//◆ 自分・攻撃 -> 相手・くらい
		//ヒット発生(攻撃成立側)
		//==========================================
		P_ExeChara pOther =  m_pOther.lock();
	
		//==========================================
		//★★★ 剣撃対抗 (打撃時にいずれかの入力で距離離し)
		//		->タイマスタート処理はExeChara_OnDamaged.cpp
		//==========================================
		// 
		// 特定技は剣撃対抗が不成立
		// 


		//超必殺技
		if ( IsOverdrive () ) { return T; }

		//足払い
		if ( IsNameAction ( U"足払い初撃" ) ) { return T; }
		if ( IsNameAction ( U"足払い追撃" ) ) { return T; }

		//剣撃走破
		if ( IsNameAction ( U"剣撃走破_地上_発生" ) ) { return T; }
		if ( IsNameAction ( U"剣撃走破_空中_発生" ) ) { return T; }
		if ( IsNameAction ( U"剣撃走破_地上_ダッシュ" ) ) { return T; }
		if ( IsNameAction ( U"剣撃走破_空中_ダッシュ" ) ) { return T; }


		//全キャラ投げ
		if ( IsNameAction ( U"投げ発生") ) { return T; }
		if ( IsNameAction ( U"投げ成立0") ) { return T; }


		//特定キャラ
		switch ( m_name )
		{

		case CHARA_OUKA:

			//EX
			if ( IsNameAction ( U"空中昇竜発生") ) { return T; }
			if ( IsNameAction ( U"空中昇竜落下") ) { return T; }
			if ( IsNameAction ( U"空中昇竜着地") ) { return T; }

		break;

		case CHARA_SAE:

			if ( IsNameAction ( U"投げ成立1") ) { return T; }
			if ( IsNameAction ( U"投げ成立2") ) { return T; }
			if ( IsNameAction ( U"投げ成立3") ) { return T; }
			if ( IsNameAction ( U"投げ成立4") ) { return T; }
			if ( IsNameAction ( U"万雷弱派生") ) { return T; }
			if ( IsNameAction ( U"万雷弱派生_成立") ) { return T; }
			if ( IsNameAction ( U"万雷弱派生_起き上がり") ) { return T; }

		break;


		case CHARA_RETSUDOU:
			if ( IsNameAction ( U"投げ成立") ) { return T; }

		break;

		case CHARA_GYAVADARUGA:

			if ( IsNameAction ( U"大攻撃") ) { return T; }
			if ( IsNameAction ( U"大攻撃2") ) { return T; }
			if ( IsNameAction ( U"竜巻EX0") ) { return T; }
			if ( IsNameAction ( U"竜巻EX1") ) { return T; }
			if ( IsNameAction ( U"竜巻EX2") ) { return T; }
			if ( IsNameAction ( U"昇竜投げ") ) { return T; }
			if ( IsNameAction ( U"昇竜投げ成立") ) { return T; }
			if ( IsNameAction ( U"昇竜投げ落下") ) { return T; }
			if ( IsNameAction ( U"昇竜投げ着地") ) { return T; }
			if ( IsNameAction ( U"半回転投げ") ) { return T; }
			if ( IsNameAction ( U"半回転投げ成立") ) { return T; }

		break;

		case CHARA_FERARIA:

		break;

		case CHARA_TSUKIHIBOSHI:
			if ( IsNameAction ( U"竜巻") ) { return T; }
			if ( IsNameAction ( U"竜巻成立") ) { return T; }
			if ( IsNameAction ( U"竜巻2") ) { return T; }
			if ( IsNameAction ( U"空中必殺技発動") ) { return T; }
			if ( IsNameAction ( U"空中必殺技着地") ) { return T; }
			if ( IsNameAction ( U"空中必殺技成立") ) { return T; }

			if ( IsNameAction ( U"小攻撃") )
			{
				uint32 i = m_pScript->Index.Get();
				if ( 3 <= i && i <= 8 )
				{ return T; }
			}
			if ( IsNameAction ( U"中攻撃") )
			{
				uint32 i = m_pScript->Index.Get();
				if ( 3 <= i && i <= 8 )
				{ return T; }
			}
			if ( IsNameAction ( U"大攻撃") )
			{
				uint32 i = m_pScript->Index.Get();
				if ( 3 <= i && i <= 8 )
				{ return T; }
			}
		break;

		default: return F;
		}
		
		//どれにも当てはまらないとき、剣撃対抗成立
		return F;
	}



}	//namespace GAME

