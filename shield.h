#pragma once
#include "settings.h"

class Shield {
public:
	Shield(sf::Vector2f playerCenterPos);
	void draw(sf::RenderWindow& window);
	void setPosition(sf::Vector2f pos);
	sf::FloatRect getHitBox();

private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Clock timer;
	
};

Shield::Shield(sf::Vector2f playerCenterPos) {
	texture.loadFromFile(IMAGES_FOLDER + SHIELD_FILE_NAME);
	sprite.setTexture(texture);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width/2, bounds.height/2);
	sprite.setPosition(playerCenterPos);
}


void Shield::setPosition(sf::Vector2f pos) { sprite.setPosition(pos); }

void Shield::draw(sf::RenderWindow& window) { window.draw(sprite); }

sf::FloatRect Shield::getHitBox() { return sprite.getGlobalBounds(); }