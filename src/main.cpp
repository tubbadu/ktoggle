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


Embedder* addWindow(QCommandLineParser *parser, const QString &id){
	Embedder *embedder = new Embedder;
	if(!parser->isSet("class")){
		qWarning() << "ERROR: class unspecified";
		parser->showHelp();
	} else {
		embedder->setClass(parser->value("class"));

		if(parser->isSet("program")){
			embedder->setProgram(parser->value("program"));
		}
		if(parser->isSet("icon")){
			embedder->addTrayIcon(parser->value("icon"));
		}
		if(parser->isSet("name")){
			embedder->setName(parser->value("name"));
		}
		if(parser->isSet("size")){
			embedder->setProgram(parser->value("size"));
		}
		if(parser->isSet("xy")){			
			embedder->move(parser->value("xy"));
		}
		embedder->setCmdToRaise(parser->isSet("cmd-to-raise"));

		if(!embedder->embed()){
			qWarning() << "Not present, running it";
			// window not present: run and embed again
			embedder->run();
		} else {
			qWarning() << "Already running";
		}
	}
	embedder->setIdentifier(id);
	return embedder;
}

bool newRequest(QList<Embedder*> *wList, QCommandLineParser *parser, const QString &id){
	qWarning() << id;
	for(Embedder *e : *wList){
		if(e->identifier() == id){
			qWarning() << "Embedder already present!";
			e->toggle();
			return false;
		}
	}
	wList->append(addWindow(parser, id));
	return true;
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

	QCommandLineOption trayOption("test",
		QCoreApplication::translate("main", "Get a list of all active windows names and classes."));
	parser.addOption(trayOption);

	QCommandLineOption cmdToRaiseOption("cmd-to-raise",
		QCoreApplication::translate("main", "Raise window running the command each time. Use this for apps like Telegram that hide the window when minimized."));
	parser.addOption(cmdToRaiseOption);

	parser.process(app);


	if( app.isSecondary() ) {
		QByteArray data;
		QDataStream dataStreamWrite(&data, QIODevice::WriteOnly);
		dataStreamWrite << QCoreApplication::arguments();
		app.sendMessage(data);
		qWarning() << "App already running.";
		qWarning() << "Primary instance PID: " << app.primaryPid();
		qWarning() << "Primary instance user: " << app.primaryUser();
		return 0;
	}

	if(parser.isSet("test")){
		Embedder e;
		e.test();
		return 0;
	}
	
	//parser.process(QStringList() << "ktoggle" <);


	QList<Embedder*> wList;
	//wList.append(addWindow(&parser));

	newRequest(&wList, &parser, QString(QCoreApplication::arguments().mid(1).join(" ")));
	

	QObject::connect( &app, &SingleApplication::receivedMessage, [&parser, &wList](int instanceId, QByteArray message) {
		QDataStream dataStreamRead(message);
		QStringList args;
		dataStreamRead >> args;
		qWarning() << args;
		parser.process(args);
		newRequest(&wList, &parser, QString(args.join(" ")));
	});
	
	return app.exec();
}