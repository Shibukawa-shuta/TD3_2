#include "Player.h"
#include "ImGuiManager.h"
#include "Mymath.h"
#include <cassert>
void Player::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();

	worldTransform_.translation_ = {0.1f, -4.8f, 12.5f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {0.6f, 0.25f, 0.0f};
}

void Player::Update() {
	Move();

	ImGui::Begin("Player");
	ImGui::DragFloat3("tr", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransform_.scale_.x, 0.1f);
	ImGui::End();
	worldTransform_.UpdateMatrix();
}

void Player::Move() { 
	if (input_->PushKey(DIK_A) && worldTransform_.translation_.x > -9.0f + worldTransform_.scale_.x) {
		worldTransform_.translation_.x -= PlayerSpeed_;
	}
	if (input_->PushKey(DIK_D)&& worldTransform_.translation_.x < 9.0f - worldTransform_.scale_.x) {
		worldTransform_.translation_.x += PlayerSpeed_;
	}
	
}

void Player::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}