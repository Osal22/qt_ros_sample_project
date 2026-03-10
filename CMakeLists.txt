cmake_minimum_required(VERSION 3.16)
project(qt_project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(ament_cmake_auto REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)

qt_standard_project_setup(REQUIRES 6.4)

qt_add_executable(app_my_project src/main.cpp src/data_interface_node.cpp src/data_interface_node.hpp)

qt_add_qml_module(app_my_project
    URI MainModule
    VERSION 1.0
    RESOURCE_PREFIX "/"
    SOURCES src/main.cpp
    QML_FILES qml/main.qml qml/StatusTable.qml
)

target_link_libraries(app_my_project PRIVATE 
    Qt6::Quick 
    rclcpp::rclcpp 
    sensor_msgs::sensor_msgs__rosidl_typesupport_cpp
    std_msgs::std_msgs__rosidl_typesupport_cpp
)
target_include_directories(app_my_project PRIVATE src)

install(TARGETS app_my_project
  DESTINATION lib/${PROJECT_NAME}
)
ament_auto_package()