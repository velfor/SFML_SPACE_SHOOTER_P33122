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

	void checkCollisions() {
		sf::FloatRect playerHitBox = player.getHitBox();
		auto laserSprites = player.getLasers();
		for (auto& meteor : meteorSprites) {
			sf::FloatRect meteorHitBox = meteor->getHitBox();
			if (meteorHitBox.intersects(playerHitBox)) {
				meteor->spawn();
				player.receiveDamage(meteor->getDamage());
			}
			for (auto& laser : (*laserSprites)) {
				sf::FloatRect laserHitBox = laser->getHitBox();
				if (laserHitBox.intersects(meteorHitBox)) {
					//начисление очков за сбитые метеоры
					meteor->spawn();
					laser->setHit();
				}
			}
		}
		//удалить попавшие пули (у которых hit == true)
		//пройти список пуль с помощью итератора, удалить нужные пули
		(*laserSprites).remove_if([](Laser* laser) {return laser->isHited(); });

	}

	void draw() {
		window.clear();
		for (auto m : meteorSprites) {
			window.draw(m->getSprite());
		}
		window.draw(rect);
		player.draw(window);
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
		while (window.isOpen() && player.isAlive())
		{
			checkEvents();
			update();
			checkCollisions();
			draw();
		}
	}
};