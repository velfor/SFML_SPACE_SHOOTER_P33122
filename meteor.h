#pragma once
#include "settings.h"

class Meteor {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speedx, speedy;
public:
	static std::string mFileNames[];
	Meteor() {
		int index = rand() % METEOR_TYPES_QTY;
		texture.loadFromFile(mFileNames[index]);
		sprite.setTexture(texture);
		speedy = rand() % 6 + 2;
		speedx = rand() % 5 - 2;
		sf::FloatRect bounds = sprite.getGlobalBounds();
		float x = rand() % (int)(WINDOW_WIDTH - bounds.width);
		float y = -(rand() % (int)(WINDOW_HEIGHT - bounds.height) + bounds.height);
		sprite.setPosition(x, y);
	}
};

std::string Meteor::mFileNames[] = { "meteorBrown_big1.png",  "meteorBrown_big2.png",
	"meteorBrown_med1.png", "meteorBrown_med2.png", "meteorBrown_small1.png",
	"meteorBrown_small2.png", "meteorBrown_tiny1.png", "meteorBrown_tiny2.png" };