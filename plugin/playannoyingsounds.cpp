#include "playannoyingsounds.h"

#include <log.h>
#include <pluginpath.h>

#include  <random>
#include  <iterator>

PlayAnnoyingSounds::PlayAnnoyingSounds(PPLYour_Project_Name::MenuItem &menu)
    : PPL::Processor(1.f), enable_(*this, menu) {

  auto addWav = [this](std::string filename) {
    try {
      auto id = this->snd_.addSoundFromFile(
          PPL::PluginPath::prependPlanePath("sounds/" + filename + ".wav"));
      this->wavIds_.push_back(id);
    } catch (PPL::ALContextManager::SoundLoadError e) {
      using PPL::Log;
      Log() << Log::Error << filename << ": " << e.what() << Log::endl;
    }
  };

  addWav("c4");
  addWav("d4");
  addWav("e4");
  addWav("f4");
  addWav("g4");
  addWav("a4");
  addWav("b4");
  addWav("c5");
  nextWavId_ = wavIds_.begin();
  running_ = true;
}

float PlayAnnoyingSounds::callback(float, float, int) {
  try {
    snd_.playSound(*nextWavId_);

  } catch (PPL::ALContextManager::SoundNotFoundError e) {
    using PPL::Log;
    Log() << Log::Error << "SNFE " << e.what() << Log::endl;
  }
  nextWavId_++;
  if (nextWavId_ == wavIds_.end()) {
    nextWavId_ = wavIds_.begin();
  }
  return 1.5f;
}

PlayAnnoyingSounds::Enable::Enable(PlayAnnoyingSounds &pas,
                                   PPLYour_Project_Name::MenuItem &menu)
    : pas_(pas) {
  menu.addSubItem(this);
}

const std::string PlayAnnoyingSounds::Enable::name() const {
  return "Toggle annoying sounds";
}

void PlayAnnoyingSounds::Enable::doAction() {
  pas_.running_ = !pas_.running_;
  pas_.setInterval(pas_.running_ ? 1.5f : 0.f);
}
