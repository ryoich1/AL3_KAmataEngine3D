#pragma once
#include <KamataEngine.h>
class Skydome {

	public:

		void Initialize();

		void Update();

		void Draw();

	private:

		KamataEngine::WorldTransform worldTransform_;

		KamataEngine::Model* model_ = nullptr;

};
