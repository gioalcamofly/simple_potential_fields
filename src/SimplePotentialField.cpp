#include "SimplePotentialField.h"
#include "geometry_msgs/Twist.h"

const double SimplePotentialField::ANGULAR_SPEED = 35*2*M_PI/360;
const double SimplePotentialField::ANGLE = M_PI;
const double SimplePotentialField::MIN_SCAN_ANGLE = 0.0/180*M_PI;
const double SimplePotentialField::MAX_SCAN_ANGLE = +30.0/180*M_PI;
const float SimplePotentialField::MIN_DIST = 0.5;

SimplePotentialField::SimplePotentialField() {

    FORWARD_SPEED = 0.5;

    commandPub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    laserSub = nh.subscribe("scan", 1, &SimplePotentialField::scanCallback, this);

}

void SimplePotentialField::moveForward() {

    geometry_msgs::Twist msg;
    msg.linear.x = FORWARD_SPEED;
    commandPub.publish(msg);

}

void SimplePotentialField::applyPotentialField() {

    geometry_msgs::Twist msg;
    msg.angular.z = ANGULAR_SPEED;

    double t0 = ros::Time::now().toSec();
    double currentAngle = 0;

    while (currentAngle < ANGLE) {
        commandPub.publish(msg);
        double t1 = ros::Time::now().toSec();
        currentAngle = ANGULAR_SPEED*(t1-t0);
    }

    msg.angular.z = 0;
    commandPub.publish(msg);


}

void SimplePotentialField::scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan) {

    bool isObstacleInFront = false;

    int minIndex = ceil((MIN_SCAN_ANGLE - scan->angle_min) / scan->angle_increment);    
    int maxIndex = floor((MAX_SCAN_ANGLE - scan->angle_min) / scan->angle_increment);

    for (int index = minIndex + 1; index <= maxIndex; index++) {
        if (scan->ranges[index] < MIN_DIST) {
            isObstacleInFront = true;
            break;
        }
    }

    if (isObstacleInFront) {
        applyPotentialField();
    }
}

void SimplePotentialField::startMoving() {
    
    ros::Rate rate(10);
    
    while (ros::ok()) {
        moveForward();

        ros::spinOnce();
        rate.sleep();
    }
}