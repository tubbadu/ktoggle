#ifndef EMBEDDER_H
#define EMBEDDER_H

#include <QObject>
#include <QProcess>
#include <QWindow>
#include <QWidget>
#include <QDebug>
#include <QPoint>
#include <QSize>
#include <QMainWindow>
#include <QWindow>
#include <QWaylandCompositor>
#include <QWaylandSurface>
#include <QElapsedTimer>
#include <unistd.h>
#include "MainWindow.h"
#include <KWindowSystem>
#include <KX11Extras>
#include <KWindowInfo>
#include <QDateTime>
#include <QRegularExpression>
#include <QCoreApplication>

class Embedder : public QObject
{
    Q_OBJECT
public:
    explicit Embedder(QObject *parent = 0);
    Q_INVOKABLE int run(const bool &detached);
    Q_INVOKABLE int run();
	Q_INVOKABLE int pid();
	//Q_INVOKABLE int getWinID();
    //Q_INVOKABLE bool embed(const QString &program);
	Q_INVOKABLE bool embed(const int &wid);
	Q_INVOKABLE void setSize(const int &h, const int &w);
	Q_INVOKABLE void setPosition(const int &x, const int &y);
	Q_INVOKABLE void setProgram(const QString &program, const QStringList &args);
	Q_INVOKABLE void setProgram(const QString &program);
	Q_INVOKABLE void setCmdToRaise(const bool &cmdToRaise);
	Q_INVOKABLE void updateGeometry();
	Q_INVOKABLE void setClass(const QString &Class);
	Q_INVOKABLE int xdotool_getId();
	Q_INVOKABLE int qdbuskwin_getId();
	Q_INVOKABLE int kwin_getId();
	Q_INVOKABLE void onWindowAdded(WId id);
	//Q_INVOKABLE int waitForId();
	Q_INVOKABLE int getId();
	Q_INVOKABLE void toggle();
	Q_INVOKABLE void show();
	Q_INVOKABLE void hide();
	Q_INVOKABLE QStringList qdbuskwin_getWidList();

private:
    QProcess *m_process;
	//MainWindow *m_parentWindow;
	QWindow *m_window;
	//QWidget *m_container;
	int m_wid;
	QSize m_size;
	QPoint m_pos;
	QString m_forceMethod;
	QString m_class;
	QString m_program;
	QStringList m_arguments;
	int m_pid;
	bool m_cmdToRaise;
};

#endif