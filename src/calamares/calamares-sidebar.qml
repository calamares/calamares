import QtQuick 2.3
import io.calamares.ui 1.0
import io.calamares.core 1.0

Column {

Rectangle {
    id: hello
    width: 200
    height: 100
    color: "red"

    Text {
        anchors.centerIn: parent
        text: Branding.string(Branding.VersionedName)
    }
}

/* perhaps we could show a branding image here */

Repeater {
    model: ViewManager
    Rectangle {
        width: 200
        height: 75
        color: "black"

        Text {
            color: completed ? "green" : "yellow"
            text: display
        }
    }
}

}
