#include "Skydome.h"
#include "cassert"

using namespace KamataEngine;

void Skydome::Initialize(/*Model* model, uint32_t textureHandle, Camera* camera*/) {

	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;
	worldTransform_.Initialize();
}

void Skydome::Update() { worldTransform_.TransferMatrix(); }

void Skydome::Draw() { /*model_->Draw(worldTransform_, *camera_, textureHandle_*/; 
//model_->Draw(worldTransform_, camera_);
}
