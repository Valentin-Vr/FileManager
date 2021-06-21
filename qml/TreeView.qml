import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import Qt.labs.folderlistmodel 2.15

Pane {
    id: root

    property bool opened: false
    property string folder: "file:///E:/"
    property int curIndex
    property bool showDirs: true
    property bool showDirsFirst: true
    property bool showDotAndDotDot: false
    property bool showFiles: true
    property bool showHidden: false
    property var nameFilters: ["*.*"]
    property var listFiles: []

    width: 500
    height: 2000

    Component.onCompleted: {
        listModel.append({"level": 0, "name": root.folder.replace(/^(file:\/{3})/,""), "url": root.folder, "fileIsDir": true, "isOpen": false})
        console.log(folderModel.rootFolder)
    }

    function getSelectedUrl() {
        return listModel.get(curIndex).url
    }

    FolderListModel {
        id: selectedModel
        showDirs: false
        folder: root.folder
        onStatusChanged: {
            var files = [];
            if (selectedModel.status == FolderListModel.Ready) {
                for (var i = 0; i < selectedModel.count; i++) {
                    files.push(selectedModel.get(i, "fileName"))
                }
            }
            listFiles = files
        }
    }

    FolderListModel {
        id: folderModel
        showDirs: root.showDirs
        showDirsFirst: root.showDirsFirst
        showDotAndDotDot: root.showDotAndDotDot
        showFiles: root.showFiles
        showHidden: root.showHidden
        folder: root.folder
        nameFilters: root.nameFilters

        onStatusChanged: {
            if (folderModel.status == FolderListModel.Ready) {
                if (listModel.get(curIndex).fileIsDir) {
                    if (listModel.get(curIndex).isOpen) {
                        while(listModel.count != curIndex + 1 && listModel.get(curIndex + 1).level > listModel.get(curIndex).level) {
                            listModel.remove(curIndex + 1)
                        }
                    } else {
                        for (var i = 0; i < folderModel.count; i++) {
                            listModel.insert(curIndex + 1 + i, {"level": listModel.get(curIndex).level + 1, "name": folderModel.get(i, "fileName"), "url": String(folderModel.get(i, "fileUrl")), "fileIsDir": folderModel.get(i, "fileIsDir")})
                        }
                    }
                    listModel.get(curIndex).isOpen = !listModel.get(curIndex).isOpen
                }
            }
        }
    }

    ScrollView {
        anchors.fill: parent
        clip: true
        implicitHeight: layout.height
        implicitWidth: layout.width


        ColumnLayout {
            id: layout
            anchors.fill: parent

            Repeater {
                model: ListModel {id: listModel}

                RowLayout {
                    Layout.fillWidth: true
                    Layout.leftMargin: model.level * 30

                    Label {
                        id: openIndicator
                        text: model.isOpen ? "-" : "+"
                        visible: model.fileIsDir

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                curIndex = index
                                selectedModel.folder = model.url
                                folderModel.folder = "file:///"
                                folderModel.folder = model.url
                            }
                        }
                    }

                    Label {
                        Layout.fillWidth: true
                        text: model.name
                        background: Rectangle {
                            color: index == curIndex ? Material.accentColor : "transparent"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                curIndex = index
                                selectedModel.folder = model.url
                            }
                            onDoubleClicked: {
                                curIndex = index
                                selectedModel.folder = model.url
                                folderModel.folder = "file:///"
                                folderModel.folder = model.url
                            }
                        }
                    }
                }
            }
        }
    }
}
