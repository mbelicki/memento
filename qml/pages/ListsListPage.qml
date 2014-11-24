/*
 * Copyright 2014 Mateusz Belicki
 *
 * free.software@belickim.net
 *
 * This file is part of Memento (Sailfish OS todo app).
 *
 * Memento is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Memento is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Memento. If not, see <http://www.gnu.org/licenses/>.
 */

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
        console.log("DATA PATH: " + StandardPaths.data)

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


