#include "playannoyingsounds.h"

#include <log.h>
#include <pluginpath.h>

#include <random>
#include <iterator>

PlayAnnoyingSounds::PlayAnnoyingSounds(PPL::MenuItem& menu)
    : PPL::Processor(1.f),  // start playing sounds after 1 second
      enable_(*this, menu) {
  // set up to load a bunch of .wav files from the <aircraft>/sounds/ folder
  auto add_wav = [this](std::string filename) {
    try {
      auto id = this->al_context_.addSoundFromFile(
          PPL::PluginPath::prependPlanePath("sounds/" + filename));
      this->wav_ids_.push_back(id);
    } catch (PPL::ALContextManager::SoundLoadError e) {
      using PPL::Log;
      Log() << Log::Error << filename << ": " << e.what() << Log::endl;
    }
  };

  add_wav("c4.wav");
  add_wav("d4.wav");
  add_wav("e4.wav");
  add_wav("f4.wav");
  add_wav("g4.wav");
  add_wav("a4.wav");
  add_wav("b4.wav");
  add_wav("c5.wav");
  next_wav_id_ = wav_ids_.begin();
  running_ = true;
}

float PlayAnnoyingSounds::callback(float, float, int) {
  // start playing next sound
  try {
    al_context_.playSound(*next_wav_id_);
  } catch (PPL::ALContextManager::SoundNotFoundError e) {
    using PPL::Log;
    Log() << Log::Error << "SoundNotFoundError: " << e.what() << Log::endl;
  }
  // move iterator to next sound in sequence
  next_wav_id_++;
  if (next_wav_id_ == wav_ids_.end()) {
    next_wav_id_ = wav_ids_.begin();
  }
  // call this function again after 1.5 seconds
  return 1.5f;
}

PlayAnnoyingSounds::Enable::Enable(PlayAnnoyingSounds& pas, PPL::MenuItem& menu)
    : pas_(pas) {
  menu.addSubItem(this);
}

const std::string PlayAnnoyingSounds::Enable::name() const {
  return "Toggle annoying sounds";
}

void PlayAnnoyingSounds::Enable::doAction() {
  pas_.running_ = !pas_.running_;
  // PPL::Processor::setInterval is from the JDeeth/PPL fork
  pas_.setInterval(pas_.running_ ? 1.5f : 0.f);
}
