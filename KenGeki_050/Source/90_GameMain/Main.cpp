//=================================================================================================
//
// メイン ソースコード
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//	ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameMain.h"
#include "CharaData.h"
#include "00_Core/DebugDisp.h"
#include "LoadImgFile.h"


//-------------------------------------------------------------------------------------------------
//	実装
//-------------------------------------------------------------------------------------------------
using namespace GAME;


//前方宣言
void Load ();
void Init ();
void Move ();
void Draw ();
void Rele ();


//ゲームシステム
GameSystem gameSystem;


//メインループ
void Main()
{
	Load ();	//読込

	//========================================
	//メインループ
	bool init = F;
	while ( System::Update() )
	{
		//初期化
		if ( ! init ) { Init (); init = T; }

		Move ();	//動作

		Draw ();	//描画

	}
	//========================================

	Rele ();	//解放
}



//---------------------------------------------------
//起動後１回のみの初期化
void Load ()
{
	//-------------------------------------
	//タイトル
	Window::SetTitle ( U"剣撃クロスゾーン" );




	//test
#if 0


	//Siv3D時間計測
	s3d::Stopwatch sw;

	//-----------------------------------------------
	Print << U"Gabadaruga_1p_bhv.lz4";
	sw.restart ();
	LoadImgFile lif;
	PAP_Tx paptx = lif.LoadLz4_Bhv ( U"Chara\\Gabadaruga_1p_bhv.lz4" );
	Print << U"bhv.lz4:" << sw.msF () << U"[ms]";
	//-----------------------------------------------
	Print << U"Gabadaruga_bhv_png.atls";
	sw.restart ();
	P_Atlas pAtls_png = LoadAtlasFilePng ( U"Chara\\Gabadaruga_bhv_png.atls" );
	Print << U"Page size = " << pAtls_png->GetnPage ();
	Print << U"Meta size = " << pAtls_png->GetMetaSize ();
	Print << U"png.atls:" << sw.msF () << U"[ms]";
	//-----------------------------------------------
	Print << U"Gabadaruga_bhv_img.atls";
	sw.restart ();
	P_Atlas pAtls_img = LoadAtlasFile ( U"Chara\\Gabadaruga_bhv_img.atls" );
	Print << U"img.atls:" << sw.msF () << U"[ms]";
	//-----------------------------------------------


#endif // 0




	//-------------------------------------
	//デバッグ用コマンドプロンプト表示

	if ( g_bCMDPRMPT_DISP )
	{
		DebugOutPrint::OpenPrompt ();
		PRINT_F_S ( U"start DebugOutPrint.\n{}"_fmt( g_VERSION ) );

		std::ostringstream oss;
		oss << "Build: " << __DATE__ << " " << __TIME__ << std::endl;
		PRINT_F_S ( s3d::Unicode::FromUTF8 ( oss.str ().c_str () ) );
	}

	//-------------------------------------
	//システム初期化
	gameSystem.SystemLoad ();

	InitVersion (  __DATE__, __TIME__ );	//バージョン初期化（日付＋時刻）


	//ゲームメイン
	UP_GameMain gameMain = std::make_unique < GameMain > ();
	gameMain->Load ();
	gameMain->Init ();


	
	//開始時一時停止
	if ( g_bWAIT_START )
	{
		gameSystem.SetbStop ( T );
	}


	//-------------------------------------
	//ゲームシステムにゲームメインオブジェクトを追加
	gameSystem.SetpGameMain ( std::move ( gameMain ) );


#if 0

	//---------------------------------------------------
	//test
	// 
	//スクリプト　
	PRINT_F_S( U"スクリプト" );
	P_Chara pChara = std::make_shared < Chara > ();	//キャラデータ実体
	LoadCharaBin_s3d lcb;
	lcb.Load ( U"Test/Test_Sae.scp", * pChara);
	PRINT_F_S( U"OK" );
	
	//Atlas
	P_Atlas pAtlas = LoadpAtlasImg ( U"Test/Sae_bhv.atls" );


#endif // 0
}


//---------------------------------------------------
//メインループ中の最初の１回のみの初期化
void Init ()
{
	//ウィンドウ設定
	GameInit gameInit;
	gameInit.SetStartCursorPos ( g_bSTART_CURSOR_POS );
	gameInit.Do ();

#if 0

	//ゲーム表示サイズ
	s3d::Size size = s3d::Scene::Size ();
	s3d::Scene::SetResizeMode ( s3d::ResizeMode::Virtual );
	s3d::Scene::Resize ( 1280, 960 );
//	s3d::Scene::Resize ( 1200, 900 );

	//ウィンドウサイズ
	s3d::Scene::SetResizeMode ( s3d::ResizeMode::Keep );
//	s3d::Window::Resize ( 1600, 900 );
	int32 wnd_w = 1728;
	int32 wnd_h = 972;
	s3d::Window::Resize ( wnd_w, wnd_h );	//16:9 で(1280,960)が入るサイズ
	s3d::Window::SetStyle ( s3d::WindowStyle::Sizable );

	//OS解像度と拡大率のためウィンドウサイズを再取得
//	int32 w = s3d::Window::Get;
//	int32 h = s3d::Window::Get;


	//ウィンドウ開始位置
#define CURSOR_POS_START 1
#if CURSOR_POS_START
	//カーソル位置のモニタの中心
	WND_UTL::MoveWindow_toCenter_onCursor ( wnd_w, wnd_h );
#else
	s3d::Window::Centering ();	//モニタ中央
#endif // CURSOR_POS_START


	//----------------------------------------
	//カーソル位置を画面外にする
	WindowState winStt = s3d::Window::GetState();
//	s3d::Cursor::SetPos ( winStt.virtualSize );	//右下
	s3d::Cursor::SetPos ( winStt.virtualSize.x - 165 , -20 );	//右上

#endif // 0
}


//---------------------------------------------------
// 動作
void Move ()
{
	gameSystem.Move ();
}

//---------------------------------------------------
// 描画
void Draw ()
{
#if 0
	//各値使用量　デバッグ表示
	s3d::ClearPrint ();
	s3d::Profiler::GetStat ().print ();

#endif // 0
	gameSystem.Draw ();
}

//---------------------------------------------------
// 解放
void Rele ()
{
	gameSystem.SystemRele ();
}
