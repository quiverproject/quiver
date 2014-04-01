import QtQuick 2.1
import QtQuick.Layouts 1.1

import "/x/d/c4/clientc4/assets/javascript/fontawesome.js" as FontAwesome

Rectangle {
  id: iPhoneWindow
  width: 214
  height: 380

  color: "#1A1A1A"

  property var deviceType: "phone"
  property var deviceScale: 0.325
  property var appWidth: width
  property var appHeight: height

  Text {
    id: idText
    anchors.centerIn: parent
    text: "iPhone"
    color: "3398DA"

    font.pointSize: 24
  }
  ViewDesigner {}
}
