#include "DeathParticles.h"
#include "MyMath.h"
#include <algorithm>

void DeathParticles::Initialize(Model* model, Camera* camera, const Vector3& position) {

	//assert(model);

	model_ = model;
	camera_ = camera;
	for (WorldTransform& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}

	objevtColor_.Initialize();
	color_ = {1, 1, 1, 1};
	
}

void DeathParticles::Update() { 

	for (WorldTransform& worldTransform : worldTransforms_) {
		worldTransform.matWorld_ = MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);
		worldTransform.TransferMatrix();
	}

	for (uint32_t i = 0; i < kNumParticles; ++i) {
	
	    Vector3 velocity_ = {kSpeed, 0, 0};

		float angle = kAngleUnit * i;

		Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);

		velocity_ = Transform(velocity_, matrixRotation);

		worldTransforms_[i].translation_ += velocity_;
	
	}

	counter_ += 1.0f / 60.0f;

	if (counter_ >= kDuration) {
	
		counter_ = kDuration;
		finished_ = true;

	}

	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);
	objevtColor_.SetColor(color_);

	if (finished_) {
		return;
	}
}

void DeathParticles::Draw() {

	for (auto& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *camera_, &objevtColor_); 
	}

}
