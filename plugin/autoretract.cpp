#include "autoretract.h"

#include <log.h>

void AutoRetract::load(CSimpleIni& ini) {
  // Load value from ini file, or use 80kts as a default if not found
  retract_speed_kts_ = ini.GetDoubleValue("Config", "FlapRetractSpeedKts", 80);
}

void AutoRetract::save(CSimpleIni& ini) {
  ini.SetDoubleValue("Config", "FlapRetractSpeedKts", retract_speed_kts_);
}

float AutoRetract::callback(float /*ElapsedSinceLastCall (seconds)*/,
                            float /*ElapsedSinceLastFlightLoop*/,
                            int /*counter*/) {
  if (flap_control_ > 0 && airspeed_kts_ > retract_speed_kts_) {
    PPL::Log() << PPL::Log::Info << "Auto-retracting flaps at " << airspeed_kts_
               << "kts" << PPL::Log::endl;
    flap_control_ = 0;
  }

  // This function is just like any XPLMFlightLoop function
  // Return a negative number to be called again after that many flight loops
  // Return a positive number to be called again after that many seconds
  // Return zero to not be called again
  return -1;
}
