import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components" as Memento

BackgroundItem {
    id: delegate

    property color color

    height: 90
    width: parent.width

    Memento.TransparetGradient {
        anchors.fill: parent
        color: Theme.highlightColor
        maxOpacity: 0.07
    }

    Rectangle {
        id: colorBar
        width: 8
        height: parent.height
        anchors.left: parent.left

        color: delegate.color
        opacity: (1 - index / listView.count) * 0.8
    }

    Rectangle {
        id: details
        width: height
        height: parent.height
        anchors.left: colorBar.right

        color: Theme.highlightColor
        opacity: (1 - index / listView.count) * 0.1
    }


    Label {
        id: doneLabel
        anchors.centerIn: details
        text: "✓"
        font.pixelSize: Theme.fontSizeHuge
        visible: itemDone
    }


    Label {
        text: name
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: details.right
        anchors.margins: Theme.paddingMedium
        color: delegate.highlighted ? Theme.highlightColor : Theme.primaryColor
    }
}
