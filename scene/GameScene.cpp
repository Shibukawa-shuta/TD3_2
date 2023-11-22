#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandleBG_ = TextureManager::Load("screen.png");
	spriteBG_ = Sprite::Create(textureHandleBG_, {0, 0});


	// ワールド
	worldTransform_.Initialize();
	viewProjection_.translation_ = {0.0f, 0.0f, 0.0f};
	viewProjection_.rotation_ = {0.0f,0.0f,0.0f};

	//
	viewProjection_.Initialize();

	//プレイヤー
	Player_ = std::make_unique<Player>();
	PlayerModel_.reset(Model::CreateFromOBJ("PlayerBox", true));
	Player_->Initialize(PlayerModel_.get());
	//弾
	Bullet_ = std::make_unique<Bullet>();
	BulletModel_.reset(Model::CreateFromOBJ("PlayerBox", true));
	Bullet_->Initialize(BulletModel_.get());

	// プレイヤー
	Block_ = std::make_unique<Block>();
	BlockModel_.reset(Model::CreateFromOBJ("PlayerBox", true));
	Block_->Initialize(BlockModel_.get());
}

void GameScene::Update() { 
	Player_->Update();
	Bullet_->Update();
	Block_->Update();

	Bullet_->SetY(Player_->GetY());
	Bullet_->SetX(Player_->GetX());
	Bullet_->SetS(Player_->GetS());
	worldTransform_.UpdateMatrix();
}

void GameScene::GameDraw2Dback() { 
	spriteBG_->Draw(); 
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	GameDraw2Dback();
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	Player_->Draw(viewProjection_);
	Bullet_->Draw(viewProjection_);
	Block_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
