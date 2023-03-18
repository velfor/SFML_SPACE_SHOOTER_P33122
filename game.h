#pragma once
#include "settings.h"
#include "player.h"
#include "meteor.h"
#include <vector>
#include "textobj.h"

class Game {
private:
	sf::RenderWindow window;
	Player player;
	std::vector<Meteor*> meteorSprites;
	TextObj lives;
	sf::RectangleShape rect;

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed) window.close();
	}

	void update() {
		player.update();
		for (auto m : meteorSprites) {
			m->update();
		}
		lives.update(std::to_string(player.getLives()));
	}

	void checkCollisions() {}

	void draw() {
		window.clear();
		player.draw(window);
		for (auto m : meteorSprites) {
			window.draw(m->getSprite());
		}
		window.draw(rect);
		window.draw(lives.getText());
		window.display();
	}

public:
	Game() : 
		window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE),
		lives(std::to_string(player.getLives()), sf::Vector2f{WINDOW_WIDTH/2,0.f})
	{
		window.setFramerateLimit(FPS);
		meteorSprites.reserve(METEOR_QTY);
		for (int i = 0; i < METEOR_QTY; i++) {
			meteorSprites.push_back(new Meteor());
		}
		rect.setFillColor(sf::Color::Green);
		rect.setSize(sf::Vector2f{ WINDOW_WIDTH, 40.f });
	}

	void play() {
		while (window.isOpen())
		{
			checkEvents();
			update();
			checkCollisions();
			draw();
		}
	}
};