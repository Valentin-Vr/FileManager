import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {

    ScrollView {
        anchors {
            fill: parent
            margins: 10
        }
        clip: true

        ListView {
            anchors.fill: parent
            delegate: Rectangle {

            }
        }
    }

}
