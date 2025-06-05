#include "Player.h"
#include "cassert"
#include "MyMath.h"
#include "GameScene.h"
#include <numbers>

using namespace KamataEngine;

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
	//if (onGround_)

}

void Player::Draw() { model_->Draw(worldTransform_, *camera_); }
