#include "TrayIcon.h"

TrayIcon::TrayIcon(QObject *parent) :
    QObject(parent),
    m_trayicon(new QSystemTrayIcon(this)),
	m_menu(new QMenu)
	
{
	m_trayicon->setContextMenu(m_menu);
	connect(m_menu, &QMenu::triggered, this, &TrayIcon::action);
}

void TrayIcon::setActions(const QStringList &actions){
	m_menu->clear();
	for ( const auto &i : actions )
	{
		m_menu->addAction(i);
	}
}

QStringList TrayIcon::actions(){
	QStringList actionList; // = new QStringList;
	for ( const auto &i : m_menu->actions()  )
	{
		actionList << i->text();
	}
	return actionList;
}

void TrayIcon::clearActions(){
    m_menu->clear();
}

void TrayIcon::show(){
    m_trayicon->show();
}

void TrayIcon::hide(){
    m_trayicon->hide();
}

void TrayIcon::setVisible(const bool &visible){
    m_trayicon->setVisible(visible);
}

bool TrayIcon::isVisible(){
	return m_trayicon->isVisible();
}

void TrayIcon::setIcon(const QString &icon){
	QIcon kirigamiIcon = KIconLoader::global()->loadIcon(icon, KIconLoader::Small);
    m_trayicon->setIcon(kirigamiIcon); //QIcon(icon));
}

QIcon TrayIcon::icon(){
	return m_trayicon->icon();
}

void TrayIcon::setToolTip(const QString &tooltip){
	m_trayicon->setToolTip(tooltip);
}

QString TrayIcon::toolTip(){
	return m_trayicon->toolTip();
}