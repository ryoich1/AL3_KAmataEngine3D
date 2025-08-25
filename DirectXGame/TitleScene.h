#pragma once
#include <KamataEngine.h>
#include"Fade.h"

using namespace KamataEngine;
class TitleScene {

public:

	enum class Phase {

		kFadeIn,
		kMain,
		kFadeOut,

	};

	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() const { return finished_; }

private:

	Model* model_ = nullptr;

	Model* modelPlayer_ = nullptr;

	Camera camera_;

    WorldTransform worldTransform_;

	WorldTransform worldTransformPlayer_;

	float rotate = 0.0f;

	bool finished_ = false;

	Fade* fade_ = nullptr;

	Phase phase_ = Phase::kFadeIn;

};
