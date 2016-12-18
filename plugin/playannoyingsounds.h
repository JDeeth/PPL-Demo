#pragma once

#include <vector>

#include <alcontextmanager.h>
#include <menuaction.h>
#include <menuitem.h>
#include <processor.h>

class PlayAnnoyingSounds : public PPL::Processor {
public:
  PlayAnnoyingSounds(PPL::MenuItem &menu);
  float callback(float, float, int) override;

private:
  PPL::ALContextManager snd_;
  std::vector<int> wavIds_;
  std::vector<int>::iterator nextWavId_;
  bool running_;

  class Enable : public PPL::MenuAction {
  public:
    Enable(PlayAnnoyingSounds &pas, PPL::MenuItem &menu);
    const std::string name() const override;
    void doAction() override;

  private:
    PlayAnnoyingSounds &pas_;
  };

  Enable enable_;
};
