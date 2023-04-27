#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QProcess>
#include <QWindow>
#include <QWidget>
#include <QDebug>
#include <QPoint>
#include <QSize>
#include <QMainWindow>
#include <QKeySequence>
#include <QKeyEvent>
#include <unistd.h>
#include <QCloseEvent>
#include <QEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QMainWindow *parent = 0);
	void closeEvent(QCloseEvent *event);
	void hideEvent(QHideEvent *event);
	void keyPressEvent(QKeyEvent *event);

	Q_INVOKABLE void toggle();



private:

};

#endif