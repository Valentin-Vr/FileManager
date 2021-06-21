import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    property var fileList

    ScrollView {
        id: scrollView
        anchors.fill: parent
        clip: true

        ListView {
            id: listView
            anchors.fill: parent
            anchors.leftMargin: 10

            clip: true
            highlightMoveDuration: 0
            highlightFollowsCurrentItem: true
            spacing: 5
            model: fileList

            delegate: Label {
                width: scrollView.width - 25
                height: implicitHeight * 2
                verticalAlignment: Text.AlignVCenter
                leftPadding: 10
                rightPadding: 10
                elide: Text.ElideRight
                text: modelData
                background: Rectangle {
                    color: index === listView.currentIndex ? "lightgrey" : "transparent"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        listView.currentIndex = index;
                    }
                }
            }
        }
    }
}
