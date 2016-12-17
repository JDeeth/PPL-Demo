#pragma once

#include <menuaction.h>
#include <dataref.h>
#include <logichandler.h>
#include <menuitem.h>
#include <owneddata.h>
#include <simpleini/SimpleIni.h>

#include <string>

// FlapRetractor retracts flaps above a specified airspeed.
// This is a trivial demonstration of PPL

// It will load the threshold speed from the referenced .ini file, and store it
// in a dataref which can be altered. On close, it saves the new value to the
// .ini file.

// The module can be suspended and enabled using a menu item.

// LogicHandler is used by inheriting from LogicHandler and implementing its
// virtual functions. `hookToSim()` and `unhookFromSim()` MUST be called in
// `XPluginStart()` and `XPluginStop()`.

class FlapRetractor : public PPL::LogicHandler {
  // Data members needed for simulation, and a constructor to set them up:
public:
  FlapRetractor(CSimpleIni &ini, PPL::MenuItem &menu);

private:
  PPL::DataRef<float> airspeed_;
  PPL::DataRef<float> flapControl_;
  PPL::OwnedData<float> retractSpeedKts_;
  bool suspended_;
  CSimpleIni &ini_;
  PPL::LHEnable enable_;

  // inherited interface from `PPL::LogicHandler` we must implement:
public:
  bool initializeAtStart() override;
  bool initializeOnAircraftChange() override;
  bool processInTheLoop() override;
  bool processInput(long input, void *param) override;
  float loopFrequency() override;
  void suspend(bool yes) override;
  bool isSuspended() const override;
  std::string name() const override;

private:
  bool aquireSimData() override;
  bool publishData() override;
  bool withdrawPublishedData() override;
};
