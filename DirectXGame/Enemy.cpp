#include "Enemy.h"
#include <numbers>
#include "MyMath.h"
#include "MapChipField.h"

using namespace KamataEngine;
using namespace MathUtility;

void Enemy::Initialize(Model* model, Camera* camera, Vector3& position) {

	assert(model);

	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	worldTransform_.rotation_.y = -std::numbers::pi_v<float> / 2.0f;

	velocity_ = {-kwalkSpeed, 0, 0};

	walkTimer_ = 0.0f;

}

void Enemy::Update() {

	walkTimer_ += 1.0f / 60.0f;

	worldTransform_.rotation_.x = std::sin(walkTimer_ * 5.0f);

	worldTransform_.translation_ += velocity_;

    worldTransform_.TransferMatrix();

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	if (turnTimer_ > 0.0f) {

		turnTimer_ -= 1.0f / 60.0f;

		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};

		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		worldTransform_.rotation_.y = EaseInOut(destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);
	}

}

void Enemy::Draw() { model_->Draw(worldTransform_, *camera_); }