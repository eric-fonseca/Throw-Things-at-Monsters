#include <vix_game.h>
#include <vector>

#include "screenmanager.h"

#define GLRENDERER ((GLRenderer*)m_renderer)

using namespace Vixen;

class TestGame : public IGame
{
public:
	TestGame();

	virtual void VOnStartup(void)    override;
	virtual void VOnUpdate(float dt) override;
	virtual void VOnRender(float dt) override;
	virtual void VOnShutdown(void)   override;

public:
	ScreenManager*  m_screenManager;
};

TestGame::TestGame()
	: IGame()
{
	
}


void TestGame::VOnStartup(void)
{
	m_screenManager = new ScreenManager(m_window, &m_content, m_keyboard, m_mouse);
}

void TestGame::VOnUpdate(float dt)
{
	m_screenManager->Update(dt);

}

void TestGame::VOnRender(float dt)
{
	m_screenManager->Render(GLRENDERER, dt);
	
}

void TestGame::VOnShutdown(void)
{

}

int main(int argc, char* argv[])
{
	TestGame game;

	return game.Run();
}