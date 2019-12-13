import QtQuick 2.0;
import QtQuick.Controls 2.3;
import io.calamares.modules.welcome 1.0;

Rectangle {
    width: 200;
    height: 200;
    color: "pink";

    Label {
        id: label;
        anchors.centerIn: parent;
        text: "Welcome to Calamares";
    }

    Button {
        anchors.top: label.bottom;
        text: PotatoConfig.helpUrl;

    }
}
