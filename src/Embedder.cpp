#include "Embedder.h"

Embedder::Embedder(QObject *parent) :
	QObject(parent),
	m_process(new QProcess(this)),
	m_parentWindow(new MainWindow)
{
	m_wid = -1;
	m_pos = QPoint(0, 0);
	m_size = QSize(600, 500);
	m_forceMethod = "";
}

int Embedder::launch(const QString &program)
{
	m_process->setProgram(program);
	m_process->startDetached();
	qWarning() << m_process->processId();
	return m_process->processId();
}

/*int Embedder::pid(){
	return m_process->processId();
}

int Embedder::getWinID()
{
	// X11 only!
	QString PId = QString::number(pid());
	//qWarning() << "pid:" << PId;
	QProcess *xdotool = new QProcess;
	QStringList args;
	args << "search" << "--onlyvisible" << "--pid" << PId;
	xdotool->setProgram("xdotool");
	xdotool->setArguments(args);
	xdotool->start();
	xdotool->waitForFinished(3000);
	
	QString output = QString::fromLocal8Bit(xdotool->readAllStandardOutput()).trimmed();
	//qWarning() << args << "\n" << output;

	int ID;
	QStringList IDs = output.split("\n");
	//qWarning() << IDs;
	if(IDs.size() > 1){
		// there are more than just one WId: take the last one
		ID = IDs[IDs.size()-1].toInt();
	} else if (output.size() < 1){
		// no WId returned
		ID = -1;
	} else {
		// just one WId
		ID = output.toInt();
	}
	
	//qWarning() << "--->" << args << output << "-" << IDs << "=" << QString::number(ID);
	return ID;
}*/

int Embedder::waitForId(const QString &Class){
	int ID;
	QElapsedTimer timer;
	timer.start();
	while(timer.elapsed() < 5000){ // after tot ms exit
		ID = getId(Class);
		if(ID > 0){
			return ID;
		} else {
			sleep(0.05);
		}
	}
	return -1;
}

int Embedder::xdotoolGetId(const QString &Class){
	QProcess *xdotool = new QProcess;
	QStringList args;
	args << "search" << "--onlyvisible" << "--class" << Class;
	xdotool->setProgram("xdotool");
	xdotool->setArguments(args);
	xdotool->start();
	xdotool->waitForFinished(3000);
	
	QString output = QString::fromLocal8Bit(xdotool->readAllStandardOutput()).trimmed();

	int ID;
	QStringList IDs = output.split("\n");
	if(IDs.size() > 1){
		// there are more than just one WId: take the last one
		ID = IDs[IDs.size()-1].toInt();
	} else if (output.size() < 1){
		// no WId returned
		ID = -1;
	} else {
		// just one WId
		ID = output.toInt();
	}
	return ID;
}

int Embedder::kwinGetId(const QString &Class){
	//for (auto it = windows.rend(); it != windows.rbegin(); --it) {
	for (auto w : kwin_getWindowList()) {
		WId window = w.toInt();
		auto windoInfo = KWindowInfo(window, NET::WMVisibleName, NET::WM2WindowClass);
		//qWarning() << window << windoInfo.visibleName() << windoInfo.windowClassName();
		if(windoInfo.windowClassName() == Class){
			return window;
		}
	}
	return -1;
}



int Embedder::getId(const QString &Class){
	if(m_forceMethod == "xdotool"){
		return xdotoolGetId(Class);
	} else if (m_forceMethod == "kwin"){
		return kwinGetId(Class);
	} else if(m_forceMethod == ""){
		if(KWindowSystem::isPlatformX11()){ // TODO tidy up
			return kwinGetId(Class);
		} else {
			qWarning() << "Error: Currently unsupported on this platform";
			return -1;
		}
	} else {
		qWarning() << "Error: Forced method unknow";
		return -1;
	}
}

void Embedder::toggle(){
	m_parentWindow->toggle();
}
void Embedder::show(){
	m_parentWindow->show();
	m_parentWindow->activateWindow();

}
void Embedder::hide(){
	m_parentWindow->hide();
}

void Embedder::setSize(const int &h, const int &w){
	m_size = QSize(h, w);
}
void Embedder::setPosition(const int &x, const int &y){
	m_pos = QPoint(x, y);
}

QStringList Embedder::kwin_getWindowList(){
	QDateTime datetime_now = QDateTime::currentDateTime();
	QString since = datetime_now.toString(Qt::ISODateWithMs).replace("T", " ");

	QProcess *kwin = new QProcess;
	QString filename = QCoreApplication::applicationDirPath() + "/listWindows.js";
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
	kwin->setArguments(QStringList() << "/usr/bin/kwin_x11" << "--since" << since);
	kwin->start();
	kwin->waitForFinished();

	QRegularExpression regex("^.*: js: >", QRegularExpression::MultilineOption);
    QStringList res = QString::fromLocal8Bit(kwin->readAllStandardOutput()).trimmed().replace(regex, "").split("\n");
	return res;
}


bool Embedder::embed(const QString &program, const QString &Class)
{
/*	m_parentWindow->move(m_pos);
	m_parentWindow->resize(m_size);
	m_parentWindow->show();
	return true;*/


	m_wid = getId(Class);
	if(m_wid < 1){
		// launch
		launch(program);
		m_wid = waitForId(Class);
		if(m_wid < 1){
			return false;
		}
	}

	m_parentWindow->move(m_pos);
	m_parentWindow->resize(m_size);

	m_window = QWindow::fromWinId(m_wid);
	m_window->setFlags(Qt::FramelessWindowHint);
	m_container = QWidget::createWindowContainer(m_window);
	m_parentWindow->setCentralWidget(m_container);
	m_container->show();
	m_window->show();
	m_parentWindow->show();

	return true;
}