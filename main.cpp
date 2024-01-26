#define _USE_MATH_DEFINES
#include <Novice.h>
#include"Ground.h"
#include <math.h>
#include "Typedef_player.h"
#include"Detection.h"
float easeInSine(float x) {
	return 1 - cosf(x + (float)M_PI);
};
const char kWindowTitle[] = "GC1D_ワタナベ＿リョウイチ";
const float Gravitation_ = 0.8f;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
    /*Player X, Y, Weight, Height, Speed, Jamp, Verosity */
	Player player = { 0.0f,500.0f,50.0f,50.0f,5.0f,10.0f,15.0f };
	/* placeX , placeY , placeW , placeH , PlaceMove */
	walkPlace Walkplace{ 0.0f,555.0f,1280.0f,700.0f,1.0f };
	/*DoorX, DoorY, DoorW, DoorH, Angle*/
	GoalDoor goaldoor{ 700.0f,455.0f,50.0f,100.0f ,0.0f };

	VariousFlag isJampFlag = { 0 };

	int scene = 1;
	int Color = RED;
	float DoorRightX = 0,DoorBottomY;
	float PlayerRightX = 0,PlayerBottomY;
	
	//int Timer = 10;
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		player.jamp -= Gravitation_;
		PlayerRightX = player.x + player.weight;
		DoorRightX = goaldoor.DoorX + goaldoor.DoorW;
		DoorBottomY = goaldoor.DoorY + goaldoor.DoorH;
		PlayerBottomY = player.y + player.height;
		Novice::ScreenPrintf(0, 0, "%d", scene);
		Novice::ScreenPrintf(20, 0, "%f", Walkplace.placeX);
		enum scene {
			
			Title,
			tutorial,
			Game,
		};
		scene Scene;

		switch (Scene)
		{
		case  Title:
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, GREEN, kFillModeSolid);
			if (keys[DIK_RETURN]) {
				Scene = tutorial;
			}

			break;

		case tutorial:

			if (player.x >= 1220) {
				player.x = 1220;
			}
			if (player.x <= 0) {
				player.x = 0;
			}
			if (player.y < 0) {
				player.y = 0;
			}

			/*if (player.y>=Walkplace.placeY-50) {
				player.y=Walkplace.placeY-50 ;
			}*/
			if (keys[DIK_RIGHT]) {
				player.x += player.speed;
			}
			if (keys[DIK_LEFT]) {
				player.x -= player.speed;
			}
			if (keys[DIK_SPACE]&&!preKeys[DIK_SPACE]) {

				player.jamp = player.verosity;

			}

			player.y -= player.jamp;


			if (player.y > Walkplace.placeY - 50) {
				player.y = Walkplace.placeY - 50;
			}
			/*if (player.jamp <= Walkplace.placeY) {
				player.jamp = Walkplace.placeY;
			}*/




			//判定する範囲までいったらあるキーを押して処理を実行する
			/*PlayerRightX = player.x + player.weight*/
			/*DoorRightX = goaldoor.DoorX + goaldoor.DoorW*/
			if (goaldoor.DoorX <= PlayerRightX && player.x <= DoorRightX&& DoorBottomY >= player.y && PlayerBottomY >= goaldoor.DoorY) {
				/*if (DoorBottomY<= player.y && PlayerBottomY <= goaldoor.DoorY) {

				}*/
					Novice::ScreenPrintf(1100, 0, "PushToKeysENTER");
					if (keys[DIK_RETURN]) {
						Color = BLUE;
					}



			}
			else {
				Color = RED;


			}
			 












			Novice::DrawBox((int)goaldoor.DoorX, (int)goaldoor.DoorY, (int)goaldoor.DoorW, (int)goaldoor.DoorH, goaldoor.angle, GREEN, kFillModeSolid);
			Novice::DrawBox((int)player.x, (int)player.y, (int)player.weight, (int)player.height, 0.0f, Color, kFillModeSolid);
			Novice::DrawBox((int)Walkplace.placeX, (int)Walkplace.placeY, (int)Walkplace.placeW * 3, (int)Walkplace.placeH, 0.0f, 0xffffffff, kFillModeSolid);

			if (Color == BLUE) {
				Scene = Game;
				Color = 0xff00ffff;
			}
			
			break;
		case Game:

			player.y -= player.jamp;

			if (player.y > Walkplace.placeY - 50) {
				player.y = Walkplace.placeY - 50;
			}
			if (player.x >= 1220) {
				player.x = 1220;
			}
			

			if (keys[DIK_RIGHT]) {
				player.x += player.speed;
				if (player.x > 1200) {
					Walkplace.placeX -= Walkplace.PlaceMove;
				}
			}
			if (keys[DIK_LEFT]) {
				player.x -= player.speed;
			}
			if (keys[DIK_SPACE]) {
				player.jamp = player.verosity;
				if (player.y < 0) {
					player.y = 0;
				}
			}

















			Novice::DrawBox((int)player.x, (int)player.y, (int)player.weight, (int)player.height, 0.0f, Color, kFillModeSolid);
			Novice::DrawBox((int)Walkplace.placeX, (int)Walkplace.placeY, (int)Walkplace.placeW * 3, (int)Walkplace.placeH, 0.0f, 0xffffffaf, kFillModeSolid);


			break;
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}

	}
	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

