import QtQuick 2.15
import QtQuick.Window 2.14
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.2
import org.kde.kirigami 2.13 as Kirigami

import Launcher 1.0
import TrayIcon 1.0
import Embedder 1.0
import "create-component.js" as CreateComponent

Item {
	id: root
	visible: false
	//title: i18nc("@title:window", "KToggle")


	function newRequest(instanceId, message) {
		let parser = JSON.parse(message)
		let present = alreadyPresent(parser.windowClass, parser.windowName)
		if(!present){
			console.warn("new request:", message)
			CreateComponent.createObject(parser)
		} else {
			console.warn("already present")
			present.toggle()
		}
    }

	function alreadyPresent(Class, Name){
		for(let i=0; i<root.children.length; i++){
			let obj = root.children[i]
			if(obj.windowClass === Class && (obj.windowName.includes(Name) || !Name)){
				obj.toggle()
				return obj
			}
		}
		return undefined
	}
}