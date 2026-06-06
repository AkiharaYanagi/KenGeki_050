//=================================================================================================
//
//	判定
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Decision.h"
#include "00_Core/SeConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Decision::Decision ()
	{
		//ヒットストップタイマー
		m_tmrOffset_Hitstop = std::make_shared < Timer > ();
		m_tmrOffset_Hitstop->SetTargetTime ( HITSTOP_TIME );
		AddpTask ( m_tmrOffset_Hitstop );

		//相殺エフェクト
		m_efClang = std::make_shared < EfClang > ();
		AddpTask ( m_efClang );


		//ヒットエフェクト
		m_efHit = std::make_shared < GrpEf > ();
		m_efHit->AddTexture_FromArchive ( U"Ef_Hit\\00.png" );
		m_efHit->AddTexture_FromArchive ( U"Ef_Hit\\01.png" );
		m_efHit->AddTexture_FromArchive ( U"Ef_Hit\\02.png" );
		m_efHit->AddTexture_FromArchive ( U"Ef_Hit\\03.png" );
		m_efHit->AddTexture_FromArchive ( U"Ef_Hit\\04.png" );
		m_efHit->AddTexture_FromArchive ( U"Ef_Hit\\05.png" );
		m_efHit->AddTexture_FromArchive ( U"Ef_Hit\\06.png" );
		m_efHit->AddTexture_FromArchive ( U"Ef_Hit\\07.png" );
		m_efHit->AddTexture_FromArchive ( U"Ef_Hit\\08.png" );
		m_efHit->AddTexture_FromArchive ( U"Ef_Hit\\09.png" );
		m_efHit->AddTexture_FromArchive ( U"Ef_Hit\\10.png" );
		m_efHit->SetBase ( VEC2 ( 0, 0 ) );
		m_efHit->SetRevised ( VEC2 ( -250, -250 ) );
		m_efHit->SetColor ( _CLR ( 0xffffffff ) );
		m_efHit->SetZ ( Z_EFF );
		m_efHit->SetShader ( F );
		AddpTask ( m_efHit );
		GRPLST_INSERT ( m_efHit );

		//ヒットエフェクト 集中線
		m_efHit_line0 = std::make_shared < GrpEf > ();
		m_efHit_line0->AddTexture_FromArchive ( U"Ef_Hit_Line0\\00.png" );
		m_efHit_line0->AddTexture_FromArchive ( U"Ef_Hit_Line0\\01.png" );
		m_efHit_line0->AddTexture_FromArchive ( U"Ef_Hit_Line0\\02.png" );
		m_efHit_line0->AddTexture_FromArchive ( U"Ef_Hit_Line0\\03.png" );
		m_efHit_line0->AddTexture_FromArchive ( U"Ef_Hit_Line0\\04.png" );
		m_efHit_line0->AddTexture_FromArchive ( U"Ef_Hit_Line0\\05.png" );
		m_efHit_line0->AddTexture_FromArchive ( U"Ef_Hit_Line0\\06.png" );
		m_efHit_line0->AddTexture_FromArchive ( U"Ef_Hit_Line0\\07.png" );
		m_efHit_line0->AddTexture_FromArchive ( U"Ef_Hit_Line0\\08.png" );
		m_efHit_line0->SetBase ( VEC2 ( 0, 0 ) );
		m_efHit_line0->SetRevised ( VEC2 ( -750, -500 ) );
		m_efHit_line0->SetColor ( _CLR ( 0xffffffff ) );
		m_efHit_line0->SetZ ( Z_EFF );
		m_efHit_line0->SetShader ( T );
		AddpTask ( m_efHit_line0 );
		GRPLST_INSERT ( m_efHit_line0 );

		//ヒットエフェクト 集中線
		m_efHit_line1 = std::make_shared < GrpEf > ();
		m_efHit_line1->AddTexture_FromArchive ( U"Ef_Hit_Line1\\00.png" );
		m_efHit_line1->AddTexture_FromArchive ( U"Ef_Hit_Line1\\01.png" );
		m_efHit_line1->AddTexture_FromArchive ( U"Ef_Hit_Line1\\02.png" );
		m_efHit_line1->AddTexture_FromArchive ( U"Ef_Hit_Line1\\03.png" );
		m_efHit_line1->AddTexture_FromArchive ( U"Ef_Hit_Line1\\04.png" );
		m_efHit_line1->AddTexture_FromArchive ( U"Ef_Hit_Line1\\05.png" );
		m_efHit_line1->AddTexture_FromArchive ( U"Ef_Hit_Line1\\06.png" );
		m_efHit_line1->AddTexture_FromArchive ( U"Ef_Hit_Line1\\07.png" );
		m_efHit_line1->AddTexture_FromArchive ( U"Ef_Hit_Line1\\08.png" );
		m_efHit_line1->AddTexture_FromArchive ( U"Ef_Hit_Line1\\09.png" );
		m_efHit_line1->AddTexture_FromArchive ( U"Ef_Hit_Line1\\10.png" );
		m_efHit_line1->SetBase ( VEC2 ( 0, 0 ) );
		m_efHit_line1->SetRevised ( VEC2 ( -750, -500 ) );
		m_efHit_line1->SetColor ( _CLR ( 0xffffffff ) );
		m_efHit_line1->SetZ ( Z_EFF );
		m_efHit_line1->SetShader ( T );
		AddpTask ( m_efHit_line1 );
		GRPLST_INSERT ( m_efHit_line1 );

		//ヒットエフェクト 煙
		m_efHit_smoke = std::make_shared < GrpEf > ();
		m_efHit_smoke->AddTexture_FromArchive ( U"Ef_Hit_Smoke\\00.png" );
		m_efHit_smoke->AddTexture_FromArchive ( U"Ef_Hit_Smoke\\01.png" );
		m_efHit_smoke->AddTexture_FromArchive ( U"Ef_Hit_Smoke\\02.png" );
		m_efHit_smoke->SetBase ( VEC2 ( 0, 0 ) );
		m_efHit_smoke->SetRevised ( VEC2 ( -750, -500 ) );
		m_efHit_smoke->SetColor ( _CLR ( 0xffffffff ) );
		m_efHit_smoke->SetZ ( Z_EFF );
		m_efHit_smoke->SetShader ( F );
		AddpTask ( m_efHit_smoke );
		GRPLST_INSERT ( m_efHit_smoke );


//		m_efHitLine = std::make_shared < EfHitLine > ();
//		AddpTask ( m_efHitLine );
//		GRPLST_INSERT ( m_efHitLine );
	}

	Decision::~Decision ()
	{
	}


	void Decision::SetpChara (P_ExeChara pExeChara1p, P_ExeChara pExeChara2p)
	{
		m_pExeChara1p = pExeChara1p;
		m_pExeChara2p = pExeChara2p;
#if 0
		m_exeChara1->SetpParticle ( m_decision->GetpEfPart () );
		m_exeChara2->SetpParticle ( m_decision->GetpEfPart () );
#endif // 0
	}

	void Decision::Init ()
	{
		TASK_VEC::Init ();
	}

	void Decision::Load ()
	{
		TASK_VEC::Load ();
	}


	//相互判定
	void Decision::Do ()
	{
		//------------------------------------------------------
		//ExeCharaステートにより、演出時は何もしない
		bool skip1p = m_pExeChara1p->SkipDecision ();
		bool skip2p = m_pExeChara2p->SkipDecision ();
		if ( skip1p || skip2p ) { return; }

		//------------------------------------------------------
		//相殺ヒットストップ時は何もしない
		if ( m_tmrOffset_Hitstop->IsActive () ) { return; }

		//------------------------------------------------------
		//粒子エフェクト取得
//		Decision_EfPart ();

		//------------------------------------------------------
		//枠の取得

		//枠管理の取得
		P_CharaRect pCharaRect1p = m_pExeChara1p->GetpCharaRect ();
		P_CharaRect pCharaRect2p = m_pExeChara2p->GetpCharaRect ();

		//攻撃枠を取得
		PV_RECT pvARect1 = pCharaRect1p->GetpvARect ();
		PV_RECT pvARect2 = pCharaRect2p->GetpvARect ();

		//相殺枠を取得
		PV_RECT pvORect1 = pCharaRect1p->GetpvORect ();
		PV_RECT pvORect2 = pCharaRect2p->GetpvORect ();

		//当り枠を取得
		PV_RECT pvHRect1 = pCharaRect1p->GetpvHRect ();
		PV_RECT pvHRect2 = pCharaRect2p->GetpvHRect ();

		//エフェクトリストの取得
		PLP_ExEf plpExEf1 = m_pExeChara1p->GetplpExEf ();
		PLP_ExEf plpExEf2 = m_pExeChara2p->GetplpExEf ();

		//重なり中心位置
		VEC2 center = VEC2 (0, 0);


#if 0
		//------------------------------------------------------
		//ダッシュぶつかり判定
		//[D]:ダッシュにおける攻撃判定[A]
		// >> 変更 [D]:ダッシュにおける相殺判定[O]


		//[D]-><-[D] : 特殊相殺
		if (DcsAtoA (pCharaRect1p, pCharaRect2p, center))
		{
			m_pExeChara1p->OnDashOffset ();
			m_pExeChara2p->OnDashOffset ();
		}

		//[D]->[A],[D]->[O] : 通常相殺
		//[D]->[H] : 通常ヒットから互いにスクリプトでアクション移行

#endif // 0


		//------------------------------------------------------
		//打合：攻撃判定と攻撃判定、または攻撃判定と相殺判定 (相殺と相殺は何もしない)

		//ヒットより相殺を優先

		//------------------------------------------------------
		//エフェクト

#if 0
		//エフェクトの相殺チェック
		bool efOffset1p = F;
		bool efOffset2p = F;
		bool bOffset = F;
		
		//エフェクトのヒットチェック
		bool efHit1p = F;
		bool efHit2p = F;
#endif // 0


		//エフェクトリストの相殺チェック
		//相殺時には各エフェクトに相殺状態をセット(反映はExeEffectがまとめて後に行う)
		DcsOffsetEf (plpExEf1, plpExEf2, pCharaRect2p);		//p1からp2へのチェック
		DcsOffsetEf (plpExEf2, plpExEf1, pCharaRect1p);		//p2からp1へのチェック


		bool offset_Dash1pEf2p = F;
		bool offset_Dash2pEf1p = F;
#define DASH_EF_OFFSET_CHECK 1
#if DASH_EF_OFFSET_CHECK

		//ダッシュとEfの相殺チェック
		bool dash1p = m_pExeChara1p->IsDash ();
		if ( dash1p )
		{
			offset_Dash1pEf2p = DcsOffsetDashEf ( plpExEf2, pCharaRect1p );	//p2からp1へのチェック
		}
		bool dash2p = m_pExeChara2p->IsDash ();
		if ( dash2p )
		{
			offset_Dash2pEf1p = DcsOffsetDashEf ( plpExEf1, pCharaRect2p );	//p1からp2へのチェック
		}

#endif // DASH_EF_OFFSET_CHECK


		//------------------------------------------------------
		//エフェクトのヒットチェック
		bool efHit1p = false;
		bool efHit2p = false;

		//p1からp2へのチェック
		if ( ! offset_Dash2pEf1p )
		{
			int powerEf1p = 0;
			efHit2p = DcsHitEf ( plpExEf1, pvHRect2, m_pExeChara2p, powerEf1p );
		}
		
		//p2からp1へのチェック	
		if ( ! offset_Dash1pEf2p )
		{
			int powerEf2p = 0;
			efHit1p = DcsHitEf ( plpExEf2, pvHRect1, m_pExeChara1p, powerEf2p );
		}


		//------------------------------------------------------
		//メインキャラ同士の本体相殺チェック
		bool NotOffset1p = m_pExeChara1p->IsNotOffset ();
		bool NotOffset2p = m_pExeChara2p->IsNotOffset ();

		bool offset_aa = F;		//攻撃・攻撃
		bool offset_ao = F;		//攻撃・相殺判定
		bool offset_oa = F;		//相殺・攻撃判定

		//どちらも相殺無効でないとき
		if ( (! NotOffset1p) && (! NotOffset2p ) )
		{
			offset_aa = OverlapAryRect_Center (pvARect1, pvARect2, center);
			offset_ao = OverlapAryRect_Center (pvARect1, pvORect2, center);
			offset_oa = OverlapAryRect_Center (pvORect1, pvARect2, center);
		}

#if 0
		//攻撃・攻撃
		bool offset_aa = OverlapAryRect_Center (pvARect1, pvARect2, center);

		//攻撃・相殺判定
		bool offset_ao = F;
		bool offset_oa = F;
		
		if ( ! m_pExeChara1p->IsNotOffset () )
		{
			offset_ao = OverlapAryRect_Center (pvARect1, pvORect2, center);
		}
		
		if ( ! m_pExeChara2p->IsNotOffset () )
		{
			offset_oa = OverlapAryRect_Center (pvORect1, pvARect2, center);
		}

#endif // 0

		bool bOffset = offset_aa || offset_ao || offset_oa;


		//------------------------------------------------------
		//メインキャラのヒットチェック
		
		bool hit1P = false;
		bool hit2P = false;
		VEC2 hit_center_1p = { 0, 0 };
		VEC2 hit_center_2p = { 0, 0 };

		//両者の判定を行ってから反映する(片方ずつ反映するとヒット状態を参照してしまうため)
		if ( ! bOffset )	//相殺していないときのみ
		{
			//「投げ」と「投げられ」
			bool b_throw1 = m_pExeChara1p->IsThrowAction ();
			bool b_thrown2 = m_pExeChara2p->CanBeThrown ();
			bool no_check_1 = b_throw1 && ( ! b_thrown2 );

			if ( ! no_check_1 )
			{
				//ヒット判定と攻撃判定(1P->2P)
				hit2P = OverlapAryRect_Center ( pvARect1, pvHRect2, hit_center_2p );
			}

			//-------------------------------------------------
			bool b_throw2 = m_pExeChara2p->IsThrowAction ();
			bool b_thrown1 = m_pExeChara1p->CanBeThrown ();
			bool no_check_2 = b_throw2 && ( ! b_thrown1 );

			if ( ! no_check_2 )
			{
				//ヒット判定と攻撃判定(2P->1P)
				hit1P = OverlapAryRect_Center ( pvARect2, pvHRect1, hit_center_1p );
			}
		}


		//------------------------------------------------------
		//反映

		//相殺処理
		if ( bOffset )
		{
			//打合時のエフェクト発生
			m_efClang->On ( center );

			//SE
			AUD_PLAY_ONESHOT_SE ( SE_Btl_Clang );

			//記録
			m_pParam->GetPrmResult().AddOffset ( 1 );

#if 0
			m_efSpark->On ( center );
//			m_efParticle->On ( center );
			m_efPart->On ( center );
#endif // 0

			//ヒットストップ開始
			m_tmrOffset_Hitstop->Start ();

			if ( offset_ao )
			{
				m_pExeChara1p->OnOffset_AO ();
				m_pExeChara2p->OnOffset_OA ();
			}
			else if ( offset_oa )
			{
				m_pExeChara1p->OnOffset_OA ();
				m_pExeChara2p->OnOffset_AO ();
			}
			else
			{
				m_pExeChara1p->OnOffset_AA ();
				m_pExeChara2p->OnOffset_AA ();
			}
		}


		//------------------------------------------------------
		//Efヒット処理
		if ( efHit2p )
		{
			//SE
			//SOUND->Play_SE ( SE_Btl_Hit );

			m_pExeChara1p->OnEfHit ();		//ヒット状態
			m_pExeChara2p->OnEfDamaged ();		//くらい状態・ダメージ処理
		}

		if ( efHit1p )
		{
			//SE
			//SOUND->Play_SE ( SE_Btl_Hit );

			m_pExeChara2p->OnEfHit ();		//ヒット状態
			m_pExeChara1p->OnEfDamaged ();		//くらい状態・ダメージ処理
		}



		//================================================================
		//メインヒット処理
		if ( hit2P )
		{
			m_pExeChara1p->OnHit ();			//ヒット状態
			m_pExeChara2p->OnDamaged ();		//くらい状態・ダメージ処理
			m_pExeChara1p->OnDamaged_After ();	//相手ダメージ後

			m_efHit->On ();		//ヒットエフェクト
			m_efHit->Start_Rnd ( hit_center_2p, 16, 50 );		//ヒットエフェクト
		}

		if ( hit1P )
		{
			m_pExeChara2p->OnHit ();			//ヒット状態
			m_pExeChara1p->OnDamaged ();		//くらい状態・ダメージ処理
			m_pExeChara2p->OnDamaged_After ();	//相手ダメージ後

			m_efHit->On ();		//ヒットエフェクト
			m_efHit->Start_Rnd ( hit_center_1p, 16, 50 );		//ヒットエフェクト
		}
		DBGOUT_WND_F ( DBGOUT_8, U"center({},{})"_fmt( hit_center_2p.x, hit_center_2p.y ) );



		m_efHit->SetDispBase ( G_BASE_POS() );

		//相手の変更を一時取得し、自分の処理が終了したあとに互いに上書きする
		if ( hit2P || efHit2p )
		{
			m_pExeChara1p->ChangeOhter ();
			m_pExeChara1p->ChangeMine ();
		}
		if ( hit1P || efHit1p )
		{
			m_pExeChara2p->ChangeMine ();
			m_pExeChara2p->ChangeOhter ();
		}

		//================================================================
		//強制変更
		s3d::String nameActionCRC_1p = m_pExeChara1p->Check_TransitAction_Condition_str ( BRC_COERACION );
		bool cpc_1p = nameActionCRC_1p != U"";
		s3d::String nameActionCRC_2p = m_pExeChara2p->Check_TransitAction_Condition_str ( BRC_COERACION );
		bool cpc_2p = nameActionCRC_2p != U"";

		//互いにチェックして反映
		if ( cpc_1p )
		{
			m_pExeChara2p->SetAction ( nameActionCRC_1p );
		}
		if ( cpc_2p )
		{
			m_pExeChara1p->SetAction ( nameActionCRC_2p );
		}


		//================================================================
		// 
		//ヒットエフェクト
		if ( m_efHit->GetValid () ) { m_efHit->Advance (); }
#if 0
		if ( m_efHit_line0->GetValid () ) { m_efHit_line0->Advance (); }
		if ( m_efHit_line1->GetValid () ) { m_efHit_line1->Advance (); }
		if ( m_efHit_smoke->GetValid () ) { m_efHit_smoke->Advance (); }

#endif // 0

	}



	//------------------------------------------------------
	//	内部関数
	//------------------------------------------------------
	//枠チェック
	bool Decision::RectCheck_Offset ()
	{
		//------------------------------------------------------
		//枠の取得

		//枠管理の取得
		P_CharaRect pCharaRect1p = m_pExeChara1p->GetpCharaRect ();
		P_CharaRect pCharaRect2p = m_pExeChara2p->GetpCharaRect ();

		//攻撃枠を取得
		PV_RECT pvARect1 = pCharaRect1p->GetpvARect ();
		PV_RECT pvARect2 = pCharaRect2p->GetpvARect ();

		//相殺枠を取得
		PV_RECT pvORect1 = pCharaRect1p->GetpvORect ();
		PV_RECT pvORect2 = pCharaRect2p->GetpvORect ();

		//当り枠を取得
		PV_RECT pvHRect1 = pCharaRect1p->GetpvHRect ();
		PV_RECT pvHRect2 = pCharaRect2p->GetpvHRect ();

		//エフェクトリストの取得
		PLP_ExEf plpExEf1 = m_pExeChara1p->GetplpExEf ();
		PLP_ExEf plpExEf2 = m_pExeChara2p->GetplpExEf ();

		//重なり中心位置
		VEC2 center = VEC2 (0, 0);

		//------------------------------------------------------
		//エフェクト

		//エフェクトリストの相殺チェック
		//相殺時には各エフェクトに相殺状態をセット(反映はExeEffectがまとめて後に行う)
		DcsOffsetEf (plpExEf1, plpExEf2, pCharaRect2p);		//p1からp2へのチェック
		DcsOffsetEf (plpExEf2, plpExEf1, pCharaRect1p);		//p2からp1へのチェック


		//ダッシュとEfの相殺チェック
		bool dash1p = m_pExeChara1p->IsDash ();
		bool offst_DashEf1p = F;
		if ( dash1p )
		{
			offst_DashEf1p = DcsOffsetDashEf ( plpExEf2, pCharaRect1p );	//p2からp1へのチェック
		}
		bool dash2p = m_pExeChara2p->IsDash ();
		bool offst_DashEf2p = F;
		if ( dash2p )
		{
			offst_DashEf2p = DcsOffsetDashEf ( plpExEf1, pCharaRect2p );	//p1からp2へのチェック
		}


		//------------------------------------------------------
		//エフェクトのヒットチェック
		bool efHit1p = false;
		bool efHit2p = false;

		//p1からp2へのチェック
		int powerEf1p = 0;
		efHit2p = DcsHitEf ( plpExEf1, pvHRect2, m_pExeChara2p, powerEf1p );
		
		//p2からp1へのチェック	
		int powerEf2p = 0;
		efHit1p = DcsHitEf ( plpExEf2, pvHRect1, m_pExeChara1p, powerEf2p );


		return F;
	}


	bool Decision::RectCheck_Hit ()
	{
#if 0

		//------------------------------------------------------
		//メインキャラ同士の本体相殺チェック

		//攻撃・攻撃
		bool offset_aa = OverlapAryRect_Center (pvARect1, pvARect2, center);

		//攻撃・相殺判定
		bool offset_ao = F;
		bool offset_oa = F;
		
		if ( ! m_pExeChara1p->IsNotOffset () )
		{
			offset_ao = OverlapAryRect_Center (pvARect1, pvORect2, center);
		}
		
		if ( ! m_pExeChara2p->IsNotOffset () )
		{
			offset_oa = OverlapAryRect_Center (pvORect1, pvARect2, center);
		}


//		m_bOffsetChara = DcsOffset ( pCharaRect1p, pCharaRect2p, center );
//		m_bOffsetChara = offset_aa || offset_ao || offset_oa;
		bool bOffset = offset_aa || offset_ao || offset_oa;

#endif // 0

		return F;
	}


	//反映・適用
	void Decision::Apply_Offset ()
	{

	}


	//相殺枠判定(中心付)
	bool Decision::Overlap_Offset (P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center)
	{
		//攻撃枠を取得
		PV_RECT pvARect1 = pcr1->GetpvARect ();
		PV_RECT pvARect2 = pcr2->GetpvARect ();

		//相殺枠を取得
		PV_RECT pvORect1 = pcr1->GetpvORect ();
		PV_RECT pvORect2 = pcr2->GetpvORect ();

		//------------------------------------------------------
		//打合：攻撃判定と攻撃判定、または攻撃判定と相殺判定 (相殺と相殺は何もしない)
		if (OverlapAryRect_Center (pvARect1, pvARect2, center)
			|| OverlapAryRect_Center (pvORect1, pvARect2, center)
			|| OverlapAryRect_Center (pvARect1, pvORect2, center))
		{
			return true;
		}

		return false;
	}

	//特殊　ダッシュとEF　相殺枠判定(中心付)
	bool Decision::Overlap_OffsetDashEf (P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center)
	{
		//pcr1 = エフェクト, pcr2 = ダッシュのやられ枠

		//枠を取得
		PV_RECT pvARect1 = pcr1->GetpvARect ();
		PV_RECT pvHRect2 = pcr2->GetpvHRect ();

		//------------------------------------------------------
		//打合：Ef攻撃判定とダッシュやられ判定
		if ( OverlapAryRect_Center (pvARect1, pvHRect2, center) )
		{
			return true;
		}

		return false;
	}

	//エフェクトの相殺枠判定
	void Decision::DcsOffsetEf ( PLP_ExEf plpExEf1, PLP_ExEf plpExEf2, P_CharaRect pCharaRect )
	{
		VEC2 centeref = VEC2 (0, 0);

		//エフェクトリストの相殺チェック
		for (P_ExEf pexef1 : (*plpExEf1))
		{
			P_CharaRect pcref1 = pexef1->GetpCharaRect ();

			//相手Chara
			if (Overlap_Offset (pcref1, pCharaRect, centeref))
			{
				//打合時のエフェクト発生
				m_efClang->On ( centeref );

				//Efに相殺状態を設定
				pexef1->SetOffset (true);
			}

			//相手のEf
			for (P_ExEf pexef2 : (*plpExEf2))
			{
				P_CharaRect pcref2 = pexef2->GetpCharaRect ();

				if (Overlap_Offset (pcref1, pcref2, centeref))
				{
					//打合時のエフェクト発生
					m_efClang->On ( centeref );

					//相殺時 各Efに記録
					pexef1->SetOffset (true);
				}
			}
		}

	}

	//ダッシュとエフェクトの相殺枠判定
	bool Decision::DcsOffsetDashEf ( PLP_ExEf plpExEf1, P_CharaRect pCharaRect )
	{
		VEC2 centeref = VEC2 (0, 0);

		//エフェクトリストの相殺チェック
		for (P_ExEf pexef1 : (*plpExEf1))
		{
			P_CharaRect pcref1 = pexef1->GetpCharaRect ();

			//相手Chara特殊（ダッシュ相殺）
			if (Overlap_OffsetDashEf (pcref1, pCharaRect, centeref))
			{
				//打合時のエフェクト発生(centerはここで取るのでOn())
				m_efClang->On ( centeref );

				//SE
				AUD_PLAY_ONESHOT_SE ( SE_Btl_Clang );

				//Efに相殺状態を設定
				//pexef1->SetOffset (true);
				return T;
			}
		}

		return F;
	}



	//エフェクトのヒット枠判定
	bool Decision::DcsHitEf (PLP_ExEf plpExEf1, PV_RECT pvHRect2, P_ExeChara pHitChara, int & refPower)
	{
		(void)pHitChara;

		bool ret = false;
		VEC2 centeref = VEC2 (0, 0);

		//エフェクトリストのヒットチェック
		for (P_ExEf pexef1 : (*plpExEf1))
		{
			P_CharaRect pcref1 = pexef1->GetpCharaRect ();

			//Efが相殺時は飛ばす
			if (pexef1->GetOffset ()) { continue; }

			//枠管理の取得
			P_CharaRect pcr1pEf = pexef1->GetpCharaRect ();

			//攻撃枠を取得
			PV_RECT pvARect1 = pcr1pEf->GetpvARect ();

			//キャラの枠と判定する
			if (OverlapAryRect_Center (pvARect1, pvHRect2, centeref))
			{
				//ヒット時
				m_efHit->On ();		//ヒットエフェクト
				m_efHit->Start_Rnd ( centeref, 16, 50 );		//ヒットエフェクト
				//SE
				AUD_PLAY_ONESHOT_SE ( SE_Btl_Hit_L );


				//攻撃値を設定
				refPower = pexef1->GetpScript()->Get_FP_B().Power.Get();

				//Efにヒット状態を設定
				pexef1->SetHit (true);

				//Charaにヒット状態を設定
				ret = true;
			}
		}

		return ret;
	}


#if 0
	bool Decision::DashDecision ( P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center )
	{
		tstring name = _T ( "FrontDash" );
		bool p1_dash = m_pExeChara1p->IsNameAction ( name );
		bool p2_dash = m_pExeChara1p->IsNameAction ( name );
		bool b = OverlapAryRect_Center ( pcr1->GetpvORect (), pcr2->GetpvORect (), center );
		return p1_dash & p2_dash & b;
	}

	//攻撃枠 同士判定　(中心付)
	bool Decision::DcsAtoA (P_CharaRect pcr1, P_CharaRect pcr2, VEC2 & center)
	{
		//攻撃枠を取得
		PV_RECT pvARect1 = pcr1->GetpvARect ();
		PV_RECT pvARect2 = pcr2->GetpvARect ();

		//------------------------------------------------------
		//攻撃判定と攻撃判定が重なっていたらtrue
		if (OverlapAryRect_Center (pvARect1, pvARect2, center))
		{
			return true;
		}

		return false;
	}

	//判定後にキャラに反映する
	void Decision::Propagate ()
	{
	}


	//粒子エフェクト
	void Decision::Decision_EfPart ()
	{
		//両者の接触枠を取得
		PV_RECT pvRect1p = m_pExeChara1p->GetpCharaRect ()->GetpvCRect ();
		PV_RECT pvRect2p = m_pExeChara2p->GetpCharaRect ()->GetpvCRect ();

		UINT n1 = m_efPart->Collision ( pvRect1p );
		UINT n2 = m_efPart->Collision ( pvRect2p );

//		m_pExeChara1p->UpMana ( n1 );
//		m_pExeChara2p->UpMana ( n2 );
	}

#endif // 0

}	//namespace GAME

