#include "data_interface_node.hpp"

namespace data_interface {

DataInterfaceNode::DataInterfaceNode(QObject *parent)
    : QObject(parent), rclcpp::Node("data_interface_node") {

  string_sub_ = create_subscription<std_msgs::msg::String>(
      "/chatter", 10,
      std::bind(&DataInterfaceNode::statusCallback, this,
                std::placeholders::_1));

  m_faultDatabase["Sensor Timeout"] =
      "Check the Ethernet cable and power supply of the LiDAR.";
  m_faultDatabase["High Temperature"] =
      "Fan failure detected in the computing unit.";
  m_faultDatabase["Localization Lost"] =
      "Inconsistent EKF variance. Re-initialize pose.";
}

void DataInterfaceNode::statusCallback(
    const std_msgs::msg::String::ConstSharedPtr msg) {
  m_faultList.prepend(QString::fromStdString(msg->data + "_m_faultList"));

  m_latentFaultList.prepend(
      QString::fromStdString(msg->data + "_m_latentFaultList"));

  m_noFaultList.prepend(QString::fromStdString(msg->data + "_m_noFaultList"));

  auto limit = [](QStringList &list) {
    if (list.size() > 20)
      list.removeLast();
  };
  limit(m_faultList);
  limit(m_latentFaultList);
  limit(m_noFaultList);

  emit dataChanged();
}

void DataInterfaceNode::selectFault(const QString &faultName) {
  RCLCPP_INFO_STREAM(get_logger(), "selectFault");
  if (m_faultDatabase.count(faultName)) {
    m_selectedInfo = m_faultDatabase[faultName];
  } else {
    m_selectedInfo = "No additional information available for: " + faultName;
  }
  emit selectedInfoChanged(); // Update the Text Box in QML
}

} // namespace data_interface