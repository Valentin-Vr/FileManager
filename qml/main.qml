import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("File manager")

//    TreeView {
//        anchors.fill: parent
//        showFiles: false
//    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10

        FolderManager {
            id: folderManager
            Layout.fillHeight: true
            Layout.minimumWidth: parent.width / 3
            Layout.preferredWidth: parent.width / 3
            Layout.maximumWidth: parent.width * 2 / 3
        }

//        FileManager {
//            id: fileManager
//            Layout.fillHeight: true
//            Layout.fillWidth: true
//        }
    }

//    ListView{
//        id: listView
//        model: foldersModel
//        anchors.fill: parent

//        delegate: Rectangle {
//            width: 150
//            height: 30
//            border.color: area.pressed ? "gold" : "black"

//            Text {
//                id: textDelegate
//                anchors.centerIn: parent
//                text: model.path
//            }

//            MouseArea{
//                id: area
//                anchors.fill: parent
//                onClicked: {
//                    console.log(index)
//                    foldersModel.nextFolder(index)
////                    label2.text = model.name
////                        menu.visible = true
//                }
//            }
//        }
//    }
}
