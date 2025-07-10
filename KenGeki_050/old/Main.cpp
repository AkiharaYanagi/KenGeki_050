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
//#include "G_Ftg.h"

#include "LocalDefine.h"
#include "DispGauge.h"


//-------------------------------------------------------------------------------------------------
//	実装
//-------------------------------------------------------------------------------------------------
using namespace GAME;


//前方宣言
void Load ();
void Init ();
void Move ();
void Draw ();

//ゲームシステム
GameSystem gameSystem;

//メインループ
void Main()
{
	//タイトル
	Window::SetTitle ( U"剣撃クロスゾーン" );

	//読込
	Load ();


	//アクセルゲージ
	//Size ( 80, 139 )
	//const VEC2 DispGauge::POS_ACCEL_VALUE_1P ( 0 + 75 + 11, 27 );
	//const VEC2 DispGauge::POS_ACCEL_VALUE_2P ( 1280 - 75 - 11, 27 );
#if 0
	double x0 = 640;
	double y0 = 640;
//	double x1 = 640 + 141;
//	double y1 = 640 - 141;
	double x2 = 640 + 100;
	double y2 = 640;
#endif // 0

	double r = 220;


#if 0
	double x0 = 1194 - 80;
	double y0 = 27 + 139;
//	double x1 = x0 + 141;
//	double y1 = y0 - 141;
	double x2 = x0 + r;
	double y2 = y0;
#endif // 0


	//Accel P1
	double x0 = 0 + 75 + 12 + 80;
	double y0 = 27 + 139;
	double x1 = x0 - r;
	double y1 = y0 - r;
	double x2 = x0 - r;
	double y2 = y0;

//	s3d::Array < s3d::Vec2 > aryVec_accel{ {x0, y0}, {x1, y1}, {x2, y2} };
//	s3d::Polygon plgn{ aryVec_accel };

//	int32 count = 0;
	double accel = 0;
	double dir = 1;

	// 線形補間関数
//	double mapRange(double value, double inMin, double inMax, double outMin, double outMax) {
//   return outMin + (outMax - outMin) * ((value - inMin) / (inMax - inMin));

	//========================================
	//メインループ
	bool init = F;
	while ( System::Update() )
	{
		//初期化
		if ( ! init ) { Init (); init = T; }

		//動作
		Move ();

		//描画
		Draw ();

		
		accel += dir * 100;
		if (accel < 0) { dir = 1; }
		if ( 10000 < accel ) { dir = -1; }

		double theta = mapRange ( accel, 0, 10000, 0, D3DX_PI_BY4 );
//		double theta = mapRange ( accel, 0, 10000, 0, D3DX_PI_HALF );
//		double theta = 0.88;
		double x = r * std::cos ( theta );
		double y = r * std::sin ( theta );
//		s3d::Array < s3d::Vec2 > aryVec_accel{ {x0, y0}, {x0 + x, y0 - y}, {x2, y2} };
		s3d::Array < s3d::Vec2 > aryVec_accel{ {x2, y2}, {x0 - x, y0 - y}, {x0, y0} };
//		s3d::Array < s3d::Vec2 > aryVec_accel{ {x2, y2}, {x1, y1}, {x0, y0} };
		s3d::Polygon plgn{ aryVec_accel };
//		plgn.draw ();

		DBGOUT_WND_F(DBGOUT_0, U"x = {}"_fmt( x ) );
		DBGOUT_WND_F(DBGOUT_1, U"y = {}"_fmt( y ) );
		DBGOUT_WND_F(DBGOUT_2, U"a = {}"_fmt( accel ) );
	}
	//========================================
}


//起動後１回のみの初期化
void Load ()
{
	//-------------------------------------
	//シーン共通
	//格闘部分共通パラメータシングルトン生成
//	G_Ftg::Create ();

	//-------------------------------------
	//システム初期化
	gameSystem.SystemLoad ();

	//ゲームメイン
	UP_GameMain gameMain = std::make_unique < GameMain > ();

	P_DispGauge pDispGauge1p = std::make_shared < DispGauge > ();
	P_DispGauge pDispGauge2p = std::make_shared < DispGauge > ();

	pDispGauge1p->LoadPlayer ( PLAYER_ID_1 );
	pDispGauge2p->LoadPlayer ( PLAYER_ID_2 );

	gameMain->AddpTask ( pDispGauge1p );
	gameMain->AddpTask ( pDispGauge2p );


	gameMain->Load ();
	gameMain->Init ();

	//ゲームシステムにメインを追加
	gameSystem.SetpGameMain ( std::move ( gameMain ) );

}

//メインループ中の最初の１回のみの初期化
void Init ()
{
	//ウィンドウ設定

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

}



//---------------------------------------------------
// 動作
//---------------------------------------------------
void Move ()
{
	//ゲームメイン
	gameSystem.Move ();
}


//---------------------------------------------------
// 描画
//---------------------------------------------------
void Draw ()
{
	//ゲームメイン
	gameSystem.Draw ();
}
