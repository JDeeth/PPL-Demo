PPL-Demo
========

This is a demonstration of [Philipp Ringler's Plugin Patterns Library](https://github.com/JDeeth/PPL), a set of C++ wrappers for the X-Plane SDK
and OpenGL/OpenAL.

This uses [my fork of PPL](https://github.com/JDeeth/PPL), which has a few
minor additions. These are marked in the comments.

To download along with the git submodules, use this command:

    git clone https://github.com/JDeeth/ppl-demo.git --recursive

then open `ppl-demo.pro` with Qt Creator. PPL and the demo plugin are
included as QMake subprojects.

This project has been developed under Linux. `plugin.pro` will definitely need
to be updated to compile under OSX and Windows, with the location of the
compiled PPL static library and OpenGL libraries. If you're able to make these
changes, please send a pull request! You should be able to compile PPL as a
subproject immediately.

When compiling the plugin, add `-recursive CONFIG+=withsound` to the QMake settings
in Qt Creator.

When testing the plugin, copy the `sounds` directory to the test aircraft folder.

--------------------------------------------------------------------------------

This project currently demonstrates these features of PPL:

* `DataRef` to access existing datarefs
* `OwnedData` to create new datarefs
* `Processor` for flight-loop callback functions
* `ALContextManager` to play sounds
* `PluginPath`
* `Log` and `LogWriter`
* `MenuItem` and `Action` for menu items
* `MessageWindow`
* `OnScreenDisplay`

These features are not demonstrated yet:

* `OwnedData` and `DataRef` with arrays and custom callbacks
* `Command` for accessing and creating commands
* `DrawCallback` for managing drawing-loop callbacks
* `FontMgr` to draw TTF fonts
* `LogicHandler`, kinda a more baroque `Processor`
* `OverlayGauge`, an OpenGL context for drawing on the 3D cockpit and in popup
   windows
* `Settings`, a wrapper around SimpleIni
* `Smoothed`, a very simple filter for smoothing out changing data
* `Texture`; loads a bitmap for OpenGL drawing
* `VertexBuffer`; wraps an OpenGL Vertex Buffer Object. Uses glMapBuffer.
