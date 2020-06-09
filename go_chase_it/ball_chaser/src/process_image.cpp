#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
  // Request a service and pass the velocities to it to drive the robot
  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;

  if (!client.call(srv))
    ROS_ERROR("Failed to call service DriveToTarget");
}


// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    int white_pixel = 255;

    // Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera

    int thirdsWhitePixelCount[3] = {0};

    const int thirdWidth = img.step / 3;
    const int secondThirdWidth = thirdWidth * 2;
    const int byteCount = img.height * img.step;
    
    for (int i = 0; i < byteCount; i += img.step) {
      int j;
      int k;
      for (j = 0; j < thirdWidth; j+=3) {
	for (k = 0; k < 3; ++k) {
	  if (img.data[i+j+k] != white_pixel)
	    break;
	}
	if (k == 3)
	  thirdsWhitePixelCount[0]++;
      }
      for (; j < secondThirdWidth; j+=3) {
	for (k = 0; k < 3; ++k) {
	  if (img.data[i+j+k] != white_pixel)
	    break;
	}
	if (k == 3)
	  thirdsWhitePixelCount[1]++;
      }
      for (; j < img.step; j+=3) {
	for (k = 0; k < 3; ++k) {
	  if (img.data[i+j+k] != white_pixel)
	    break;
	}
	if (k == 3)
	  thirdsWhitePixelCount[2]++;
      }
    }

    int maxWhitePixelCount = 0;
    int thirdWithMaxWhitePixelCount;
    for (int i = 0; i < 3; ++i) {
      // ROS_INFO("White pixel Count for %d third is %d", i+1, thirdsWhitePixelCount[i]); 
      if (thirdsWhitePixelCount[i] > maxWhitePixelCount) {
	maxWhitePixelCount = thirdsWhitePixelCount[i];
	thirdWithMaxWhitePixelCount = i;
      }
    }

    // stop if white pixel count is 0, i.e. no white ball visible
    if (maxWhitePixelCount == 0) {
      drive_robot(0.0, 0.0);
    } else {
      if (thirdWithMaxWhitePixelCount == 0) {
	//ROS_INFO_STREAM("Telling robot to go LEFT");
	drive_robot(1, 5);
      } else if (thirdWithMaxWhitePixelCount == 1) {
	//ROS_INFO_STREAM("Telling robot to go STRAIGHT");
	drive_robot(1, 0);
      } else {
	//ROS_INFO_STREAM("Telling robot to go RIGHT");
	drive_robot(1, -5);
      }
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
