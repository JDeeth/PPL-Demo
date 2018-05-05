#pragma once

#include <simpleini/SimpleIni.h>

#include "autoretract.h"

class Demo {
public:
  Demo();
  ~Demo();

private:
  const std::string ini_path_;
  CSimpleIniA ini_;

  AutoRetract autoretract_{ini_};
};
