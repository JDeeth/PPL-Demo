// Copyright Jack Deeth, 2018 - see attached LICENSE

/* autoretract.h
 *
 * Automatically retracts the flaps above a specified speed.
 *
 * Demonstrates PPL::DataRef, PPL::OwnedData, and PPL::Processor
 */
#pragma once

#include <XPLMUtilities.h>

#include <dataref.h>
#include <owneddata.h>
#include <processor.h>
#include <simpleini/SimpleIni.h>

class AutoRetract : private PPL::Processor {
public:
  void load(CSimpleIni& ini);
  void save(CSimpleIni& ini);

private:
  // PPL::Processor wraps the SDK functions to register a FlightLoopCallback
  // function. This is the callback function.
  virtual float callback(float, float, int) override;

  // PPL::DataRef connects to an existing dataref. Can be int, float, double,
  // std::vector<int>, std::vector<float>, or std::string.
  PPL::DataRef<float> airspeed_kts_{
      "sim/cockpit2/gauges/indicators/airspeed_kts_pilot"};

  PPL::DataRef<float> flap_control_{"sim/cockpit2/controls/flap_ratio",
                                    PPL::ReadWrite};

  // PPL::OwnedData creates a new dataref.
  // It can be read-only, read/write or write-only, be publised in DataRefEditor
  // or not, and you can also specify custom read and/or write callback
  // functions.
  PPL::OwnedData<float> retract_speed_kts_{
      "PPLDemo/flap_retract_speed_kts", PPL::ReadWrite, true};
};
