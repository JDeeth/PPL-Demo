// Copyright Jack Deeth, 2018 - see attached LICENSE

/* sendamessage.h
 *
 * Plays a sound and draws a message window after 5 seconds
 *
 * Demonstrates PPL::ALContextManager and PPL::MessageWindow
 */
#pragma once

#include <memory>

#include <alcontextmanager.h>
#include <messagewindow.h>
#include <processor.h>

class SendAMessage : public PPL::Processor {
public:
  SendAMessage();
  float callback(float, float, int) override;

private:
  std::unique_ptr<PPL::MessageWindow> msg_;
  PPL::ALContextManager sound_context_;
  int sound_id_revseatbelt_;
};
