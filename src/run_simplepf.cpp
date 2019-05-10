#include "SimplePotentialField.h"

int main(int argc, char **argv) {

    ros::init(argc, argv, "SimplePotentialField");

    SimplePotentialField simplePotentialField;

    simplePotentialField.startMoving();

    return 0;
}