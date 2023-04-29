// Includes relevant modules used by the QML
import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.13 as Kirigami

import Launcher 1.0
import TrayIcon 1.0
import Embedder 1.0

Kirigami.ApplicationWindow {
	// ID provides unique identifier to reference this element
	id: window
	visible: false
	// Window title
	// i18nc is useful for adding context for translators, also lets strings be changed for different languages
	title: i18nc("@title:window", "Hello World")
	Launcher {
        id: launcher
    }

	// Initial page to be loaded on app load
	pageStack.initialPage: Kirigami.Page {
		Layout.fillWidth: true
		Layout.fillHeight: true
		Label{
			anchors.centerIn: parent
			text: "hello world!"
		}
	}

	TrayIcon{
		actions: ["show", "hide", "toggle"]
		property var execute: {
			"show": e.show,
			"hide": e.hide,
			"toggle": e.toggle
		}
		
		Component.onCompleted:{
			setIcon("/home/tubbadu/Pictures/SWsticker1.png")
			show()
			
			console.warn(actions)
		}

		onAction: {
			console.warn("action " + actions.keys)
			execute[action.text]();
		}
	}

	Embedder{
		id: e
		property string pclass: "kate"
		property string pcmd: "kate"

		Component.onCompleted:{
			setPosition(0, 0)
			setSize(800, 600)
			if(!embed(pcmd, pclass)){
				Qt.quit()
			}
		}
	}

	Timer{
		interval: 5000
		running: !true
		repeat: true
		onTriggered:{
			console.warn("t")
			e.toggle()
		}
	}
}