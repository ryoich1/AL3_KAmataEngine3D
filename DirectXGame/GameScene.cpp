#include "GameScene.h"
#include"MyMath.h"

using namespace KamataEngine;

GameScene::~GameScene() { 
	delete modelBlock_; 

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();

	delete debugCamera_;

	delete modelSkydome_;

	delete skydome_;

	delete mapChipField_;

	delete player_;

	delete cameraController_;

	for (Enemy* enemy : enemies_) {
		delete enemy;
	}

	delete deathParticles_;

	delete fade_;

}

void GameScene::Initialize() {

	modelBlock_ = Model::CreateFromOBJ("block");

	worldTransform_.Initialize();

	camera_.Initialize();

	debugCamera_ = new DebugCamera(1280, 720);

	skydome_ = new Skydome();

	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	skydome_->Initialize(modelSkydome_, &camera_);

	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");

	GenerateBlocks();

	player_ = new Player();

	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1,18);

	modelPlayer_ = Model::CreateFromOBJ("player", true);
	player_->Initialize(modelPlayer_, &camera_, playerPosition);
	player_->SetmapChipField(mapChipField_);

	cameraController_ = new CameraController();
	cameraController_->Initialize();
	cameraController_->SetTarget(player_);
	cameraController_->Reset();

	CameraController::Rect cameraArea = {12.0f, 100 - 12.0f, 6.0f, 6.0f};
	cameraController_->SetMovableArea(cameraArea);

	model_ = Model::CreateFromOBJ("enemy", true);

	for (int32_t i = 0; i < 3; ++i) {
	
	    Enemy* newEnemy = new Enemy();
		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(6 + i, 18);
		newEnemy->Initialize(model_, &camera_, enemyPosition);

	    enemies_.push_back(newEnemy);
	}

	//deathParticles_ = new DeathParticles;
	modelDeathParticles_ = Model::CreateFromOBJ("deathParticle", true);
	//deathParticles_->Initialize(model_, &camera_, playerPosition);

	phase_ = Phase::kFadeIn;

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);

}

void GameScene::Update() {

	fade_->Update();

	switch (phase_) {

	case Phase::kPlay:

		/*if (player_->IsDead()) {

		    phase_ = Phase::kDeath;

		    const Vector3& deathParticlesPosition = player_->GetWorldPosition();

		    deathParticles_ = new DeathParticles;

		    deathParticles_->Initialize(model_, &camera_, deathParticlesPosition);
		}*/

		CheckAllCollisions();
		break;

	case Phase::kDeath:

		deathParticles_->Update();
		break;

	case Phase::kFadeIn:

		fade_->Update();
		break;

	case Phase::kFadeOut:

		fade_->Update();
		break;
	}

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}

			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

			worldTransformBlock->TransferMatrix();
		}
	}

	debugCamera_->Update();

	#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
	#endif

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;

		camera_.TransferMatrix();
	} else {
		camera_.UpdateMatrix();
		camera_.matView = cameraController_->GetViewProjection().matView;
		camera_.matProjection = cameraController_->GetViewProjection().matProjection;
		camera_.TransferMatrix();
	}

	skydome_->Update();

	player_->Update();

	cameraController_->Update();

	for (Enemy* enemy : enemies_) {
		enemy->Update();
	}

	CheckAllCollisions();

	if (deathParticles_) {
		deathParticles_->Update();
	}

	

	if (deathParticles_ && deathParticles_->IsFinished()) {
		finished_ = true;
	}

}

void GameScene::Draw() {

	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());

	skydome_->Draw();

	if (phase_ == Phase::kPlay || phase_ == Phase::kFadeIn) {
		player_->Draw();
	}

	for (Enemy* enemy : enemies_) {
		enemy->Draw();
	}

	modelBlock_->Draw(worldTransform_, camera_);

    for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}
		    modelBlock_->Draw(*worldTransformBlock, camera_);
		}
	}
	
	if (deathParticles_) {
		deathParticles_->Draw();
	}

	Model::PostDraw();

	fade_->Draw();

}

void GameScene::GenerateBlocks() {

	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	worldTransformBlocks_.resize(numBlockHorizontal);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j]=worldTransform;
				worldTransformBlocks_[i][j]->translation_ =mapChipField_->GetMapChipPositionByIndex(j,i);
			}
		}
	}
}

void GameScene::CheckAllCollisions() {

	#pragma region
	{
	
		AABB aabb1, aabb2;

		aabb1 = player_->GetAABB();

		for (Enemy* enemy : enemies_) {
		
		   aabb2 = enemy->GetAABB();

		   if (IsCollision(aabb1, aabb2)) {
		
		       player_->Oncollision(enemy);
			   enemy->OnCollision(player_);
		   
	      	}
		
		}
	
	}
    #pragma endregion

}
void GameScene::ChangePhase(){

	switch (phase_) {

	case Phase::kPlay:

		if (player_->IsDead() == true) {
		
		    phase_ = Phase::kDeath;
			const Vector3& deathParticlePosition = player_->GetWorldPosition();
			deathParticles_ = new DeathParticles;
			deathParticles_->Initialize(modelDeathParticles_, &camera_, deathParticlePosition);

		}	
		break;

	case Phase::kDeath:

		if (deathParticles_->IsFinished()) {
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
		}
		break;

	case Phase::kFadeIn:

		if (fade_->isFinished()) {
			phase_ = Phase::kPlay;
		}
		break;

	case Phase::kFadeOut:

		if (fade_->isFinished()) {
			finished_ = true;
		}
		break;

	}

}
