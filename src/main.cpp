#include <QApplication>
#include <singleapplication.h>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QUrl>
#include <KLocalizedContext>
#include <KLocalizedString>
#include <QCommandLineParser>
#include <QVariant>
#include <QJSValue>
#include <QJsonDocument>
#include <QJsonObject>

#include "launcher.h"
#include "TrayIcon.h"
#include "Embedder.h"
#include "DbusKwin.h"


QByteArray parserToJs(const QCommandLineParser &parser){
	QMap<QString, QString> map;

	map["class"] = "windowClass";
	map["name"] = "windowName";
	map["program"] = "program";
	map["icon"] = "icon";
	map["no-tray"] = "noTray";
	map["xy"] = "xy";
	map["size"] = "size";
	map["cmd-to-raise"] = "cmdToRaise";
	
	map["p"] = map["program"];
	map["n"] = map["name"];
	map["c"] = map["class"];
	map["i"] = map["icon"];


	QJsonObject parserJS;

	qWarning() << parser.isSet("icon");

	const QStringList options = map.keys(); //parser.optionNames();
	for (const QString& option : options) {
		if(parser.isSet(option)){
			parserJS[map[option]] = parser.value(option);
		} else {
			qWarning() << option << "not set";
		}
	}

	QJsonDocument docJS(parserJS);
	return docJS.toJson();
}

int main(int argc, char *argv[])
{
	SingleApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	SingleApplication app(argc, argv, true);
	KLocalizedString::setApplicationDomain("ktoggle");
	QCoreApplication::setOrganizationName(QStringLiteral("KDE"));
	QCoreApplication::setOrganizationDomain(QStringLiteral("kde.org"));
	QCoreApplication::setApplicationName(QStringLiteral("KToggle"));
	QCoreApplication::setApplicationVersion("1.0");

	QCommandLineParser parser;
	parser.setApplicationDescription("KToggle, a tool to toggle any app");
	parser.addHelpOption();
	parser.addVersionOption();
	QCommandLineOption classOption(QStringList() << "c" << "class",
		QCoreApplication::translate("main", "Window class to toggle."),
		QCoreApplication::translate("main", "class"));
	parser.addOption(classOption);

	QCommandLineOption nameOption(QStringList() << "n" << "name",
		QCoreApplication::translate("main", "Window name to toggle. Substrings are also accepted."),
		QCoreApplication::translate("main", "name"));
	parser.addOption(nameOption);

	QCommandLineOption programOption(QStringList() << "p" << "program",
		QCoreApplication::translate("main", "Command to run program. May include optional flags."),
		QCoreApplication::translate("main", "program"));
	parser.addOption(programOption);

	QCommandLineOption iconOption(QStringList() << "i" << "icon",
		QCoreApplication::translate("main", "Tray icon to display. If unspecified, window's own icon will be displayed."),
		QCoreApplication::translate("main", "icon"));
	parser.addOption(iconOption);

	QCommandLineOption xyOption(QStringList() << "xy",
		QCoreApplication::translate("main", "x and y coordinates of the window."),
		QCoreApplication::translate("main", "x,y"));
	xyOption.setDefaultValue("0,0");
	parser.addOption(xyOption);

	QCommandLineOption sizeOption(QStringList() << "size",
		QCoreApplication::translate("main", "Size of the window."),
		QCoreApplication::translate("main", "height,width"));
	sizeOption.setDefaultValue("500,700");
	parser.addOption(sizeOption);

	QCommandLineOption trayOption("no-tray",
		QCoreApplication::translate("main", "Do not display tray icon."));
	parser.addOption(trayOption);

	QCommandLineOption cmdToRaiseOption("cmd-to-raise",
		QCoreApplication::translate("main", "Raise window running the command each time. Use this for apps like Telegram that hide the window when minimized."));
	parser.addOption(cmdToRaiseOption);

	parser.process(app);

	if( app.isSecondary() ) {
		app.sendMessage(parserToJs(parser));
		qWarning() << "App already running.";
		qWarning() << "Primary instance PID: " << app.primaryPid();
		qWarning() << "Primary instance user: " << app.primaryUser();
		return 0;
	}

	/*QQmlApplicationEngine engine;
	qmlRegisterType<Launcher>("Launcher", 1, 0, "Launcher");
	qmlRegisterType<TrayIcon>("TrayIcon", 1, 0, "TrayIcon");
	qmlRegisterType<Embedder>("Embedder", 1, 0, "Embedder");

	engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	if (engine.rootObjects().isEmpty()) {
		return -1;
	}

	
	QObject* rootObject = engine.rootObjects().first();

	QObject::connect( &app, &SingleApplication::receivedMessage, [&rootObject](int instanceId, QByteArray message) {
		QMetaObject::invokeMethod(rootObject, "newRequest", Q_ARG(QVariant, instanceId), Q_ARG(QVariant, message));
	});

	QMetaObject::invokeMethod(rootObject, "newRequest", Q_ARG(QVariant, 0), Q_ARG(QVariant, parserToJs(parser)));
	*/
	DbusKwin *kwin = new DbusKwin;
	Embedder *embedder = new Embedder;

	QObject::connect( &app, &SingleApplication::receivedMessage, [&embedder](int instanceId, QByteArray message) {
		//QMetaObject::invokeMethod(rootObject, "newRequest", Q_ARG(QVariant, instanceId), Q_ARG(QVariant, message));
	});
	
	kwin->activateWindow(kwin->searchWindow("org.telegram.desktop"));

	return app.exec();
}