
#define NOMINMAX
#include "cassert"
#include "MyMath.h"
#include "GameScene.h"
#include <numbers>
#include <algorithm>

using namespace KamataEngine;
using namespace MathUtility;

void Player::Initialize(Model* model, Camera* camera,Vector3& position) {

	assert(model);

	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	worldTransform_.rotation_.y = std::numbers::pi_v<float>/2.0f;
	

}

void Player::Update() { 

	worldTransform_.TransferMatrix(); 

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	//移動入力、設置状態
	if (onGround_) {
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {

			Vector3 accelaration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				accelaration.x += kAcceleration;
				if (Velocity_.x < 0.0f) {
					Velocity_.x *= (1.0f - kAttenuation);
				}
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}
			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				accelaration.x -= kAcceleration;
				if (Velocity_.x > 0.0f) {
					Velocity_.x *= (1.0f - kAttenuation);
				}
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}
			}
			Velocity_ += accelaration;
			Velocity_.x = std::clamp(Velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

		} else {
			Velocity_.x *= (1.0f - kAttenuation);
		}
		if (Input::GetInstance()->PushKey(DIK_UP)) {
			Velocity_ += Vector3(0, kJumpAcceleration, 0);
		}

	} else {
	
		Velocity_ += Vector3(0, -kGravityAcceleration, 0);
		Velocity_.y = std::max(Velocity_.y, -kLimitFallSpeed);

	}

	bool landing = false;

	if (Velocity_.y < 0) {
		if (worldTransform_.translation_.y <= 1.0f) {
			landing = true;
		}
	}

	if (onGround_) {
		if (Velocity_.y > 0.0f) {
			onGround_ = false;
		}
	} else {
	
	    if(landing) {
			worldTransform_.translation_.y = 1.0f;
			Velocity_.x *= (1.0f - kAttenuation);
			Velocity_.y = 0.0f;
			onGround_ = true;
	    }
	
	}

	worldTransform_.translation_ += Velocity_;

	if (turnTimer_ > 0.0f) {
	
		turnTimer_ -= 1.0f / 60.0f;

		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};

		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		worldTransform_.rotation_.y = EaseInOut(destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);

	}

}

void Player::Draw() { model_->Draw(worldTransform_, *camera_); }
