#pragma once
#include "Window.h"
#include "MyTimer.h"

class App
{
public:
	App();
	// マスタ―フレーム / メッセージループ
	int Go();
private:
	void DoFrame();
private:
	Window window;
	MyTimer timer;
};