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
	Player player = { 0.0f,500.0f,50.0f,50.0f,5.0f,10.0f,15.0f };
	walkPlace Walkplace{ 0,555,1280,700 };
	GoalDoor goaldoor{ 700.0f,455.0f,50.0f,100.0f ,0.0f };
	int scene = 1;
	int Color = RED;
	float DoorRightX = 0;
	float PlayerRightX=0 ;
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
		Novice::ScreenPrintf(0, 0,"%d", scene);
		switch (scene)
		{
		case  1:
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, GREEN, kFillModeSolid);
			if (keys[DIK_RETURN]) {
				scene = 2;
			}
		
			break;
		
		case 2:

			if (player.x >= 1220) {
				player.x = 1220;

			}   
			if (player.x <= 0) {
				player.x = 0;
		
			}
			/*if (player.y>=Walkplace.placeY-50) {
				player.y=Walkplace.placeY-50 ;
			}*/
			if(keys[DIK_RIGHT]){
				player.x += player.speed;
			}
			if (keys[DIK_LEFT]) {
				player.x -= player.speed;
			}
			if (keys[DIK_SPACE]) {
				player.jamp = player.verosity;
			}
				player.y -= player.jamp;
				
				if (player.y <= player.weight) {
					player.y = player.height;
			}

			//判定する範囲までいったらあるキーを押して処理を実行する
			if (goaldoor.DoorX <= PlayerRightX && player.x <= DoorRightX) {

				if (DoorRightX <= player.y && player.y + player.height <= goaldoor.DoorY) {

				}
				if (keys[DIK_SPACE]) {

					Color = BLUE;
				}

			}
			else {
				Color = RED;
			}
		

			







			Novice::DrawBox((int)goaldoor.DoorX, (int)goaldoor.DoorY, (int)goaldoor.DoorW, (int)goaldoor.DoorH, goaldoor.angle, GREEN, kFillModeSolid);
			Novice::DrawBox((int)player.x, (int)player.y, (int)player.weight, (int)player.height, 0.0f, Color, kFillModeSolid);
			Novice::DrawBox((int)Walkplace.placeX, (int)Walkplace.placeY, (int)Walkplace.placeW * 3, (int)Walkplace.placeH, 0.0f, 0xffffff0f, kFillModeSolid);

			/*if (Color == BLUE) {
				scene = 3;

			}*/
			break;
		case 3:

			if (player.y >= Walkplace.placeY - 50) {
				player.y = Walkplace.placeY - 50;
			}

			if (keys[DIK_RIGHT]) {
				player.x += player.speed;
			}
			if (keys[DIK_LEFT]) {
				player.x -= player.speed;
			}
			if (keys[DIK_SPACE]) {
				player.y -= player.jamp++;
				
			   
			}
		   















			Novice::DrawBox((int)player.x, (int)player.y, (int)player.weight, (int)player.height, 0.0f, Color, kFillModeSolid);
			Novice::DrawBox((int)Walkplace.placeX, (int)Walkplace.placeY, (int)Walkplace.placeW * 3, (int)Walkplace.placeH, 0.0f, 0xffffff0f, kFillModeSolid);


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
