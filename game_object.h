#pragma once
#include "settings.h"
#include <iostream>

class GameObject {
public:
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

	sf::Vector2f getPosition() { return sprite.getPosition(); }
	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }

protected:
	sf::Texture texture;
	sf::Sprite sprite;
};