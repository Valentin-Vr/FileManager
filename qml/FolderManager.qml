import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import Ust1 1.0

Page {
    property var fileList
    property int _currentIndex: -1

    FileEngine{
        id: foldersModel
    }

    ScrollView {
        id: scrollView
        anchors.fill: parent
        anchors.rightMargin: 5
        clip: true

        ColumnLayout {
            anchors.fill: parent

            Repeater {
                id: repeater
                model: foldersModel
                delegate: RowLayout {
                    Layout.fillWidth: true
                    Layout.leftMargin: model.level * 20

                    Button {
                        Layout.preferredWidth: icon.width
                        Layout.preferredHeight: icon.height
                        background: Rectangle {
                            color: index === _currentIndex ? "lightgrey" : "transparent"
                        }
                        padding: 0
                        icon.source: model.isOpen ? "images/minus.png" : "images/plus.png"
                        enabled: model.childrenCount
                        onClicked: {
                            if (model.isOpen === false) foldersModel.nextFolder(index);
                            else {
                                _currentIndex = -1;
                                foldersModel.previousFolder(index);
                            }
                        }
                    }

                    Label {
                        Layout.preferredWidth: implicitWidth
                        Layout.preferredHeight: parent.height
                        text: model.path
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: 10
                        rightPadding: 10
                        background: Rectangle {
                            color: index === _currentIndex ? "lightgrey" : "transparent"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                _currentIndex = index;
                                foldersModel.createFileList(model.path + "/");
                                fileList = foldersModel.fileList;
                            }
                        }
                    }
                }
            }
        }
    }
}
