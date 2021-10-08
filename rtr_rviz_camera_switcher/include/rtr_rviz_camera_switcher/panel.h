#pragma once

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif

#include <rviz/panel.h>

namespace Ui {
class CameraSwitcherUI;
}

namespace rtr_rviz_camera_switcher
{
class Panel: public rviz::Panel
{
  Q_OBJECT
 public:
  Panel(QWidget* parent = nullptr);
  ~Panel() override;

  void onInitialize() override;
  void onEnable();
  void onDisable();

private Q_SLOTS:
  void dialValueChanged(int value);
  void lineEditChanged();
  void buttonClicked();

protected:
  Ui::CameraSwitcherUI* ui_;

  ros::NodeHandle nh_;

//  ros::ServiceClient client;
  std::vector<std::string> service_names;
  std::vector<ros::ServiceClient> service_clients;
};
} // end namespace rtr_rviz_camera_switcher
