import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components" as Memento

BackgroundItem {
    id: delegate
    height: 90
    width: parent.width

    Memento.TransparetGradient {
        anchors.fill: parent
        color: Theme.highlightColor
        maxOpacity: 0.07
    }

    Rectangle {
        id: details

        anchors.right: parent.right
        width: height
        height: parent.height

        color: listColor
        opacity: delegate.highlighted ? 0.2 : 0.8

    }

    Text {
        id: taskNumer

        anchors.fill: details
        text: "6"

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Theme.fontSizeHuge
        color: Theme.primaryColor
    }

    Text {
        id: nameLine

        x: 30
        width: parent.width - x - details.width
        height: parent.height * 0.66

        text: name
        clip: true

        verticalAlignment: Text.AlignVCenter
        font.pixelSize: Theme.fontSizeMedium
        color: Theme.primaryColor
    }

    Text {
        id: infoLine

        x: 30
        anchors.top: nameLine.baseline
        width: parent.width - x - details.width
        height: 40

        text: "3 of 9 done"

        verticalAlignment: Text.AlignVCenter
        font.pixelSize: Theme.fontSizeTiny
        color: Theme.highlightColor
    }
}
