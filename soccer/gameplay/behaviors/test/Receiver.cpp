/*
 * Receiver.cpp
 *
 *  Created on: Nov 8, 2009
 *      Author: alexgc
 */

#include "Receiver.hpp"

using namespace Gameplay::Behaviors;

Receiver::Receiver(GameplayModule *gameplay)
: Behavior(gameplay)
  {

}

bool Receiver::run() {

}

bool Receiver::done() {
	return true;
}

float Receiver::score(Robot* robot) {
	return 0.0;
}