import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.1
import QtQuick.Dialogs 1.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0

// When this file is saved the app will automatically reload.

// example js import
import "../../assets/javascript/app.js" as App

Rectangle { id: main // only in Main.qml is id not `root` for global referencing
  anchors { fill:parent; }
  color: "transparent"

  // workspace

    // example:
  Rectangle { id: centeredBox
    anchors {centerIn: parent;}
    width: idText.width // example of pulling an object from a higher scope.
    height: idText.height + titleTest.height*2
    color: "transparent"
    Text { id: titleTest
      anchors {bottom: parent.bottom;horizontalCenter: parent.horizontalCenter;}
      color: "#ff9800"
      font {pointSize: 48}
      text: App.name
    }
  }

  // private parameters and methods
  QtObject { id: p
  }
  Component.onCompleted: {
  }
}
