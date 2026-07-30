//=================================================================================================
//
// DispMainImage ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispMainImage.h"
#include "03_FtgMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	DispMainImage::DispMainImage ()
	{
#if 0
		//キャラメイングラフィック
		m_mainGraphic = std::make_shared < GameGraphic > ();

		m_mainGraphic->SetZ ( Z_CH );
		AddpTask ( m_mainGraphic );
		GRPLST_INSERT ( m_mainGraphic );

#endif // 0


		//atlas
		m_grpAtlas = std::make_shared < GrpAtlas > ();
		AddpTask ( m_grpAtlas );
		GRPLST_INSERT ( m_grpAtlas );


		//影
		m_grpShadow = std::make_shared < GameGraphic > ();
		m_grpShadow->AddTexture_FromArchive ( U"shadow.png" );
		m_grpShadow->SetZ ( Z_SHADOW );
		AddpTask ( m_grpShadow );
		GRPLST_INSERT ( m_grpShadow );
	}

	DispMainImage::~DispMainImage ()
	{
	}


	void DispMainImage::SetpChara ( P_Chara pChara )
	{
#if 0
		//キャラのメインテクスチャアレイを設置
		//mpap_Tx = pChara->GetBehavior().GetpapTx ();
		PAP_Tx pap_Tx = pChara->GetBehavior().GetpapTx ();

		m_mainGraphic->ClearTexture ();
		for ( P_Tx ptx : *pap_Tx )
		{
			m_mainGraphic->AddpTexture ( ptx );
		}
#endif // 0


		//キャラのメインアトラスを設置
		m_grpAtlas->SetpAtlas ( pChara->GetBehavior ().GetpAtlas () );

	}

	//メインイメージの更新
	void DispMainImage::UpdateMainImage ( P_Frame pScript, const BtlParam & btlprm )
	{
		VEC2 ptChara = btlprm.GetPos();
		bool dirRight = btlprm.GetDirRight ();

		float fDir = dirRight ? ( 1.f ) : ( -1.f );		//向き
//		float fDir = ( 1.f );		//向き

		//位置
		VEC2 posScript = pScript->Pos.Get();
		float bx = G_BASE_POS ().x;	//基準位置
		float by = G_BASE_POS ().y;	//基準位置
		float vib = btlprm.GetVib ();	//振動量
		float x = bx + ptChara.x + fDir * posScript.x + vib;	//反転位置補正
//		float x = bx + ptChara.x + posScript.x;	//->ScalingCenterの指定により位置補正は無し
		float y = by + ptChara.y + posScript.y;
//		float y =  0 + ptChara.y + posScript.y;
		VEC2 vecImg = VEC2 ( x, y );

		//IDチェックはスクリプト作成時、ロード時に行う
		UINT index = pScript->ImageIndex.Get();
//		P_Tx pTexture = mpap_Tx->at ( index );


#if 0
		float rad = D3DX_PI * 0.01f * pScript->m_prmStaging.Rotate;		//回転
		m_mainGraphic->SetRadian ( rad * fDir );

		//スクリプトからの指定がなければテクスチャの中心
		VEC2 center { 0, 0 };
		if ( center != pScript->m_prmStaging.Rotate_center )
		{
			center = pScript->m_prmStaging.Rotate_center;
		}
		else
		{
			center = pTexture->GetCenter ();
		}

		m_mainGraphic->SetRotationCenter ( center );
#endif // 0
		

#if 0

		//表示に反映
		m_mainGraphic->SetPos ( vecImg );
//		m_mainGraphic->SetScalingCenter ( center );
		m_mainGraphic->SetScaling ( 1.f * fDir, 1.f );

//		m_mainGraphic->SetpTexture ( pTexture );
		m_mainGraphic->SetIndexTexture ( index );

#endif // 0


		//---------------------------------------------------------
		//atlas

		//VEC2 vecImgAtlas = vecImg + VEC2 ( -200, -10 );
		m_grpAtlas->In ();
		//m_grpAtlas->SetPos ( vecImgAtlas );
		m_grpAtlas->SetPos ( vecImg );
		m_grpAtlas->SetScaling ( 1.f * fDir, 1.f );
		m_grpAtlas->SetIndexTexture ( index );

#if 0
#endif // 0


		//---------------------------------------------------------
		//影
		//VEC2 vecImgShadow = VEC2 ( bx, 0 ) + ptChara + VEC2 ( -160 + fDir * 12, 0 );
		VEC2 vecImgShadow = VEC2 ( bx, by ) + ptChara + VEC2 ( -160 + fDir * 12, 0 );
		//vecImgShadow.y = -0.f + (float)PLAYER_BASE_Y;	//y方向のみ指定
		vecImgShadow.y = by + (float)PLAYER_BASE_Y;	//y方向のみ指定
		m_grpShadow->SetPos ( vecImgShadow );

	}


	//影化
	void DispMainImage::TurnShadow ( bool b )
	{
		//m_mainGraphic->SetColor ( b ? 0xff000000 : 0xffffffff );
		m_grpAtlas->SetColor ( b ? 0xff000000 : 0xffffffff );
	}

	//乗算カラー指定
	void DispMainImage::SetColor ( uint32 clr )
	{
		//m_mainGraphic->SetColor ( clr );
		m_grpAtlas->SetColor ( clr );
	}


	//メイングラフィックを同一Z値で先頭にする
	void DispMainImage::TopByZ ()
	{
		//GrpLst::Inst()->TopByZ ( m_mainGraphic );
		GrpLst::Inst()->TopByZ ( m_grpAtlas );
	}



}	//namespace GAME

