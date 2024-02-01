#define _USE_MATH_DEFINES
#include <Novice.h>
#include"Ground.h"
#include <math.h>
#include "Typedef_player.h"
#include"Detection.h"
float easeInSine(float x) {
	return 1 - cosf(x + (float)M_PI);
};
void ColisionFunction(float LeftX, float RightX, float TopY, float BottomY, float PosRX, float& PosX, float PosBY, float& PosY, int& isjamp)
{
	if (LeftX<PosRX && PosX>RightX && TopY<PosBY && PosY>BottomY) {
		if (PosY <= TopY) {

			PosY = TopY - 50;
		}
		isjamp = 0;
	}
}
const char kWindowTitle[] = "GC1D_ワタナベ＿リョウイチ";
const float Gravitation_ = 0.8f;
const float WORLD_WIDTH = 3840.0f;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int StartDoor = Novice::LoadTexture("./ResourceFile./GoDoorSprite1.png");
	//int GameOver;
	int GoolDoor_ = Novice::LoadTexture("./ResourceFile./GoDoorSprite1.png");
	int ClearSprite = Novice::LoadTexture("./ResourceFile./ClearSprite-0001.png");
	int Title[2] = { Novice::LoadTexture("./ResourceFile./Don'tFall_Sprite1.png"),
						   Novice::LoadTexture("./ResourceFile./Don'tFall_Sprite0.png") };

	int PlaceSprite[3] = { Novice::LoadTexture("./ResourceFile./PlaceSprite.png"),
		Novice::LoadTexture("./ResourceFile./PlaceSprite.png"),
		Novice::LoadTexture("./ResourceFile./PlaceSprite.png") };

	int BackSprite[3] = { Novice::LoadTexture("./ResourceFile./Don'tFallBackSprite.png"),
		Novice::LoadTexture("./ResourceFile./Don'tFallBackSprite.png"),
		Novice::LoadTexture("./ResourceFile./Don'tFallBackSprite.png") };

	int PlayerSprite0 = Novice::LoadTexture("./ResourceFile./PlayerSprite0.png");
	int PlayerSprite1 = Novice::LoadTexture("./ResourceFile./PlayerSprite1.png");
	/*Player X, Y, Weight, Height, Speed, Jamp, Verosity */
	Player player = { 0.0f,500.0f,50.0f,50.0f,5.0f,20.0f,15.0f };
	/* placeX ,X2,X3, placeY , placeW , placeH , PlaceMove,ScrollX,ScreenX */
	walkPlace Walkplace{ 0.0f,1330.0f,2760.0f,555.0f,1280.0f,165.0f,1.0f,0.0f,0.0f };
	/*DoorX, DoorY, DoorW, DoorH, Angle*/
	GoalDoor startdoor{ 700.0f,455.0f,50.0f,100.0f ,0.0f };
	GoalDoor goaldoor{ 3500.0f,455.0f,50.0f,100.0f ,0.0f };
	BackGround backSP{ 0.0f,1280.0f,2560.0f };
	VariousFlag isFlag = { 0 ,0,false,false,false,false,false,false };
	//isjamp, playeranime //SceneFlagC1, SceneFlagC2, SceneFlagC3, GameOverFlag, CleaFlag, CharFlag
	int sceneselect = 1;
	int prescene = sceneselect;
	int Color = RED, doorC = 0xffffffff;
	float DoorRightX = 0, DoorBottomY;
	float GoalDoorRightX = 0, GoalDoorBottomY;
	float PlayerRightX = 0, PlayerBottomY;
	float PlaceRightX, PlaceBottomY;
	int titleFlag = 0;
	int Timer = 20;
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
		DoorRightX = startdoor.DoorX + startdoor.DoorW;
		GoalDoorRightX = goaldoor.DoorX + goaldoor.DoorW;
		DoorBottomY = startdoor.DoorY + startdoor.DoorH;
		GoalDoorBottomY = goaldoor.DoorY + goaldoor.DoorH;
		PlayerBottomY = player.y + player.height;
		PlaceRightX = Walkplace.placeX + 1280;
		PlaceBottomY = Walkplace.placeY + Walkplace.placeH;
		Novice::ScreenPrintf(0, 0, "%d", titleFlag);
		Novice::ScreenPrintf(20, 0, "%f", Walkplace.placeX);
		/*enum scene {

			Title,
			tutorial,
			Game,
		}
		 Scene = Title;*/
		if (sceneselect != prescene) {
			switch (sceneselect)
			{
			case 1:

				break;
			case 2:

				break;
			case 3:

				break;




			default:
				break;
			}
		}
		prescene = sceneselect;
		switch (sceneselect)
		{
		case  1:
			Novice::ScreenPrintf(0, 100, "Push_to_Enter");
			Novice::DrawSprite(0, 0, Title[0], 1.0f, 1.0f, 0.0f, WHITE);
			Timer--;
			if (Timer > 0) {
				titleFlag = 1;
				Timer = 20;
				if (titleFlag == 1) {
					Novice::DrawSprite(0, 0, Title[1], 1.0f, 1.0f, 0.0f, WHITE);
				}
			}
			if (Timer <= 10) {
				titleFlag = 0;
			}if (titleFlag == 0) {

				//Novice::DrawSprite(0, 0, Title[0], 1.0f, 1.0f, 0.0f, WHITE);
			}
			//else { titleFlag = 0; }


			//Novice::DrawSprite(player.x, player.y, PlayerSprite0, 1.0f, 1.0f, 0.0f, WHITE);

			if (keys[DIK_RETURN]) {

				isFlag.SceneFlagC1 = true;
			}
			if (isFlag.SceneFlagC1 == true) {
				sceneselect = 2;
			}
			else {
				isFlag.SceneFlagC1 = false;
			}
			break;

		case 2:
			Novice::DrawSprite(0, 0, BackSprite[0], 1.0f, 1.0f, 0.0f, WHITE);

			Novice::ScreenPrintf(50, 150, "%d", isFlag.isjamp);
			player.speed = 5;
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
				isFlag.playeranime = 1;
			}
			else {
				isFlag.playeranime = 0;
			}
			if (player.y >= Walkplace.placeY - 50) {
				isFlag.isjamp = 0;
			}
			if (isFlag.isjamp == 0)
			{
				if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && !isFlag.isjamp) {

					player.jamp = player.verosity;
					isFlag.isjamp = 1;

				}
			}

			/*else {
				isJampFlag.isjamp = 0;
			}*/
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
			if (startdoor.DoorX <= PlayerRightX && player.x <= DoorRightX && DoorBottomY >= player.y && PlayerBottomY >= startdoor.DoorY) {
				/*if (DoorBottomY<= player.y && PlayerBottomY <= goaldoor.DoorY) {

				}*/
				Novice::ScreenPrintf(1100, 0, "PushToKeysENTER");
				if (keys[DIK_RETURN]) {
					Color = BLUE;
					isFlag.SceneFlagC2 = true;

				}



			}
			else {
				Color = RED;


			}


			Novice::DrawSprite((int)startdoor.DoorX, (int)startdoor.DoorY, StartDoor, 1.0f, 1.0f, 0.0f, doorC);
			Novice::DrawSprite((int)Walkplace.placeX, (int)Walkplace.placeY, PlaceSprite[0], 1.0f, 1.0f, 0.0f, WHITE);
			//Novice::DrawBox((int)goaldoor.DoorX, (int)goaldoor.DoorY, (int)goaldoor.DoorW, (int)goaldoor.DoorH, goaldoor.angle, GREEN, kFillModeSolid);
			if (isFlag.playeranime == 1) {
				Novice::DrawSprite((int)player.x, (int)player.y, PlayerSprite1, 1.0f, 1.0f, 0.0f, WHITE);
			}
			else {
				Novice::DrawSprite((int)player.x, (int)player.y, PlayerSprite0, 1.0f, 1.0f, 0.0f, WHITE);
			}

			//Novice::DrawBox((int)player.x, (int)player.y, (int)player.weight, (int)player.height, 0.0f, Color, kFillModeSolid);
			Novice::DrawBox((int)Walkplace.placeX, (int)Walkplace.placeY, (int)Walkplace.placeW * 3, (int)Walkplace.placeH, 0.0f, 0xffffff0f, kFillModeSolid);

			if (isFlag.SceneFlagC2 == true) {
				doorC = 0xffffff00;
				sceneselect = 3;
				Color = 0xff00ffff;
			}
			else {
				isFlag.SceneFlagC2 = false;

			}

			break;
		case 3://gamescene





			Novice::DrawSprite((int)Walkplace.placeX - (int)Walkplace.ScrollX, 0, BackSprite[0], 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite((int)Walkplace.placeX + 1280 - (int)Walkplace.ScrollX, 0, BackSprite[1], 1.0f, 1.0f, 0.0f, WHITE);
			Novice::DrawSprite((int)Walkplace.placeX + 2560 - (int)Walkplace.ScrollX, 0, BackSprite[2], 1.0f, 1.0f, 0.0f, WHITE);
			Novice::ScreenPrintf(50, 50, "%f\n", Walkplace.ScrollX);
			Novice::ScreenPrintf(50, 70, "%f", Walkplace.ScreenX);
			Novice::ScreenPrintf(50, 90, "playerposX=%f", player.x);
			Novice::ScreenPrintf(50, 110, "playerposY=%f", player.y);
			Novice::ScreenPrintf(50, 150, "%d", isFlag.isjamp);


			Walkplace.ScrollX = player.x - 1280.0f / 2.0f;

			player.y -= player.jamp;

			/*if (player.y > Walkplace.placeY - 50) {
				player.y = Walkplace.placeY - 50;
			}*/
			if (keys[DIK_RIGHT]) {
				player.x += player.speed;
				Walkplace.ScrollX -= player.speed;

			}
			if (keys[DIK_LEFT]) {

				Walkplace.ScrollX += player.speed;
				player.x -= player.speed;
				isFlag.playeranime = 1;
			}
			else {
				isFlag.playeranime = 0;

			}
			if (player.x <= 0) {
				player.x = 0;
			}


			if (player.y >= Walkplace.placeY - 50) {
				isFlag.isjamp = 0;
			}
			if (isFlag.isjamp == 0)
			{
				if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && !isFlag.isjamp) {

					player.jamp = player.verosity;
					isFlag.isjamp = 1;

				}
			}
			ColisionFunction(Walkplace.placeX - Walkplace.ScrollX, PlaceRightX - Walkplace.ScrollX, Walkplace.placeY, PlaceBottomY, PlayerRightX, player.y, PlayerBottomY, player.y, isFlag.isjamp);


			if (Walkplace.ScrollX <= 0) {
				Walkplace.ScrollX = 0;
			}
			if (Walkplace.ScrollX >= WORLD_WIDTH - 1280) {
				Walkplace.ScrollX = WORLD_WIDTH - 1280;
			}
			if (player.x >= WORLD_WIDTH - player.weight) {
				player.x = WORLD_WIDTH - player.weight;

			}
			if (Walkplace.ScreenX <= 1280 && Walkplace.ScreenX >= 1380 && isFlag.isjamp == 0) {
				player.y = Walkplace.placeY - 50;
			}
			if (Walkplace.placeX <= PlayerRightX && PlayerRightX && player.x <= Walkplace.placeX + Walkplace.placeW && Walkplace.placeY + Walkplace.placeH >= player.y && player.y + player.height >= Walkplace.placeY) {
				if (player.y >= Walkplace.placeY - 50) {
					player.y = Walkplace.placeY - 50;
					isFlag.isjamp = 0;
				}
			}
			if (Walkplace.placeX2 <= PlayerRightX && PlayerRightX && player.x <= Walkplace.placeX2 + Walkplace.placeW && Walkplace.placeY + Walkplace.placeH >= player.y && player.y + player.height >= Walkplace.placeY) {
				if (player.y >= Walkplace.placeY - 50) {
					player.y = Walkplace.placeY - 50;
					isFlag.isjamp = 0;
				}

			}
				if (goaldoor.DoorX <= PlayerRightX && player.x <= GoalDoorRightX && GoalDoorBottomY >= player.y && PlayerBottomY >= goaldoor.DoorY) {
					/*if (DoorBottomY<= player.y && PlayerBottomY <= goaldoor.DoorY) {

					}*/
					Novice::ScreenPrintf(1100, 0, "PushToKeysENTER");
					if (keys[DIK_RETURN]) {
						Color = BLUE;
						isFlag.ClearFlag = true;

					}



				}

				Walkplace.ScreenX = player.x - Walkplace.ScrollX;

				Novice::DrawSprite((int)Walkplace.placeX - (int)Walkplace.ScrollX, (int)Walkplace.placeY, PlaceSprite[0], 1.0f, 1.0f, 0.0f, WHITE);
				Novice::DrawSprite((int)Walkplace.placeX + 1380 - (int)Walkplace.ScrollX, (int)Walkplace.placeY, PlaceSprite[1], 1.0f, 1.0f, 0.0f, WHITE);//1280
				Novice::DrawSprite((int)Walkplace.placeX + 2760 - (int)Walkplace.ScrollX, (int)Walkplace.placeY, PlaceSprite[2], 1.0f, 1.0f, 0.0f, WHITE);//2560
				Novice::DrawSprite((int)goaldoor.DoorX - (int)Walkplace.ScrollX, (int)goaldoor.DoorY, GoolDoor_, 1.0f, 1.0f, 0.0f, WHITE);


				if (isFlag.playeranime == 1) {
					Novice::DrawSprite((int)Walkplace.ScreenX, (int)player.y, PlayerSprite1, 1.0f, 1.0f, 0.0f, WHITE);
				}
				else {
					Novice::DrawSprite((int)Walkplace.ScreenX, (int)player.y, PlayerSprite0, 1.0f, 1.0f, 0.0f, WHITE);
				}
				//Novice::DrawBox((int)player.x, (int)player.y, (int)player.weight, (int)player.height, 0.0f, Color, kFillModeSolid);
				//Novice::DrawBox((int)Walkplace.placeX - (int)Walkplace.ScrollX, (int)Walkplace.placeY, (int)Walkplace.placeW * 3, (int)Walkplace.placeH, 0.0f, 0xffffff0f, kFillModeSolid);
				//Novice::DrawSprite((int)goaldoor.DoorX, (int)goaldoor.DoorY, StartDoor, 1.0f, 1.0f, 0.0f, doorC);











				if (isFlag.ClearFlag == true) {
					sceneselect = 4;
				}


				break;
		case 4://クリア
			Novice::DrawSprite(0, 0, ClearSprite, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::ScreenPrintf(0, 0, "Push_to_Enter");
			if (keys[DIK_RETURN] && !preKeys[DIK_SPACE]) {
				sceneselect = 1;

			}
			break;

			}



















			//break;



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


