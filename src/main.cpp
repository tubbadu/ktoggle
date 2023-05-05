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
#include "KwinController.h"
#include "DbusKwin.h"



KwinController* newKwinController(QCommandLineParser *parser, const QString &id){
	KwinController *kwinController = new KwinController;
	if(!parser->isSet("class") || !parser->isSet("name")){
		qWarning() << "ERROR: class and name cannot be unspecified";
		parser->showHelp();
	} else {
		kwinController->setClass(parser->value("class"));
		kwinController->setName(parser->value("name"));

		if(parser->isSet("program")){
			kwinController->setProgram(parser->value("program"));
		}
		if(parser->isSet("icon")){
			kwinController->addTrayIcon(parser->value("icon"));
		}
		if(parser->isSet("size")){
			kwinController->setProgram(parser->value("size"));
		}
		if(parser->isSet("xy")){			
			kwinController->move(parser->value("xy"));
		}
		kwinController->setStandalone(parser->isSet("standalone"));
	}
	kwinController->setIdentifier(id);
	return kwinController;
}

bool newRequest(QList<KwinController*> *wList, QCommandLineParser *parser, const QString &id){
	// minimize all and exit if run with --minimize-all
	if(parser->isSet("minimize-all")){ 
		for(KwinController *e : *wList){
			if(!e->isStandalone()){
				e->hide();
			}
		}
		return false;
	}

	// find and toggle or run the requested window in wList
	KwinController *found = nullptr;
	for(KwinController *e : *wList){
		if(e->identifier() == id){
			found = e;
			if(!e->toggle()){
				e->run();
			}
			break;
		}
	}

	// minimize all other windows (not set as --standalone)
	for(KwinController *e : *wList){
		if(e->identifier() != id && !e->isStandalone() && !parser->isSet("standalone")){
			e->hide();
		}
	}

	if(found){
		return false;
	} else {
		// requested window is not present in wList. Add it
		KwinController *newE = newKwinController(parser, id);
		QObject::connect( newE, &KwinController::wantsToDie, [&wList]() {
			qWarning() << "wants to die!";
			// destroy newE-> TODO
		});
		wList->append(newE);
		if(!newE->toggle()){
			newE->run();
		}
		return !true;
	}
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

	QCommandLineOption standaloneOption("standalone",
		QCoreApplication::translate("main", "Does not get minimized when other windows are toggled and does not minimize other windows when toggled."));
	parser.addOption(standaloneOption);

	QCommandLineOption minimizeAllOption("minimize-all",
		QCoreApplication::translate("main", "Minimize all windows that were not set as --standalone"));
	parser.addOption(minimizeAllOption);

	parser.process(app);


	if( app.isSecondary() ) {
		if(parser.isSet("test")){
			KwinController e;
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
		KwinController e;
		e.test();
		return 0;
	}
	


	QList<KwinController*> wList;

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