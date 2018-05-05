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
#include <sstream>
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

// Project libraries
#include "demo.h"
#include <playannoyingsounds.h>
#include <sendamessage.h>

static const std::string LogFilename(
    PPL::PluginPath::prependPlanePath("PPLDemo.log"));
using PPL::Log;

static std::unique_ptr<Demo> demo;

// Draw popup window with compilation info
static std::unique_ptr<PPL::MessageWindow> compile_msg;

// Create submenu and actions
static PPL::MenuItem menu("PPL-Demo");

// Our classes and sim elements
static std::unique_ptr<PlayAnnoyingSounds> playannoyingsounds;
static std::unique_ptr<SendAMessage> sendmsg;

// Draw a translucent box with a title and concealed close button
static PPL::OnScreenDisplay osd(200, 50, "Hi I'm a PPL::OnScreenDisplay");

PLUGIN_API int XPluginStart(char* outName, char* outSig, char* outDesc) {
  {
    char name[] = "PPLDemo";
    char sig[] = "PPLDemo";
    std::stringstream desc;
    desc << "Compiled " << __DATE__ << " " << __TIME__;
    strcpy(outName, name);
    strcpy(outSig, sig);
    strcpy(outDesc, desc.str().c_str());
    compile_msg = std::make_unique<PPL::MessageWindow>(
        500, 100, name, desc.str().c_str(), false);
  }

  // set up log
  PPL::LogWriter::getLogger().setLogFile(LogFilename);
  Log() << Log::Info << "Plugin started. Hello world!" << Log::endl;

  // Link up our classes
  sendmsg = std::make_unique<SendAMessage>();
  playannoyingsounds = std::make_unique<PlayAnnoyingSounds>(menu);

  demo = std::make_unique<Demo>();

  return 1;
}

PLUGIN_API void XPluginStop(void) {
  Log() << Log::Info << "Plugin stopped." << Log::endl;
}

PLUGIN_API void XPluginDisable(void) {}
PLUGIN_API int XPluginEnable(void) {
  return 1;
}
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID, long, void*) {}
