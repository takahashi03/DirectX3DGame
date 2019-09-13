#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "ImguiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include <set>

class App
{
public:
	App();
	int Go();
	~App();
private:
	void DoFrame();
private:
	ImguiManager imgui;
	Window window;
	MyTimer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	std::vector<class Box*> boxes;
	float speed_factor = 1.0f;
	Camera cam;
	PointLight light;
	static constexpr size_t nDrawables = 180;
	std::optional<int> comboBoxIndex;
	std::set<int> boxControlIds;
};