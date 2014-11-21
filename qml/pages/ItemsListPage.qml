import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components" as Memento

Page {
    id: page

    property var model

    SilicaListView {
        id: listView

        model: page.model
        anchors.fill: parent

        header: PageHeader {
            title: page.model.name
            description: "6 open tasks (3 done, 9 total)"
        }

        delegate: Memento.ItemsListDelegate {
            id: delegate
            color: page.model.color
            onClicked: {
                page.model.setChecked(index, true)
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





