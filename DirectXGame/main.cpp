#include <Windows.h>
#include <KamataEngine.h>
#include "GameScene.h"
#include "TitleScene.h"

using namespace KamataEngine;

GameScene* gameScene = nullptr;
TitleScene* titleScene = nullptr;

enum class Scene {

	kUnknown = 0,

	kTitle,
	kGame,

};

Scene scene = Scene::kUnknown;

void ChangeScene() {

	switch (scene) {

	case Scene::kTitle:

		if (titleScene->IsFinished()) {
		
			scene = Scene::kGame;

			delete titleScene;
			titleScene = nullptr;

			gameScene = new GameScene;
			gameScene->Initialize();

		}
		break;
	case Scene::kGame:

		if (gameScene->IsFinished()) {
		
		    scene = Scene::kTitle;

			delete gameScene;
			gameScene = nullptr;

			titleScene = new TitleScene;
			titleScene->Initialize();

		}
		break;

	}

}

void UpdataScene() {

	switch (scene) {

	case Scene::kTitle:
		titleScene->Update();
		break;

	case Scene::kGame:
		gameScene->Update();
		break;
	}

}

void DrawScene() {

	switch (scene) {

	case Scene::kTitle:
		titleScene->Draw();
		break;

	case Scene::kGame:
		gameScene->Draw();
		break;
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
	KamataEngine::Initialize(L"GC2C_11_モトハシ_リョウイチ");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	scene = Scene::kTitle;
	titleScene = new TitleScene;
	titleScene->Initialize();

	while (true) {
		if (KamataEngine::Update()) {
			break;
		}

		ChangeScene();

		UpdataScene();

		dxCommon->PreDraw();

		DrawScene();

		dxCommon->PostDraw();

	};

	delete gameScene;
	delete titleScene;
	KamataEngine::Finalize();

	//何かしらの変更

	return 0;
}
