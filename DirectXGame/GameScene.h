#pragma once
#include <KamataEngine.h>
class GameScene 
{
public:

	void Initialize();

	void Update();

	void Draw();

	uint32_t texturHandle_ = 0;

	KamataEngine::Sprite* sprite_ = nullptr;

};
