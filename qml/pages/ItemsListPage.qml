import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components" as Memento

Page {
    id: page

    property var model
    property int openCount: model.size - model.doneCount

    SilicaListView {
        id: listView

        model: page.model
        anchors.fill: parent

        header: PageHeader {
            title: page.model.name
            description: page.openCount + qsTr(" open tasks (")
                         + page.model.doneCount + qsTr(" done, ")
                         + page.model.size + qsTr(" total)")
        }

        delegate: Memento.ItemsListDelegate {
            id: delegate
            color: page.model.color
            onClicked: {
                page.model.setChecked(index, !itemDone)
            }
        }

        PullDownMenu {
            MenuItem {
                text: qsTr("Add Item")
                onClicked: {
                    var dialog = pageStack.push("../components/CreateItemDialog.qml")
                    dialog.accepted.connect(function() {
                        page.model.createItem(dialog.name)
                    })
                }
            }
        }

        VerticalScrollDecorator {}
    }
}





