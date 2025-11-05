//=================================================================================================
//
// LoadCharaFunc ソースファイル
//
//=================================================================================================
#include "LoadCharaBinFunc.h"

//#include <codecvt>

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	LoadCharaBinFunc::LoadCharaBinFunc ()
	{
	}


	void LoadCharaBinFunc::LoadChara ( CUPR_BYTE buf, UINT32 & pos, Chara & ch )
	{
		LoadCharaScript ( buf, pos, ch );
		LoadCharaImage ( buf, pos, ch );
	}

	void LoadCharaBinFunc::LoadCharaScript ( CUPR_BYTE buf, UINT32 & pos, Chara & ch )
	{
//		LoadBehavior ( buf, pos, ch );	//Behavior
//		LoadGarnish ( buf, pos, ch );	//Garnish
		LoadCompend ( buf, pos, ch.GetBehavior () );	//Behavior
		LoadCompend ( buf, pos, ch.GetGarnish  () );	//Garnish

		LoadCommand ( buf, pos, ch );	//Command
		LoadBranch ( buf, pos, ch );	//Branch
		LoadRoute ( buf, pos, ch );		//Route

		LoadListName ( buf, pos, ch.GetaSE() );
		LoadListName ( buf, pos, ch.GetaVC() );
	}

	void LoadCharaBinFunc::LoadCharaImage ( CUPR_BYTE buf, UINT32 & pos, Chara & ch )
	{
		(void)buf, (void)pos, (void)ch;
#if 0
		LoadImg ( buf, pos, ch.GetpapTxMain () );
		LoadImg ( buf, pos, ch.GetpapEfTexture () );
#endif // 0
	}


	void LoadCharaBinFunc::LoadCompend ( CUPR_BYTE buf, UINT32 & pos, Compend & cmpd )
	{
		//@afford メモリコントローラ
		//先頭に 総シークエンス数, 総スクリプト数 を記述、必要時に該当分のアドレスを返す

		//シークエンス個数 と メモリの確保
		UINT32 nSqc = m_utl.LoadUInt ( buf, pos );


//		std::unique_ptr < P_Sequence [] > aryAct = std::make_unique < P_Sequence [] > ( nSqc );
		UP_AP_Sqc paSqc = std::make_unique < AP_Sqc > ( nSqc );
		for ( UINT32 i = 0; i < nSqc; ++ i ) { (*paSqc) [ i ] = std::make_shared < Sequence > (); }


		//実データ
		for ( UINT32 iSqc = 0; iSqc < nSqc; ++ iSqc )
		{
			P_Sqc pSqc = (*paSqc) [ iSqc ];

			//シークエンス
			(*paSqc) [ iSqc ]->Name.Set ( m_utl.LoadS3dString ( buf, pos ) );
			(*paSqc) [ iSqc ]->Next.Set ( (UINT32)m_utl.LoadUInt ( buf, pos ) );
			(*paSqc) [ iSqc ]->Category.Set ( (ACTION_CATEGORY)buf [ pos ++ ] );
			(*paSqc) [ iSqc ]->Posture.Set ( (ACTION_POSTURE)buf [ pos ++ ] );
			(*paSqc) [ iSqc ]->HitNum.Set ( (UINT32)buf [ pos ++ ] );
			(*paSqc) [ iSqc ]->HitPitch.Set ( (UINT32)buf [ pos ++ ] );
			(*paSqc) [ iSqc ]->Balance.Set ( m_utl.LoadInt ( buf, pos ) );
			(*paSqc) [ iSqc ]->Mana.Set ( m_utl.LoadInt ( buf, pos ) );
			(*paSqc) [ iSqc ]->Accel.Set ( m_utl.LoadInt ( buf, pos ) );

			for ( size_t i = 0; i < Sequence::VRS_SIZE; ++ i )
			{
				int value = m_utl.LoadInt ( buf, pos );
				(*paSqc) [ iSqc ]->Versatile[i].Set ( value );
			}

			//フレーム個数 と メモリの確保
			UINT32 nFrm = m_utl.LoadUInt ( buf, pos );

			UP_AP_Frame paFrm = std::make_unique < AP_Frame > ( nFrm );
			for ( UINT32 i = 0; i < nFrm; ++ i ) { (*paFrm) [ i ] = std::make_shared < Frame > (); }

			for ( UINT32 iFrm = 0; iFrm < nFrm; ++ iFrm )
			{
				(*paFrm) [ iFrm ]->Index.Set ( iFrm );
				LoadFrame ( buf, pos, *(*paFrm) [ iFrm ] );
			}

			(*paSqc) [ iSqc ]->AddaFrame ( std::move ( paFrm ) );
		}

		cmpd.SetpSqc ( std::move ( paSqc ) );

	}


#if 0
	void LoadCharaBinFunc::LoadBehavior ( CUPR_BYTE buf, UINT32 & pos, Chara & ch )
	{
		//@afford メモリコントローラ
		//先頭に 総アクション数, 総スクリプト数 を記述、必要時に該当分のアドレスを返す

		//アクション個数 と メモリの確保
		UINT32 nAct = m_utl.LoadUInt ( buf, pos );

#if 0
		unique_ptr < Action [] > pi = make_unique < Action [] > ( nAct );

		unique_ptr < P_Sequence [] > aryAct = make_unique < P_Sequence [] > ( nAct );
//		for ( UINT32 i = 0; i < nAct; ++ i ) { aryAct [ i ] = make_shared < Action > (); }

		std::shared_ptr < P_Sequence [] > aryShared { new P_Sequence [ nAct ] , default_delete < P_Sequence [] > () };
		for ( UINT32 i = 0; i < nAct; ++ i ) { aryAct [ i ] = aryShared [ i ]; }
#endif // 0
#if 0
		unique_ptr < P_Sequence [] > aryAct = make_unique < P_Sequence [] > ( nAct );
		std::shared_ptr < Action [] > aryShared = make_shared < Action [] > ( nAct );
		for ( UINT32 i = 0; i < nAct; ++ i ) { aryAct [ i ].reset ( & aryShared [ i ] ); }
#endif // 0


		std::unique_ptr < P_Sequence [] > aryAct = std::make_unique < P_Sequence [] > ( nAct );
//		std::vector < P_Sequence > aryAct ( nAct );
		for ( UINT32 i = 0; i < nAct; ++ i ) { aryAct [ i ] = std::make_shared < Action > (); }


		//実データ
		for ( UINT32 iAct = 0; iAct < nAct; ++ iAct )
		{
			P_Sequence pAct = aryAct [ iAct ];

			//アクション
			aryAct [ iAct ]->SetName ( m_utl.LoadS3dString ( buf, pos ) );
			aryAct [ iAct ]->SetNextID ( (UINT32)m_utl.LoadUInt ( buf, pos ) );
			aryAct [ iAct ]->SetCategory ( (ACTION_CATEGORY)buf [ pos ++ ] );
			aryAct [ iAct ]->SetPosture ( (ACTION_POSTURE)buf [ pos ++ ] );
			aryAct [ iAct ]->SetHitNum ( (UINT32)buf [ pos ++ ] );
			aryAct [ iAct ]->SetHitPitch ( (UINT32)buf [ pos ++ ] );
			aryAct [ iAct ]->SetBalance ( m_utl.LoadInt ( buf, pos ) );
			aryAct [ iAct ]->SetMana ( m_utl.LoadInt ( buf, pos ) );
			aryAct [ iAct ]->SetAccel ( m_utl.LoadInt ( buf, pos ) );

			for ( size_t i = 0; i < Action::VRS_SIZE; ++ i )
			{
				int value = m_utl.LoadInt ( buf, pos );
				aryAct [ iAct ]->SetVersatile ( i, value );
			}

			//スクリプト個数 と メモリの確保
			UINT32 nScp = m_utl.LoadUInt ( buf, pos );

			AUP_P_Script aryScp = std::make_unique < P_Frame [] > ( nScp );
			for ( UINT32 i = 0; i < nScp; ++ i ) { aryScp [ i ] = std::make_shared < Script > (); }

			for ( UINT32 iScp = 0; iScp < nScp; ++ iScp )
			{
				aryScp [ iScp ]->SetFrame ( iScp );
				LoadScript ( buf, pos, (* aryScp [ iScp ]) );
			}

			aryAct [ iAct ]->AddaScript ( std::move (aryScp), nScp );
		}

//		ch.AddpAction ( aryAct, nAct );
		ch.AddpAction ( std::move ( aryAct ), nAct );

	}
	
	void LoadCharaBinFunc::LoadGarnish ( CUPR_BYTE buf, UINT32 & pos, Chara & ch )
	{
		//エフェクト個数 と メモリの確保
		UINT32 nEfc = m_utl.LoadUInt ( buf, pos );

		std::vector < P_Sequence > aryEfc( nEfc );
		for ( UINT32 i = 0; i < nEfc; ++ i ) { aryEfc [ i ] = std::make_shared < Effect > (); }

		//実データ
		for ( UINT32 iEfc = 0; iEfc < nEfc; ++ iEfc )
		{
			//エフェクト
			aryEfc [ iEfc ]->SetName ( m_utl.LoadS3dString ( buf, pos ) );

			//スクリプト個数 と メモリの確保
			UINT32 nScp = m_utl.LoadUInt ( buf, pos );
			std::unique_ptr < P_Frame [] > aryScp = std::make_unique < P_Frame [] > ( nScp );
			for ( UINT32 i = 0; i < nScp; ++ i ) { aryScp [ i ] = std::make_shared < Script > (); }

			for ( UINT32 iScp = 0; iScp < nScp; ++ iScp )
			{
				aryScp [ iScp ]->SetFrame ( iScp );
				LoadScript ( buf, pos, ( * aryScp [ iScp ] ) );
			}

			aryEfc [ iEfc ]->AddaScript ( std::move ( aryScp ), nScp );
		}

		ch.AddpEffect ( aryEfc, nEfc );
	}
#endif // 0


	//フレーム
	void LoadCharaBinFunc::LoadFrame ( CUPR_BYTE buf, UINT32 & pos, Frame & frm )
	{
		//グループ (Editorで用いる値)
		int group = m_utl.LoadInt ( buf, pos );
		(void)group;
		//読み込み後、使用しない

		//イメージインデックス
		UINT32 imdIndex = m_utl.LoadUInt ( buf, pos );
		frm.ImageIndex.Set ( imdIndex );

		//イメージ名
		s3d::String imgName { m_utl.LoadS3dString ( buf, pos ) };
		(void)imgName;
		//読み込み後、使用しない

		//位置
		frm.Pos.Set ( m_utl.LoadVec2 ( buf, pos ) );

		// [] ルートID
		m_utl.LoadAryUint ( buf, pos, frm.GetaRouteID () );

		//枠
		m_utl.LoadListRect ( buf, pos, frm.GetpvCRect () );
		m_utl.LoadListRect ( buf, pos, frm.GetpvHRect () );
		m_utl.LoadListRect ( buf, pos, frm.GetpvARect () );
		m_utl.LoadListRect ( buf, pos, frm.GetpvORect () );

		// [] エフェクト生成
		UINT32 nIdEfGnrt = m_utl.LoadUInt ( buf, pos );
		for ( UINT32 i = 0; i < nIdEfGnrt; ++ i )
		{
			//設定用
			P_EfGnrt pEfGnrt = std::make_shared < EffectGenerate > ();

			//生成名
			pEfGnrt->Name.Set ( m_utl.LoadS3dString ( buf, pos ) );

			//対象エフェクト
			pEfGnrt->Ef_Name.Set ( m_utl.LoadS3dString ( buf, pos ) );
			//エフェクトID
			pEfGnrt->Index.Set ( m_utl.LoadUInt ( buf, pos ) );

			//位置
			int pos_x = m_utl.LoadInt ( buf, pos );
			int pos_y = m_utl.LoadInt ( buf, pos );
			pEfGnrt->Pos.Set ( VEC2 ( (float)pos_x, (float)pos_y ) );
			//Z値
			int z_per100F = (int)m_utl.LoadInt ( buf, pos );
			pEfGnrt->Z.Set ( z_per100F * 0.01f );
			//生成
			pEfGnrt->Gnrt.Set ( (bool)buf [ pos ++ ] );
			//位置同期
			pEfGnrt->Sync.Set ( (bool)buf [ pos ++ ] );

			//描画モード
			pEfGnrt->GnrtCnd.Set ( (GENERATE_CONDITION) m_utl.LoadInt ( buf, pos ) );

			//描画モード
			pEfGnrt->DrawMode.Set ( (DRAW_MODE) m_utl.LoadInt ( buf, pos ) );

			//ループ回数(0は無限)
			pEfGnrt->Loop.Set ( m_utl.LoadInt ( buf, pos ) );
			//画面外で終了
			pEfGnrt->DeleteOut.Set ( (bool)buf [ pos ++ ] );
			//カウントで終了(0は無限)
			pEfGnrt->DeleteCount.Set ( m_utl.LoadInt ( buf, pos ) );

			//基準回転[rad]
			pEfGnrt->Rotate.Set ( m_utl.LoadFloat ( buf, pos ) );
			//基準回転中心
			pEfGnrt->Rotate_center.Set ( m_utl.LoadVec2 ( buf, pos ) );

			//次エフェクト生成名
			pEfGnrt->NextName.Set ( m_utl.LoadS3dString ( buf, pos ) );

			//フレームに設定
			frm.GetpapEfGnrt ()->push_back ( pEfGnrt );
		}

		//SEジェネレート
		UINT32 nIdSEGnrt = m_utl.LoadUInt ( buf, pos );
		for ( UINT32 i = 0; i < nIdSEGnrt; ++ i )
		{
			Generator gnrt;

			gnrt.Name.Set ( m_utl.LoadS3dString ( buf, pos ) );
			gnrt.m_cnd.Set ( (GENERATE_CONDITION)m_utl.LoadInt( buf, pos ) );
			gnrt.m_group.Set ( m_utl.LoadUInt( buf, pos ) );

//			gnrt.m_target_id.Set ( m_utl.LoadUInt( buf, pos ) );
			//->ファイル名アセットで再生

			//フレームに設定
			frm.GetaSE().push_back ( gnrt );
		}

		//VCジェネレート
		UINT32 nIdVCGnrt = m_utl.LoadUInt ( buf, pos );
		for ( UINT32 i = 0; i < nIdVCGnrt; ++ i )
		{
			Generator gnrt;

			gnrt.Name.Set ( m_utl.LoadS3dString ( buf, pos ) );
			gnrt.m_cnd.Set ( (GENERATE_CONDITION)m_utl.LoadInt( buf, pos ) );
			gnrt.m_group.Set ( m_utl.LoadUInt( buf, pos ) );

//			gnrt.m_target_id.Set ( m_utl.LoadUInt( buf, pos ) );
			//->ファイル名アセットで再生

			//フレームに設定
			frm.GetaVC().push_back ( gnrt );
		}


		//バトルパラメータ
		LoadFrmPrm_Btl ( buf, pos, frm );

		//ステージング(演出)パラメータ
		LoadFrmPrm_Stg ( buf, pos, frm );

		//汎用パラメータ
//		m_utl.LoadAryInt ( buf, pos, frm.GetaVersatile () );
		A_INT32 aVst = frm.GetaVersatile ();
		for ( int32 i = 0; i < VERSATILE_ARY_SIZE; ++i)
		{
			aVst [ i ] = m_utl.LoadInt ( buf, pos );
		}
	}


	//スクリプト・戦闘パラメータ
	void LoadCharaBinFunc::LoadFrmPrm_Btl ( CUPR_BYTE buf, UINT32 & pos, Frame & frm )
	{
		//設定用一時変数
		Frame_Param_Battle fpb;

		fpb.CalcState = (CLC_ST)m_utl.LoadInt ( buf, pos );

		//@info 編集時は(下１桁有効の)１０倍整数なので、読込時は移動量を0.1f倍する
		fpb.Vel = m_utl.LoadVec2_Dev10F ( buf, pos );
		fpb.Acc = m_utl.LoadVec2_Dev10F ( buf, pos );

		fpb.Power = m_utl.LoadInt ( buf, pos );
		fpb.DirectDamage_I = m_utl.LoadInt ( buf, pos );
		fpb.DirectDamage_E = m_utl.LoadInt ( buf, pos );

		fpb.Recoil_I = m_utl.LoadInt ( buf, pos );
		fpb.Recoil_E = m_utl.LoadInt ( buf, pos );
		fpb.Balance_I = m_utl.LoadInt ( buf, pos );
		fpb.Balance_E = m_utl.LoadInt ( buf, pos );
		fpb.Gauge_I = m_utl.LoadInt ( buf, pos );
		fpb.Gauge_E = m_utl.LoadInt ( buf, pos );

		fpb.Warp_I = m_utl.LoadInt ( buf, pos );
		fpb.Warp_E = m_utl.LoadInt ( buf, pos );
		fpb.GuardWarp_I = m_utl.LoadInt ( buf, pos );
		fpb.GuardWarp_E = m_utl.LoadInt ( buf, pos );

		//フレームに設置
		frm.Set_FP_B ( fpb );
	}


	//スクリプト・演出パラメータ
	void LoadCharaBinFunc::LoadFrmPrm_Stg ( CUPR_BYTE buf, UINT32 & pos, Frame & frm )
	{
		//設定用一時変数
		Frame_Param_Staging fps;

		fps.BlackOut		 = m_utl.LoadByte ( buf, pos );
		fps.Vibration		 = m_utl.LoadByte ( buf, pos );
		fps.Stop			 = m_utl.LoadByte ( buf, pos );

		fps.AfterImage_N	 = m_utl.LoadByte ( buf, pos );
		fps.AfterImage_time = m_utl.LoadByte ( buf, pos ); ;
		fps.AfterImage_pitch = m_utl.LoadByte ( buf, pos ); ;
		fps.Vibration_S	 = m_utl.LoadByte ( buf, pos );;
		fps.Color			 = (_CLR)m_utl.LoadUInt ( buf, pos );
		fps.Color_time		 = m_utl.LoadByte ( buf, pos );

		fps.Rotate			 = m_utl.LoadInt ( buf, pos );
		fps.Rotate_center	 = m_utl.LoadVec2 ( buf, pos );
		fps.Omega			 = m_utl.LoadFloat ( buf, pos );
		fps.Scaling		= m_utl.LoadVec2 ( buf, pos );
		fps.Scaling_center		= m_utl.LoadVec2 ( buf, pos );

#if 0
		fps.SE				 = m_utl.LoadUInt ( buf, pos );
		fps.SE_Name		 = m_utl.LoadS3dString ( buf, pos );
		fps.VC_Name		 = m_utl.LoadS3dString ( buf, pos );

		if ( 0 != scp.m_prmStaging.SE_Name.compare ( U"" ) )
		{
			TRACE_F ( _T("%s\n"), scp.m_prmStaging.SE_Name.toWstr().c_str() );
		}
#endif // 0

		//フレームに設置
		frm.Set_FP_S ( fps );
	}

#if 0

	//イメージ
	void LoadCharaBinFunc::LoadImg ( CUPR_BYTE buf, UINT32 & pos, PAP_Tx pvpTx )
	{
		//個数
		UINT32 nImg = m_utl.LoadUInt ( buf, pos );
		pvpTx->clear ();
		pvpTx->resize ( nImg );

		for ( UINT32 i = 0; i < nImg; ++ i )
		{
			//名前を取得
			s3d::String name = m_utl.LoadS3dString ( buf, pos );

			//サイズを取得
			UINT32 filesize = m_utl.LoadUInt ( buf, pos );

#if 0
			UINT32 temp_pos = pos;
			byte b0 = buf [ pos ++ ];
			byte b1 = buf [ pos ++ ];
			byte b2 = buf [ pos ++ ];
			byte b3 = buf [ pos ++ ];
#endif // 0

#if 0
			pos = temp_pos + size;

			//メモリ上のデータからゲームテクスチャに変換
			s3d::Image img ();

			s3d::BinaryReader br ();
			P_Tx pTx = std::make_shared < s3d::Texture > ( (LPCVOID)(buf.get() + pos), size );
			pos += size;


			s3d::BinaryReader br;

			//キャラ内部のテクスチャリストに加える
			( *pvpTx ) [ i ] = pTx;
#endif

#if 0
			//ファイルからテクスチャを作成
			P_Tx pTx = std::make_shared < s3d::Texture > ( U"Image/" + name );


			P_Tx pTx0 = std::make_shared < s3d::Texture > ( U"000_立ち_00.png" );
			( *pvpTx ) [ i ] = pTx0;
#endif // 0


#if 0
#endif // 0

			//メモリ上からテクスチャに変換
			s3d::MemoryReader mr ( (void*)(buf.get() + pos), filesize );
			mr.setPos ( 0 );

			P_Tx pTx = std::make_shared < s3d::Texture > ( std::move ( mr ) );


			//キャラ内部のテクスチャリストに加える
			( *pvpTx ) [ i ] = pTx;


			pos += filesize;
		}

	}


#endif // 0


	void LoadCharaBinFunc::LoadCommand ( CUPR_BYTE buf, UINT32 & pos, Chara & ch )
	{
		//コマンド個数 と メモリの確保
		UINT32 nCmd = m_utl.LoadUInt ( buf, pos );
//		std::unique_ptr < P_Command[] > aryCmd = std::make_unique < P_Command[] > ( nCmd );
		UP_AP_Cmd paCmd = std::make_unique < AP_Cmd > ( nCmd );
		for ( UINT32 i = 0; i < nCmd; ++ i ) { (*paCmd) [ i ] = std::make_shared < Command > (); }

		//実データ
		for ( UINT32 i = 0; i < nCmd; ++ i )
		{
			//コマンド名
			s3d::String str = m_utl.LoadS3dString ( buf, pos );
			(*paCmd) [ i ]->Name.Set ( str );

			//受付時間[byte]
			byte lmtTime = buf [ pos ++ ];
			(*paCmd) [ i ]->LimitTime.Set ( (UINT32)lmtTime );

			//ゲームキー
			byte nGameKey = buf [ pos ++ ];
			//std::unique_ptr < GameKeyCommand [] > gkc = std::make_unique < GameKeyCommand [] > ( nGameKey );
			UP_A_GKCMD pgkc = std::make_unique < A_GKCMD > ( nGameKey );
			for ( UINT32 iKey = 0; iKey < nGameKey; ++ iKey )
			{
				//否定
//				bool bNot = (bool)buf [ pos ++ ];
				bool bNot = m_utl.LoadBool ( buf, pos );

				//レバー [ GameKey::LVR_NUM = 8 ]
				KEY_ST lvr [ GameKey::LVR_NUM ] = { GameKeyCommand::GAME_KEY_WILD };
				for ( UINT32 iLvr = 0; iLvr < GameKey::LVR_NUM; ++ iLvr )
				{
					lvr [ iLvr ] = (KEY_ST)buf [ pos ++ ];
				}

				//ボタン [ _GameKey::BTN_NUM = 8 ]
				KEY_ST btn [ GameKey::BTN_NUM ] = { GameKeyCommand::GAME_KEY_WILD };
				for ( UINT32 iBtn = 0; iBtn < GameKey::BTN_NUM; ++ iBtn )
				{
					btn [ iBtn ] = (KEY_ST)buf [ pos ++ ];
				}

				(*pgkc) [ iKey ].SetNot ( bNot );
				(*pgkc) [ iKey ].SetaLvr ( lvr );
				(*pgkc) [ iKey ].SetaBtn ( btn );
			}

			(*paCmd) [ i ]->SetaGameKeyCmd ( *pgkc );
		}

		ch.SetaCommand ( std::move ( paCmd ) );
	}


	void LoadCharaBinFunc::LoadBranch ( CUPR_BYTE buf, UINT32 & pos, Chara & ch )
	{
		//ブランチ個数 と メモリの確保
		UINT32 nBrc = m_utl.LoadUInt ( buf, pos );
//		std::unique_ptr < P_Brc [] > aryBrc = std::make_unique < P_Brc [] > ( nBrc );
		UP_AP_Brc paBrc = std::make_unique < AP_Brc > ( nBrc );
		for ( UINT32 i = 0; i < nBrc; ++ i ) { (*paBrc) [ i ] = std::make_shared < Branch > (); }

		//実データ
		for ( UINT32 i = 0; i < nBrc; ++ i )
		{
			P_Brc brc = (*paBrc) [ i ];

			//ブランチ名
			brc->Name.Set ( m_utl.LoadS3dString ( buf, pos ) );

			//条件
			brc->Condition.Set ( (BRANCH_CONDITION)buf [ pos ++ ] );

			//条件コマンド名(複数)
			UINT32 nCmd = m_utl.LoadUInt ( buf, pos );
			for (UINT32 iCmd = 0; iCmd < nCmd; ++ iCmd )
			{
				brc->NameCommand.Set ( m_utl.LoadS3dString ( buf, pos ) );
			}

			//条件コマンドインデックス
			brc->IndexCommand.Set ( m_utl.LoadUInt ( buf, pos ) );

			//遷移先シークエン名
			brc->NameSequence.Set ( m_utl.LoadS3dString ( buf, pos ) );

			//遷移先シークエンインデックス
			brc->IndexSequence.Set ( m_utl.LoadUInt ( buf, pos ) );

			//遷移先スクリプト位置
			brc->IndexFrame.Set ( m_utl.LoadUInt ( buf, pos ) );

			//同一で遷移
			brc->Other.Set ( m_utl.LoadBool ( buf, pos ) );

#if 0

			if ( brc->Condition.Is( BRANCH_CONDITION::BRC_THR_E ) )
			{
				TRACE_F_S ( U"Load Branch Command Name" );
			}

#endif // 0
		}
		ch.SetaBranch ( std::move ( paBrc ) );
	}


	void LoadCharaBinFunc::LoadRoute ( CUPR_BYTE buf, UINT32 & pos, Chara & ch )
	{
		//ルート個数 と メモリの確保
		UINT32 nRut = m_utl.LoadUInt ( buf, pos );
//		UP_AP_Route aryRut = std::make_unique < P_Rut [] > ( nRut );
		UP_AP_Rut paRut = std::make_unique < AP_Rut > ( nRut );
		for ( UINT32 i = 0; i < nRut; ++ i )
		{
			(*paRut) [ i ] = std::make_shared < Route > ();
		}

		//実データ
		for ( UINT32 i = 0; i < nRut; ++ i )
		{
			P_Rut pr = (*paRut) [ i ];

			//ルート名
			(*paRut) [ i ]->Name.Set ( m_utl.LoadS3dString ( buf, pos ) );

			//ブランチIDリスト
			m_utl.LoadAryUint ( buf, pos, (*paRut) [ i ]->GetaIDBranch () );
		}

		ch.SetaRoute ( std::move ( paRut ) );
	}


	void LoadCharaBinFunc::LoadListName ( CUPR_BYTE buf, UINT32 & pos, A_STR & aStr )
	{
		//個数
		UINT32 n = m_utl.LoadUInt ( buf, pos );
		for (UINT32 i = 0; i < n; ++i)
		{
			aStr[i] = m_utl.LoadS3dString ( buf, pos );
		}
	}



}	//namespace GAME

