#pragma once
#include "Window.h"
#include "MyTimer.h"

class App
{
public:
	App();
	// �}�X�^�\�t���[��/ ���b�Z�[�W���[�v
	int Go();
	~App();
private:
	void DoFrame();
private:
	Window window;
	MyTimer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 180;
};