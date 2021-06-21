import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Ust1 1.0

Page {

    FileEngine{
        id: foldersModel
    }

    ScrollView {
        anchors.fill: parent
        clip: true

        ColumnLayout {
            anchors.fill: parent
            anchors.rightMargin: 20

            Repeater {

                id: repeater
                model: foldersModel

                RowLayout {
                    Layout.fillWidth: true
                    Layout.leftMargin: model.level * 30

                    Label {
                        id: openIndicator
                        text: model.isOpen ? "-" : "+"/*(model.childrenCount > 0 ? (model.isOpen ? "-" : "+") : "-")*/

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (model.isOpen === false) {
                                    foldersModel.nextFolder(index);
                                } else
                                    foldersModel.previousFolder(index);
                            }
                        }
                    }

                    Label {
                        Layout.fillWidth: true
                        text: model.path
                        //                        background: Rectangle {
                        //                            color: index == curIndex ? Material.accentColor : "transparent"
                        //                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                //                                foldersModel.nextFolder(index)
                            }
                            onDoubleClicked: {
                                //                                curIndex = index
                                //                                selectedModel.folder = model.url
                                //                                folderModel.folder = "file:///"
                                //                                folderModel.folder = model.url
                            }
                        }
                    }
                }
            }
        }
    }
}
