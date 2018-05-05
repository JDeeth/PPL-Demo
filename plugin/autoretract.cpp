#include "autoretract.h"

#include <log.h>

AutoRetract::AutoRetract(CSimpleIniA& ini) : ini_{ini} {}

void AutoRetract::load() {
  retract_speed_kts_ = ini_.GetDoubleValue("Config", "FlapRetractSpeedKts", 80);
}

void AutoRetract::save() {
  ini_.SetDoubleValue("Config", "FlapRetractSpeedKts", retract_speed_kts_);
}

float AutoRetract::callback(float, float, int) {
  if (flap_control_ > 0 && airspeed_kts_ > retract_speed_kts_) {
    PPL::Log() << PPL::Log::Info << "Auto-retracting flaps at " << airspeed_kts_
               << "kts" << PPL::Log::endl;
    flap_control_ = 0;
  }

  return -1;
}
