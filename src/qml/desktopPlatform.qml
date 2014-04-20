import QtQuick 2.2

// TODO: make this a general template that is built in c++ for any given target.
Rectangle { id: platform
  width:   1440          // 1280 // 1440 //1536
  height:  900           // 720  // 900 //864
  color: "#1A1A1A"

    // The devEnv holds the display environment for the QMLkit interactive
    // development display.  This is so the deployment targets can be mapped
    // into the developers display in real world size or with optional scaling.
    // TODO: Build these from the QML env, and project settings.
  property var devEnv: {
    type: "desktop";
    os: "osx";
    displayName: "27\" Cinema Display";
    screenMode: "windowable"; // or "dedicated" i.e. phone etc.
    widthReal: 650;  // mm  -- FIX: these measurements are device size not display size.
    heightReal: 491; // mm
    widthTruePixels: 2560;  // May be higher regular pixels for retina
    heightTruePixels: 1440;
    widthPixels: 2560;
    heightPixels: 1440;
    scale: 1.0
  }

    // We need 3 coordinate systems and a platform selector for special cases
    // Real world measurements in millimeters.
    // Relative measurements based on device size or font size (em?).
    // Absolute measurements in pixels. (how to handle retina?)
    // TODO: Create a db for as many devices / displays as possible.
  property var env: {
    type: "desktop";
    os: "osx";
    displayName: "27\" Cinema Display";
    screenMode: "windowable"; // or "dedicated" i.e. phone etc.
    widthReal: 650;  // mm  -- FIX: these measurements are device size not display size.
    heightReal: 491; // mm
    widthTruePixels: 2560;  // May be higher regular pixels for retina
    heightTruePixels: 1440;
    widthPixels: 2560;
    heightPixels: 1440;
    scale: 1.0
  }

  Text {
    id: idText
    anchors.centerIn: parent
    text: "Desktop"
    color: "#0098ff"
    font.pointSize: 24
  }

  Main {}
}
