#include "screenmanager.h"

ScreenManager::ScreenManager(Vixen::IGameWindow* window, Vixen::ContentManager* content, Vixen::SDLKeyboardState* keyboard, Vixen::SDLMouseState* mouse)
{
	m_content = content;
	m_keyboard = keyboard;
	m_mouse = mouse;
	m_window = window;

	m_titleScreen = new TitleScreen(this);
	m_gamePlayScreen = new GamePlayScreen(this);
	m_screens.push_back(m_titleScreen);
	m_screens.push_back(m_gamePlayScreen);

	m_titleScreen->SetState(ScreenState::TRANSON);
}

Vixen::ContentManager* const ScreenManager::ContentManager()
{
	return m_content;
}

Vixen::SDLKeyboardState* const ScreenManager::Keyboard()
{
	return m_keyboard;
}

Vixen::SDLMouseState* const ScreenManager::Mouse()
{
	return m_mouse;
}

Vixen::IGameWindow* const ScreenManager::Window()
{
	return m_window;
}

TitleScreen* const ScreenManager::GetTitleScreen()
{
	return m_titleScreen;
}

GamePlayScreen* const ScreenManager::GetGamePlayScreen()
{
	return m_gamePlayScreen;
}

void ScreenManager::Update(float dt)
{
	for(GameScreen*& screen : m_screens)
	{
		switch(screen->GetState())
		{
		case ScreenState::OFF:
		case ScreenState::PAUSED:
			//DO NOTHING
			break;

		case ScreenState::ACTIVE:
		case ScreenState::TRANSOFF:
		case ScreenState::TRANSON:
			//UPDATE
			screen->Update(dt);
			break;
		}
	}
}

void ScreenManager::Render(GLRenderer* renderer, float dt)
{
	for(GameScreen*& screen : m_screens)
	{
		switch(screen->GetState())
		{
			case ScreenState::OFF:
			//DO NOTHING
			break;

		case ScreenState::ACTIVE:
		case ScreenState::TRANSOFF:
		case ScreenState::TRANSON:
		case ScreenState::PAUSED:
			screen->Draw(renderer, dt);
			break;
		}
	}
}

void ScreenManager::OpenNextScreen(GameScreen* current, GameScreen* next)
{
	current->SetState(ScreenState::TRANSOFF);
	next->SetState(ScreenState::TRANSON);
	next->SetPrev(current);
}

void ScreenManager::OpenPrevScreen(GameScreen* current)
{
	current->SetState(ScreenState::TRANSOFF);
	current->GetPrev()->SetState(ScreenState::TRANSON);
}