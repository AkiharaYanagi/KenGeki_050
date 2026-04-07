//=================================================================================================
//
//	CharaSele_Face
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Face.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_Face::CharaSele_Face ()
	{
		//テクスチャ読込
		m_grp = std::make_shared < GameGraphic > ();
		m_grp->AddTexture_FromArchive ( U"CharaSele\\Face\\Chara_Face_Ouka.png");
		m_grp->AddTexture_FromArchive ( U"CharaSele\\Face\\Chara_Face_Sae.png");
		m_grp->AddTexture_FromArchive ( U"CharaSele\\Face\\Chara_Face_Retsu.png");
		m_grp->AddTexture_FromArchive ( U"CharaSele\\Face\\Chara_Face_Gaba.png");
		m_grp->AddTexture_FromArchive ( U"CharaSele\\Face\\Chara_Face_Feraria.png");
		m_grp->AddTexture_FromArchive ( U"CharaSele\\Face\\Chara_Face_Tsuki.png");
		m_grp->AddTexture_FromArchive ( U"CharaSele\\Face\\Chara_Face_Reina.png");
		m_grp->AddTexture_FromArchive ( U"CharaSele\\Face\\Chara_Face_Hero.png");
		m_grp->AddTexture_FromArchive ( U"CharaSele\\Face\\Chara_Face_Dox.png");
		m_grp->AddTexture_FromArchive ( U"CharaSele\\Face\\Chara_Face_Enemy0.png");


		//オブジェクト個数
		m_grp->ClearObject ();	//クリア
		for ( int i = 0; i < CHARA_NUM; ++ i )
		{
			//追加
			m_grp->AddObject ();
			P_Ob pob = m_grp->GetpObject ( i );

			//初期テクスチャ
			pob->SetIndexTexture ( i );
		}

		AddpTask ( m_grp );
		GRPLST_INSERT ( m_grp );
	}

	CharaSele_Face::~CharaSele_Face ()
	{
	}

	void CharaSele_Face::SetPlayerID ( PLAYER_ID id )
	{
		m_id = id;

		//@info 定数計算かつLoad()前

		//初期化と共通項
		m_aryPos.clear ();
		const float radius = 204;

		//固定配置を計算
		if ( PLAYER_ID_1 == m_id )
		{
			for ( int i = 0; i < CHARA_NUM; ++ i )
			{
				const float start = - D3DX_PI / 4;		//開始角度
				const float angle = - i * D3DX_PI_TWICE / CHARA_NUM;	//個数分の角度
				const float x = 0 + radius * cosf ( start + angle );
				const float y = 960 - 36  + radius * sinf ( start + angle );

				//大きさと位置(先頭のみ大)
				//位置の保存
				if ( i == 0 )
				{
					VEC2 rev_L { ( - 124 / 2 ), ( - 124 / 2 ) };
					m_aryPos.push_back ( rev_L + VEC2 { x, y } );
				}
				else
				{
					VEC2 rev_S { ( - 82 / 2 ), ( - 82 / 2 ) };
					m_aryPos.push_back ( rev_S + VEC2 { x, y } );
				}
			}

		}
		else if ( PLAYER_ID_2 == m_id )
		{
			for ( int i = 0; i < CHARA_NUM; ++ i )
			{
				const float start = - 3 * D3DX_PI / 4;		//開始角度
				const float angle = i * D3DX_PI_TWICE / CHARA_NUM;	//個数分の角度
				const float x = 1280 + radius * cosf ( start + angle );
				const float y = 960 - 36  + radius * sinf ( start + angle );

				//大きさと位置(先頭のみ大)
				//位置の保存
				if ( i == 0 )
				{
					VEC2 rev_L { ( 124 / 2), (- 124 / 2) };
					m_aryPos.push_back ( rev_L + VEC2 { x, y } );
				}
				else
				{
					VEC2 rev_S { ( 82 / 2), (- 82 / 2) };
					m_aryPos.push_back ( rev_S + VEC2 { x, y } );
				}
			}
		}

		//各オブジェクトの位置を設定
		float dir = (PLAYER_ID_1 == m_id) ? 1.f: -1.f;	//向き
		for ( int i = 0; i < CHARA_NUM; ++ i )
		{
			P_Ob pob = m_grp->GetpObject ( i );

			//大きさと位置(先頭のみ大)
			if ( i == 0 )
			{
				pob->SetScaling ( dir, 1.f );
			}
			else
			{
				pob->SetScaling ( dir * 0.66f, 0.66f );
			}
			pob->SetPos ( m_aryPos [ i ] );
		}

	}

	void CharaSele_Face::Load ()
	{
		TASK_VEC::Load ();
	}

	void CharaSele_Face::Init ()
	{
		TASK_VEC::Init ();
	}


	void CharaSele_Face::Move ()
	{
		if ( m_turn )
		{
			SetPos ( m_pos_turn );
		}

		TASK_VEC::Move ();
	}

	void CharaSele_Face::Next ()
	{
		m_turn = T;
//		int CHARA_NUM = N;
//		int CHARA_NUM = 6;
		int CHARA_NUM = 5;

		if ( CHARA_NUM <= m_pos_turn + 1 )
		{
			m_pos_turn = 0;
		}
		else
		{
			++ m_pos_turn;
		}


		if ( PLAYER_ID_1 == m_id )
		{
			DBGOUT_WND_F ( DBGOUT_4, U"m_pos_turn = {}"_fmt( m_pos_turn ) );
		}
	}

	void CharaSele_Face::Prev ()
	{
		m_turn = T;
//		int CHARA_NUM = N;
//		int CHARA_NUM = 6;
		int CHARA_NUM = 5;

		if ( m_pos_turn - 1 < 0 )
		{
			m_pos_turn = CHARA_NUM - 1;
		}
		else
		{
			-- m_pos_turn;
		}

		if ( PLAYER_ID_1 == m_id )
		{
			DBGOUT_WND_F ( DBGOUT_4, U"m_pos_turn = {}"_fmt( m_pos_turn ) );
		}
	}

	void CharaSele_Face::SetPos ( int pos_turn )
	{
		m_pos_turn = pos_turn;
		ResetPos ();
	}

	void CharaSele_Face::Assign ( CHARA_NAME name )
	{
		m_pos_turn = static_cast < int > ( name );
		ResetPos ();
	}

	void CharaSele_Face::ResetPos ()
	{


		//対象キャラと、前後をインデックスで指定に変更


		for ( int i = 0; i < CHARA_NUM; ++ i )
		{
			int pos = 0;

			//インデックスはi, 位置はm_pos_turn
			if ( i < m_pos_turn )	//マイナス側のみチェック
			{
				pos = CHARA_NUM + ( i - m_pos_turn );
			}
			else
			{
				pos = i - m_pos_turn;
			}

			P_Ob pob = m_grp->GetpObject ( i );
			pob->SetPos ( m_aryPos [ pos ] );

			//大きさを再設定
			float dir = (PLAYER_ID_1 == m_id) ? 1.f: -1.f;	//向き
			if ( pos == 0 )
			{
				pob->SetScaling ( dir, 1.f );
			}
			else
			{
				pob->SetScaling ( dir * 0.66f, 0.66f );
			}

		}

		m_turn = F;
	}

}	//namespace GAME

