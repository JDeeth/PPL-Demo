#include "demo.h"

#include <log.h>
#include <pluginpath.h>

Demo::Demo() : ini_path_{PPL::PluginPath::prependPlanePath("PPLDemo.ini")} {
  SI_Error ini_state = ini_.LoadFile(ini_path_.c_str());
  if (ini_state < 0) {
    PPL::Log() << PPL::Log::Warn << "No ini file found - will create one now."
               << PPL::Log::endl;
    ini_.SaveFile(ini_path_.c_str());
  }
  autoretract_.load();
}

Demo::~Demo() {
  PPL::Log() << PPL::Log::Info << "Saving values to " << ini_path_ << "...";
  autoretract_.save();
  ini_.SaveFile(ini_path_.c_str());
  PPL::Log() << "done" << PPL::Log::endl;
}
