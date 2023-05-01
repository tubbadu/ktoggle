#include <QApplication>
#include <singleapplication.h>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QUrl>
#include <KLocalizedContext>
#include <KLocalizedString>

#include "launcher.h"
#include "TrayIcon.h"
#include "Embedder.h"

int main(int argc, char *argv[])
{
	SingleApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	SingleApplication app(argc, argv, true);
	KLocalizedString::setApplicationDomain("helloworld");
	QCoreApplication::setOrganizationName(QStringLiteral("KDE"));
	QCoreApplication::setOrganizationDomain(QStringLiteral("kde.org"));
	QCoreApplication::setApplicationName(QStringLiteral("Hello World"));

	if( app.isSecondary() ) {
		app.sendMessage( app.arguments().join(' ').toUtf8() );
		qWarning() << "App already running.";
		qWarning() << "Primary instance PID: " << app.primaryPid();
		qWarning() << "Primary instance user: " << app.primaryUser();
		return 0;
	}

	QQmlApplicationEngine engine;
	qmlRegisterType<Launcher>("Launcher", 1, 0, "Launcher");
	qmlRegisterType<TrayIcon>("TrayIcon", 1, 0, "TrayIcon");
	qmlRegisterType<Embedder>("Embedder", 1, 0, "Embedder");

	engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	if (engine.rootObjects().isEmpty()) {
		return -1;
	}

	QObject::connect( &app, &SingleApplication::receivedMessage, [&engine](int instanceId, QByteArray message) {
		QObject* rootObject = engine.rootObjects().first();
		QMetaObject::invokeMethod(rootObject, "dewit", Q_ARG(QVariant, instanceId), Q_ARG(QVariant, message));
	});

	return app.exec();
}