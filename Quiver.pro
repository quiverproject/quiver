# All
CONFIG += qt
#LIBS += -L$$PWD/lib #add -l[libname] for all additional project libs.
QT += widgets xml quick sql
DEFINES += QT_USE_QSTRINGBUILDER
#TARGET = design

INCLUDEPATH += inc
include(inc/cpp/headers.pri)
include(src/cpp/source.pri)

# OSX
mac {
        # lib.source = lib #add lib folder to deployment
        # DEPLOYMENTFOLDERS = lib #add lib folder to deployment
        QMAKE_LFLAGS = -v
        # ICON = appName.icns
        CONFIG += x86 # Only Intel binaries are accepted so force this
        plist.path = "$$DESTDIR/$$join(TARGET,,,.app)/Contents"
        plist.files = Info.plist
        INSTALLS += plist

# Debugging
#	CONFIG += debug
#	QMAKE_CXXFLAGS -= -O
#	QMAKE_CXXFLAGS -= -O1
#	QMAKE_CXXFLAGS -= -O2
#	QMAKE_CXXFLAGS -= -O3
#	QMAKE_CXXFLAGS *= -O0

# Release
        CONFIG += release
        QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.6
        QMAKE_CFLAGS += -gdwarf-2
        QMAKE_CXXFLAGS += -gdwarf-2
        # Select optimization level
        QMAKE_CXXFLAGS -= -O
        QMAKE_CXXFLAGS -= -O1
        QMAKE_CXXFLAGS -= -O2
        QMAKE_CXXFLAGS *= -O3 # '*' means add if not present
}

# Design mode verses deploy mode.
# However, the cpp switch may be unnecessary. Is there a reason to differentiate?
design {
  DEFINES += DESIGNER
  SOURCES += src/cpp/designer.cpp
  T
} else {
  TEMPLATE = lib
  CONFIG += staticlib
}

# Linux and non-OSX unixes.
!macx {
        # Deployment options for linux
        # Needs work.
        # Copy and pasted form another project, so not tested or ready.

        #QMAKE_RPATHDIR = $ORIGIN #<- This doesn't work
        QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN\''

        # Add more folders to ship with the application, here

        RC_FILE       = appName.rc

        IMAGEPATH = $$OUT_PWD

        installconfig.path = $$OUT_PWD/../install
        installraw.path = $$IMAGEPATH
        qtbin.path = $$IMAGEPATH
        qtsql.path = $$IMAGEPATH/sqldrivers
        qtplatforms.path = $$IMAGEPATH
        qtqml.path = $$IMAGEPATH
        qtimageformats.path = $$IMAGEPATH
        installicon.path = $$IMAGEPATH
        microsoftredist.path = $$IMAGEPATH

                # Prebuilt installer templates
        installconfig.files = $$PWD/installer/*

                # Qt requirements
        qtqml.files = $$[QT_INSTALL_QML]/QtQuick
        qtqml.files += $$[QT_INSTALL_QML]/QtQuick.2
        qtqml.files += $$[QT_INSTALL_QML]/QtGraphicalEffects
        qtqml.files += $$[QT_INSTALL_QML]/Qt
        qtimageformats.files = $$[QT_INSTALL_PLUGINS]/imageformats
}

win32 {

        qtbin.files = $$[QT_INSTALL_BINS]/Qt5Core.dll
        qtbin.files += $$[QT_INSTALL_BINS]/Qt5Gui.dll
        qtbin.files += $$[QT_INSTALL_BINS]/Qt5Network.dll
        qtbin.files += $$[QT_INSTALL_BINS]/Qt5Qml.dll
        qtbin.files += $$[QT_INSTALL_BINS]/Qt5Quick.dll
        qtbin.files += $$[QT_INSTALL_BINS]/Qt5Sql.dll
        qtbin.files += $$[QT_INSTALL_BINS]/Qt5V8.dll
        qtbin.files += $$[QT_INSTALL_BINS]/Qt5Widgets.dll
        qtbin.files += $$[QT_INSTALL_BINS]/Qt5Xml.dll
        qtbin.files += $$[QT_INSTALL_BINS]/icudt51.dll
        qtbin.files += $$[QT_INSTALL_BINS]/icuin51.dll
        qtbin.files += $$[QT_INSTALL_BINS]/icuuc51.dll
        qtbin.files += $$[QT_INSTALL_BINS]/libeay32.dll
        qtbin.files += $$[QT_INSTALL_BINS]/libssl32.dll
        qtbin.files += $$[QT_INSTALL_BINS]/libGLESv2.dll
        qtbin.files += $$[QT_INSTALL_BINS]/libEGL.dll
        qtbin.files += $$[QT_INSTALL_BINS]/D3DCompiler_43.dll

        qtsql.files = $$[QT_INSTALL_PLUGINS]/sqldrivers/qsqlite.dll

        qtplatforms.files = $$[QT_INSTALL_PLUGINS]/platforms/qwindows.dll

        microsoftredist.files = $$(VCINSTALLDIR)/redist/x86/Microsoft.VC100.OPENMP/vcomp100.dll
}

unix:!macx {
        installraw.files = $$PWD/lib/libraw_r.so*
        installraw.files += $$PWD/lib/libraw.so*

        qtbin.files = $$[QT_INSTALL_LIBS]/libQt5Core.so.5
        qtbin.files += $$[QT_INSTALL_LIBS]/libQt5Gui.so.5
        qtbin.files += $$[QT_INSTALL_LIBS]/libQt5Network.so.5
        qtbin.files += $$[QT_INSTALL_LIBS]/libQt5Qml.so.5
        qtbin.files += $$[QT_INSTALL_LIBS]/libQt5Quick.so.5
        qtbin.files += $$[QT_INSTALL_LIBS]/libQt5Sql.so.5
        qtbin.files += $$[QT_INSTALL_LIBS]/libQt5V8.so.5
        qtbin.files += $$[QT_INSTALL_LIBS]/libQt5Widgets.so.5
        qtbin.files += $$[QT_INSTALL_LIBS]/libQt5Xml.so.5
        qtbin.files += $$[QT_INSTALL_LIBS]/libQt5DBus.so.5
        qtbin.files += $$[QT_INSTALL_LIBS]/libicudata.so*
        qtbin.files += $$[QT_INSTALL_LIBS]/libicui18n.so*
        qtbin.files += $$[QT_INSTALL_LIBS]/libicuuc.so*

        qtsql.files = $$[QT_INSTALL_PLUGINS]/sqldrivers/libqsqlite.so

        qtplatforms.files = $$[QT_INSTALL_PLUGINS]/platforms
        qtplatforms.files += $$[QT_INSTALL_PLUGINS]/platformthemes
        installicon.files = $$PWD/assets/Icon



INSTALLS += TARGET installconfig installraw qtbin qtqml qtsql qtplatforms qtimageformats \
                                                microsoftredist installicon

externalLibs.source = lib
DEPLOYMENTFOLDERS += externalLibs


}
