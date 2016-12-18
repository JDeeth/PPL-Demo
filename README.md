PPL-Demo
========

This is a QMake project which contains the PPL library and a demo plugin as subprojects, such that both can be built and linked in one go.

https://github.com/JDeeth/PPL is a PPL fork which can be compiled, still as a static library, as a subproject. Just add `subproject` to the CONFIG list.

Rather than defining your PPL namespace with a command line flag, the `#define PRIVATENAMESPACE=<your unique identifier>` is stored in `common.pri`, which is then included in the plugin and PPL .pro files.

PPL is included as a *git submodule*. To download, run this command:

    git clone https://github.com/JDeeth/ppl-demo.git --recursive

Then rename the namespace in `common.pri`.
