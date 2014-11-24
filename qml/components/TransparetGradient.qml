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
