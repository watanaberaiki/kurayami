#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1B_31_ワタナベライキ:";

// ウィンドウ横幅
const int WIN_WIDTH = 640;

// ウィンドウ縦幅
const int WIN_HEIGHT = 640;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int block = LoadGraph("block.png");

	// ゲームループで使う変数の宣言
	int map[20][20] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};

	enum direction {
		Down,//0
		Left,//1
		Up,//2
		Right//3
	};
	//方向切り替え
	int scene = Down;

	//光
	int startX[4] = { 200 ,640,200,0};
	int startY[4] = { 0 ,300,640,300};
	int endX[4] = { 200 ,0,200,640};
	int endY[4] = { 640 ,300,0,300};
	int startXMap[4] = { };
	int startYMap[4] = {};
	int endXMap[4] = { };
	int endYMap[4] = {};
	// 最新のキーボード情報用
	char keys[256] = {0};

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = {0};

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//
		
		// 更新処理
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
			if (scene==Right) {
				scene = Down;
			}
			else {
				scene += 1;
			}
		}
		for (int i = 0; i < 4; i++) {
			startXMap[i] = startX[i] / 32;
			startYMap[i] = startY[i] / 32;
			endXMap[i] = endX[i] / 32;
			endYMap[i] = endY[i] / 32;
		}
		// 描画処理
		
		//暗闇
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 10);
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				if (map[y][x] == 1) {
					DrawGraph(x * 32, y * 32, block, true);
				}
			}
		}

		
		switch(scene) {

			//上から下の光
		case Down:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			for (int x = -2; x < 3; x++) {
				for (int i = startYMap[Down]; i < endYMap[Down]; i++) {
					if (map[i][startXMap[Down] - x] == 1) {
						DrawGraph((startXMap[Down] - x) * 32, i * 32, block, true);
					}
				}
			}

			//水色
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawLine(startX[Down], startY[Down], endX[Down], endY[Down], GetColor(0, 128, 128), 50);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawLine(startX[Down], startY[Down], endX[Down], endY[Down], GetColor(0, 128, 128), 35);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
			DrawLine(startX[Down], startY[Down], endX[Down], endY[Down], GetColor(255, 255, 255), 10);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawFormatString(10, 650, GetColor(255, 255, 255), "%d", startXMap[Down]);
			DrawFormatString(30, 650, GetColor(255, 255, 255), "%d", startYMap[Down]);
			DrawFormatString(50, 650, GetColor(255, 255, 255), "%d", endXMap[Down]);
			DrawFormatString(70, 650, GetColor(255, 255, 255), "%d", endYMap[Down]);
			break;
			
			//右から左の光
		case Left:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			for (int y = -2; y < 3; y++) {
				for (int i = startXMap[Left]; i >= endXMap[Left]; i--) {
					if (map[startYMap[Left]-y][i] == 1) {
						DrawGraph( i * 32,(startYMap[Left] - y) * 32, block, true);
					}
				}
			}

			//水色
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawLine(startX[Left], startY[Left], endX[Left], endY[Left], GetColor(0, 128, 128), 50);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawLine(startX[Left], startY[Left], endX[Left], endY[Left], GetColor(0, 128, 128), 35);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
			DrawLine(startX[Left], startY[Left], endX[Left], endY[Left], GetColor(255, 255, 255), 10);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawFormatString(10, 650, GetColor(255, 255, 255), "%d", startXMap[Left]);
			DrawFormatString(30, 650, GetColor(255, 255, 255), "%d", startYMap[Left]);
			DrawFormatString(50, 650, GetColor(255, 255, 255), "%d", endXMap[Left]);
			DrawFormatString(70, 650, GetColor(255, 255, 255), "%d", endYMap[Left]);
			break;


			//下から上の光
		case Up:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			for (int x = -2; x < 3; x++) {
				for (int i = startYMap[Up]; i >= endYMap[Up]; i--) {
					if (map[i][startXMap[Up] - x] == 1) {
						DrawGraph((startXMap[Up] - x) * 32, i * 32, block, true);
					}
				}
			}

			//水色
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawLine(startX[Up], startY[Up], endX[Up], endY[Up], GetColor(0, 128, 128), 50);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawLine(startX[Up], startY[Up], endX[Up], endY[Up], GetColor(0, 128, 128), 35);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
			DrawLine(startX[Up], startY[Up], endX[Up], endY[Up], GetColor(255, 255, 255), 10);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawFormatString(10, 650, GetColor(255, 255, 255), "%d", startXMap[Up]);
			DrawFormatString(30, 650, GetColor(255, 255, 255), "%d", startYMap[Up]);
			DrawFormatString(50, 650, GetColor(255, 255, 255), "%d", endXMap[Up]);
			DrawFormatString(70, 650, GetColor(255, 255, 255), "%d", endYMap[Up]);
			break;

		case Right:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			for (int y = -2; y < 3; y++) {
				for (int i = startXMap[Right]; i < endXMap[Right]; i++) {
					if (map[startYMap[Right] - y][i] == 1) {
						DrawGraph(i * 32, (startYMap[Right] - y) * 32, block, true);
					}
				}
			}

			//水色
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawLine(startX[Right], startY[Right], endX[Right], endY[Right], GetColor(0, 128, 128), 50);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawLine(startX[Right], startY[Right], endX[Right], endY[Right], GetColor(0, 128, 128), 35);
			SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
			DrawLine(startX[Right], startY[Right], endX[Right], endY[Right], GetColor(255, 255, 255), 10);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
			DrawFormatString(10, 650, GetColor(255, 255, 255), "%d", startXMap[Right]);
			DrawFormatString(30, 650, GetColor(255, 255, 255), "%d", startYMap[Right]);
			DrawFormatString(50, 650, GetColor(255, 255, 255), "%d", endXMap[Right]);
			DrawFormatString(70, 650, GetColor(255, 255, 255), "%d", endYMap[Right]);
			break;
		}
		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
