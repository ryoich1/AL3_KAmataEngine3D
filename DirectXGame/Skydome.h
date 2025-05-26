#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

class Skydome {

	public:

		void Initialize(Model* model, Camera* camera);

		void Update();

		void Draw();

	private:

		KamataEngine::WorldTransform worldTransform_;

		KamataEngine::Model* model_ = nullptr;

		KamataEngine::Camera* camera_ = nullptr;

};
