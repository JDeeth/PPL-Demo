// Copyright Jack Deeth, 2018 - see attached LICENSE

/* ppldemo.h
 *
 * This class contains the functional parts of the plugin. Encapsulating them in
 * a class like this (rather than putting everything in global scope in the
 * plugin.cpp file) gives us much easier control of, and nicer syntax for,
 * initialisation order. Because this class is constructed by a call to
 * std::make_unique in XPluginStart, we know for certain that X-Plane is in the
 * correct state when our components start calling XPLMRegister... and
 * XPLMFind...
 *
 * This class also manages loading and saving from the .ini file.
 *
 * Demonstrates PPL::MenuItem, PPL::OnScreenDisplay, and SimpleIni
 */

#pragma once

// PPL
#include <menuitem.h>
#include <onscreendisplay.h>
#include <simpleini/SimpleIni.h>

#include "autoretract.h"
#include "playannoyingsounds.h"
#include "sendamessage.h"

class PPLDemo {
public:
  PPLDemo();
  ~PPLDemo();

  static std::string name();
  static std::string description();

private:
  const std::string ini_path_;
  CSimpleIniA ini_;

  // We're using C++11 default member initialisation for the following
  // data members
  // Remember: class members are initialised in the order they're listed here
  // (not the order used in the constructor initialiser list, if there is one)

  // Draw a translucent box on the screen
  PPL::OnScreenDisplay osd_{350, 50, description().c_str()};

  // Create an entry in the Plugins menu with the specified name
  PPL::MenuItem menu_{name().c_str()};

  // Our plugin components
  AutoRetract autoretract_{};
  PlayAnnoyingSounds playannoyingsounds_{menu_};
  SendAMessage sendmsg_{};
};
