#pragma once
#include "settings.h"
#include "laser.h"
#include <list>

class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speedx = 0.f;
	int lives = 3;
	std::list<Laser*> lasers;

public:
	Player() {
		texture.loadFromFile(IMAGES_FOLDER + PLAYER_FILE_NAME);
		sprite.setTexture(texture);
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sprite.setPosition(
			(WINDOW_WIDTH - bounds.width) / 2, 
			WINDOW_HEIGHT - bounds.height - 50.f
		);

	}

	void update() {
		speedx = 0.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			speedx = -PLAYER_SPEED;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			speedx = PLAYER_SPEED;
		}
		sprite.move(speedx, 0.f);
		
		sf::FloatRect bounds = sprite.getGlobalBounds();
		sf::Vector2f playerPos = sprite.getPosition();
		if (playerPos.x < 0) {
			sprite.setPosition(0.f, playerPos.y);
		}
		else if (playerPos.x > WINDOW_WIDTH - bounds.width) {
			sprite.setPosition(WINDOW_WIDTH - bounds.width, playerPos.y);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			fire();
		}
		for (auto laser : lasers) {
			laser->update();
		}
	}

	//sf::Sprite getSprite() { return sprite; }
	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
		for (auto laser : lasers) {
			window.draw(laser->getSprite());
		}
	}

	int getLives() { return lives; }
	void incLives() { lives++; }
	void decLives() { lives--; }
	
	void fire() {
		Laser* l = new Laser(sprite.getPosition());
		lasers.push_back(l);
	}
};