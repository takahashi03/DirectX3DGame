#pragma once
#include "Window.h"

class App
{
public:
	App();
	// �}�X�^�\�t���[�� / ���b�Z�[�W���[�v
	int Go();
private:
	void DoFrame();
private:
	Window wnd;
};