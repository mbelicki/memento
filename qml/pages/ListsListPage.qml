import QtQuick 2.0
import Sailfish.Silica 1.0
import "../components" as Memento

Page {
    id: page

    function monthToString(month) {
        var months = [ "January", "February", "March", "April", "May"
                     , "June", "July", "August", "September", "October"
                     , "November", "December"
                     ];
        return months[month]
    }

    function createDefaultListName() {
        var date = new Date()
        var month = monthToString(date.getMonth())
        return month + " " + date.getDate()
    }

    SilicaListView {

        id: listOfLists

        anchors.fill: parent
        model: listModel

        header: Item {
            height: 60
            width: parent.width

            Text {
                text: listOfLists.count + qsTr(" lists")

                x: 30
                width: parent.width - x
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeSmall
            }
        }

        delegate: Memento.ListsListDelegate {
            onClicked: {
                if (appModel.setActiveList(listId)) {
                    var model = appModel.createListModel(listId)
                    var page = pageStack.push(Qt.resolvedUrl("ItemsListPage.qml"), {"model": model})
                }
            }
        }

        PullDownMenu {
            MenuItem {
                text: qsTr("Add List")
                onClicked: {
                    var defaultName = createDefaultListName()
                    var dialog = pageStack.push( "../components/CreateListDialog.qml"
                                               , {"name": defaultName}
                                               )
                    dialog.accepted.connect(function() {
                        listModel.addTaskList(dialog.name, dialog.color)
                    })
                }
            }
        }

        VerticalScrollDecorator {}
    }
}


