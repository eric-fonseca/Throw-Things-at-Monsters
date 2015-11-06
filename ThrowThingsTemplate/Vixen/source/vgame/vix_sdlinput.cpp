#include <vix_sdlinput.h>

namespace Vixen {

	/*************************MOUSE**************************/

	SDLMouseState::SDLMouseState()
	{
		m_x = 0;
		m_y = 0;
		m_current[MOUSECS_LEFT].state = SDL_RELEASED;
		m_current[MOUSECS_RIGHT].state = SDL_RELEASED;
		m_current[MOUSECS_MIDDLE].state = SDL_RELEASED;
		m_prev[MOUSECS_LEFT].state = SDL_RELEASED;
		m_prev[MOUSECS_RIGHT].state = SDL_RELEASED;
		m_prev[MOUSECS_MIDDLE].state = SDL_RELEASED;
		
	}

	const int SDLMouseState::X() const
	{
		return m_x;
	}

	const int SDLMouseState::Y() const
	{
		return m_y;
	}

	bool SDLMouseState::ButtonPress(int button)
	{
		if(button >= 3) {
			return false;
		}

		return m_current[button].state == SDL_PRESSED;
	}

	bool SDLMouseState::ButtonRelease(int button)
	{
		if(button >= 3) {
			return false;
		}

		return m_current[button].state == SDL_RELEASED && m_prev[button].state == SDL_PRESSED;
	}

	bool SDLMouseState::SingleButtonPress(int button)
	{
		if(button >= 3) {
			return false;
		}

		return m_current[button].state == SDL_PRESSED &&
			m_prev[button].state == SDL_RELEASED;
	}

	void SDLMouseState::MouseMove(int x, int y)
	{
		m_x = x;
		m_y = y;
	}

	void SDLMouseState::MouseEvent(SDL_MouseButtonEvent mbEvent)
	{
		switch(mbEvent.button)
		{
		case SDL_BUTTON_LEFT:
			m_current[MOUSECS_LEFT].state = mbEvent.state;
			m_current[MOUSECS_LEFT].clicks = mbEvent.clicks;
			break;

		case SDL_BUTTON_RIGHT:
			m_current[MOUSECS_RIGHT].state = mbEvent.state;
			m_current[MOUSECS_RIGHT].clicks = mbEvent.clicks;
			break;

		case SDL_BUTTON_MIDDLE:
			m_current[MOUSECS_MIDDLE].state = mbEvent.state;
			m_current[MOUSECS_MIDDLE].clicks = mbEvent.clicks;
			break;
		}
	}

	void SDLMouseState::UpdatePrev()
	{
		memcpy(m_prev, m_current, sizeof(m_current));
	}

	/*************************KEYBOARD***********************/

	SDLKeyboardState::SDLKeyboardState()
	{

	}

	void SDLKeyboardState::KeyDown(SDL_Scancode code)
	{
		m_current[code] = true;
	}

	void SDLKeyboardState::KeyUp(SDL_Scancode code)
	{
		m_current[code] = false;
	}

	void SDLKeyboardState::UpdatePrev()
	{
		m_previous = m_current;
	}

	bool SDLKeyboardState::KeyPress(IKEY key)
	{
		SDL_Scancode code = convertFromIKEY(key);
		return m_current[code];
	}

	bool SDLKeyboardState::SingleKeyPress(IKEY key)
	{
		SDL_Scancode code = convertFromIKEY(key);
		return m_current[code] && !m_previous[code];
	}

	SDL_Scancode SDLKeyboardState::convertFromIKEY(IKEY key)
	{
		switch (key)
		{
		case Vixen::IKEY::A:
			return SDL_SCANCODE_A;
		case Vixen::IKEY::B:
			return SDL_SCANCODE_B;
		case Vixen::IKEY::C:
			return SDL_SCANCODE_C;
		case Vixen::IKEY::D:
			return SDL_SCANCODE_D;
		case Vixen::IKEY::E:
			return SDL_SCANCODE_E;
		case Vixen::IKEY::F:
			return SDL_SCANCODE_F;
		case Vixen::IKEY::G:
			return SDL_SCANCODE_G;
		case Vixen::IKEY::H:
			return SDL_SCANCODE_H;
		case Vixen::IKEY::I:
			return SDL_SCANCODE_I;
		case Vixen::IKEY::J:
			return SDL_SCANCODE_J;
		case Vixen::IKEY::K:
			return SDL_SCANCODE_K;
		case Vixen::IKEY::L:
			return SDL_SCANCODE_L;
		case Vixen::IKEY::M:
			return SDL_SCANCODE_M;
		case Vixen::IKEY::N:
			return SDL_SCANCODE_N;
		case Vixen::IKEY::O:
			return SDL_SCANCODE_O;
		case Vixen::IKEY::P:
			return SDL_SCANCODE_P;
		case Vixen::IKEY::Q:
			return SDL_SCANCODE_Q;
		case Vixen::IKEY::R:
			return SDL_SCANCODE_R;
		case Vixen::IKEY::S:
			return SDL_SCANCODE_S;
		case Vixen::IKEY::T:
			return SDL_SCANCODE_T;
		case Vixen::IKEY::U:
			return SDL_SCANCODE_U;
		case Vixen::IKEY::V:
			return SDL_SCANCODE_V;
		case Vixen::IKEY::W:
			return SDL_SCANCODE_W;
		case Vixen::IKEY::X:
			return SDL_SCANCODE_X;
		case Vixen::IKEY::Y:
			return SDL_SCANCODE_Y;
		case Vixen::IKEY::Z:
			return SDL_SCANCODE_Z;
		case Vixen::IKEY::UP:
			return SDL_SCANCODE_UP;
		case Vixen::IKEY::DOWN:
			return SDL_SCANCODE_DOWN;
		case Vixen::IKEY::LEFT:
			return SDL_SCANCODE_LEFT;
		case Vixen::IKEY::RIGHT:
			return SDL_SCANCODE_RIGHT;
		case Vixen::IKEY::F1:
			return SDL_SCANCODE_F1;
		case Vixen::IKEY::F2:
			return SDL_SCANCODE_F2;
		case Vixen::IKEY::F3:
			return SDL_SCANCODE_F3;
		case Vixen::IKEY::F4:
			return SDL_SCANCODE_F4;
		case Vixen::IKEY::F5:
			return SDL_SCANCODE_F5;
		case Vixen::IKEY::F6:
			return SDL_SCANCODE_F6;
		case Vixen::IKEY::F7:
			return SDL_SCANCODE_F7;
		case Vixen::IKEY::F8:
			return SDL_SCANCODE_F8;
		case Vixen::IKEY::F9:
			return SDL_SCANCODE_F9;
		case Vixen::IKEY::F10:
			return SDL_SCANCODE_F10;
		case Vixen::IKEY::F11:
			return SDL_SCANCODE_F11;
		case Vixen::IKEY::F12:
			return SDL_SCANCODE_F12;
		default:
			return SDL_SCANCODE_0;
			break;
		}
	}

}