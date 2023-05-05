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
		embedder->setStandalone(parser->isSet("standalone"));

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
	if(parser->isSet("minimize-all")){
		for(Embedder *e : *wList){
			if(!e->isStandalone()){
				e->hide();
			}
		}
	}
	qWarning() << "new request id:" << id;
	Embedder *found = nullptr;
	for(Embedder *e : *wList){
		if(e->identifier() == id){
			found = e; 
			e->toggle();
			break;
		}
	}

	for(Embedder *e : *wList){
		if(e->identifier() != id && !e->isStandalone() && !parser->isSet("standalone")){
			e->hide();
		}
	}

	if(found){
		return true;
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

	QCommandLineOption standaloneOption("standalone",
		QCoreApplication::translate("main", "Does not get minimized when other windows are toggled and does not minimize other windows when toggled."));
	parser.addOption(standaloneOption);

	QCommandLineOption minimizeAllOption("minimize-all",
		QCoreApplication::translate("main", "Minimize all windows that were not set as --standalone"));
	parser.addOption(minimizeAllOption);

	parser.process(app);


	if( app.isSecondary() ) {
		if(parser.isSet("test")){
			Embedder e;
			e.test();
			return 0;
		}
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
	


	QList<Embedder*> wList;

	newRequest(&wList, &parser, QString(QCoreApplication::arguments().mid(1).join(" ")));
	

	QObject::connect( &app, &SingleApplication::receivedMessage, [&parser, &wList](int instanceId, QByteArray message) {
		QDataStream dataStreamRead(message);
		QStringList args;
		dataStreamRead >> args;
		qWarning() << "args received" << args;
		parser.process(args);
		newRequest(&wList, &parser, QString(args.mid(1).join(" ")));
	});
	
	return app.exec();
}