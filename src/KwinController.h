#ifndef KWINCONTROLLER_H
#define KWINCONTROLLER_H
// TODO remove unused libraries (also in cmake!)
#include <QObject>
#include <QProcess>
#include <QWindow>
#include <QWidget>
#include <QDebug>
#include <QPoint>
#include <QSize>
#include <QMainWindow>
#include <QWindow>
#include <QElapsedTimer>
#include <unistd.h>
#include <KWindowSystem>
#include <KX11Extras>
#include <KWindowInfo>
#include <QDateTime>
#include <QRegularExpression>
#include <QCoreApplication>
#include <KIconThemes/KIconLoader>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QAction>

#include "DbusKwin.h"
#include "TrayIcon.h"

class KwinController : public QObject
{
    Q_OBJECT
public:
    explicit KwinController(QObject *parent = 0);
    Q_INVOKABLE int run(const bool &detached);
    Q_INVOKABLE int run();
	Q_INVOKABLE void setSize(const int &h, const int &w);
	Q_INVOKABLE void setPosition(const int &x, const int &y);
	Q_INVOKABLE void setProgram(const QString &program, const QStringList &args);
	Q_INVOKABLE void setProgram(const QString &program);
	Q_INVOKABLE void setClass(const QString &Class);
	Q_INVOKABLE void setName(const QString &Name);
	Q_INVOKABLE void setIdentifier(const QString &id);
	Q_INVOKABLE void setStandalone(const bool &standalone);

	Q_INVOKABLE QString identifier();
	Q_INVOKABLE bool isStandalone();

	Q_INVOKABLE void addTrayIcon(const QString &icon);
	Q_INVOKABLE bool toggle();
	Q_INVOKABLE bool show();
	Q_INVOKABLE bool hide();
	Q_INVOKABLE void move(const QString &x, const QString &y);
	Q_INVOKABLE void move(const QString &xy);
	Q_INVOKABLE void resize(const QString &h, const QString &w);
	Q_INVOKABLE void resize(const QString &size);
	Q_INVOKABLE void test();	
	
	void menuAction(QAction *action);
	void trayIconClicked();

signals:
	void wantsToDie();

private:
    QProcess *m_process;
	QString m_wid;
	QSize m_size;
	QPoint m_pos;
	QString m_class, m_name;
	QString m_program;
	QStringList m_arguments;
	DbusKwin *kwin;
	QSystemTrayIcon *m_trayicon;
	QMenu *m_menu;
	QString m_identifier;
	bool m_standalone;
};

#endif