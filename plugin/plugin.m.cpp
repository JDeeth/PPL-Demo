/* Copyright (c) 2016, Jack Deeth
 * For licensing information see LICENSE.
 */

/* PPLDemo
 *
 * This plugin demonstrates the use of PPL and is intended as an easy starting
 * point for new plugin projects.
 *
 */

// Standard libraries
#include <memory>
#include <string>
#include <vector>

// SDK libraries
#include <XPLMPlugin.h>
#include <XPLMProcessing.h>
#include <XPLMUtilities.h>

// PPL libraries
#include <log.h>
#include <logwriter.h>
#include <menuitem.h>
#include <onscreendisplay.h>
#include <pluginpath.h>
#include <simpleini/SimpleIni.h>

// Project libraries
#include <flapretractor.h>
#include <playannoyingsounds.h>
#include <sendamessage.h>

// Declare `ini` file and the ini and log filenames
CSimpleIniA ini;
const std::string IniFilename(PPL::PluginPath::prependPlanePath("PPLDemo.ini"));
const std::string LogFilename(PPL::PluginPath::prependPlanePath("PPLDemo.log"));

// Create submenu and actions
PPL::MenuItem menu("PPL-Demo");

// Our classes and sim elements
FlapRetractor flapretractor(ini, menu);
PlayAnnoyingSounds playAnnoyingSounds(menu);
SendAMessage sendmsg();

// Draw a translucent box with a title and concealed close button
PPL::OnScreenDisplay osd(200, 50, "Hi I'm a PPL::OnScreenDisplay");

PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc) {
  char pluginName[] = "PPLDemo";
  char pluginSig[] = "PPLDemo";
  char pluginDesc[] = "Demonstrates PPL features.";
  strcpy(outName, pluginName);
  strcpy(outSig, pluginSig);
  strcpy(outDesc, pluginDesc);

  // set up log
  using PPL::Log;
  PPL::LogWriter::getLogger().setLogFile(LogFilename);
  Log() << Log::Info << "Plugin started. Hello world!" << Log::endl;

  // set up ini
  SI_Error iniState = ini.LoadFile(IniFilename.c_str());
  if (iniState < 0) {
    Log() << Log::Warn
          << "Ini file not found. Will create new one with default values."
          << Log::endl;
    ini.SetDoubleValue("Config", "FlapRetractSpeedKts", 80);
    ini.SaveFile(IniFilename.c_str());
  }

  // Link up our classes
  flapretractor.hookToSim();
  return 1;
}

PLUGIN_API void XPluginStop(void) {
  // Unlink our classes
  flapretractor.unhookFromSim();

  // Save changes to .ini file
  using PPL::Log;
  Log() << Log::Info << "Saving settings file." << Log::endl;
  ini.SaveFile(IniFilename.c_str());

  Log() << Log::Info << "Plugin stopped." << Log::endl;
}

PLUGIN_API void XPluginDisable(void) {}
PLUGIN_API int XPluginEnable(void) { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID, long, void *) {}
