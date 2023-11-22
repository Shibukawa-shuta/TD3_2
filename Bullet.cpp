#include "ImGuiManager.h"
#include "Mymath.h"
#include "Bullet.h"
#include <cassert>
void Bullet::Initialize(Model* model) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();

	worldTransform_.translation_ = {0.1f, 0.0f, 12.5f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {0.2f, 0.2f, 0.0f};
}

void Bullet::Update() {
	Move();
	Space();
	ImGui::Begin("Bullet");
	ImGui::DragFloat3("tr", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat3("rot", &worldTransform_.rotation_.x, 0.1f);
	ImGui::DragFloat3("sc", &worldTransform_.scale_.x, 0.1f);

	ImGui::DragFloat3("PlayerY", &PlayerX_, 0.1f);
	ImGui::End();
	worldTransform_.UpdateMatrix();
}

void Bullet::Space() { 
		worldTransform_.translation_.y += BulletSpeedY_;
		worldTransform_.translation_.x += BulletSpeedX_;
	    worldTransform_.rotation_.z += rotSpeed_;
}

void Bullet::Move() { 
	if (worldTransform_.translation_.x > 9.0f || worldTransform_.translation_.x < -9.0f) {
		BulletSpeedX_ *= -1.0f;
		rotSpeed_ *= -1.0f;
	}
	if (worldTransform_.translation_.y > 5.0f) {
		BulletSpeedY_ *= -1.0f;
	}
	if (worldTransform_.translation_.y < -5.0f) {
		BulletSpeedY_ = 0.0f;
		BulletSpeedX_ = 0.0f;
	}
	if (worldTransform_.translation_.y <= PlayerY_+0.5f && (worldTransform_.translation_.x >= PlayerX_-(PlayerS_)) && (worldTransform_.translation_.x <= PlayerX_+(PlayerS_))) {
		BulletSpeedY_ *= -1.0f;
	}

	/*if ((worldTransform_.translation_.x < PlayerX_ - (PlayerS_)) &&
	    (worldTransform_.translation_.x > PlayerX_ + (PlayerS_)) &&
	    worldTransform_.translation_.y <= PlayerY_) {
		BulletSpeedY_ *= -1.0f;
	}*/
}

void Bullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}