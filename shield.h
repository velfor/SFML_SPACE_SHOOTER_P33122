#pragma once
#include "settings.h"

class Shield {
public:
	Shield(sf::Vector2f playerCenterPos);
	void update();
	void draw(sf::RenderWindow& window);
	void activate(); 
	bool isActive();
	void deactivate();
	void setPosition(sf::Vector2f pos);

private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Clock timer;
	bool active = false;
};

Shield::Shield(sf::Vector2f playerCenterPos) {
	texture.loadFromFile(IMAGES_FOLDER + SHIELD_FILE_NAME);
	sprite.setTexture(texture);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width/2, bounds.height/2);
	sprite.setPosition(playerCenterPos);
}

void Shield::activate() { active = true; }

bool Shield::isActive() { return active; }

void Shield::deactivate() { active = false; }

void Shield::setPosition(sf::Vector2f pos) { sprite.setPosition(pos); }

void Shield::update() {}
void Shield::draw(sf::RenderWindow& window) { window.draw(sprite); }