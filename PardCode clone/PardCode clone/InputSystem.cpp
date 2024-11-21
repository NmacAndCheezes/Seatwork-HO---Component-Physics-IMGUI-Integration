#include "InputSystem.h"
#include <Windows.h>
#include "Editor UI/imgui-master/imgui.h"
InputSystem* InputSystem::sharedInstance = nullptr;

InputSystem::InputSystem()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);
	m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
}
void InputSystem::update()
{
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);

	if (current_mouse_pos.x != m_old_mouse_pos.m_x ||
		current_mouse_pos.y != m_old_mouse_pos.m_y)
	{
		//HAS MOUSE EVENT
		std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

		while (it != m_set_listeners.end())
		{
			(*it)->onMouseMove(Point( current_mouse_pos.x, current_mouse_pos.y ));
			++it;
		}
	}

	m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);

	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			//KEY IS DOWN
			if (m_keys_state[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
				
				while (it != m_set_listeners.end())
				{
					if (i == VK_LBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
						{
							(*it)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
							m_left_mouse_down = true;
						}
					}
					else if (i == VK_RBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
						{
							(*it)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
							m_right_mouse_down = true;
						}
					}
					else
					{
						(*it)->onKeyDown(i);
					}
					
					++it;
				}
			} 
			else //KEY IS UP
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

					while (it != m_set_listeners.end())
					{
						if (i == VK_LBUTTON)
						{
							(*it)->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
							m_left_mouse_down = false;
						}
						else if (i == VK_RBUTTON)
						{
							(*it)->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
							m_right_mouse_down = false;
						}
						else
						{
							(*it)->onKeyUp(i);
						}
						
						++it;
					}
				}
			}
		}
		//store current state to old
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListner(InputListener* listener)
{
	m_set_listeners.insert(listener);
}

void InputSystem::removeListner(InputListener* listener)
{
	m_set_listeners.erase(listener);
}

bool InputSystem::isKeyDown(int key)
{
	for (int i = 0; i < ARRAYSIZE(this->m_keys_state); i++) {
		if (this->m_keys_state[i] & 0x80 && i == key) {
			return true;
		}
		else if (i == key) {
			return false;
		}
	}


	return false;
}

bool InputSystem::isKeyUp(int key)
{
	for (int i = 0; i < ARRAYSIZE(this->m_keys_state); i++) {
		if (!(this->m_keys_state[i] & 0x80) && i == key) {
			return true;
		}
		else if (i == key) {
			return false;
		}
	}

	return false;
}

void InputSystem::setCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

InputSystem* InputSystem::get()
{
	static InputSystem system;
	return &system;
}

void InputSystem::initialize()
{
	InputSystem::sharedInstance = new InputSystem();
}

void InputSystem::destroy()
{
	if (!InputSystem::sharedInstance) return;
	delete InputSystem::sharedInstance;
}

InputSystem::~InputSystem()
{
	InputSystem::sharedInstance = nullptr;
}
