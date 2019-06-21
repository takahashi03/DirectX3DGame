#pragma once
#include "Window.h"
#include "MyTimer.h"

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
	Window window;
	MyTimer timer;
	std::vector<std::unique_ptr<class Box>> boxes;
};