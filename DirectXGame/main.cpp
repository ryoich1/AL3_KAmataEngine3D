#include <Windows.h>
#include <KamataEngine.h>
#include "GameScene.h"

using namespace KamataEngine;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
	KamataEngine::Initialize(L"GC2C_11_モトハシ_リョウイチ");

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	GameScene* gameScene = new GameScene();
	gameScene->Initialize();

	while (true) {
		if (KamataEngine::Update()) {
			break;
		}

		gameScene->Update();

		dxCommon->PreDraw();

		gameScene->Draw();

		dxCommon->PostDraw();
	};

	delete gameScene;
	gameScene = nullptr;
	KamataEngine::Finalize();

	//何かしらの変更

	return 0;
}
