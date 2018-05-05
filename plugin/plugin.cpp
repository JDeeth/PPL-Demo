// Copyright Jack Deeth, 2018 - see attached LICENSE

/* plugin.cpp
 *
 * This file sets up all the plugin's infrastructure: the five functions needed
 * by XPLM, PPL::Log (which is a singleton), and creating an instance of the
 * class which contains the plugin's functionality.
 *
 * This file demonstrates PPL::PluginPath and PPL::Log
 */

#include <memory>

#include <XPLMPlugin.h>

// PPL
#include <log.h>
#include <logwriter.h>
#include <pluginpath.h>

#include "ppldemo.h"

static std::unique_ptr<PPLDemo> ppldemo;

PLUGIN_API int XPluginStart(char* outName, char* outSig, char* outDesc) {
  strcpy(outName, PPLDemo::name().c_str());
  strcpy(outSig, PPLDemo::name().c_str());
  strcpy(outDesc, PPLDemo::description().c_str());

  // set up log
  auto filename = PPL::PluginPath::prependPlanePath("PPLDemo.log");
  PPL::LogWriter::getLogger().setLogFile(filename);

  using PPL::Log;
  Log() << Log::Info << "Plugin started. Hello world!" << Log::endl;

  // create instance of PPLDemo or log failure to do so
  try {
    ppldemo = std::make_unique<PPLDemo>();
  } catch (std::runtime_error e) {
    Log() << Log::Error << "Failure to construct Demo: " << e.what()
          << Log::endl;
  }

  return 1;
}

PLUGIN_API void XPluginStop(void) {
  // Destroy the instance of PPLDemo
  // I'm not sure this is necessary - on my machine (XP10, Linux) unique_ptrs
  // destroy themselves when the plugin is unloaded
  ppldemo.reset();

  using PPL::Log;
  Log() << Log::Info << "Plugin stopped." << Log::endl;
}

PLUGIN_API void XPluginDisable(void) {}
PLUGIN_API int XPluginEnable(void) {
  return 1;
}
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID, long, void*) {}
