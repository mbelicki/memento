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
    height: 90
    width: parent.width

    property int __undoneCount: listSize - doneCount

    Memento.TransparentGradient {
        anchors.fill: parent
        color: Theme.highlightColor
        maxOpacity: 0.07
    }

    Rectangle {
        id: details

        anchors.right: parent.right
        width: height
        height: parent.height

        color: listColor
        opacity: delegate.highlighted ? 0.2 : 0.8

    }

    Text {
        id: taskNumber

        anchors.fill: details
        text: __undoneCount

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Theme.fontSizeHuge
        color: Theme.primaryColor
    }

    Text {
        id: nameLine

        x: 30
        width: parent.width - x - details.width
        height: parent.height * 0.66

        text: name
        clip: true

        verticalAlignment: Text.AlignVCenter
        font.pixelSize: Theme.fontSizeMedium
        color: Theme.primaryColor
        opacity: __undoneCount > 0 ? 1 : 0.4
    }

    Text {
        id: infoLine

        x: 30
        anchors.top: nameLine.baseline
        width: parent.width - x - details.width
        height: 40

        text: doneCount + " of " + listSize + " done"

        verticalAlignment: Text.AlignVCenter
        font.pixelSize: Theme.fontSizeTiny
        color: Theme.highlightColor
    }
}
