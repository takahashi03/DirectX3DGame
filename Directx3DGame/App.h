#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "ImguiManager.h"
#include "Camera.h"

class App
{
public:
	App();
	// マスタ―フレーム/ メッセージループ
	int Go();
	~App();
private:
	void DoFrame();
private:
	ImguiManager imgui;
	Window window;
	MyTimer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	float speed_factor = 1.0f;
	Camera cam;
	static constexpr size_t nDrawables = 180;
};