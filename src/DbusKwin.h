#ifndef DBUSKWIN_H
#define DBUSKWIN_H

#include <QObject>
#include <QProcess>
#include <QTemporaryFile>
#include <QFile>
#include <QDateTime>
#include <QRegularExpression>
#include <QIODevice>
#include <QDebug>
#include <unistd.h>
#include <KWindowSystem>

class DbusKwin : public QObject
{
    Q_OBJECT
public:
    explicit DbusKwin(QObject *parent = 0);

	Q_INVOKABLE QStringList runScript(const QString filename);
	Q_INVOKABLE QString createFile(const QString filecontent);
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


private:
    QTemporaryFile *m_temp;
};

#endif