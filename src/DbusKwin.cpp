#include "DbusKwin.h"

DbusKwin::DbusKwin(QObject *parent) :
    QObject(parent)
{
}

QStringList DbusKwin::runScript(const QString &filename, const bool &stopImediately){
	QString platform;
	if(KWindowSystem::isPlatformWayland()){
		platform = "/usr/bin/kwin_wayland";
	} else if(KWindowSystem::isPlatformX11()){
		platform = "/usr/bin/kwin_x11";
	} else {
		qWarning() << "WARNING: unknow platform, assuming X11. May not work. I'm sorry.";
		platform = "/usr/bin/kwin_x11";
	}
	QDateTime datetime_now = QDateTime::currentDateTime();
	QString since = datetime_now.toString(Qt::ISODateWithMs).replace("T", " ");

	QProcess *kwin = new QProcess;

	kwin->setProgram("dbus-send");
	kwin->setArguments(QStringList() << "--print-reply" << "--dest=org.kde.KWin" << "/Scripting" << "org.kde.kwin.Scripting.loadScript" << "string:" + filename);
	kwin->start();
	kwin->waitForFinished();

    QString output = QString::fromLocal8Bit(kwin->readAllStandardOutput());
	QString script_number = output.trimmed().split(" ").constLast();

	kwin->setArguments(QStringList() << "--print-reply" << "--dest=org.kde.KWin" << "/" + script_number << "org.kde.kwin.Script.run");
	kwin->start(); 
	kwin->waitForFinished();
	if(stopImediately){
		kwin->setArguments(QStringList() << "--print-reply" << "--dest=org.kde.KWin" << "/" + script_number << "org.kde.kwin.Script.stop");
		kwin->start(); 
		kwin->waitForFinished();
	}
	
	kwin->setProgram("journalctl");
	kwin->setArguments(QStringList() << platform << "--since" << since);
	kwin->start();
	kwin->waitForFinished();

	QRegularExpression regex("^.*: js: >", QRegularExpression::MultilineOption);
    QStringList res = QString::fromLocal8Bit(kwin->readAllStandardOutput()).trimmed().replace(regex, "").split("\n");
	kwin->deleteLater();
	m_temp->remove();
	if(res == QStringList("-- No entries --")){
		return QStringList();
	} else {
		return res;
	}
}

QStringList DbusKwin::runScript(const QString &filename){
	return runScript(filename, true);
}


QString DbusKwin::createFile(const QString filecontent){
	m_temp = new QTemporaryFile();
	m_temp->setAutoRemove(true);
    if (m_temp->open()) {
        QFile file(m_temp->fileName());
		if(file.open(QIODevice::WriteOnly)){
			file.write(filecontent.toUtf8());
			file.close();
			return m_temp->fileName();
		}
    } 
	return QString();
}

void DbusKwin::test(){
	QString script(
		"let clients = workspace.clientList(); \
		const maxLength = clients.reduce((max, current) => { \
			return current.resourceClass.length > max ? current.resourceClass.length : max; \
		}, 0); \
		console.warn('>' + 'Class'.padEnd(maxLength + 5, ' ') + 'Name'.padEnd(maxLength + 5, ' ')); \
		for(var i=0; i<clients.length; i++){ \
			console.warn('>' + clients[i].resourceClass.padEnd(maxLength + 5, ' ') + clients[i].resourceName); \
		}"
	);
	QTextStream cout(stdout);
	QStringList res = runScript(createFile(script));
	cout << "\033[1m" + res[0] + "\033[0m"<< Qt::endl;
	cout << res.mid(1).join("\n") << Qt::endl;
}


bool DbusKwin::toggle(const QString wclass, const QString wname, const bool &followDesktop){
	QString actionsBeginning = QString(" \
		var wname = '$NAME'; \
		var wclass = '$CLASS'; \
		let done = 0; \
	");
	QString actionsActive = QString(" \
		client.skipPager = true; \
		client.skipSwitcher = true; \
		client.minimized = true; \
		done=1; \
	");
	QString actionsInactive = QString(" \
		client.skipPager = false; \
		client.skipSwitcher = false; \
		client.minimized = false; \
		workspace.activeClient = client; \
		done=1; \
	");
	if(followDesktop){
		actionsInactive = "client.desktop = workspace.currentDesktop; " + actionsInactive;
	}

	QString actionsEnd = QString("console.warn('>' + done);");

	QString script = composeScript(actionsBeginning, actionsActive, actionsInactive, actionsEnd);

	script = script.replace("$CLASS", wclass).replace("$NAME", wname);
	QStringList ret = runScript(createFile(script));
	if(ret.length() > 0){
		if(ret[0] == "1") {
			return true;
		}
	}
	return false;
}

bool DbusKwin::move(const QString wclass, const QString wname, const QString x, const QString y){
	QString actionsBeginning = QString(" \
		var wname = '$NAME'; \
		var wclass = '$CLASS'; \
		let done = 0; \
	");
	QString actionsActive = QString(" \
		client.geometry = { \
			x: $X, \
			y: $Y, \
			width: client.width, \
			height: client.height \
		}; \
		done = 1; \
	");
	QString actionsInactive = actionsActive + "break;";
	QString actionsEnd = QString("console.warn('>' + done);");

	QString script = composeScript(actionsBeginning, actionsActive, actionsInactive, actionsEnd);

	script = script.replace("$X", x).replace("$Y", y).replace("$CLASS", wclass).replace("$NAME", wname);
	QStringList ret = runScript(createFile(script));

	if(ret.length() > 0){
		if(ret[0] == "1") {
			return true;
		}
	}
	return false;
}

bool DbusKwin::resize(const QString wclass, const QString wname, const QString height, const QString width){
	QString actionsBeginning = QString(" \
		var wname = '$NAME'; \
		var wclass = '$CLASS'; \
		let done = 0; \
	");
	QString actionsActive = QString(" \
		client.geometry = { \
			x: client.x, \
			y: client.y, \
			width: $WIDTH, \
			height: $HEIGHT \
		}; \
		done = 1; \
	");
	QString actionsInactive = actionsActive + "break;";
	QString actionsEnd = QString("console.warn('>' + done);");

	QString script = composeScript(actionsBeginning, actionsActive, actionsInactive, actionsEnd);

	script = script.replace("$WIDTH", width).replace("$HEIGHT", height).replace("$CLASS", wclass).replace("$NAME", wname);
	QStringList ret = runScript(createFile(script));

	if(ret.length() > 0){
		if(ret[0] == "1") {
			return true;
		}
	}
	return false;
}

bool DbusKwin::setGeometry(const QString wclass, const QString wname, const QString x, const QString y, const QString height, const QString width){
	QString actionsBeginning = QString(" \
		var wname = '$NAME'; \
		var wclass = '$CLASS'; \
		let done = 0; \
	");
	QString actionsActive = QString(" \
		client.geometry = { \
			x: $X, \
			y: $Y, \
			width: $WIDTH, \
			height: $HEIGHT \
		}; \
		done = 1; \
	");
	QString actionsInactive = actionsActive + "break;";
	QString actionsEnd = QString("console.warn('>' + done);");

	QString script = composeScript(actionsBeginning, actionsActive, actionsInactive, actionsEnd);

	script = script.replace("$WIDTH", width).replace("$HEIGHT", height).replace("$X", x).replace("$Y", y).replace("$CLASS", wclass).replace("$NAME", wname);
	QStringList ret = runScript(createFile(script));

	if(ret.length() > 0){
		if(ret[0] == "1") {
			return true;
		}
	}
	return false;
}

bool DbusKwin::show(const QString wclass, const QString wname){
	QString actionsBeginning = QString(" \
		var wname = '$NAME'; \
		var wclass = '$CLASS'; \
		let done = 0; \
	");
	QString actionsActive = QString("done = 1");
	QString actionsInactive = QString(" \
		client.skipPager = false; \
		client.skipSwitcher = false; \
		client.minimized = false; \
		workspace.activeClient = client; \
		done = 1; break; \
	");;
	QString actionsEnd = QString("console.warn('>' + done);");

	QString script = composeScript(actionsBeginning, actionsActive, actionsInactive, actionsEnd);

	script = script.replace("$CLASS", wclass).replace("$NAME", wname);
	QStringList ret = runScript(createFile(script));
	if(ret.length() > 0){
		if(ret[0] == "1") {
			return true;
		}
	}
	return false;
}

bool DbusKwin::hide(const QString wclass, const QString wname){
	QString actionsBeginning = QString(" \
		var wname = '$NAME'; \
		var wclass = '$CLASS'; \
		let done = 0; \
	");
	QString actionsActive = QString(" \
		client.skipPager = true; \
		client.skipSwitcher = true; \
		client.minimized = true; \
		done = 1; \
	");
	QString actionsInactive = actionsActive + "break;";
	QString actionsEnd = QString("console.warn('>' + done);");

	QString script = composeScript(actionsBeginning, actionsActive, actionsInactive, actionsEnd);

	script = script.replace("$CLASS", wclass).replace("$NAME", wname);
	QStringList ret = runScript(createFile(script));
	if(ret.length() > 0){
		if(ret[0] == "1") {
			return true;
		}
	}
	return false;
}


QString DbusKwin::composeScript(const QString &actionsBeginning, const QString &actionsActive, const QString &actionsInactive, const QString actionsEnd){
	return QString(actionsBeginning + 
		"if(workspace.activeClient.resourceClass == wclass && workspace.activeClient.resourceName.includes(wname)){ \
			var client = workspace.activeClient; \
			" + actionsActive + " \
		} else { \
			var clients = workspace.clientList(); \
			for (var i = 0; i < clients.length; i++) { \
				var client = clients[i]; \
				if(client.resourceClass == wclass && client.resourceName.includes(wname)){ \
					" + actionsInactive + " \
				} \
			} \
		}" + actionsEnd);
}


/* alternative implementation using only js, has some problems


	QString script(
		"workspace.clientAdded.connect(function(client) { \
			var wname = '$NAME'; \
			var wclass = '$CLASS'; \
			if(client.resourceClass == wclass && client.resourceName.includes(wname)){ \
				client.geometry = { \
					x: $X, \
					y: $Y, \
					width: $WIDTH, \
					height: $HEIGHT \
				}; \
			} \
		});"
	);
	
	script = script.replace("$X", x).replace("$Y", y).replace("$CLASS", wclass).replace("$NAME", wname);
	runScript(createFile(script), false);

	return true;
	



*/