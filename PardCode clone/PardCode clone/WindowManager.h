#pragma once
#include "Window.h"

class WindowManager
{
public:
	static void initialize();
	static void destroy();
	static WindowManager* get();

	void registerWindow(Window* window);
	Window* getCurrentWindow();
private:
	WindowManager();
	static WindowManager* sharedInstance;
	WindowManager(WindowManager const&) {}
	WindowManager& operator=(WindowManager const&) {};
	~WindowManager();

private:
	Window* m_window = NULL;
};

