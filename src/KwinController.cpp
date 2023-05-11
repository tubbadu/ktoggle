#include "KwinController.h"

KwinController::KwinController(QObject *parent) :
	QObject(parent),
	m_process(new QProcess(this)),
	kwin(new DbusKwin(this))
{
	m_pos = "";
	m_size = "";
	m_class = "";
	m_program = "";
	m_arguments = QStringList();
	m_identifier = "";
	m_standalone = false;
}

int KwinController::run()
{
	return run(false);
}
int KwinController::run(const bool &detached)
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
	return process->processId();
}

void KwinController::setProgram(const QString &program, const QStringList &args){
	m_program = program;
	m_arguments = args;
}
void KwinController::setProgram(const QString &program){
	m_program = program;
}
void KwinController::setSize(const QString &size){
	m_size = size;
}
void KwinController::setPosition(const QString &pos){
	m_pos = pos;
}
void KwinController::setClass(const QString &Class){
	m_class = Class;
}
void KwinController::setName(const QString &Name){
	m_name = Name;
}
void KwinController::setIdentifier(const QString &id){
	m_identifier = id;
}
void KwinController::setStandalone(const bool &standalone){
	m_standalone = standalone;
}

QString KwinController::identifier(){
	return m_identifier;
}
bool KwinController::isStandalone(){
	return m_standalone;
}



void KwinController::addTrayIcon(const QString &icon){
	m_menu = new QMenu();
	m_trayicon = new QSystemTrayIcon();

	m_menu->addAction("Show");
	m_menu->addAction("Hide");
	m_menu->addAction("Toggle");
	m_menu->addAction("Quit " + m_class);
	m_menu->addAction("Quit KToggle");
	m_trayicon->setContextMenu(m_menu);

	QIcon kirigamiIcon = KIconLoader::global()->loadIcon(icon, KIconLoader::Toolbar);
    m_trayicon->setIcon(kirigamiIcon);
	m_trayicon->show();

	connect(m_menu, &QMenu::triggered, this, &KwinController::menuAction);
	connect(m_trayicon, &QSystemTrayIcon::activated, this, &KwinController::trayIconClicked);
}

bool KwinController::toggle(){
	return kwin->toggle(m_class, m_name);
}

bool KwinController::show(){
	return kwin->show(m_class, m_name);
}
bool KwinController::hide(){
	return kwin->hide(m_class, m_name);
}

bool KwinController::move(){
	if(!m_pos.contains(".")){
		qWarning() << "WARNING: position not specified correctly.";
		return false;
	} else {
		QString x = m_pos.split(",")[0];
		QString y = m_pos.split(",")[1];
		return kwin->move(m_class, m_name, x, y);
	}
}

bool KwinController::resize(){
	if(!m_size.contains(".")){
		qWarning() << "WARNING: size not specified correctly.";
		return false;
	} else {
		QString height = m_size.split(",")[0];
		QString width = m_size.split(",")[1];
		return kwin->resize(m_class, m_name, height, width);
	}
}

bool KwinController::setGeometry(){
	if(!m_size.contains(".")){
		qWarning() << "WARNING: size not specified correctly.";
		return false;
	} else if(!m_size.contains(".")){
		qWarning() << "WARNING: size not specified correctly.";
		return false;
	} else {
		QString x = m_pos.split(",")[0];
		QString y = m_pos.split(",")[1];
		QString height = m_size.split(",")[0];
		QString width = m_size.split(",")[1];
		return kwin->setGeometry(m_class, m_name, x, y, height, width);
	}
}


void KwinController::menuAction(QAction *action){
	if(action->text() == "Hide") {
		hide();
	} else if(action->text() == "Show") {
		show();
	} else if(action->text() == "Toggle") {
		toggle();
	} else if(action->text() == "Quit KToggle") {
		QCoreApplication::quit();
	} else if(action->text() == ("Quit " + m_class)){
		qWarning() << "wants to die";
		Q_EMIT wantsToDie();
	} else {
		qWarning() << "WARNING: unknown action detected:" << action->text();
	}
}
void KwinController::trayIconClicked(){
	toggle();
}
void KwinController::test(){
	kwin->test();
}