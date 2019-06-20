#include "App.h"
#include <sstream>
#include <iomanip>

App::App()
	:
	window(800, 600, "Title")
{}

int App::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	window.Gfx().ClearBuffer(c, c, 1.0f);
	window.Gfx().DrawTestTriangle(
		timer.Peek(),
		window.mouse.GetPosX() / 400.0f - 1.0f,
		-window.mouse.GetPosY() / 300.0f + 1.0f
	);
	window.Gfx().EndFrame();
}