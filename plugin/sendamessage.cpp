#include "sendamessage.h"

#include <log.h>
#include <pluginpath.h>

SendAMessage::SendAMessage()
    : PPL::Processor(5.f) {  // start after five seconds
  try {
    // load a wav file from <aircraft>/sounds/
    auto revseatbelt =
        PPL::PluginPath::prependPlanePath("sounds/revseatbelt.wav");
    sound_id_revseatbelt_ = sound_context_.addSoundFromFile(revseatbelt);
  } catch (PPL::ALContextManager::SoundLoadError e) {
    using PPL::Log;
    Log() << Log::Error << "SoundLoadError " << e.what() << Log::endl;
  }
}

// PPL::Processor will call this after five seconds, as specified in the
// constructor
float SendAMessage::callback(float, float, int) {
  try {
    // attempt to play the sound
    sound_context_.playSound(sound_id_revseatbelt_);
  } catch (PPL::ALContextManager::SoundNotFoundError e) {
    using PPL::Log;
    Log() << Log::Error << "SoundNotFoundError " << e.what() << Log::endl;
  }

  msg_ = std::make_unique<PPL::MessageWindow>(
      500,                                                 // width
      100,                                                 // height
      "Hello, world!",                                     // title
      "I am a message box! Close me and the world ends.",  // message
      true);  // should closing this message quit X-Plane

  // return 0 to stop the function being called again
  return 0;
}
