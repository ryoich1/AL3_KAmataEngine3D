#pragma once
#include <KamataEngine.h>
#include <array>
#include <numbers>

using namespace KamataEngine;
using namespace MathUtility;

class DeathParticles {

public:

    void Initialize(Model* model, Camera* camera, const Vector3& position);

	void Update();

	void Draw();

	bool IsFinished() const { return finished_; }

private:

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	static inline const uint32_t kNumParticles = 8;

	std::array<WorldTransform, kNumParticles> worldTransforms_;

	static inline const float kDuration = 0.5f;

	static inline const float kSpeed = 0.5f;

	static inline const float kAngleUnit = 2.0f * std::numbers::pi_v<float> / kNumParticles;

	bool finished_ = false;

	float counter_ = 0.0f;

	ObjectColor objevtColor_;

	Vector4 color_;

};
