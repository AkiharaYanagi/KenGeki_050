//=================================================================================================
//
// メイン ソースコード
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//	ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"


//CharaData総合ヘッダファイル
#include "CharaData.h"


#if 0
#include "GameMain.h"
#include "G_Ftg.h"
#endif // 0


//-------------------------------------------------------------------------------------------------
//	実装
//-------------------------------------------------------------------------------------------------
using namespace GAME;


//前方宣言
void Load ();
void Init ();
void Move ();
void Draw ();


#if 0
//ゲームシステム
GameSystem gameSystem;
#endif // 0


//メインループ
void Main()
{

	//タイトル
	Window::SetTitle ( U"剣撃クロスゾーン" );

	//Size(320,20)
	Texture tx { U"life_value.png" };
	//Size(100,100)
//	Texture tx { U"Face_Sae.png" };

//	Texture tx { U"16_16_Padding.png" };
//	Texture tx { U"ClrPicker.png" };

	Quad quad { 100, 100, 350, 100, 300, 300, 50, 300 };

	//頂点
	Array < Float2 > aryFlt { { 0, 0 }, { 350, 100 }, {300, 300}, {50, 300} };




	//
	//			       /─────────────/
	//	   /──────────/				/
	//	  /						   /
	//	 /			/─────────────/ 
	//	/──────────/
	//
	s3d::Polygon plgn_sp
	{
		{ 10, 100 }, { 100, 100 }, { 110, 10 }, { 310, 10 },
		{ 300, 100 }, { 210, 100 }, { 200, 200 }, { 0, 200 },
	};


	//背景テクスチャ
	s3d::Texture tx_frame { U"Battle\\gauge_all.png" };
	//const VEC2 DispFrontEnd_all::POS_FRAME_ALL_1P ( 0 + 516, 10 );
	//const VEC2 DispFrontEnd_all::POS_FRAME_ALL_2P ( 1280 - 516 - 0, 10 );

	//ライフ
	s3d::Texture tx_life { U"Battle\\life_value.png" };
	//Size ( 320, 20 )
	//const VEC2 DispFrontEnd_all::POS_LIFE_VALUE_1P ( WND_CNT - 151, 62 );
	//const VEC2 DispFrontEnd_all::POS_LIFE_VALUE_2P ( WND_CNT + 151, 62 );
	double x0 = 640 + 151;
	double y0 = 62;
	double x1 = x0 + 320;
	double y1 = y0;
	double x2 = x0 + 320 - 10;
	double y2 = y0 + 20;
	double x3 = x0 - 10;
	double y3 = y0 + 20;


	double x10 = 100;
	double y10 = 100;
	double x11 = x0 + 500;
	double y11 = y0;
	double x12 = x0 + 500 - 10;
	double y12 = y0 + 500;
	double x13 = x0 - 10;
	double y13 = y0 + 500;
	s3d::Polygon plgn1 { { x10, y10 }, { x11, y11 }, { x12, y12 }, { x13, y13 } };

	//移動した値
	double x = x1;

	//読込
	Load ();

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


		//--------------------------------------------------------
		//ゲージ枠
		tx_frame.draw ( 1280 - 516 - 0, 10 );

		//体力ゲージ
		x -= 1;
		x1 = x;
		x2 = x -10;
		s3d::Polygon plgn_life { { x0, y0 }, { x1, y1 }, { x2, y2 }, { x3, y3 } };
		//体力ゲージ表示用ポリゴン
		plgn_life.toBuffer2D ( Vec2(x0, y0), tx_life.size() ).draw ( tx_life );
		//tx_life.draw ( 640 + 151, 62 );


		//剣撃ゲージ
		x -= 1;
		x1 = x;
		x2 = x -10;
		s3d::Polygon plgn_life { { x0, y0 }, { x1, y1 }, { x2, y2 }, { x3, y3 } };
		//剣撃ゲージ表示用ポリゴン
		plgn_life.toBuffer2D ( Vec2(x0, y0), tx_life.size() ).draw ( tx_life );
		//tx_life.draw ( 640 + 151, 62 );


		//体力ゲージ、剣撃ゲージ
		//平行四辺形が２つ重なる形
		//上辺の長さを100%として、値分の長さを減らす


		//超必殺技ゲージ
		//平行四辺形だが、段差がある
		//透明部分は維持できるかどうか


		//アクセルゲージ（疑似円弧）
		//角度と三角関数
		//0から10000の範囲を -π/2 から +π/4の範囲に変換するコード
#if 0
	#include <iostream>
	#include <cmath>

		double mapRange(double value, double inMin, double inMax, double outMin, double outMax) {
			return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
		}

		int main() {
			double inputValue = 5000; // 変換したい値
			double mappedValue = mapRange(inputValue, 0, 10000, -M_PI / 2, M_PI / 4);

			std::cout << "Mapped Value: " << mappedValue << std::endl;
			return 0;
		}
#endif // 0

#if 0
#include <iostream>
#include <cmath>

		double mapRange(double value, double inMin, double inMax, double outMin, double outMax) {
			return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
		}

		void calculateCirclePoint(double value, double inMin, double inMax, double outMin, double outMax, double radius, double x0, double y0) {
			double theta = mapRange(value, inMin, inMax, outMin, outMax); // 角度変換
			double x = x0 + radius * cos(theta);
			double y = y0 + radius * sin(theta);

			std::cout << "Mapped Angle: " << theta << " radians" << std::endl;
			std::cout << "Point P(x, y): (" << x << ", " << y << ")" << std::endl;
		}

		int main() {
			double inputValue = 1000; // 変換したい値
			double radius = 10.0; // 円の半径
			double x0 = 5.0, y0 = 5.0; // 原点の座標

			calculateCirclePoint(inputValue, -5000, 2500, -M_PI / 2, M_PI / 4, radius, x0, y0);

			return 0;
		}

#endif // 0


//		s3d::Polygon plgn { { x0, y0 }, { x1, y1 }, { x2, y2 }, { x3, y3 } };
//		plgn.toBuffer2D ( Vec2(0, 0), tx.size() ).draw ( tx );
//		plgn1.toBuffer2D ( Arg::center (10, 10), Vec2{16,16} ).draw ( tx );
//		plgn1.toBuffer2D ( Arg::center (200, 200), tx.size() ).draw ( tx );
//		plgn1.toBuffer2D ( Vec2(200, 200), tx.size() ).draw ( tx );


//		plgn_sp.draw(0, 0);

//		plgn.draw (400, 500);
//		plgn1.draw (0, 0);

//		tx.draw ( 100, 400 );

//		quad( tx ).draw ();
	}
	//========================================



#if 0
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	const Texture texture1{ U"example/windmill.png", TextureDesc::Mipped };
	const Texture texture2{ U"example/siv3d-kun.png", TextureDesc::Mipped };

	const s3d::Polygon star = Shape2D::Star(180, Vec2{ 200, 200 });
	const s3d::Polygon hexagon = Shape2D::Hexagon(60, Vec2{ 480, 380 });

	while (System::Update())
	{
		const double xOffset = (200 + Periodic::Sine1_1(5s) * 80.0);

		// star に対し、(xOffset, 200) を画像の中心とするようにテクスチャを貼り付けて描画する
//		star.toBuffer2D(Arg::center(xOffset, 200), texture1.size()).draw(texture1);
		star.toBuffer2D(Arg::center(0, 0), texture1.size()).draw(texture1);

//		hexagon.draw(HSV{ 240, 0.5, 1.0 });

		// hexagon に対し、(515, 562) を画像の中心とするようにテクスチャを貼り付けて描画する
		hexagon.toBuffer2D(Arg::center = Vec2{ 500, 500 }, texture2.size()).draw(texture2);
	}
#endif // 0
}


//起動後１回のみの初期化
void Load ()
{
	//test
	test_MakeCharaData test_mcd;
	P_Chara pChara = test_mcd.Make();


	//test Load




#if 0

	//-------------------------------------
	//シーン共通
	//格闘部分共通パラメータシングルトン生成
	G_Ftg::Create ();

	//-------------------------------------
	//システム初期化
	gameSystem.SystemLoad ();

	//ゲームメイン
	UP_GameMain gameMain = std::make_unique < GameMain > ();
	gameMain->Load ();
	gameMain->Init ();

	//ゲームシステムにメインを追加
	gameSystem.SetpGameMain ( std::move ( gameMain ) );

#endif // 0

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
//	gameSystem.Move ();

}


//---------------------------------------------------
// 描画
//---------------------------------------------------
void Draw ()
{
	//ゲームメイン
//	gameSystem.Draw ();

}

