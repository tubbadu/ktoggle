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
    SingleApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("helloworld");
    QCoreApplication::setOrganizationName(QStringLiteral("KDE"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("kde.org"));
    QCoreApplication::setApplicationName(QStringLiteral("Hello World"));

	QObject::connect( &app, &SingleApplication::instanceStarted, [ &app ]() {
        qWarning() << "raise!!!!";
    });


	/*QList<WId> windows = KWindowSystem::windows();
	for (WId window : windows) {
		auto windoInfo = KWindowInfo(window, NET::WMVisibleName, NET::WM2WindowClass);
		qWarning() << window << windoInfo.visibleName() << windoInfo.windowClassName();
		
	}
	return 0;*/

    QQmlApplicationEngine engine;

    qmlRegisterType<Launcher>("Launcher", 1, 0, "Launcher");
	qmlRegisterType<TrayIcon>("TrayIcon", 1, 0, "TrayIcon");
	qmlRegisterType<Embedder>("Embedder", 1, 0, "Embedder");

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }	

    return app.exec();
}
