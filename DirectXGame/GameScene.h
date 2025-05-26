#pragma once
#include <KamataEngine.h>
#include <vector>
#include "Skydome.h"

class GameScene 
{
public:

	~GameScene();

	void Initialize();

	void Update();

	void Draw();

private:
	uint32_t textureHandle_ = 0;

	KamataEngine::Model* modelBlock_ = nullptr;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Camera camera_;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	bool isDebugCameraActive_ = false;

	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	Skydome* skydome_ = nullptr;

	KamataEngine::Model* modelSkydome_ = nullptr;

};
