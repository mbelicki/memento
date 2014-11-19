import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property string name

    Column {
        spacing: 10
        anchors.fill: parent

        DialogHeader {
            acceptText: "create"
        }

        TextField {
            id: nameField
            width: parent.width
            label: "item name"
            text: name

            EnterKey.enabled: text.length > 0
            EnterKey.iconSource: "image://theme/icon-m-enter-accept"
            EnterKey.onClicked: accept()
        }
    }

    onDone: {
        if (result === DialogResult.Accepted) {
            name = nameField.text
        }
    }
}


