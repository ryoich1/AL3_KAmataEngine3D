#include "Player.h"
#include "cassert"

using namespace KamataEngine;

void Player::Initialize(Model* model, uint32_t textureHandle, Camera* camera) {

	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;
	worldTransform_.Initialize();

}

void Player::Updete() {

	worldTransform_.TransferMatrix();

}

void Player::Draw() {

	model_->Draw(worldTransform_, *camera_, textureHandle_);

}
