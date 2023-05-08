#ifndef EMBEDDER_H
#define EMBEDDER_H

#include <QObject>
#include <QProcess>
#include <QTemporaryFile>
#include <QFile>
#include <QDateTime>
#include <QRegularExpression>
#include <QIODevice>
#include <KWindowSystem>

#include <KWayland/Client/registry.h>
#include <KWayland/Client/plasmawindowmanagement.h>

#include <QDebug>
#include <unistd.h>

class Embedder : public QObject
{
    Q_OBJECT
public:
    explicit Embedder(QObject *parent = 0);

	//Q_INVOKABLE QStringList runScript(const QString filename);
	/*Q_INVOKABLE QString createFile(const QString filecontent);
	Q_INVOKABLE QString searchWindow(const QString wclass, const QString wname, const QString wpid);
	Q_INVOKABLE QString searchWindow(const QString wclass, const QString wname);
	Q_INVOKABLE QString searchWindow(const QString wclass);
	Q_INVOKABLE bool activateWindow(const QString wid);
	Q_INVOKABLE QString activeClientId();
	Q_INVOKABLE void hideWindow(const QString wid);
	Q_INVOKABLE void moveWindow(const QString &x, const QString &y);
	Q_INVOKABLE void resizeWindow(const QString &h, const QString &w);
	Q_INVOKABLE void setWindowGeometry(const QString &x, const QString &y, const QString &h, const QString &w);
	Q_INVOKABLE void test();
	Q_INVOKABLE bool existsId(const QString wid);
	Q_INVOKABLE bool toggle(const QString wclass, const QString wname);
	Q_INVOKABLE bool hide(const QString wclass, const QString wname);
	Q_INVOKABLE bool show(const QString wclass, const QString wname);*/


private:
    //QTemporaryFile *m_temp;
};

#endif