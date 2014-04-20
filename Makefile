include Makefile.inc

DIRS = src
TESTDIRS = spec/qml
SPEC_BUILD_DIR = build/spec
DESIGNER_BUILD_DIR = build/designer
DESKTOP_BUILD_DIR = build/osx
SPEC_BUILD_DIR = build/spec

BUILD_DIRS = $(DESIGNER_BUILD_DIR) $(DESKTOP_BUILD_DIR) $(SPEC_BUILD_DIR)

# Output name and platform for actual application should be configured
# dynamically per project.  'osx' is a stand in for both until that's setup.

.phony: clean precompile all designer osx

all: run_tests osx

design: designer
	$(DESIGNER_BUILD_DIR)/Qkit.app/Contents/MacOS/Qkit

designer: precompile Qkit.pro
	$(ECHO) Desktop build in $(DESIGNER_BUILD_DIR)
	cd $(DESIGNER_BUILD_DIR); qmake ../../Qkit.pro -r -spec macx-clang "CONFIG+=x86_64 design"
	cd $(DESIGNER_BUILD_DIR); make -j 4 # make threads should be configured from env.

run_tests: run_specs run_qml_specs

run_specs: specs
	$(SPEC_BUILD_DIR)/spec | sed -f spec/specs.sed

run_qml_specs: qml_specs
	# example:
	# $(SPEC_BUILD_DIR)/qml_specs -input spec/qml/tst_object_name.qml | sed -f spec/specs.sed # colorize Qt's horrible test output.
	#
	# A more flexible test runner needs to be setup.

#specs for qml side
qml_specs: testprecompile precompile
	$(ECHO) Building QML specs in $(SPEC_BUILD_DIR)
	cd $(SPEC_BUILD_DIR); qmake qml_specs.pro
	cd $(SPEC_BUILD_DIR); make -j 4 # make threads should be configured from env.

#specs for c++/qt side
specs: precompile
	$(ECHO) Building specs in $(SPEC_BUILD_DIR)
	cd $(SPEC_BUILD_DIR); qmake specs.pro
	cd $(SPEC_BUILD_DIR); make -j 4  # make threads should be configured from env.

osx: precompile
	$(ECHO) Desktop build in $(DESKTOP_BUILD_DIR)
	# Application name must be configured.
	cd $(DESKTOP_BUILD_DIR); qmake Qkit.pro -r -spec macx-clang CONFIG+=x86_64 'DEFINES += osx_release'
	cd $(DESKTOP_BUILD_DIR); make -j 4 # make threads should be configured from env.
	cd $(DESKTOP_BUILD_DIR); macdeployqt ApplicationName.app -qmldir=../../src/qml
	# add plist files form framework that macdeployqt missed, for code signing.
	# must include *all* relevant frameworks.  These steps should probably be moved to a helper script, and additional make step.
	# cd $(DESKTOP_BUILD_DIR); cp /Applications/Qt/5.2.1/clang_64/lib/QtCore.framework/Contents/Info.plist ApplicationName.app/Contents/Frameworks/QtCore.framework/Resources
	# cd $(DESKTOP_BUILD_DIR); rm -rf ApplicationName.app/Contents/Frameworks/QtCore.framework/Contents
	# Apple Dev code signing:
	# cd $(DESKTOP_BUILD_DIR); codesign --deep --force --verify --sign "Developer ID Application: DevName" ApplicationName.app

precompile: $(BUILD_DIRS)
	$(ECHO) Build in ./
	for d in $(DIRS); do (cd $$d; $(MAKE) $(MFLAGS)); done

testprecompile: $(BUILD_DIRS)
	for d in $(TESTDIRS); do ($(ECHO) Build in $$d; cd $$d; $(MAKE) $(MFLAGS)); done

$(DESIGNER_BUILD_DIR):
	mkdir -p $(DESIGNER_BUILD_DIR)

$(DESKTOP_BUILD_DIR):
	mkdir -p $(DESKTOP_BUILD_DIR)

$(SPEC_BUILD_DIR):
	mkdir -p $(SPEC_BUILD_DIR)

clean:
	$(ECHO) cleaning up in ./
	for d in $(DIRS); do (cd $$d; $(MAKE) clean ); done
	$(ECHO) cleaning up in $(SPEC_BUILD_DIR)
	cd $(SPEC_BUILD_DIR); rm -rf *
	$(ECHO) cleaning up in $(DESIGNER_BUILD_DIR)
	cd $(DESIGNER_BUILD_DIR); rm -rf *
	$(ECHO) cleaning up in $(DESKTOP_BUILD_DIR)
	cd $(DESKTOP_BUILD_DIR); rm -rf *


