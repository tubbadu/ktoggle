#include "MainWindow.h"

MainWindow::MainWindow(QMainWindow *parent) :
    QMainWindow(parent)
{
	//grabShortcut(QKeySequence::Quit, Qt::ApplicationShortcut);
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    qWarning() << "Closing requested. Hiding window instead";
	hide();
	event->ignore();
}

void MainWindow::hideEvent(QHideEvent *event){
	if (isMinimized()) {
		qWarning() << "minimized!";
		hide();
	}
}

void MainWindow::keyPressEvent(QKeyEvent *event){
	qWarning() << event;
	if(event->matches(QKeySequence::Quit)){
		qWarning() << "quitting";
	}
}

void MainWindow::toggle(){
	if(isActiveWindow()){
		// hide
		hide();
	} else {
		// activate
		setWindowState(Qt::WindowNoState);
		show();
		activateWindow();
	}
}