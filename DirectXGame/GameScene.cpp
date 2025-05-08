#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() { 
	delete modelBlock_; 

	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
		delete worldTransformBlock;
	}
	worldTransformBlocks_.clear();

}

void GameScene::Initialize() {

	const uint32_t kNumBlockHolizontal = 20;
	const float kBlockWidth = 2.0f;

	worldTransformBlocks_.resize(kNumBlockHolizontal);

	for (uint32_t i = 0; i < kNumBlockHolizontal; ++i) {
	
		worldTransformBlocks_[i] = new WorldTransform();
		worldTransformBlocks_[i]->Initialize();
		worldTransformBlocks_[i]->translation_.x = kBlockWidth * i;
		worldTransformBlocks_[i]->translation_.y = 0.0f;

	}

	/*textureHandle_ = TextureManager::Load("sample.png");

	modelBlock_ = Model::Create();

	worldTransform_.Initialize();

	camera_.Initialize();*/

}

void GameScene::Update() {

	for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
	

		worldTransformBlock->TransferMatrix();
	}

}

void GameScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	Model::PostDraw();

}