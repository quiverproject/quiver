import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.1
import QtQuick.Dialogs 1.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import Qt.labs.settings 1.0
import QtGraphicalEffects 1.0

import ""
import ""
import ""
import ""
import ""
import ""

Rectangle {
  id: viewDesigner

  anchors.centerIn: parent
  anchors.fill: parent

  color: backgroundColor

  property string db_name: "C4_dev"
  property url     server: "http://localhost"

  property string colorMode: "light"
  property color backgroundColor: Color.app
  property color lineColor: Color.app.lineColor
  property color activeColor: Color.app.activeColor
  property color hintedLineColor: Color.app.hintedLineColor

  Settings {
    id: genericSettings

    property alias colorMode: viewDesigner.colorMode
    property alias backgroundColor: viewDesigner.backgroundColor
    property alias lineColor: viewDesigner.lineColor
    property alias activeColor: viewDesigner.activeColor
    property alias hintedLineColor: viewDesigner.hintedLineColor
  }

  signal action(string action)

  signal addImages

  onColorModeChanged: {
    viewDesigner.backgroundColor = Color.app
    viewDesigner.lineColor = Color.app.lineColor
    viewDesigner.activeColor = Color.app.activeColor
    viewDesigner.hintedLineColor = Color.app
  }

  onAction: {
    App.actions[action]()
  }

  Component.onCompleted: {
    Crom.init_db(db_name)
    assets.init()
  }

  C4AssetsInterface {
    id: assets

    onAddImages: {
      loadImagesDialog.open()
    }
  }

  C4ImageGrid {
    id: imageGrid
    opacity: 1.0
    cellSize: thumbSize.value*1024

    anchors.left: leftSidebar.right
    anchors.top: toolBar.bottom
    anchors.right: rightSidebar.left
    anchors.bottom: bottomBar.top
    anchors.margins: 5
  }

}
