#pragma once

#include <XPLMUtilities.h>

#include <dataref.h>
#include <owneddata.h>
#include <processor.h>
#include <simpleini/SimpleIni.h>

class AutoRetract : private PPL::Processor {
public:
  AutoRetract(CSimpleIni& ini);

  void load();
  void save();

private:
  // This function is registered as a XPLMFlightLoopCallback function by
  // PPL::Processor
  virtual float callback(float, float, int) override;

  CSimpleIni& ini_;

  // PPL::DataRef connects to an existing dataref. Can be int, float, double,
  // std::vector<int>, std::vector<float>, or std::string.
  PPL::DataRef<float> airspeed_kts_{
      "sim/cockpit2/gauges/indicators/airspeed_kts_pilot"};

  // Here we're using C++11 member initialisation, but these could be
  // initialised in a class constructor instead.
  PPL::DataRef<float> flap_control_{"sim/cockpit2/controls/flap_ratio",
                                    PPL::ReadWrite};

  // PPL::OwnedData creates a new dataref.
  // It can be read-only, read/write or write-only, be publised in DataRefEditor
  // or not, and you can also specify custom read and/or write callback
  // functions.
  PPL::OwnedData<float> retract_speed_kts_{
      "PPLDemo/flap_retract_speed_kts", PPL::ReadWrite, true};
};
