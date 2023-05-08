#include <singleapplication.h>
#include <KLocalizedContext>
#include <KLocalizedString>
#include <QCommandLineParser>

#include "KwinController.h"
#include "Embedder.h"

#include <KWayland/Client/registry.h>
#include <KWayland/Client/plasmashell.h>
#include <KWayland/Client/plasmawindowmanagement.h>


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


	KWayland::Client::Registry *registry = new KWayland::Client::Registry(&app);
	KWayland::Client::PlasmaWindowManagement *p; // = registry->createPlasmaWindowManagement("org.kde.PlasmaShell", "1.0");
	qWarning() << "helo";
	//qWarning() << p->windows();




	QObject::connect(registry, &KWayland::Client::Registry::plasmaWindowManagementAnnounced, &app, [&](quint32 name, quint32 version) {
		// Create a PlasmaShell object to access the list of windows
		p = registry->createPlasmaWindowManagement(name, version, &app);
		qWarning() << "added" << p->windows();
		/*QObject::connect(shell, &KWayland::Client::PlasmaShell::surfaceAdded, &app, [](KWayland::Client::PlasmaShellSurface *surface) {
			// Get the id of each window and print it to the console
			auto windowId = surface->windowId();
			qInfo() << "Window ID:" << windowId;
		});*/
	});

	qWarning() << "exiting";
	return app.exec();







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
		QCoreApplication::translate("main", "Command to run program. If it contains spaces, make sure to use quotes."),
		QCoreApplication::translate("main", "program"));
	parser.addOption(programOption);

	QCommandLineOption iconOption(QStringList() << "i" << "icon",
		QCoreApplication::translate("main", "Add a system tray icon with the specified name or path."),
		QCoreApplication::translate("main", "icon"));
	parser.addOption(iconOption);

	QCommandLineOption xyOption(QStringList() << "xy",
		QCoreApplication::translate("main", "x and y coordinates of the window. NOT IMPLEMENTED YET"),
		QCoreApplication::translate("main", "x,y"));
	xyOption.setDefaultValue("0,0");
	parser.addOption(xyOption);

	QCommandLineOption sizeOption(QStringList() << "size",
		QCoreApplication::translate("main", "Size of the window. NOT IMPLEMENTED YET"),
		QCoreApplication::translate("main", "height,width"));
	sizeOption.setDefaultValue("500,700");
	parser.addOption(sizeOption);

	QCommandLineOption standaloneOption("standalone",
		QCoreApplication::translate("main", "Does not get minimized when other windows are toggled and does not minimize other windows when toggled."));
	parser.addOption(standaloneOption);

	QCommandLineOption minimizeAllOption("minimize-all",
		QCoreApplication::translate("main", "Minimize all windows that were not set as standalone."));
	parser.addOption(minimizeAllOption);

	QCommandLineOption trayOption("test",
		QCoreApplication::translate("main", "Get a list of all active windows names and classes. Use this to check the correct class and name for your application."));
	parser.addOption(trayOption);

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