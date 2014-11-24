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

Dialog {
    property string name
    property color color

    canAccept: !!nameField.text

    Column {
        spacing: 10
        anchors.fill: parent

        DialogHeader {
            acceptText: "create"
        }

        TextField {
            id: nameField
            width: parent.width
            placeholderText: "Enter List Name"
            label: "List Name"
            text: name
            focus: true

            EnterKey.enabled: text.length > 0
            EnterKey.iconSource: "image://theme/icon-m-enter-accept"
            EnterKey.onClicked: accept()
        }

        ColorPicker {
            id: picker
            width: parent.width
            opacity: 0.8

            color: colors[Math.floor(Math.random() * colors.length)]

            rows: 3
            columns: 5
        }
    }

    onDone: {
        if (result === DialogResult.Accepted) {
            name = nameField.text
            color = picker.color
        }
    }
}

