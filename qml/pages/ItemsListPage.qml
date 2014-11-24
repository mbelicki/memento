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





