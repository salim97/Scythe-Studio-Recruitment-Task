import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import Qt.labs.platform 1.1
import Qt.labs.qmlmodels 1.0
import QtQuick.Controls 1.4

Window {
    id: root
    width: 640
    height: 600
    visible: true
    title: qsTr("Hello World")

    ColumnLayout{

        anchors.fill: parent


        RowLayout{

            Layout.fillWidth: true

            FolderDialog {
                id: openFolderDialog
                currentFolder: ""
                folder: StandardPaths.standardLocations(StandardPaths.DesktopLocation)[0]

                onAccepted: {
                    inputTextAddPath.text = folder
                }
            }
            //            FileDialog {
            //                id: openFolderDialog
            //                currentFolder: ""
            //                folder: StandardPaths.standardLocations(StandardPaths.DesktopLocation)[0]

            //                onAccepted: {
            //                     inputTextAddPath.text = folder
            //                }
            //            }




            TextField {
                id: inputTextAddPath
                Layout.fillWidth: true

                placeholderText: qsTr("Add path to watch")
                MouseArea {
                    anchors.fill: parent
                    onClicked:{
                        openFolderDialog.open();

                    }


                }


            }




            Button {
                text: "Add"
                onClicked: {
                    fileSystemWatcherService.onAddClicked(inputTextAddPath.text)
                    inputTextAddPath.text = ""
                }
            }
        }

        Label {
            text: "Watched paths"
        }
        ListView {
            height: 200

            model: WatchPathModel.paths

            delegate:  RowLayout{

                Layout.fillWidth: true
                Text {
                    text: modelData
                }

                Button {
                    text: "Remove"
                    onClicked: {
                        fileSystemWatcherService.onRemove(modelData)

                    }
                }
            }
        }

        TableView {

            TableViewColumn {
                   role: "EvetType"
                   title: "Evet Type"

               }
               TableViewColumn {
                   role: "Path"
                   title: "Path"

               }
               TableViewColumn {
                      role: "IsFolder"
                      title: "Is Folder"

                  }
                  TableViewColumn {
                      role: "TimeStamp"
                      title: "TimeStamp"

                  }

            Layout.fillWidth: true
            height: 200
            model: EventLogModel


            itemDelegate: RowLayout{

                Layout.fillWidth: true
                Text {
                    text: styleData.value
                }


            }

        }

        RowLayout{
            Layout.fillWidth: true

            Button {
                text: "Clear"
                onClicked: fileSystemWatcherService.onClearClicked()
            }
            Button {
                text: "Start"
                onClicked: fileSystemWatcherService.onStartClicked()
            }
            Button {
                text: "Stop"
                onClicked: fileSystemWatcherService.onStopClicked()
            }

        }

    }

}
