#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QDebug>
#include <KIconThemes/KIconLoader>
//#include <KIconThemes/KIconTheme>

class TrayIcon : public QObject
{
    Q_OBJECT
	/*Q_PROPERTY(QString author
		READ author 
		WRITE setAuthor 
		NOTIFY authorChanged
	)*/

	Q_PROPERTY(QStringList actions
		READ actions 
		WRITE setActions 
	)

	/*Q_PROPERTY(QIcon icon
		READ icon 
		WRITE setIcon
	)*/

	
public:
    explicit TrayIcon(QObject *parent = 0);
	Q_INVOKABLE void clearActions();
	void setActions(const QStringList &actions);
	QStringList actions();
	Q_INVOKABLE void show();
	Q_INVOKABLE void hide();
	Q_INVOKABLE void setVisible(const bool &visible);
	Q_INVOKABLE void setIcon(const QString &icon);
	Q_INVOKABLE bool isVisible();
	Q_INVOKABLE QIcon icon();
	Q_INVOKABLE void setToolTip(const QString &tooltip);
	Q_INVOKABLE QString toolTip();

signals:
	void action(QAction *action);



private:
    QSystemTrayIcon *m_trayicon;
	QMenu *m_menu;
};

#endif