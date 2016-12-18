/* Copyright (c) 2015, Jack Deeth
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of the FreeBSD Project.
 */

/* PPLDemo
 *
 * This plugin demonstrates the use of PPL and is intended as an easy starting
 * point for new plugin projects.
 *
 * It retracts the flaps when the aircraft exceeds a certain threshold speed.
 *
 * DataRef reads the airspeed and writes to the flap controls.
 *
 * OwnedData publishes the flap retraction threshold speed as a dataref. This
 * can be adjusted in-flight, for instance using DataRefEditor
 *
 * Log records status and error messages
 *
 * SimpleIni loads and saves the flap retraction threshold speed in an .ini file
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
