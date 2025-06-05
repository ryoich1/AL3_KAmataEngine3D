#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

class Player {

public:

	void Update();

	void Draw();

	void Initialize(Model* model, Camera* camera, Vector3& position);

private:

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::WorldTransform worldTransform_;

	Camera* camera_ = nullptr;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

};