#include <SFML/Graphics.hpp>
#include <resources/Cfg.h>

sf::RenderWindow gwnd{ sf::VideoMode(sf::Vector2u{640U,480U},32U), "Balls_One", sf::State::Fullscreen, {} };
sf::Clock gtimer{};
int UnloadProgram();
int InitProgram();
int HandleEvent(const std::optional<sf::Event> evt_);
int ProcessStateInput(float gameTime_);
int Update(float gameTime_);
int RenderScene();

int main(int argc, char* argv[])
{
	int result = InitProgram();

	if (result >= 0) { return result; }
	while (gwnd.isOpen())
	{
		while (const auto event = gwnd.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				gwnd.close();

			if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
				if (keyReleased->scancode == sf::Keyboard::Scancode::Escape)
					gwnd.close();

			result = HandleEvent(event);
			if (result >= 0) { return result; }
		//	sceneMgr.handleEvent(&event);
		}

	//	sceneMgr.handleInput();

		auto gameTime = gtimer.restart().asSeconds();
		result = ProcessStateInput(gameTime);
		if (result >= 0) { return result; }
		result = Update(gameTime);
		if (result >= 0) { return result; }
		//	sceneMgr.update(gameTime);

		if (gwnd.isOpen())
		{
			result = RenderScene();
			if (result >= 0) { return result; }
		}
	}

	
	result = UnloadProgram();
	if (result >= 0)
		return result;
	else
		return 143;

}

/// <summary>
/// This is for loading initial assets and stuff in Cfg::
/// </summary>
/// <returns></returns>
int InitProgram()
{
	Cfg::Initialize();
	gtimer.restart();
	return -1;
}

int HandleEvent(const std::optional<sf::Event> evt_)
{
	return -2;
}

int ProcessStateInput(float gameTime_)
{
	return -3;
}

int Update(float gameTime_)
{
	return -4;
}

int RenderScene()
{
	gwnd.clear(sf::Color::Blue);



	gwnd.display();
	return -5;
}

int UnloadProgram()
{
	// delete any heap variables for main program or global
	return -6;
}