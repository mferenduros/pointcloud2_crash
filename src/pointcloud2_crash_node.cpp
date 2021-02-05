#include <pcl_conversions/pcl_conversions.h>
#include <ros/node_handle.h>
#include <sensor_msgs/PointCloud2.h>

void OnPCL(const sensor_msgs::PointCloud2 &msg) {
  ROS_INFO(
      "Received message with width=%u, height=%u, row_step=%u, data size=%zu",
      msg.width, msg.height, msg.row_step, msg.data.size());
  pcl::PointCloud<pcl::PointXYZ> cloud;
  pcl::fromROSMsg(msg, cloud);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "node");
  ros::NodeHandle nh("~");

  std::string topic = "points";
  nh.getParam("topic", topic);
  ROS_INFO("Subscribing to %s", topic.c_str());
  auto sub = nh.subscribe(topic, 1, OnPCL);

  ros::spin();

  return 0;
}
