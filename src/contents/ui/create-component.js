var component;
var parser;

function createObject(p) {
	parser = p;
    component = Qt.createComponent("KToggle.qml");
    if (component.status === Component.Ready || component.status === Component.Error) {
        finishCreation();
    } else {
        component.statusChanged.connect(finishCreation);
    }
}

function finishCreation() {
    if (component.status === Component.Ready) {
        var obj = component.createObject(root, parser);
        if (obj === null) {
            console.warn("Error creating object");
        } else {
			obj.embed()
		}
    } else if (component.status === Component.Error) {
        console.warn("Error loading component:", component.errorString());
    }
}
