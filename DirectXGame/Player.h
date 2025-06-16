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

	Vector3 Velocity_ = {};

	static inline const float kAcceleration = 0.05f;
	static inline const float kAttenuation = 0.05f;
	static inline const float kLimitRunSpeed = 0.5f;

	enum class LRDirection {

		kRight,
		kLeft,

	};
	LRDirection lrDirection_ = LRDirection::kRight;

	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;
	static inline const float kTimeTurn = 0.3f;

	bool onGround_ = true;

	static inline const float kGravityAcceleration = 0.25;
	static inline const float kLimitFallSpeed = 1.0f;
	static inline const float kJumpAcceleration = 2.0f;

};