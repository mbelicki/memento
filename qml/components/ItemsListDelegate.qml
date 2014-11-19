import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: delegate

    property color color

    height: 90
    width: parent.width

    Rectangle {
        id: details
        width: height
        height: parent.height
        anchors.right: parent.right

        color: delegate.color
        opacity: 1 - index / listView.count
    }

    Rectangle {
        height: 1
        width: parent.width - details.width

        color: delegate.color
        opacity: 0.2
    }

    Label {
        x: Theme.paddingLarge
        text: name
        anchors.verticalCenter: parent.verticalCenter
        color: delegate.highlighted ? Theme.highlightColor : Theme.primaryColor
    }
}
