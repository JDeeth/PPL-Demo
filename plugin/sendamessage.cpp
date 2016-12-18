#include "sendamessage.h"

#include <log.h>
#include <pluginpath.h>

SendAMessage::SendAMessage() : PPL::Processor(5.f) { // start after five seconds
  try {
    snd_revseatbelt_ = snd_.addSoundFromFile(
        PPL::PluginPath::prependPlanePath("sounds/revseatbelt.wav"));
  } catch (PPL::ALContextManager::SoundLoadError e) {
    using PPL::Log;
    Log() << Log::Error << "SLE " << e.what() << Log::endl;
  }
}

float SendAMessage::callback(float, float, int) {
  try {
    snd_.playSound(snd_revseatbelt_);
  } catch (PPL::ALContextManager::SoundNotFoundError e) {
    using PPL::Log;
    Log() << Log::Error << "SNFE " << e.what() << Log::endl;
  }
  msg_ = std::make_unique<PPL::MessageWindow>(
      500, 100, "Hello, world!", "I am a message box! Close me and you die.",
      true);
  return 0;
}
