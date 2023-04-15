#pragma once
#include "settings.h"

class Bonus {
public:
	enum BonusType { MULTI_LASER, HP, SHIELD, BONUSES_TYPE_QTY };
	Bonus(BonusType type, sf::Vector2f position);
	void update();
	void draw(sf::RenderWindow& window);
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
	void setDel();
	bool isToDel();
	bool offScreen();
	void act(Player& player);


private:
	sf::Sprite sprite;
	sf::Texture texture;
	BonusType type;
	bool del = false;
};

Bonus::Bonus(BonusType type, sf::Vector2f position) {
	this->type = type;
	switch (type) {
	case MULTI_LASER:
		texture.loadFromFile(IMAGES_FOLDER + MULTI_LASER_BONUS_FILE_NAME);
		break;
	case HP:
		texture.loadFromFile(IMAGES_FOLDER + HP_BONUS_FILE_NAME);
		break;
	case SHIELD:
		texture.loadFromFile(IMAGES_FOLDER + SHIELD_BONUS_FILE_NAME);
		break;
	}
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Bonus::update() { sprite.move(0.f, BONUS_SPEED); }

void Bonus::draw(sf::RenderWindow& window) { window.draw(sprite); }

sf::FloatRect Bonus::getHitBox() { return sprite.getGlobalBounds(); }

sf::Vector2f Bonus::getPosition() { return sprite.getPosition(); }

bool Bonus::isToDel() { return del; }

void Bonus::setDel() { del = true; }

bool Bonus::offScreen() {
	if (sprite.getPosition().y > WINDOW_HEIGHT) return true;
	return false;
}

void Bonus::act(Player& player) {
	switch (type) {
	case MULTI_LASER:
		player.activateThreeLasers();
		break;
	case HP:
		player.heal(HP_BONUS_MEDICINE);
		if (player.getHp() > INITIAL_PLAYER_HP) {
			player.setMaxHp();
		}
		break;
	case SHIELD:
		player.activateShield();
		break;
	}
}