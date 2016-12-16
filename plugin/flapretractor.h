#pragma once

#include <logichandler.h>

#include <string>
#include <dataref.h>
#include <owneddata.h>

// FlapRetractor retracts flaps above a specified airspeed.
// This is a trivial demonstration of PPL.

// LogicHandler is used by inheriting from LogicHandler and implementing its
// virtual functions. `hookToSim()` and `unhookFromSim()` MUST be called in
// `XPluginStart()` and `XPluginStop()`.

class FlapRetractor : public PPL::LogicHandler {
  // Data members needed for simulation, and a constructor to set them up:
public:
  FlapRetractor();

private:
  PPL::DataRef<float> airspeed_;
  PPL::DataRef<float> flapControl_;
  PPL::OwnedData<float> retractSpeedKts_;
  PPL::OwnedData<int> suspended_;

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
