//==============================================================================
//
//
//		Ｗｉｎｄｏｗｓ用 オリジナル同人２Ｄ対戦格闘ゲーム
//						『剣撃クロスゾーン』
//
//		早期アクセス版　　※完成版まで無償アップデート可能
//
//==============================================================================
//
//	ver 0.62	2026/04/01(水) 月日星ボイス追加＋修正
//
// 過去更新情報の詳細は別ファイル「◆公開用　修正点・変更点.txt」にて
//
//------------------------------------------------------------------------------
//
//	製作サークル	：　攻勢道場
//	公式サイト		：	https://sites.google.com/view/kouseidojo
//	E-mail			：	kouseidojo@gmail.com
//
//==============================================================================

//-------------------------------------------------------------------------------
◆動作環境

[OS]:  Windows11, Windows10 デスクトップ (Windows8以前は非推奨)
[入力]: １～２プレイヤー / ゲームパッドまたはキーボード (キー設定可能)
[出力]: ゲーム画面解像度 [1280*960] (ウィンドウモードで拡大縮小可能)
[ネットワーク]: 未対応 (将来対応検討)
[言語]: 日本語のみ(将来対応検討)


【ファイルコピー版】
・インストール		:「KenGeki_CrossZone.zip」を適当な場所に解凍する。
・アンインストール	:上記ファイル群をフォルダごと削除する。
・ゲーム実行		:「KenGeki」フォルダ内の実行ファイル「KenGeki_CrossZone.exe」をダブルクリック等で開く。


その他の実行ファイル
・"KenGeki_Manual.pdf" でゲームが操作の説明書です。
・"KenGeki_KeyConfig.exe" でゲームパッド・キーボードのキー設定が可能です。
・"剣撃クロスゾーン ゲーム設定.exe" でソフトウェア開始時の環境設定が可能です。


※このソフトウェアの使用に関して何らかの問題が発生したとしても当方は責任を一切負いません。


//-------------------------------------------------------------------------------
◆ゲーム概要
いわゆる２Ｄ対戦格闘ゲームです。
キャラクターを操作して攻撃し、相手のライフを無くせば勝ちです。


//-------------------------------------------------------------------------------
◆バトル操作 (方向はテンキー表示)
7 8 9
4 5 6	(5はニュートラル(入力無し))
1 2 3


レバー4(前):	ダッシュ 
レバー6(後):	ガード 

レバー7(上後):後方ジャンプ 
レバー8(上):	ジャンプ 
レバー9(上前):低空ダッシュ 

レバー1(下後):しゃがみガード 
レバー2(下):	しゃがみ 
レバー3(下前):歩き 

ボタン１	：	弱攻撃
ボタン２	：	中攻撃
ボタン３	：	強攻撃
ボタン４	：	特大攻撃
ボタン５	：	必殺技ボタン
ボタン６	：	投げボタン

ボタン７	：　ポーズボタン
ボタン８	：　（トレーニングモード時）リセット

各種コマンド：　キャラクターの固有必殺技が出せます
			（レバーと必殺技ボタンの組み合わせでも出せます）


◆システム操作
ボタン１	：決定
ボタン２	：キャンセル
ボタン８	：前の画面に戻る

PrintScreen		：画面のスクリーンショット
　(インストール先がシステムディレクトリの場合は管理者権限が必要です)
Esc			：	強制終了



◆デバッグ操作
キーボード　"1"キー	：デバッグ操作表示 切り換え
キーボード　"2"キー	：判定枠表示 切り換え
キーボード　"3"キー	：入力表示 切り換え
キーボード　"4"キー	：状態表示 切り換え
キーボード　"5"キー	：現在操作表示 切り換え
キーボード　"6"キー	：１プレイヤー側（プレイヤー/CPU)操作切り換え
キーボード　"7"キー	：２プレイヤー側（プレイヤー/CPU)操作切り換え



//-------------------------------------------------------------------------------
◆付録
//==============================================================================//
//　スクリプト編集ツール
//	"ScriptEditor.exe"
//	キャラクタファイル ver 2.11
//		2025/04/20(日) 公開
//
//==============================================================================
[OS]: Windows11, Windows10 デスクトップ (Windows8以前は非推奨)
[ライブラリ]: microsoft.NET Framework 4.6.1を使用
キャラクタファイルを編集できますが、動作は非サポートです。
キャラクタファイルが 動作スクリプトの"*.scp",
テクスチャファイルが"*.lz4"(1Pカラー, 2Pカラー, キャラエフェクト)となりました。


//-------------------------------------------------------------------------------
◆素材・クレジット

[作品情報]

・サークルスタッフ
企画・原案・キャラデザイン：	髭武者	(https://x.com/OLT826gnB319137)
3Dグラフィック・エフェクト：	龍村某	(https://x.com/nani_gassy)
プログラム・スクリプト：		秋原やなぎ	(https://x.com/akiharasoft)

・指南書・ミニキャライラスト：　あねほし (https://x.com/ane_hoshimaru)
・メインBGM:　高良郁斗@IKUTO	(https://lit.link/ikutotakara)
・その他BGM, 効果音: Audiostock	(https://audiostock.jp/)

・VOICE:
鵯 桜花：		konohana	(https://iikoe.org/actor_page/4590)
巴 紗絵：		雲雀ゆい	(https://iikoe.org/actor_page/3833)
烈火 烈堂：		髭武者		(https://x.com/OLT826gnB319137)
ギャバダルガ：	髭武者		(https://x.com/OLT826gnB319137)
フェラリア：	古條 凜		(https://iikoe.org/actor_page/435)

・ゲームプログラミングライブラリ	：
Siv3D (https://siv3d.github.io/)


//-----------------------------------------------------------------------------


LZ4 - Extremely Fast Compression algorithm
Copyright (c) 2011-2021, Yann Collet
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



LZ4 - 超高速圧縮アルゴリズム
Copyright (c) 2011-2021, Yann Collet
All rights reserved.

ソースコードおよびバイナリ形式での再配布および使用は、変更の有無にかかわらず、
以下の条件を満たす場合に許可されます。

1. ソースコードを再配布する場合、上記の著作権表示、本条件一覧、
   および以下の免責条項を必ず含めなければなりません。

2. バイナリ形式で再配布する場合、上記の著作権表示、本条件一覧、
   および以下の免責条項を、配布物に付属する文書またはその他の資料に
   必ず含めなければなりません。

本ソフトウェアは、著作権者およびコントリビューターによって「現状のまま」
提供されるものであり、明示的または黙示的な保証（商品性や特定目的への
適合性の保証を含むがそれに限定されない）は一切否認されます。
いかなる場合においても、著作権者またはコントリビューターは、本ソフトウェアの
使用によって生じたいかなる直接的、間接的、偶発的、特別、懲罰的、または
結果的損害（代替品やサービスの調達、使用不能、データ損失、利益損失、
業務中断などを含むがそれに限定されない）についても責任を負わないものとします。
たとえそのような損害の可能性について知らされていた場合でも同様です。


