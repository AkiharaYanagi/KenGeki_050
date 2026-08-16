//=================================================================================================
//
// DispEffect ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DispEffect.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	DispEffect::DispEffect ( float z ) 
	{
#if 0

//		//メイングラフィック
//		m_grp = std::make_shared < GameGraphic > ();
		m_grp = std::make_shared < GrpEf > ();
		m_grp->SetZ ( z );	//初期位置

		//テクスチャ中心位置で表示
		m_grp->SetbCenterOfTx ( F );

		AddpTask ( m_grp );
		GRPLST_INSERT ( m_grp );

		//最初から表示
		m_grp->On ();
		m_grp->SetShader ( T );

#endif // 0

		//atlas
		m_grpAtlas = std::make_shared < GrpAtlas > ();
		m_grpAtlas->SetZ ( z );	//初期位置
		AddpTask ( m_grpAtlas );
		GRPLST_INSERT ( m_grpAtlas );
		


		//枠表示
		m_dispRect = std::make_shared < DispRect > ();
		AddpTask ( m_dispRect );
	}

	DispEffect::~DispEffect ()
	{
		//終了時にグラフィックタスクを外す
		//GRPLST_REMOVE ( m_grp );
		GRPLST_REMOVE ( m_grpAtlas );
	}

	void DispEffect::SetpChara(P_Chara pChara)
	{
#if 0
		//キャラのエフェクトテクスチャアレイを設置
		mpap_EfTx = pChara->GetGarnish().GetpapTx ();

		m_grp->ClearTexture ();
		for ( P_Tx ptx : * mpap_EfTx )
		{
			m_grp->AddpTexture ( ptx );
		}
#endif // 0

		//キャラのEFアトラスを設置
		m_grpAtlas->SetpAtlas ( pChara->GetGarnish ().GetpAtlas () );
	}


	void DispEffect::Update ( P_Frame pScript, VEC2 ptEf, bool dirRight )
	{
		//Disp：スクリプトのイメージ表示位置

		//位置 (エフェクトのゲーム位置＋スクリプトの表示位置(*向き)＋キャラによる画面補正位置)
		float fDir = dirRight ? (1.f) : (-1.f);
		VEC2 tempImgPos = pScript->Pos.Get();
		VEC2 imgPos = VEC2( fDir * tempImgPos.x, tempImgPos.y );
//		VEC2 imgPos = VEC2( tempImgPos.x, tempImgPos.y );
		VEC2 vecEfImg = ptEf + imgPos + G_BASE_POS ();

		//整数化しておく　テクスチャの描画位置は整数でないとアトラスのスキマが見える
		int fx = static_cast < int > ( vecEfImg.x );
		int fy = static_cast < int > ( vecEfImg.y );
		vecEfImg = VEC2 ( fx, fy  );

#if 0
		//回転
		float rad = D3DX_PI * 0.01f * pScript->m_prmStaging.Rotate;
		m_grp->SetRadian ( rad * fDir );

		//スクリプトからの指定がなければテクスチャの中心
		VEC2 center { 0, 0 };
		if ( center != pScript->m_prmStaging.Rotate_center )
		{
			center = pScript->m_prmStaging.Rotate_center;
		}
		else
		{
//			center = pEfTx->GetCenter ();
			s3d::TextureDesc txDesc = pEfTx->getDesc ();
			txDesc
		}

		m_grp->SetRotationCenter ( center );
		m_grp->SetScalingCenter ( center );
#endif // 0


		//テクスチャの指定
		UINT index = pScript->ImageIndex.Get();



		//---------------------------------------------------------
		//表示に反映
#if 0
		m_grp->SetScaling ( 1.f * fDir, 1.f );		//拡大(向き)
//		m_grp->SetPos ( vecEfImg );
		m_grp->SetBase ( vecEfImg );	//Grp "Ef" Shdは基本位置指定をBaseで行う
		m_grp->SetIndexTexture ( index );	//テクスチャID
#endif // 0

		//atlas
		m_grpAtlas->In ();
		m_grpAtlas->SetPos ( vecEfImg );
		m_grpAtlas->SetScaling ( 1.f * fDir, 1.f );
		m_grpAtlas->SetIndexTexture ( index );


		//-------------------------------------
		//枠
		m_dispRect->Update ();
	}


	//画面全体表示
	void DispEffect::Update_FullDisplay ( P_Frame pScript, bool dirRight )
	{
		//位置 (エフェクトのゲーム位置＋スクリプトの表示位置(*向き)＋キャラによる画面補正位置)
		float fDir = dirRight ? (1.f) : (-1.f);
		VEC2 vecEfImg = VEC2 ( 0, 0 );

#if 0

		//表示に反映
		m_grp->SetBase ( vecEfImg );	//Grp "Ef" Shdは基本位置指定をBaseで行う

		//拡大(向き)
		m_grp->SetScaling ( 1.f * fDir, 1.f );

		//テクスチャIDの指定
		UINT index = pScript->ImageIndex.Get();
		m_grp->SetIndexTexture ( index );

#endif // 0
		UINT index = pScript->ImageIndex.Get();
		//atlas
		m_grpAtlas->In ();
		m_grpAtlas->SetPos ( vecEfImg );
		m_grpAtlas->SetScaling ( 1.f * fDir, 1.f );
		m_grpAtlas->SetIndexTexture ( index );

	}

	//画面全体表示 Xのみ
	void DispEffect::Update_FullDisplay_X ( P_Frame pScript, VEC2 ptEf, bool dirRight )
	{
		//位置 (エフェクトのゲーム位置＋スクリプトの表示位置(*向き)＋キャラによる画面補正位置)
		float x = dirRight ? 0 : (1280.f);
		VEC2 vecPtBase = VEC2 ( x, ptEf.y );	//Xのみエフェクトのゲーム位置は、画面端とする

#if 0

		//表示に反映
		m_grp->SetBase ( vecPtBase );	//Grp "Ef" Shdは基本位置指定をBaseで行う

		//拡大(向き)
		float fDir = dirRight ? (1.f) : (-1.f);
		m_grp->SetScaling ( 1.f * fDir, 1.f );

		//テクスチャIDの指定
		UINT index = pScript->ImageIndex.Get();
		m_grp->SetIndexTexture ( index );

#endif // 0
		float fDir = dirRight ? (1.f) : (-1.f);
		UINT index = pScript->ImageIndex.Get();
		//atlas
		m_grpAtlas->In ();
		m_grpAtlas->SetPos ( vecPtBase );
		m_grpAtlas->SetScaling ( 1.f * fDir, 1.f );
		m_grpAtlas->SetIndexTexture ( index );

	}

	void DispEffect::SetpCharaRect ( P_CharaRect pCharaRect )
	{
		m_dispRect->SetCharaRect ( pCharaRect );
	}


}	//namespace GAME

