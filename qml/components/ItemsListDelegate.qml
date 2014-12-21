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

BackgroundItem {
    id: delegate

    property color color

    height: 90
    width: parent.width

    Memento.TransparentGradient {
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

        color: itemDone ? delegate.color : Theme.highlightColor
        opacity: (1 - index / listView.count) * (itemDone ? 0.4 : 0.1)
    }


    Label {
        id: doneLabel
        anchors.centerIn: details
        text: "✓"
        font.pixelSize: Theme.fontSizeHuge
        visible: itemDone
    }

    Label {
        id: nameLabel
        text: name
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: details.right
        anchors.margins: Theme.paddingMedium
        color: delegate.highlighted ? Theme.highlightColor : Theme.primaryColor
        opacity: itemDone ? 0.4 : 1
    }

    Label {
        anchors.top: nameLabel.baseline
        anchors.left: nameLabel.left
        text: (itemUrgent ? "urgent " : "") + (itemImportant ? "important" : "")
        color: Theme.highlightColor
        opacity: itemDone ? 0.4 : 1
        visible: itemUrgent || itemImportant
        font.pixelSize: Theme.fontSizeTiny
    }
}
