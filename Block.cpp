#include "Mymath.h"
#include "ImGuiManager.h"
#include "Block.h"
#include <cassert>

void Block::Initialize(Model* model) {
	assert(model);
	model_ = model;

	for (int i = 0; i < 100; i++) {

		worldTransform_[i].scale_ = {1.3f, 0.25f, 0.0f};
		worldTransform_[i].translation_ = {-7.5f, 4.5f, 12.5f};
		worldTransform_[i].rotation_ = {0.0f,0.0f,0.0f};
		worldTransform_[i].Initialize();
	}
}

void Block::Update() {
	for (int i = 0; i < 100; i++) {
		worldTransform_[i].UpdateMatrix();
	}

	for (int i = 0; i < 1; i++) {
		ImGui::Begin("Block");
		ImGui::DragFloat3("tr", &worldTransform_[i].translation_.x, 0.1f);
		ImGui::DragFloat3("rot", &worldTransform_[i].rotation_.x, 0.1f);
		ImGui::DragFloat3("sc", &worldTransform_[i].scale_.x, 0.1f);

		
		ImGui::End();
	}
}



void Block::Draw(const ViewProjection& viewProjection) {
	for (int i = 0; i < 100; i++) {
		if (alive_[i] == 0) {
			model_->Draw(worldTransform_[i], viewProjection);
		}
	}
}