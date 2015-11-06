#ifndef VIX_SDLINPUT_H
#define VIX_SDLINPUT_H

#include <vix_platform.h>
#include <vix_input.h>
#ifdef VIX_SYS_WINDOWS
#include <SDL.h>
#elif defined(VIX_SYS_LINUX)
#include <SDL2/SDL.h>
#endif#include <SDL.h>
#include <map>

#define MOUSECS_BUTTONS 3
#define MOUSECS_LEFT	0
#define MOUSECS_MIDDLE  1
#define MOUSECS_RIGHT	2

namespace Vixen {

	struct MouseClickState
	{
		Uint8 clicks;
		Uint8 state;
	};

	class VIX_API SDLMouseState
	{
	public:
		SDLMouseState();

		/*GETTERS*/
		const int  X() const;
		const int  Y() const;

		bool ButtonRelease(int button);
		bool ButtonPress(int button);
		bool SingleButtonPress(int button);

		/*State Methods*/
		void MouseMove(int x, int y);
		void MouseEvent(SDL_MouseButtonEvent mbEvent);
		void UpdatePrev();
	private:
		int					m_x;
		int					m_y;
		MouseClickState		m_current[MOUSECS_BUTTONS];
		MouseClickState		m_prev[MOUSECS_BUTTONS];
	};

	class VIX_API SDLKeyboardState
	{
		typedef std::map<SDL_Scancode, bool> KeyState;

	public:
		SDLKeyboardState();

		void KeyDown(SDL_Scancode code);
		void KeyUp(SDL_Scancode code);
		void UpdatePrev();
		bool KeyPress(IKEY key);
		bool SingleKeyPress(IKEY key);
	private:
		KeyState  m_current;
		KeyState  m_previous;

		SDL_Scancode convertFromIKEY(IKEY key);
	};

}

#endif
