
import QtQuick 2.5
import QtQuick.Dialogs 1.2


FileDialog {
    id: fileDialog
    title: "Please choose a file"
    visible: true

    onAccepted: {
        console.log("You chose: " + fileDialog.fileUrls)
        Qt.quit()
    }
    onRejected: {
        console.log("Canceled")
        //Qt.quit()
    }
    //Component.onCompleted: visible = true
}

