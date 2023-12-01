#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include<QKeyEvent>
#include<QFontDatabase>
#include<QWebEngineSettings>
#include<QWebEngineCookieStore>
#include<QWebEnginePage>
#include <QUrl>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);



private:
	Ui::MainWindowClass ui;


	void handleLinkClicked(const QUrl& url);





private slots:
	void openWeb();
	void on_pushButton_back_clicked();
	void on_pushButton_forward_clicked();
	void on_pushButton_reload_clicked();
	void zoomInView();
	void zoomOutView();
	void styleRun();

	void on_pushButton_7_clicked();
	void on_pushButton_8_clicked();


protected:
	void keyPressEvent(QKeyEvent* event);




};





