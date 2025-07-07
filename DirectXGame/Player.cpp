#define NOMINMAX
#include "cassert"
#include "MyMath.h"
#include "GameScene.h"
#include <numbers>
#include <algorithm>
#include "MapChipField.h"

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

	//1.移動入力
	InputMove();

	//2.移動量を加味して衝突判定する
	CollisionMapInfo collisionMapInfo;
	collisionMapInfo.move = Velocity_;
	CheckMapCollision(collisionMapInfo);

	//3.判定結果を反映して移動させる
	CheckMapMove(collisionMapInfo);

	//4.天井に接触している場合の処理
	CheckMapCeiling(collisionMapInfo);

	//5.壁に接触している場合の処理

	//6.設置状態の切り替え

	//設置フラグ
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

	AnimateTurn();

	worldTransform_.TransferMatrix();

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	if (turnTimer_ > 0.0f) {
	
		turnTimer_ -= 1.0f / 60.0f;

		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};

		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		worldTransform_.rotation_.y = EaseInOut(destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);

	}

}

void Player::Draw() { model_->Draw(worldTransform_, *camera_); }

void Player::InputMove() {

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

}

void Player::AnimateTurn() {

	float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};

	float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

	worldTransform_.rotation_.y = EaseInOut(destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);

}

void Player::CheckMapCollision(CollisionMapInfo& Info) {

	CheckMapCollisionUp(Info);
	CheckMapCollisionDown(Info);
	/*CheckMapCollisionRight(Info);
	CheckMapCollisionLeft(Info);*/

}

void Player::CheckMapCollisionUp(CollisionMapInfo& Info) {

	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + Info.move, static_cast<Corner>(i));
	}

	if (Info.move.y <= 0) {
		return;
	}

	MapChipType mapChipType;
	MapChipType mapChipTypeNext;
	bool hit = false;
	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex + 1);
	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {
		hit = true;
	}

	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightTop]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex + 1);
	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {
		hit = true;
	}

	if (hit) {
	
	    indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Info.move + Vector3(0, +kHeight / 2.0f, 0));
		MapChipField::IndexSet indexSetNow;
		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3(0, +kHeight / 2.0f, 0));
		if (indexSetNow.yIndex != indexSet.yIndex) {
			MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
			Info.move.y = std::max(0.0f, rect.bottom - worldTransform_.translation_.y - (kHeight / 2.0f + kBlank));
			Info.ceiling = true;
		}
	}
}

void Player::CheckMapCollisionDown(CollisionMapInfo& Info) {

	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {
		positionsNew[i] = CornerPosition(worldTransform_.translation_ + Info.move, static_cast<Corner>(i));
	}

	if (Info.move.y >= 0) {
		return;
	}

	MapChipType mapChipType;
	MapChipType mapChipTypeNext;
	bool hit = false;

	MapChipField::IndexSet indexSet;
	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kLeftBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex - 1);
	if (mapChipType == MapChipType::kBlock&&mapChipTypeNext!=MapChipType::kBlock) {
		hit = true;
	}

	indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[kRightBottom]);
	mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);
	mapChipTypeNext = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex - 1);
	if (mapChipType == MapChipType::kBlock && mapChipTypeNext != MapChipType::kBlock) {
		hit = true;
	}

	if (hit) {

		indexSet = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Info.move + Vector3(0, -kHeight / 2.0f, 0));
		MapChipField::IndexSet indexSetNow;
		indexSetNow = mapChipField_->GetMapChipIndexSetByPosition(worldTransform_.translation_ + Vector3(0, -kHeight / 2.0f, 0));
		if (indexSetNow.yIndex != indexSet.yIndex) {
			MapChipField::Rect rect = mapChipField_->GetRectByIndex(indexSet.xIndex, indexSet.yIndex);
			Info.move.y = std::min(0.0f, rect.top - worldTransform_.translation_.y + (kHeight / 2.0f + kBlank));
			Info.landing = true;
		}
		
	}
}

void Player::CheckMapMove(const CollisionMapInfo& Info) {

	worldTransform_.translation_ += Info.move;

}

void Player::CheckMapCeiling(const CollisionMapInfo& Info) {

	if (Info.ceiling) {
		DebugText::GetInstance()->ConsolePrintf("hitceiling\n");
		Velocity_.y = 0;
	}

}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {

	Vector3 offsetTable[kNumCorner] =
	{
		{+kWidth / 2.0f, -kHeight / 2.0f, 0},
		{-kWidth / 2.0f, -kHeight / 2.0f, 0},
		{+kWidth / 2.0f, +kHeight / 2.0f, 0},
		{-kWidth / 2.0f, +kHeight / 2.0f, 0},
	};

	return center +offsetTable[static_cast<uint32_t>(corner)];
}
