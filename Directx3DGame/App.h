#pragma once
#include "Window.h"

class App
{
public:
	App();
	// マスタ―フレーム / メッセージループ
	int Go();
private:
	void DoFrame();
private:
	Window wnd;
};