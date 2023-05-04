#include "DbusKwin.h"

DbusKwin::DbusKwin(QObject *parent) :
    QObject(parent)
{
}




QStringList DbusKwin::runScript(const QString filename){
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
	//QString filename = QCoreApplication::applicationDirPath() + "/listWindows.js";
	kwin->setProgram("dbus-send");
	kwin->setArguments(QStringList() << "--print-reply" << "--dest=org.kde.KWin" << "/Scripting" << "org.kde.kwin.Scripting.loadScript" << "string:" + filename);
	kwin->start();
	kwin->waitForFinished();

    QString output = QString::fromLocal8Bit(kwin->readAllStandardOutput());
	QString script_number = output.trimmed().split(" ").constLast();

	kwin->setArguments(QStringList() << "--print-reply" << "--dest=org.kde.KWin" << "/" + script_number << "org.kde.kwin.Script.run");
	kwin->start(); 
	kwin->waitForFinished();
	kwin->setArguments(QStringList() << "--print-reply" << "--dest=org.kde.KWin" << "/" + script_number << "org.kde.kwin.Script.stop");
	kwin->start(); 
	kwin->waitForFinished();
	
	kwin->setProgram("journalctl");
	kwin->setArguments(QStringList() << platform << "--since" << since);
	kwin->start();
	kwin->waitForFinished();

	QRegularExpression regex("^.*: js: >", QRegularExpression::MultilineOption);
    QStringList res = QString::fromLocal8Bit(kwin->readAllStandardOutput()).trimmed().replace(regex, "").split("\n");
	kwin->deleteLater();
	m_temp->remove();
	return res;
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

QString DbusKwin::searchWindow(const QString wclass, const QString wname, const QString wpid){
	QString script(
		"var wclass = '$CLASS'; \
		var wname = '$NAME'; \
		var wpid = '$PID'; \
		var clients = workspace.clientList(); \
		for (var i = 0; i < clients.length; i++) { \
			var client = clients[i]; \
			if(client.resourceClass == wclass && client.resourceName.includes(wname) && client.pid !== wpid){ \
				console.warn('>' + client.internalId); \
				break; \
			} \
		}"
	);
	script = script.replace("$CLASS", wclass).replace("$NAME", wname).replace("$PID", wpid);
	QStringList ret = runScript(createFile(script));
	if(ret.length() > 0){
		return ret[0];
	} else {
		return QString();
	}
}

QString DbusKwin::searchWindow(const QString wclass, const QString wname){
	QString script(
		"var wclass = '$CLASS'; \
		var wname = '$NAME'; \
		var clients = workspace.clientList(); \
		for (var i = 0; i < clients.length; i++) { \
			var client = clients[i]; \
			if(client.resourceClass == wclass && client.resourceName.includes(wname){ \
				console.warn('>' + client.internalId); \
				break; \
			} \
		}"
	);
	script = script.replace("$CLASS", wclass).replace("$NAME", wname);
	QStringList ret = runScript(createFile(script));
	if(ret.length() > 0){
		return ret[0];
	} else {
		return QString();
	}
}

QString DbusKwin::searchWindow(const QString wclass){
	QString script( 
		"var wclass = '$CLASS'; \
		var clients = workspace.clientList(); \
		for (var i = 0; i < clients.length; i++) { \
			var client = clients[i]; \
			if(client.resourceClass == wclass){ \
				console.warn('>' + client.internalId); \
				break; \
			} \
		}"
	);
	script = script.replace("$CLASS", wclass);
	QStringList ret = runScript(createFile(script));
	if(ret.length() > 0){
		return ret[0];
	} else {
		return QString();
	}
}

bool DbusKwin::activateWindow(const QString wid){
	QString script(
		"var wid = '$WID'; \
		var clients = workspace.clientList(); \
		let done = false; \
		for (var i = 0; i < clients.length; i++) { \
			var client = clients[i]; \
			if(client.internalId == wid){ \
				workspace.activeClient = client; \
				client.skipTaskbar = false; \
				client.skipPager = false; \
				client.skipSwitcher = false; \
				console.warn('>0'); \
				done = true; break; \
			} \
		} \
		if(!done){console.warn('>1');}"
	);
	script = script.replace("$WID", wid);
	QStringList ret = runScript(createFile(script));
	qWarning() << ret;
	if(ret.length() > 0){
		if(ret[0] == "0") {
			return true;
		}
	}
	return false;
}

QString DbusKwin::activeClientId(){
	QString script(
		"console.warn('>' + workspace.activeClient.internalId);"
	);
	QStringList ret = runScript(createFile(script));
	if(ret.length() > 0){
		return ret[0];
	} else {
		return QString();
	}
}

void DbusKwin::hideWindow(const QString wid){
	QString script(
		"var wid = '$WID'; \
		var clients = workspace.clientList(); \
		for (var i = 0; i < clients.length; i++) { \
			var client = clients[i]; \
			if(client.internalId == wid){ \
				client.minimized = true; \
				client.skipTaskbar = true; \
				client.skipPager = true; \
				client.skipSwitcher = true; \
			} \
		}"
	);

	script = script.replace("$WID", wid);
	runScript(createFile(script));
}