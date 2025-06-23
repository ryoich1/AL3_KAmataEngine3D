#pragma once
#include <KamataEngine.h>

class Player;
class CameraController {

public:

	void Initialize();

	void Update();

	void SetTarget(Player* target) { target_ = target; }

	void Reset();

	const KamataEngine::Camera& GetViewProjection() const { return camera_; }

	struct Rect {

		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0f;
	};

	Rect movableArea_ = {0, 100, 0, 100};

	void SetMovableArea(Rect area) { movableArea_ = area; }

private:

	KamataEngine::Camera camera_;

	Player* target_ = nullptr;

	KamataEngine::Vector3 targetOffset_ = {0, 0, -15.0f};

	KamataEngine::Vector3 targetCoordinate;

	static inline const float kInterpolationRate = 5.0f;

	static inline const float kVelocityBias = 30.0f;

	static inline const Rect targetMargin = {-9.0f, 9.0f, -5.0f, 5.0f};

};
