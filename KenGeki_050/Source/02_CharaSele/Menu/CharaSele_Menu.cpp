//=================================================================================================
//
//	CharaSele_Menu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "CharaSele_Menu.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	CharaSele_Menu::CharaSele_Menu ()
	{
		m_part_upper_back = std::make_shared < GameGraphic > ();
		m_part_upper_back->AddTexture_FromArchive ( U"CharaSele\\upper_back.png" );
		m_part_upper_back->SetPos ( 640 - 710 / 2, -450 );
		m_part_upper_back->SetRotationCenter ( VEC2 { 710 / 2, 710 / 2 } );
		AddpTask ( m_part_upper_back );
		GRPLST_INSERT ( m_part_upper_back );

		m_part_upper = std::make_shared < GameGraphic > ();
		m_part_upper->AddTexture_FromArchive ( U"CharaSele\\upper.png" );
		AddpTask ( m_part_upper );
		GRPLST_INSERT ( m_part_upper );

#if 0
		m_part_upper_item = std::make_shared < GameGraphic > ();
		m_part_upper_item->SetPos ( 640 - 248 / 2, 150 );
		m_part_upper_item->AddTexture_FromArchive ( U"Item.png" );
		AddpTask ( m_part_upper_item );
		GRPLST_INSERT ( m_part_upper_item );
#endif // 0


		//矢印

#if 0

		m_arrow = std::make_shared < GameGraphic > ();
		m_arrow->AddTexture_FromArchive ( U"CharaSele\\Arrow.png" );
		AddpTask ( m_arrow );
		GRPLST_INSERT ( m_arrow );

		//矢印にオブジェクトを増やす
		m_arrow->AddObject ();
		m_arrow->AddObject ();
		m_arrow->AddObject ();

		for ( int i = 0; i < 4; ++ i )
		{
			m_aryPob [ i ] = m_arrow->GetpObject ( i );
		}

		float by = 175;
		m_aryBasePos.push_back (  VEC2 ( 1280 / 2 - 18 / 2 - 150, by ) );
		m_aryBasePos.push_back (  VEC2 ( 1280 / 2 - 18 / 2		 , by - 50 ));
		m_aryBasePos.push_back (  VEC2 ( 1280 / 2 - 18 / 2 + 150, by ) );
		m_aryBasePos.push_back (  VEC2 ( 1280 / 2 - 18 / 2		 , by + 50 ));

		for ( int i = 0; i < m_aryBasePos.size (); ++ i )
		{
			m_aryPob [ i ]->SetPos ( m_aryBasePos [ i ] );
			m_aryPob [ i ]->SetRotationCenter ( VEC2 ( 18 / 2, 31 * 0.5f ) );
			m_aryPob [ i ]->SetRadian ( D3DX_PI_HALF * i );	//[0] [<] が正
		}

		//[0] [<] が正
		//	  3
		//	0   2
		//	  1


		m_arrow_frq = 0.15f;
		m_arrow_w = 3.f;



#endif // 0

		//選択矢印
		m_arrow = std::make_shared < SelectArrow > ( SelectArrow::DIR::UP_DOWN, Z_MENU );
		m_arrow->SetPos ( VEC2 ( 1280 / 2 - 18 / 2, 175 ) );
		m_arrow->SetH ( 50 );
		AddpTask ( m_arrow );

		//----------------------------------------------------------
		m_Item = std::make_shared < GameGraphic > ();
		AddpTask ( m_Item );
		GRPLST_INSERT ( m_Item );
		m_Item->AddTexture_FromArchive ( U"CharaSele\\Menu\\ChSl_StageSelect.png" );
		m_Item->AddTexture_FromArchive ( U"CharaSele\\Menu\\ChSl_BGMSelect.png" );
		m_Item->AddTexture_FromArchive ( U"CharaSele\\Menu\\ChSl_Round.png" );
		m_Item->AddTexture_FromArchive ( U"CharaSele\\Menu\\ChSl_Cmd.png" );
		m_Item->AddTexture_FromArchive ( U"CharaSele\\Menu\\ChSl_Volume.png" );

		s3d::Array < VEC2 > aryPos =
		{
			{ 640		- 248 / 2, 150 },
			{ 640 - 190 - 248 / 2, 75 },
			{ 640 - 225 - 248 / 2, 10 },
			{ 640 + 190 - 248 / 2, 75 },
			{ 640 + 225 - 248 / 2, 10 },
		};


		m_Item->ClearObject ();
		uint32 index = 0;
		for ( VEC2 pos : aryPos )
		{
			m_Item->AddObject ();
			P_Ob pob = m_Item->GetpObject ( index );
			pob->SetPos ( pos );
			pob->SetIndexTexture ( index );

			pob->SetbScalingCntrOfTx ( T );
			if ( index != 0 )
			{
				pob->SetScaling ( VEC2 ( 0.6f, 0.6f ) );
				pob->SetColor ( 0xff808080 );
			}
			else
			{
				pob->SetScaling ( VEC2 ( 1.f, 1.f ) );
			}

			m_posItem.push_back ( pos );

			++ index;
		}

	}

	CharaSele_Menu::~CharaSele_Menu ()
	{
	}

	void CharaSele_Menu::Load ()
	{
		TASK_VEC::Load ();
	}

	void CharaSele_Menu::Move ()
	{
		//円盤回転
		m_angle += m_omega;
		m_part_upper_back->SetRadian ( m_angle );

#if 0


		//時間
		const float MAX_TIME = 10000.f;
		++ m_arrow_time;
		if ( m_arrow_time >= MAX_TIME ) { m_arrow_time = 0; }

		//角度と位置
		float period = D3DX_PI_TWICE / m_arrow_frq;
		float wrappedTime = fmod ( m_arrow_time, period );
		float dx = m_arrow_w * sin ( m_arrow_frq * wrappedTime );
		DBGOUT_WND_F ( DBGOUT_2, U"arrow_x = {}"_fmt( dx ) );

		VEC2 pos0;
		pos0.x = m_aryBasePos [ 0 ].x - dx;
		pos0.y = m_aryBasePos [ 0 ].y;
		m_aryPob [ 0 ]->SetPos ( pos0 );

		VEC2 pos1;
		pos1.x = m_aryBasePos [ 1 ].x;
		pos1.y = m_aryBasePos [ 1 ].y - dx;
		m_aryPob [ 1 ]->SetPos ( pos1 );

		VEC2 pos2;
		pos2.x = m_aryBasePos [ 2 ].x + dx;
		pos2.y = m_aryBasePos [ 2 ].y;
		m_aryPob [ 2 ]->SetPos ( pos2 );

		VEC2 pos3;
		pos3.x = m_aryBasePos [ 3 ].x;
		pos3.y = m_aryBasePos [ 3 ].y + dx;
		m_aryPob [ 3 ]->SetPos ( pos3 );

#endif // 0


		TASK_VEC::Move ();
	}


	void CharaSele_Menu::Next ()
	{
		PAP_Ob papOb = m_Item->Getpap_ob ();
		UINT32 size = static_cast < UINT32 > ( papOb->size () );

		//最大値のときのみ特殊処理
		if ( m_pos == size - 1 )
		{
			m_pos = 0;
		}
		else
		{
			++ m_pos;
		}

		Pos ( m_pos, size );
	}

	void CharaSele_Menu::Prev ()
	{
		PAP_Ob papOb = m_Item->Getpap_ob ();
		UINT32 size = static_cast < UINT32 > ( papOb->size () );

		//0のときのみ特殊処理
		if ( m_pos == 0 )
		{
			m_pos = size - 1;
		}
		else
		{
			-- m_pos;
		}

		//位置の再配置
		Pos ( m_pos, size );
	}

	void CharaSele_Menu::Pos ( UINT32 pos, UINT32 size )
	{
		PAP_Ob papOb = m_Item->Getpap_ob ();
		for ( UINT32 i = 0; i < size; ++ i )
		{
			//範囲でラップ (負数対応)
			//UINT32 index = size > 0 ? ( ( pos + i ) % size + size ) % size : 0; 
			UINT32 index = size > 0 ? ( pos + i ) % size : 0; 

			P_Ob pob = papOb->at(i);
			pob->SetPos ( m_posItem [ index ] );

			//先頭以外は縮小
			if ( index != 0 )
			{
				pob->SetScaling ( VEC2 ( 0.6f, 0.6f ) );
			}
			else
			{
				pob->SetScaling ( VEC2 ( 1.f, 1.f ) );
			}
		}
	}



}	//namespace GAME

