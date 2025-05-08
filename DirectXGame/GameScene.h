#pragma once
#include <KamataEngine.h>
#include <vector>

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

	std::vector<WorldTransform*> worldTransformBlocks_;

};
