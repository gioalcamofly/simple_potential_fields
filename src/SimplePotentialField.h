#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

class SimplePotentialField {
    public:
        const static double ANGULAR_SPEED;
        const static double ANGLE;
        const static double MIN_SCAN_ANGLE;
        const static double MAX_SCAN_ANGLE;
        const static float MIN_DIST;

        SimplePotentialField();
        void startMoving();

    private:

        ros::NodeHandle nh;
        ros::Publisher commandPub;

        ros::Subscriber laserSub;
        double FORWARD_SPEED;

        void moveForward();
        void applyPotentialField();
        void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan);
};