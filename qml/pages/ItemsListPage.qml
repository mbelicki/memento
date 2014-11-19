import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: page
    SilicaListView {
        id: listView
        model: 20
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("settings")
                onClicked: console.log("no settings yet.")
            }
        }

        VerticalScrollDecorator {}

        header: PageHeader {
            title: appModel.activeList ? appModel.activeList.name : qsTr("unknown")
            description: "6 open tasks (3 done, 9 total)"
        }

        delegate: BackgroundItem {
            id: delegate
            height: 90
            width: parent.width

            Rectangle {
                id: details
                width: height
                height: parent.height
                anchors.right: parent.right

                color: appModel.activeList ? appModel.activeList.color : "white"
                opacity: 1 - index / listView.count
            }

            Rectangle {
                height: 1
                width: parent.width - details.width

                color: appModel.activeList ? appModel.activeList.color : "white"
                opacity: 0.2
            }

            Label {
                x: Theme.paddingLarge
                text: "Item " + index
                anchors.verticalCenter: parent.verticalCenter
                color: delegate.highlighted ? Theme.highlightColor : Theme.primaryColor
            }

            onClicked: console.log("Clicked " + index)
        }

    }
}





