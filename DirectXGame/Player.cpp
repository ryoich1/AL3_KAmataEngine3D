#include "Player.h"
#include "cassert"
#include "MyMath.h"
#include "GameScene.h"

using namespace KamataEngine;

void Player::Initialize(Model* model,Camera* camera) {

	assert(model);

	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();
	model_ = Model::CreateFromOBJ("skydome", true);

}

void Player::Updete() { 

	worldTransform_.TransferMatrix(); 

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

}

void Player::Draw() { model_->Draw(worldTransform_, *camera_); }
