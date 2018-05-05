// Copyright Jack Deeth, 2018 - see attached LICENSE

/* playannoyingsounds.h
 *
 * Plays a charming octave, which can be stopped from the menu
 *
 * Note this relies on a modification to PPL::Processor from the JDeeth/PPL fork
 * (the PPL::Processor::setInterval function)
 *
 * Demonstrates ALContextManager and PPL::Action
 */

#pragma once

#include <vector>

#include <action.h>
#include <alcontextmanager.h>
#include <menuitem.h>
#include <processor.h>

class PlayAnnoyingSounds : public PPL::Processor {
public:
  PlayAnnoyingSounds(PPL::MenuItem& menu);
  float callback(float, float, int) override;

private:
  PPL::ALContextManager al_context_;
  std::vector<int> wav_ids_;
  decltype(wav_ids_)::iterator next_wav_id_;
  bool running_;

  // It may be poor design to nest classes - it works though
  // PPL::Action is an element on a submenu under the "Plugins" menu
  // PPL::MenuItem is the submenu
  // This class toggles the sounds on and off
  class Enable : public PPL::Action {
  public:
    Enable(PlayAnnoyingSounds& pas, PPL::MenuItem& menu);
    // this returns the text that appears on the menu
    virtual const std::string name() const override;
    // this is what happens when it's clicked on
    virtual void doAction() override;

  private:
    PlayAnnoyingSounds& pas_;
  };

  Enable enable_;
};
