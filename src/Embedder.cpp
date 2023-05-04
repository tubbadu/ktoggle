#include "Embedder.h"

Embedder::Embedder(QObject *parent) :
	QObject(parent),
	m_process(new QProcess(this)),
	kwin(new DbusKwin(this))
{
	m_wid = -1;
	m_pos = QPoint(0, 0);
	m_size = QSize(600, 500);
	m_class = "";
	m_program = "";
	m_arguments = QStringList();
	m_cmdToRaise = false;
	m_identifier = "";
	m_standalone = false;
}

int Embedder::run()
{
	return run(false);
}
int Embedder::run(const bool &detached)
{
	QProcess *process = new QProcess;
	if(m_program.length() < 0){
		qWarning() << "ERROR: trying to run program, but program is unspecified";
		QCoreApplication::quit();
	} if(m_arguments.length() > 0){
		process->setArguments(m_arguments);
	}
	process->setProgram(m_program);

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
	m_menu->addAction("Quit KToggle");
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
	if(m_wid.length() < 2){
		embed();
	}
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
	if(m_wid.length() < 2){
		embed();
	}
	if(m_cmdToRaise){
		//if(searchId().length() > 1){ // TODO improove time
		//	kwin->activateWindow(m_wid);
		//	qWarning() << "no need to run again, just raising";
		//} else {
			run(true);
			qWarning() << "run to raise";
		//	qWarning() << embed();
		//}
	} else {
		kwin->activateWindow(m_wid);
	}
}
void Embedder::hide(){
	if(m_wid.length() < 2){
		embed();
	}
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

bool Embedder::embed(){
	if(m_class.length() < 1){
		qWarning() << "ERROR: Class unspecified.";
		QCoreApplication::quit();
	}

	QString id = searchId();
	
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
	} else if(action->text() == "Quit KToggle") {
		QCoreApplication::quit();
	} else {
		qWarning() << "WARNING: unknown action detected:" << action->text();
	}
}
void Embedder::trayIconClicked(){
	toggle();
}

void Embedder::move(const QString &x, const QString &y){
	kwin->moveWindow(x, y);
}
void Embedder::resize(const QString &h, const QString &w){
	kwin->resizeWindow(h, w);
}
void Embedder::move(const QString &xy){
	QString x = xy.split(",")[0];
	QString y = xy.split(",")[1];
	kwin->moveWindow(x, y);
}
void Embedder::resize(const QString &size){
	QString h = size.split(",")[0];
	QString w = size.split(",")[1];
	kwin->resizeWindow(h, w);
}

void Embedder::test(){
	kwin->test();
}

void Embedder::setName(const QString &Name){
	m_name = Name;
}

QString Embedder::identifier(){
	return m_identifier;
}

void Embedder::setIdentifier(const QString &id){
	m_identifier = id;
}

QString Embedder::searchId(){
	QString id;

	if(m_name.length() > 0){
		if(m_pid > 0){
			id = kwin->searchWindow(m_class, m_name, QString::number(m_pid));
		} else {
			id = kwin->searchWindow(m_class, m_name);
		}
	} else {
		id = kwin->searchWindow(m_class);
	}

	return id;
}

bool Embedder::isStandalone(){
	return m_standalone;
}
void Embedder::setStandalone(const bool &standalone){
	m_standalone = standalone;
}