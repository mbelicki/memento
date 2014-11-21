import QtQuick 2.0

Rectangle {
    id: root
    property color color: "white"
    property double maxOpacity: 0.1

    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: Qt.rgba(root.color.r, root.color.g, root.color.b, maxOpacity)
        }
        GradientStop {
            position: 1.0
            color: Qt.rgba(root.color.r, root.color.g, root.color.b, 0)
        }
    }
}
