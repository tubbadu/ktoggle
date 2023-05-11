#ifndef DBUSKWIN_H
#define DBUSKWIN_H

#include <QObject>
#include <QProcess>
#include <QTemporaryFile>
#include <QFile>
#include <QDateTime>
#include <QRegularExpression>
#include <QIODevice>
#include <KWindowSystem>

#include <QDebug>
#include <unistd.h>


class DbusKwin : public QObject
{
    Q_OBJECT
public:
    explicit DbusKwin(QObject *parent = 0);

	Q_INVOKABLE QStringList runScript(const QString filename);
	Q_INVOKABLE QString createFile(const QString filecontent);
	Q_INVOKABLE void test();
	Q_INVOKABLE bool toggle(const QString wclass, const QString wname, const bool &followDesktop);
	Q_INVOKABLE bool hide(const QString wclass, const QString wname);
	Q_INVOKABLE bool show(const QString wclass, const QString wname);
	Q_INVOKABLE bool move(const QString wclass, const QString wname, const QString x, const QString y);
	Q_INVOKABLE bool resize(const QString wclass, const QString wname, const QString height, const QString width);
	Q_INVOKABLE bool setGeometry(const QString wclass, const QString wname, const QString x, const QString y, const QString height, const QString width);

	Q_INVOKABLE QString composeScript(const QString &actionsBeginning, const QString &actionsActive, const QString &actionsInactive, const QString actionsEnd);



private:
    QTemporaryFile *m_temp;
};

#endif