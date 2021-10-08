#include <pluginlib/class_list_macros.h>
#include <rtr_rviz_camera_switcher/panel.h>
#include <std_msgs/Float64.h>
#include <std_srvs/SetBool.h>

#include "ui_rtr_camera_switcher.h"

namespace rtr_rviz_camera_switcher
{
Panel::Panel(QWidget* parent) : rviz::Panel(parent),  ui_(new Ui::CameraSwitcherUI())
{
  ui_->setupUi(this);
  service_names = {
      "/RTRDoubleArmV7/Camera00/set_enabled",
      "/RTRDoubleArmV7/Camera01/set_enabled",
      "/RTRDoubleArmV7/Camera02/set_enabled",
      "/RTRDoubleArmV7/Camera03/set_enabled",
      "/RTRDoubleArmV7/Camera04/set_enabled",
      "/RTRDoubleArmV7/Camera05/set_enabled",
      "/RTRDoubleArmV7/Camera06/set_enabled",
      "/RTRDoubleArmV7/Camera07/set_enabled",
      "/RTRDoubleArmV7/Camera08/set_enabled",
      "/RTRDoubleArmV7/Camera09/set_enabled",
      "/RTRDoubleArmV7/Camera10/set_enabled",
      "/RTRDoubleArmV7/Camera11/set_enabled",
      "/RTRDoubleArmV7/Camera12/set_enabled",
      "/RTRDoubleArmV7/Camera13/set_enabled",
      "/RTRDoubleArmV7/Camera14/set_enabled",
      "/RTRDoubleArmV7/Camera15/set_enabled",
      "/RTRDoubleArmV7/ManiDepthCamera00/set_enabled",
      "/RTRDoubleArmV7/ManiDepthCamera01/set_enabled",
      "/RTRDoubleArmV7/ManiSideCamera00/set_enabled",
      "/RTRDoubleArmV7/ManiSideCamera01/set_enabled",
      "/RTRDoubleArmV7/TohokuDepthCamera00/set_enabled",
      "/RTRDoubleArmV7/TohokuDepthCamera01/set_enabled",
      "/RTRDoubleArmV7/TohokuSideCamera00/set_enabled",
      "/RTRDoubleArmV7/TohokuSideCamera01/set_enabled"
  };

  for(auto name : service_names){
    service_clients.emplace_back(nh_.serviceClient<std_srvs::SetBool>(name.c_str()));
  }
}

Panel::~Panel() = default;

void Panel::onInitialize()
{
  std::vector<QPushButton*> on_buttons = {
      ui_->CAM00_ON,
      ui_->CAM01_ON,
      ui_->CAM02_ON,
      ui_->CAM03_ON,
      ui_->CAM04_ON,
      ui_->CAM05_ON,
      ui_->CAM06_ON,
      ui_->CAM07_ON,
      ui_->CAM08_ON,
      ui_->CAM09_ON,
      ui_->CAM10_ON,
      ui_->CAM11_ON,
      ui_->CAM12_ON,
      ui_->CAM13_ON,
      ui_->CAM14_ON,
      ui_->CAM15_ON,
      ui_->MANI_DCAM00_ON,
      ui_->MANI_DCAM01_ON,
      ui_->MANI_SCAM00_ON,
      ui_->MANI_SCAM01_ON,
      ui_->TOHOKU_DCAM00_ON,
      ui_->TOHOKU_DCAM01_ON,
      ui_->TOHOKU_SCAM00_ON,
      ui_->TOHOKU_SCAM01_ON
  };

  std::vector<QPushButton*> off_buttons = {
      ui_->CAM00_OFF,
      ui_->CAM01_OFF,
      ui_->CAM02_OFF,
      ui_->CAM03_OFF,
      ui_->CAM04_OFF,
      ui_->CAM05_OFF,
      ui_->CAM06_OFF,
      ui_->CAM07_OFF,
      ui_->CAM08_OFF,
      ui_->CAM09_OFF,
      ui_->CAM10_OFF,
      ui_->CAM11_OFF,
      ui_->CAM12_OFF,
      ui_->CAM13_OFF,
      ui_->CAM14_OFF,
      ui_->CAM15_OFF,
      ui_->MANI_DCAM00_OFF,
      ui_->MANI_DCAM01_OFF,
      ui_->MANI_SCAM00_OFF,
      ui_->MANI_SCAM01_OFF,
      ui_->TOHOKU_DCAM00_OFF,
      ui_->TOHOKU_DCAM01_OFF,
      ui_->TOHOKU_SCAM00_OFF,
      ui_->TOHOKU_SCAM01_OFF
  };


  for(int i=0;i< on_buttons.size();i++){
    connect(on_buttons[i], &QPushButton::clicked,[this,i](){
        std_srvs::SetBool srv;
        srv.request.data = true;
        std::cout << "call : " << i << std::endl;
        bool success = this->service_clients[i].call(srv);
        std::cout << "success : " << success << std::endl;
    });
  }

  for(int i=0;i< off_buttons.size();i++){
    connect(off_buttons[i], &QPushButton::clicked,[this,i](){
      std_srvs::SetBool srv;
      srv.request.data = false;
      std::cout << "call : " << i << std::endl;
      bool success = this->service_clients.at(i).call(srv);
      std::cout << "success : " << success << std::endl;
    });
  }

  parentWidget()->setVisible(true);
}

void Panel::onEnable()
{
  show();
  parentWidget()->show();
}

void Panel::onDisable()
{
  hide();
  parentWidget()->hide();
}


}  // namespace rtr_rviz_camera_switcher

PLUGINLIB_EXPORT_CLASS(rtr_rviz_camera_switcher::Panel, rviz::Panel )
