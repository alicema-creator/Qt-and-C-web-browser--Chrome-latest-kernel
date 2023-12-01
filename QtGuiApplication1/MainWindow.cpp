#include "MainWindow.h"

#include "QUrl"
#include <iostream>
#include<string>
#include<QKeyEvent>



using namespace std;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	styleRun();

	QObject::connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(openWeb()));
	
	QObject::connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_reload_clicked()));
	QObject::connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_forward_clicked()));
	QObject::connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(on_pushButton_back_clicked()));
	QObject::connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(zoomInView()));
	QObject::connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(zoomOutView()));

	ui.pushButton_5->hide();
	ui.pushButton_6->hide();



	ui.mainToolBar->hide();
	ui.frame->setStyleSheet("QFrame{border-width: 0px;border-style: none;}");
	ui.frame_2->setStyleSheet("QFrame{border-width: 0px;border-style: none;}");


	ui.tabWidget->setCurrentIndex(0);

	
}


//加载样式表
void MainWindow::styleRun()
{
	//网页字体设置
	QFontDatabase fontDataBase;
	QWebEngineSettings* defaultSettings = QWebEngineSettings::globalSettings();
	QFont standardFont = fontDataBase.font("Microsoft Yahei", "", 12);
	defaultSettings->setFontFamily(QWebEngineSettings::StandardFont, standardFont.family());
	//网页字体设置结束

	//加载样式表
	QString cssStr = "./style/style_pushButton2.css";
	QString css;
	QFile file(cssStr);


	//加载样式表结束

	//设置主窗口背景颜色
	//QPalette palette;
	//palette.setColor(QPalette::Window, QColor(145, 247, 247));
	//this->setPalette(palette);
	//设置主窗口背景颜色结束

	ui.statusBar->showMessage(QStringLiteral("状态栏的显示信息"), 0);//一直显示
	QPalette palette2;
	palette2.setColor(QPalette::Window, Qt::red);
	ui.statusBar->setPalette(palette2);

	//ui.statusBar->setStyleSheet("style_pushButton2.css"); //继续测试

	//控件与主窗口间距
	//ui.gridLayout_3->setMargin(0);

}

//生成网页
void MainWindow::openWeb()
{
	////关闭缓存
	//QWebEngineSettings* webEngineSettings = ui.webEngineView->settings();
	//webEngineSettings->setAttribute(QWebEngineSettings::LocalStorageEnabled, false); //关闭缓存
	////关闭缓存结束

	QString webAdd = ui.lineEdit->text();
	string webAddS= webAdd.toLocal8Bit();
	cout << "webAddS: " << webAddS<<endl;
	string httpS = "https://";
	string http = "http://";
	//cout << "httpS: " << httpS << endl;

	string::size_type idxS;
	string::size_type idx;

	//ui.webEngineView->load(QUrl("https://www.baidu.com/"));
	idxS = webAddS.find(httpS);  //在a中查找b.
	idx = webAddS.find(http);  //在a中查找b.
	cout << "idxS: " << idxS << endl;



	else if (idx == 0)		//不存在。
	{
		cout << " found http://\n";
		ui.webEngineView->load(QUrl(webAdd));
	}		
	else		//不存在。
	{
		cout << " not found http:// or http://\n";
		ui.webEngineView->load(QUrl("https://" + webAdd));
		//ui.webEngineView->load(QUrl("http://www.baidu.com"));
	}


		

	// 设置网页缩放比例，范围是0.25-5，默认1
	ui.webEngineView->setZoomFactor(1.5);

	// 鼠标悬停网页里面的连接打印出网页地址
	QObject::connect(ui.webEngineView, &QWebEngineView::loadFinished, [this](bool) {
		QWebEnginePage* page = ui.webEngineView->page();
		if (page) {
			QObject::connect(page, &QWebEnginePage::linkHovered, this, &MainWindow::handleLinkClicked);
		}
	});







	// 鼠标悬停网页里面的连接打印出网页地址-这个也能用
	//QObject::connect(ui.webEngineView->page(), &QWebEnginePage::linkHovered, [this]() {
	//	qDebug() << "clicked22";
	//	});

	// 鼠标悬停网页里面的连接打印出网页地址-这个好像也能用
	//QObject::connect(ui.webEngineView->page(), &QWebEnginePage::action, [this](const QVariant& variant) {
	//	if (variant.canConvert<QWebEnginePage::WebAction>() && variant.value<QWebEnginePage::WebAction>() == QWebEnginePage::OpenLinkInNewTab) {
	//		QWebEnginePage* page = qobject_cast<QWebEnginePage*>(sender());
	//		if (page) {
	//			QUrl url = page->requestedUrl();
	//			cout << "Link clicked2: " << url.toString().toStdString() << endl;
	//			cout << "click" << endl; // 添加打印语句
	//		}
	//	}
	//	});




	//鼠标右键点击view page source查看源码
	//ui.webEngineView->pageAction(QWebEnginePage::ViewSource)->setText(QStringLiteral("查看源码"));
	QAction* viewSourceAction = ui.webEngineView->pageAction(QWebEnginePage::ViewSource);
	if (viewSourceAction)
	{
		viewSourceAction->setText(QStringLiteral("查看源码"));
		connect(viewSourceAction, &QAction::triggered, [=]() {
			qDebug() << "view page source clicked!";
			});
	}

	// 获取鼠标点击的链接

	//鼠标右键点击open link in new tab打开新的tab
	QAction* openLinkInNewTabAction = ui.webEngineView->pageAction(QWebEnginePage::OpenLinkInNewTab);
	if (openLinkInNewTabAction)
	{
		//openLinkInNewTabAction->setText(QStringLiteral("在新标签页中打开链接"));
		connect(openLinkInNewTabAction, &QAction::triggered, [=]() {
			qDebug() << "open link in new tab clicked!";




		

			//ui.webEngineView_2->setUrl(clickedLink);
			ui.webEngineView_2->load(QUrl("http://www.baidu.com"));

			ui.tabWidget->setCurrentIndex(1);

		});
	}




}






// 鼠标悬停网页里面的连接打印出网页地址
void MainWindow::handleLinkClicked(const QUrl& url)
{
	cout << "Link clicked: " << url.toString().toStdString() << endl;

	/*QString urlT;*/
	
	//if (!url.isEmpty()) {
	//	
	//	urlT = url.toString(); // 将url的字符串表示赋值给aa
	//	cout << "urlT: " << urlT.toStdString() << endl;
	//	// 在这里执行你的操作，因为 url 不为空
	//}


	////ui.webEngineView->load(QUrl(url.toString()));
	////鼠标右键点击open link in new tab打开新的tab
	//QAction* openLinkInNewTabAction = ui.webEngineView->pageAction(QWebEnginePage::OpenLinkInNewTab);
	//if (openLinkInNewTabAction)
	//{
	//	//openLinkInNewTabAction->setText(QStringLiteral("在新标签页中打开链接"));
	//	connect(openLinkInNewTabAction, &QAction::triggered, [=]() {
	//		qDebug() << "open link in new tab clicked!";
	//		//ui.webEngineView_2->load(QUrl("http://www.baidu.com"));
	//		cout << "urlT2: " << urlT.toStdString() << endl;
	//		ui.webEngineView_2->load(QUrl(urlT));
	//		ui.tabWidget->setCurrentIndex(1);

	//		});
	//}
}



//测试-打印出ui.webEngineView里面所有超级连接地址
void MainWindow::on_pushButton_7_clicked()
{
	cout << "on_pushButton_7_clicked" << endl;

	// 获取当前页面的QWebEnginePage对象
	QWebEnginePage* page = ui.webEngineView->page();
	if (page) {
		// 执行JavaScript代码，获取页面中的超链接
		page->runJavaScript("Array.from(document.getElementsByTagName('a')).map(a => a.href);",
			[this](const QVariant& result) {
				if (result.canConvert<QStringList>()) {
					QStringList links = result.toStringList();
					for (const QString& link : links) {
						qDebug() << "Link: " << link;
					}
				}
			});
	}




}

//返回
void MainWindow::on_pushButton_back_clicked()
{
	ui.webEngineView->back();
}

//向前
void MainWindow::on_pushButton_forward_clicked()
{
	ui.webEngineView->forward();
}

//刷新
void MainWindow::on_pushButton_reload_clicked()
{
	ui.webEngineView->reload();
}

//查看page source
void MainWindow::on_pushButton_8_clicked()
{

	qDebug() << "doProcessShowSourceCode";
	//ui.webEngineView->page()->load(QUrl("http://www.baidu.com"));
	ui.webEngineView->load(QUrl("http://www.baidu.com"));
	//ui.webEngineView->pageAction(QWebEnginePage::ViewSource)->setText(QStringLiteral("查看源码"));

	QAction* viewSourceAction = ui.webEngineView->pageAction(QWebEnginePage::ViewSource);
	if (viewSourceAction)
	{
		viewSourceAction->setText(QStringLiteral("查看源码"));
		connect(viewSourceAction, &QAction::triggered, [=]() {
			qDebug() << "查看源码 clicked!";
			});
	}

}




//大键盘回车键与小键盘回车键绑定按钮
void MainWindow::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Return) {
		cout << "aa" << endl;
		openWeb();
	}
	else if (event->key() == Qt::Key_Return) {
		cout << "aa" << endl;
		openWeb();
	}
}

double ii = 0.1;
void MainWindow::zoomInView()
{
	ii = ii - 0.01;
	cout << ii << endl;
	ui.webEngineView->setZoomFactor(ii);
	ui.webEngineView->load(QUrl("https://www.baidu.com"));

}

void MainWindow::zoomOutView()
{
	ii = ii + 0.01;
	cout << ii << endl;
	ui.webEngineView->setZoomFactor(ii);
	ui.webEngineView->load(QUrl("https://www.baidu.com"));

}