import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {

    Label {
        id: label

        text: qsTr("Memento")

        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: Theme.highlightColor
        font.pixelSize: Theme.fontSizeSmall
    }

    CoverActionList {
        id: coverAction

        CoverAction {
            iconSource: "image://theme/icon-cover-next"
        }

        CoverAction {
            iconSource: "image://theme/icon-cover-new"
        }
    }
}


