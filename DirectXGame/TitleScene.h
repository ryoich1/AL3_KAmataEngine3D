#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;
class TitleScene {

public:

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

};
