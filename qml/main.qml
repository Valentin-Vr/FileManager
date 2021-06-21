import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("File manager")

    footer: Pane {
        Row {
            anchors.right: parent.right
            spacing: 10

            Button {
                text: qsTr("Apply")
                onClicked: { }
            }

            Button {
                text: qsTr("Cancel")
                onClicked: { root.close() }
            }
        }
    }

    Frame {
        anchors.fill: parent
        anchors.margins: 10
        leftPadding: 5
        rightPadding: 5


        ColumnLayout {
            anchors.fill: parent

            SplitView {
                Layout.fillWidth: true
                Layout.fillHeight: true

                FolderManager {
                    id: folderManager
                    SplitView.maximumWidth: parent.width * 2 / 3
                    SplitView.minimumWidth: parent.width / 2
                    SplitView.preferredWidth: parent.width / 2
                    SplitView.fillHeight: true
                }

                FileManager {
                    id: fileManager
                    SplitView.fillWidth: true
                    SplitView.fillHeight: true
                    fileList: folderManager.fileList
                }
            }
        }
    }
}
