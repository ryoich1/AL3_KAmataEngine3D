#pragma once
#include <KamataEngine.h>
class GameScene 
{
public:
	~GameScene();

	void Initialize();

	void Update();

	void Draw();

private:
	uint32_t texturHandle_ = 0;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Camera camera_;

};
