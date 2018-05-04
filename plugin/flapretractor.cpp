#include "flapretractor.h"

#include <log.h>
#include <menuitem.h>
#include <simpleini/SimpleIni.h>

using namespace PPL;

// Our constructor just needs to set up the data members
FlapRetractor::FlapRetractor(CSimpleIni& ini)
    : airspeed_("sim/cockpit2/gauges/indicators/airspeed_kts_pilot"),
      flapControl_("sim/cockpit2/controls/flap_ratio", ReadWrite),
      retractSpeedKts_("PPLDemo/flap_retract_speed_kts", ReadWrite, true),
      suspended_(false),
      ini_(ini) {}

// We then add definitions to each of the inherited functions as needed

// This function runs once, one frame after startup
bool FlapRetractor::initializeAtStart() {
  retractSpeedKts_ = ini_.GetDoubleValue("Config", "FlapRetractSpeedKts", 80);
  return true;
}

// This function is called as per `loopFrequency()` unless `isSuspended()`
bool FlapRetractor::processInTheLoop() {
  if (!suspended_ && airspeed_ >= retractSpeedKts_ && flapControl_ > 0) {
    Log() << Log::Info << "Flaps auto-retracted; airspeed greater than "
          << retractSpeedKts_ << Log::endl;
    flapControl_ = 0;
  }
  return true;
}

// Sets the timing of the next call to `processInTheLoop()`.
// return value: +ve seconds, -ve frames.
float FlapRetractor::loopFrequency() {
  return -1;
}

// Get and set suspended status, and do any on-suspend actions
void FlapRetractor::suspend(bool yes) {
  suspended_ = yes;
}
bool FlapRetractor::isSuspended() const {
  return suspended_;
}

// Called when `hookToSim()` is called - will generate log message if false
bool FlapRetractor::aquireSimData() {
  return true;
}
bool FlapRetractor::publishData() {
  return true;
}

// Called when `unhookFromSim()` is called
// Not sure what "withdraw published data" is supposed to mean...
bool FlapRetractor::withdrawPublishedData() {
  ini_.SetDoubleValue("Config", "FlapRetractSpeedKts", retractSpeedKts_);
  return true;
}

// These functions are not called by PPL but can be useful elsewhere:
bool FlapRetractor::initializeOnAircraftChange() {
  return true;
}
bool FlapRetractor::processInput(long /*input*/, void* /*param*/) {
  return true;
}
std::string FlapRetractor::name() const {
  return "Flap Retractor";
}
