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
#include <QWaylandCompositor>
#include <QWaylandSurface>
#include <QElapsedTimer>
#include <unistd.h>
#include "MainWindow.h"
#include <KWindowSystem>
#include <KX11Extras>
#include <KWindowInfo>


class Embedder : public QObject
{
    Q_OBJECT
public:
    explicit Embedder(QObject *parent = 0);
    Q_INVOKABLE int launch(const QString &program);
	//Q_INVOKABLE int pid();
	//Q_INVOKABLE int getWinID();
    Q_INVOKABLE bool embed(const QString &program, const QString &Class);
	Q_INVOKABLE void setSize(const int &h, const int &w);
	Q_INVOKABLE void setPosition(const int &x, const int &y);
	Q_INVOKABLE int xdotoolGetId(const QString &Class);
	Q_INVOKABLE int x11_kwinGetId(const QString &Class);
	Q_INVOKABLE int waitForId(const QString &Class);
	Q_INVOKABLE int getId(const QString &Class);
	Q_INVOKABLE void toggle();
	Q_INVOKABLE void show();
	Q_INVOKABLE void hide();






private:
    QProcess *m_process;
	MainWindow *m_parentWindow;
	int m_wid;
	QSize m_size;
	QPoint m_pos;

};

#endif