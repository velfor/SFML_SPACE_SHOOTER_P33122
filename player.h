#pragma once
#include "settings.h"
#include "laser.h"
#include <list>
#include "textobj.h"
#include "shield.h"

class Player {

public:
	Player();

	void update();

	void draw(sf::RenderWindow& window);

	int getLives() { return lives; }

	void incLives() { lives++; }

	void decLives() { lives--; }
	
	void fire();
	

	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }

	bool isDead() { return hp <= 0; }

	bool isAlive() { return hp > 0; }

	void receiveDamage(int damage) { hp -= damage; }

	std::list<Laser*>* getLasers() { return &lasers; }

	void activateThreeLasers() { 
		threeLasers = true;
		prevThreeLasersBonusTime = timer.getElapsedTime().asMilliseconds();
	}

	void deactivateThreeLasers() { threeLasers = false; }

	void heal(int medicine) { hp += medicine; }

	int getHp() { return hp; }

	void setMaxHp() { hp = INITIAL_PLAYER_HP; }

	sf::Vector2f getCenterPosition();

	void activateShield();

	bool shieldIsActive() { return shieldActive; }

	void deactivateShield() { shieldActive = false; }

	void decreaseShieldMargin() { shieldMargin--; }

	sf::FloatRect getShieldHitBox() { return shield.getHitBox(); }


private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speedx = 0.f;
	int lives = 3;
	std::list<Laser*> lasers;
	int hp = INITIAL_PLAYER_HP;
	TextObj hpText;
	sf::FloatRect bounds;
	sf::Clock timer;
	bool threeLasers = false;
	Shield shield;
	bool shieldActive = false;
	int currTime, prevFireTime;
	int prevThreeLasersBonusTime;//currThreeLasersBonusTime,
	int prevShieldTime;//currShieldTime,
	int shieldMargin = SHIELD_MARGIN;
};

Player::Player() : hpText(std::to_string(hp), sf::Vector2f(0.f, 0.f)),
shield(getCenterPosition())
{
	texture.loadFromFile(IMAGES_FOLDER + PLAYER_FILE_NAME);
	sprite.setTexture(texture);
	bounds = sprite.getGlobalBounds();
	sprite.setPosition(
		(WINDOW_WIDTH - bounds.width) / 2,
		WINDOW_HEIGHT - bounds.height - 50.f
	);
	timer.restart();
	prevFireTime = timer.getElapsedTime().asMilliseconds();
}

void Player::update() {
	currTime = timer.getElapsedTime().asMilliseconds();
	if (currTime - prevThreeLasersBonusTime > THREE_LASERS_BONUS_DURATION) {
		threeLasers = false;
	}
	if (shieldMargin <= 0) {
		shieldActive = false;
	}

	bounds = sprite.getGlobalBounds();
	speedx = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		speedx = -PLAYER_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		speedx = PLAYER_SPEED;
	}
	sprite.move(speedx, 0.f);

	shield.setPosition(getCenterPosition());

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
	hpText.update("HP:" + std::to_string(hp));

	if (shieldIsActive()) {
		shield.setPosition(getCenterPosition());
	}
	else {
		shield.setPosition(sf::Vector2f{WINDOW_WIDTH/2, WINDOW_HEIGHT + 100.f});
	}
}

void Player::draw(sf::RenderWindow& window) {
	if (shieldIsActive()) {
		shield.draw(window);
	}
	window.draw(sprite);
	for (auto laser : lasers) {
		window.draw(laser->getSprite());
	}
	window.draw(hpText.getText());
}

void Player::fire() {
	
	if (currTime - prevFireTime > FIRE_COOLDOWN) {
		sf::Vector2f centralLaserPos{ sprite.getPosition().x + bounds.width / 2,  sprite.getPosition().y };
		Laser* centralLaser = new Laser(centralLaserPos);
		lasers.push_back(centralLaser);
		if (threeLasers) {
			sf::Vector2f leftLaserPos{ sprite.getPosition().x,
				sprite.getPosition().y + bounds.height / 2 };
			Laser* leftLaser = new Laser(leftLaserPos);
			lasers.push_back(leftLaser);

			sf::Vector2f rightLaserPos{ sprite.getPosition().x + bounds.width,
				sprite.getPosition().y + bounds.height / 2 };
			Laser* rightLaser = new Laser(rightLaserPos);
			lasers.push_back(rightLaser);
		}
		prevFireTime = currTime;
	}
}

sf::Vector2f Player::getCenterPosition() {
	return sf::Vector2f{bounds.left + bounds.width/2, bounds.top + bounds.height/2};
}

void Player::activateShield() {	
	shieldActive = true;
	shieldMargin = SHIELD_MARGIN;
	prevShieldTime = timer.getElapsedTime().asMilliseconds();
}