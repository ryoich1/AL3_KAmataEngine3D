#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

class Player {

public:

	void Initialize(Model* model, uint32_t textureHandle, Camera* camera);

	void Updete();

	void Draw();

private:

	uint32_t textureHandle_ = 0u;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::WorldTransform worldTransform_;

	Camera* camera_ = nullptr;

};
