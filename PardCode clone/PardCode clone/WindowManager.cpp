#include "WindowManager.h"

WindowManager* WindowManager::sharedInstance = nullptr;

WindowManager::WindowManager()
{
}

void WindowManager::initialize()
{
	WindowManager::sharedInstance = new WindowManager();
}

void WindowManager::destroy()
{
	if (!WindowManager::sharedInstance) return;
	delete WindowManager::sharedInstance;
}

WindowManager* WindowManager::get()
{
	return sharedInstance;
}

void WindowManager::registerWindow(Window* window)
{
	m_window = window;
}

Window* WindowManager::getCurrentWindow()
{
	return m_window;
}

WindowManager::~WindowManager()
{
	m_window = NULL;
}
