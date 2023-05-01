#include "Embedder.h"

Embedder::Embedder(QObject *parent) :
	QObject(parent),
	m_process(new QProcess(this))
{
	m_wid = -1;
	m_pos = QPoint(0, 0);
	m_size = QSize(600, 500);
	m_forceMethod = "";
	m_class = "";
	m_program = "";
	m_arguments = QStringList();
	m_cmdToRaise = false;
	QObject::connect(KX11Extras::self(), &KX11Extras::windowAdded, this, &Embedder::onWindowAdded);
}

int Embedder::run()
{
	return run(false);
}
int Embedder::run(const bool &detached)
{
	QProcess *process = new QProcess;
	process->setProgram(m_program);
	process->setArguments(m_arguments);
	if(detached){
		qWarning() << "eh no eh";
		process->startDetached();
	} else {
		process->start();
	}
	m_pid = process->processId();
	return m_pid;
}

void Embedder::setProgram(const QString &program, const QStringList &args){
	m_program = program;
	m_arguments = args;
}
void Embedder::setProgram(const QString &program){
	m_program = program;
}

int Embedder::pid(){
	return m_pid;
}


void Embedder::onWindowAdded(WId id){
	auto windoInfo = KWindowInfo(id, NET::WMVisibleName, NET::WM2WindowClass);
	//qWarning() << id << windoInfo.visibleName() << windoInfo.windowClassClass();
	if(windoInfo.windowClassClass() == m_class){
		if(m_wid < 1){
			embed(id);
		}
	}
}
/*
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

int Embedder::xdotool_getId(){
	QProcess *xdotool = new QProcess;
	QStringList args;
	args << "search" << "--onlyvisible" << "--class" << m_class;
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

QStringList Embedder::qdbuskwin_getWidList(){
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

int Embedder::qdbuskwin_getId(){
	//for (auto it = windows.rend(); it != windows.rbegin(); --it) {
	for (auto w : qdbuskwin_getWidList()) {
		WId window = w.toInt();
		auto windoInfo = KWindowInfo(window, NET::WMVisibleName, NET::WM2WindowClass);
		//qWarning() << window << windoInfo.visibleName() << windoInfo.windowm_className();
		if(windoInfo.windowClassName() == m_class){
			return window;
		}
	}
	return -1;
}

int  Embedder::kwin_getId(){
	// get window list
	for(auto window : KWindowSystem::windows()){
		auto windoInfo = KWindowInfo(window, NET::WMVisibleName, NET::WM2WindowClass);
		if(windoInfo.windowClassClass() == m_class){
			return window;
		}
	}
	return -1;
}

void Embedder::setClass(const QString &Class){
	m_class = Class;
}

void Embedder::setCmdToRaise(const bool &cmdToRaise){
	m_cmdToRaise = cmdToRaise;
}

int Embedder::getId(){
	if(m_forceMethod == "xdotool"){
		return xdotool_getId();
	} else if (m_forceMethod == "kwin"){
		return kwin_getId();
	} else if(m_forceMethod == ""){
		if(KWindowSystem::isPlatformX11()){ // TODO tidy up
			return kwin_getId();
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
	//m_parentWindow->toggle();
	if(KX11Extras::activeWindow() == m_window->winId()){
		hide();
	} else {
		bool wasVisible = m_window->isVisible();
		show();
		if(m_window->isVisible() && wasVisible && m_cmdToRaise){
			run(!true);
			qWarning() << "relaunching";
		}
	}
}

void Embedder::show(){
	m_window->show();
	m_window->raise();
	m_window->requestActivate();
	KX11Extras::forceActiveWindow(m_window->winId());
}
void Embedder::hide(){
	m_window->hide();
}

void Embedder::setSize(const int &h, const int &w){
	m_size = QSize(h, w);
}
void Embedder::setPosition(const int &x, const int &y){
	m_pos = QPoint(x, y);
}

void Embedder::updateGeometry(){
	qWarning() << "updated geometry";
	m_window->resize(m_size);
	m_window->setPosition(m_pos);
	// run another times otherwise it won't work, dunno why
	m_window->resize(m_size);
	m_window->setPosition(m_pos);
}

bool Embedder::embed(const int &wid){
	if(wid < 1){
		return false;
	}
	m_wid = wid;
	m_window = QWindow::fromWinId(m_wid);
	m_window->setFlags(Qt::FramelessWindowHint);
	updateGeometry();
	m_window->show();
	
	return true;
}