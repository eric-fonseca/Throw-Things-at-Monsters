#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <vix_contentmanager.h>
#include <vector>
#include <vix_sdlinput.h>
#include <vix_gamewindow.h>

#include "gamescreen.h"
#include "titlescreen.h"
#include "gameplayscreen.h"

class ScreenManager
{
	typedef std::vector<GameScreen*> ScreenList;
public:
	ScreenManager(IGameWindow* window, ContentManager* content, SDLKeyboardState* keyboard, SDLMouseState* mouse);

	/*GETTERS*/
	ContentManager*  const ContentManager();
	SDLKeyboardState* const Keyboard();
	SDLMouseState* const Mouse();
	IGameWindow* const Window();

	TitleScreen* const		GetTitleScreen();
	GamePlayScreen* const   GetGamePlayScreen();

	void Update(float dt);
	void Render(GLRenderer* renderer, float dt);

	/*SCREEN UTILITIES*/

	void OpenNextScreen(GameScreen* current, GameScreen* next);
	void OpenPrevScreen(GameScreen* current);

private:
	ScreenList					m_screens;
	TitleScreen*				m_titleScreen;
	GamePlayScreen*				m_gamePlayScreen;
	Vixen::ContentManager*		m_content;
	Vixen::SDLKeyboardState*	m_keyboard;
	Vixen::SDLMouseState*       m_mouse;
	Vixen::IGameWindow*         m_window;
};

#endif