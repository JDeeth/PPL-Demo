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
  PPL::ALContextManager snd_;
  int snd_revseatbelt_;
};
