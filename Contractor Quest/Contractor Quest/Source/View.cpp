#include "View.h"

View::View() {
	posX = 0;
	posY = 0;
}

View::View( float posX, float posY) {
	this->posX = posX;
	this->posY = posY;
}

View::~View() {
}

float View::getPosX() {
	return posX;
}

float View::getPosY() {
	return posY;
}

/*If the player is past the halfway point, engine calls this function and passes it the posX need 
for the player to stay centered in the view.  The effect is that the view follows the player if they
attempt to pass the center.*/
void View::update(float updatedPosX) {
	this->posX = updatedPosX;
}
