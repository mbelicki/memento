import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property string name
    property color color: "cyan"

    canAccept: !!nameField.text

    Column {
        spacing: 10
        anchors.fill: parent

        DialogHeader {
            acceptText: "create"
        }

        TextField {
            id: nameField
            width: parent.width
            placeholderText: "Enter List Name"
            label: "List Name"
            text: name
            focus: true

            EnterKey.enabled: text.length > 0
            EnterKey.iconSource: "image://theme/icon-m-enter-accept"
            EnterKey.onClicked: accept()
        }

        ColorPicker {
            id: picker
            width: parent.width

            rows: 3
            columns: 5
        }
    }

    onDone: {
        if (result === DialogResult.Accepted) {
            name = nameField.text
            color = picker.color
        }
    }
}

