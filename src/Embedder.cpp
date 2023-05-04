#include "Embedder.h"

Embedder::Embedder(QObject *parent) :
	QObject(parent),
	m_process(new QProcess(this)),
	kwin(new DbusKwin(this))
{
	m_wid = -1;
	m_pos = QPoint(0, 0);
	m_size = QSize(600, 500);
	m_forceMethod = "";
	m_class = "";
	m_program = "";
	m_arguments = QStringList();
	m_cmdToRaise = false;
	
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

void Embedder::addTrayIcon(const QString &icon){
	m_menu = new QMenu();
	m_trayicon = new QSystemTrayIcon();

	m_menu->addAction("Show");
	m_menu->addAction("Hide");
	m_menu->addAction("Toggle");
	m_trayicon->setContextMenu(m_menu);

	QIcon kirigamiIcon = KIconLoader::global()->loadIcon(icon, KIconLoader::Toolbar);
    m_trayicon->setIcon(kirigamiIcon);
	m_trayicon->show();

	connect(m_menu, &QMenu::triggered, this, &Embedder::menuAction);
	connect(m_trayicon, &QSystemTrayIcon::activated, this, &Embedder::trayIconClicked);
}

int Embedder::pid(){
	return m_pid;
}

void Embedder::toggle(){
	if(isActiveClient()){
		hide();
	} else {
		show();
	}
}

bool Embedder::isActiveClient(){
	return (kwin->activeClientId() == m_wid);
}

void Embedder::show(){
	kwin->activateWindow(m_wid);
}
void Embedder::hide(){
	kwin->hideWindow(m_wid);
}

void Embedder::setSize(const int &h, const int &w){
	m_size = QSize(h, w);
}
void Embedder::setPosition(const int &x, const int &y){
	m_pos = QPoint(x, y);
}
void Embedder::setClass(const QString &Class){
	m_class = Class;
}
void Embedder::setCmdToRaise(const bool &cmdToRaise){
	m_cmdToRaise = cmdToRaise;
}

bool Embedder::embed(const QString &Class){
	setClass(Class);
	QString id = kwin->searchWindow(Class).trimmed();
	if(id.length() > 1){
		m_wid = id;
		return true;
	} else {
		return false;
	}
}


void Embedder::menuAction(QAction *action){
	if(action->text() == "Hide") {
		hide();
	} else if(action->text() == "Show") {
		show();
	} else if(action->text() == "Toggle") {
		toggle();
	} else {
		qWarning() << "WARNING: unknown action detected:" << action->text();
	}
}
void Embedder::trayIconClicked(){
	toggle();
}