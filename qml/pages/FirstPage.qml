/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: page

    SilicaListView {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("Show Page 2")
                onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
            }
            MenuItem {
                text: qsTr("Test")
                onClicked: {
                    var lists = appModel.getOrderedLists();
                    console.log(lists.length);
                    console.log(lists[0].name);
                }
            }
        }

        VerticalScrollDecorator {}

        id: listOfLists
        model: listModel

        header: Item {
            height: 60
            width: parent.width

            Text {
                text: listOfLists.count + qsTr(" items")

                x: 30
                width: parent.width - x - details.width
                height: parent.height
                verticalAlignment: Text.AlignVCenter
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeSmall
            }
        }

        delegate: BackgroundItem {
            id: delegate
            height: 90
            width: parent.width

            onClicked: {
                if (appModel.setActiveList(listId)) {
                    pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
                }
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
                id: taskNumer

                anchors.fill: details
                text: "6"

                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: Theme.fontSizeHuge
                color: Theme.primaryColor
            }

            Rectangle {
                height: 1
                width: parent.width - details.width

                color: listColor
                opacity: 0.2
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
            }

            Text {
                id: infoLine

                x: 30
                anchors.top: nameLine.baseline
                width: parent.width - x - details.width
                height: 40

                text: "3 of 9 done, next due date: 2014-08-30"

                verticalAlignment: Text.AlignVCenter
                font.pixelSize: Theme.fontSizeTiny
                color: Theme.highlightColor
            }
        }
    }
}


