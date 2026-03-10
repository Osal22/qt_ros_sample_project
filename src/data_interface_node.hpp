#pragma once
#include <QObject>
#include <QtQml>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

namespace data_interface {

class DataInterfaceNode : public QObject, public rclcpp::Node {
  Q_OBJECT
  Q_PROPERTY(QStringList logList READ logList NOTIFY logListChanged)
  Q_PROPERTY(QStringList faultList READ faultList NOTIFY dataChanged)
  Q_PROPERTY(
      QStringList latentFaultList READ latentFaultList NOTIFY dataChanged)
  Q_PROPERTY(QStringList noFaultList READ noFaultList NOTIFY dataChanged)
  Q_PROPERTY(QString selectedInfo READ selectedInfo NOTIFY selectedInfoChanged)
public:
  explicit DataInterfaceNode(QObject *parent = nullptr);
  ~DataInterfaceNode() = default;

  QStringList logList() const { return m_logList; }
  QStringList faultList() const { return m_faultList; }
  QStringList latentFaultList() const { return m_latentFaultList; }
  QStringList noFaultList() const { return m_noFaultList; }
  QString selectedInfo() const { return m_selectedInfo; }
  Q_INVOKABLE void selectFault(const QString &faultName);
signals:
  void logListChanged();
  void dataChanged();
  void selectedInfoChanged();

private:
  void statusCallback(const std_msgs::msg::String::ConstSharedPtr msg);

  QStringList m_logList;
  QStringList m_faultList;
  QStringList m_latentFaultList;
  QStringList m_noFaultList;
  QString m_selectedInfo;
  std::map<QString, QString> m_faultDatabase;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr string_sub_;
};

} // namespace data_interface