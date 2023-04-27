#include "Embedder.h"

Embedder::Embedder(QObject *parent) :
    QObject(parent),
    m_process(new QProcess(this)),
	m_parentWindow(new MainWindow)
{
	m_wid = -1;
	m_pos = QPoint(0, 0);
	m_size = QSize(600, 500);
}

int Embedder::launch(const QString &program)
{
    m_process->start(program);
	return m_process->processId();
}

/*int Embedder::pid(){
	return m_process->processId();
}

int Embedder::getWinID()
{
	// X11 only!
	QString PId = QString::number(pid());
	//qWarning() << "pid:" << PId;
	QProcess *xdotool = new QProcess;
	QStringList args;
	args << "search" << "--onlyvisible" << "--pid" << PId;
	xdotool->setProgram("xdotool");
	xdotool->setArguments(args);
	xdotool->start();
	xdotool->waitForFinished(3000);
	
    QString output = QString::fromLocal8Bit(xdotool->readAllStandardOutput()).trimmed();
	//qWarning() << args << "\n" << output;

	int ID;
	QStringList IDs = output.split("\n");
	//qWarning() << IDs;
	if(IDs.size() > 1){
		// there are more than just one WId: take the last one
		ID = IDs[IDs.size()-1].toInt();
	} else if (output.size() < 1){
		// no WId returned
		ID = -1;
	} else {
		// just one WId
		ID = output.toInt();
	}
	
	//qWarning() << "--->" << args << output << "-" << IDs << "=" << QString::number(ID);
	return ID;
}*/

int Embedder::getRealWinID(const QString &Class){
	int ID;
	QElapsedTimer timer;
    timer.start();
	while(timer.elapsed() < 1000){ // after 1000 ms exit
		//ID = getWinID();
		ID = xdotoolGetId(Class);
		if(ID > 0){
			return ID;
		} else {
			sleep(0.05);
		}
	}
	return -1;
}

int Embedder::xdotoolGetId(const QString &Class){
	QProcess *xdotool = new QProcess;
	QStringList args;
	args << "search" << "--onlyvisible" << "--class" << Class;
	xdotool->setProgram("xdotool");
	xdotool->setArguments(args);
	xdotool->start();
	qWarning() << "aaa";
	xdotool->waitForFinished(3000);
	
    QString output = QString::fromLocal8Bit(xdotool->readAllStandardOutput()).trimmed();

	int ID;
	QStringList IDs = output.split("\n");
	//qWarning() << IDs;
	if(IDs.size() > 1){
		// there are more than just one WId: take the last one
		ID = IDs[IDs.size()-1].toInt();
	} else if (output.size() < 1){
		// no WId returned
		ID = -1;
	} else {
		// just one WId
		ID = output.toInt();
	}
	qWarning() << ID;
	return ID;
}

void Embedder::toggle(){
	m_parentWindow->toggle();
}
void Embedder::show(){
	m_parentWindow->show();
	m_parentWindow->activateWindow();
}
void Embedder::hide(){
	m_parentWindow->hide();
}

void Embedder::setSize(const int &h, const int &w){
	m_size = QSize(h, w);
}
void Embedder::setPosition(const int &x, const int &y){
	m_pos = QPoint(x, y);
}


bool Embedder::embed(const QString &Class)
{
	m_wid = getRealWinID(Class);
	if(m_wid < 1){
		return false;
	}

	m_parentWindow->move(m_pos);
	m_parentWindow->resize(m_size);

	QWindow *window = QWindow::fromWinId(m_wid);
	window->setFlags(Qt::FramelessWindowHint);
	QWidget *container = QWidget::createWindowContainer(window);
	m_parentWindow->setCentralWidget(container);	
	container->show();
	window->show();
	m_parentWindow->show();

    return true;
}