import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.13 as Kirigami

import Launcher 1.0
import TrayIcon 1.0
import Embedder 1.0
Item{
	property string windowClass: ""
	property string windowName: ""
	property string program: ""
	property string icon: "/home/tubbadu/Pictures/SWsticker1.png"
	property bool noTray: false
	property string xy: "0,0"
	property string size: "500,700"
	property bool cmdToRaise: false

	Timer{
		running: true
		repeat: false
		interval: 1000
		onTriggered:{
			
		}
	}

	
	function embed(){
		console.warn("embed: ", embedder.height)
		embedder.setPosition(embedder.x, embedder.y)
		embedder.setSize(embedder.height, embedder.width)
		embedder.setClass(windowClass)
		embedder.setCmdToRaise(cmdToRaise)
		//embedder.setName(windowName)
		embedder.setProgram(program)
		if(!embedder.embed(embedder.getId())){
			embedder.run()
		} else {
			console.warn("window already present: catching it")
		}
		trayicon.setIcon(icon)
		trayicon.show()
	}

	function toggle(){
		embedder.toggle()
	}

	Embedder{
		id: embedder
		property int x: xy.split(",")[0]
		property int y: xy.split(",")[0]
		property int height: size.split(",")[0]
		property int width: size.split(",")[1]
	}

	TrayIcon{
		id: trayicon
		actions: ["show", "hide", "toggle"]
		property var execute: {
			"show": embedder.show,
			"hide": embedder.hide,
			"toggle": embedder.toggle
		}

		onAction: {
			execute[action.text]();
		}

		onClicked: {
			console.warn("clicked")
			embedder.toggle()
		}
	}
}