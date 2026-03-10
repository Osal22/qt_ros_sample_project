#include "data_interface_node.hpp"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <thread>

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  auto ros_node = std::make_shared<data_interface::DataInterfaceNode>();
  std::thread ros_thread([ros_node]() { rclcpp::spin(ros_node); });
  // 2. REGISTER FIRST
  qmlRegisterSingletonInstance<data_interface::DataInterfaceNode>(
      "MainModule", 1, 0, "DataInterfaceNode", ros_node.get());
  const QUrl url(QStringLiteral("qrc:/MainModule/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);
  int result = app.exec();
  rclcpp::shutdown();
  ros_thread.join();
  return result;
}