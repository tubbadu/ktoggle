#ifndef EMBEDDER_H
#define EMBEDDER_H
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



class Embedder : public QObject
{
    Q_OBJECT
public:
    explicit Embedder(QObject *parent = 0);
    Q_INVOKABLE int run(const bool &detached);
    Q_INVOKABLE int run();
	Q_INVOKABLE int pid();
	Q_INVOKABLE bool embed(const QString &Class);
	Q_INVOKABLE void setSize(const int &h, const int &w);
	Q_INVOKABLE void setPosition(const int &x, const int &y);
	Q_INVOKABLE void setProgram(const QString &program, const QStringList &args);
	Q_INVOKABLE void setProgram(const QString &program);
	Q_INVOKABLE void setCmdToRaise(const bool &cmdToRaise);
	Q_INVOKABLE void setClass(const QString &Class);
	Q_INVOKABLE void addTrayIcon(const QString &icon);
	Q_INVOKABLE void toggle();
	Q_INVOKABLE void show();
	Q_INVOKABLE void hide();
	Q_INVOKABLE bool isActiveClient();
	void menuAction(QAction *action);
	void trayIconClicked();
/*
signals:
	void menuAction(QAction *action);
	void trayIconClicked();*/

private:
    QProcess *m_process;
	QString m_wid;
	QSize m_size;
	QPoint m_pos;
	QString m_forceMethod;
	QString m_class;
	QString m_program;
	QStringList m_arguments;
	int m_pid;
	bool m_cmdToRaise;
	DbusKwin *kwin;
	QSystemTrayIcon *m_trayicon;
	QMenu *m_menu;
};

#endif