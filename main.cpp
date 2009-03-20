/*main.cpp*/

#include <QApplication>
#include <QtGui>
#include "desktop.h"

#include "MediaInfoDLL.h"

Desktop *g_desktop;

QTimer *g_timela;
MyLaunch::MyLaunch(void)
{
}

void MyLaunch::launchDesktop(void)
{
	g_timela->stop();
	g_desktop= new Desktop;
	g_desktop->showFullScreen();
	
	qDebug()<<"call";
}

int main(int argc, char* argv[])
{
	MediaInfo_New();


	QApplication app(argc, argv);
	app.processEvents();
#if 0
	QSplashScreen *splash = new QSplashScreen(QPixmap("desk.gif"));
	splash->show();
	app.processEvents();

	Qt::Alignment topRight = Qt::AlignTop;
    	splash->showMessage(QObject::tr("initializing..."),topRight, Qt::red);
	app.processEvents();
#endif
	QMovie *movie=new QMovie("/app/samba/p/desk.gif");
	QLabel label;
	label.setMovie(movie);
	movie->start();
	label.showFullScreen();

	QTimer *stopmovie = new QTimer; 
	app.connect(stopmovie,SIGNAL(timeout()),movie,SLOT(stop()));
	stopmovie->start(15000);

	MyLaunch *hi = new MyLaunch;
	g_timela = new QTimer;
	app.connect(g_timela,SIGNAL(timeout()),hi,SLOT(launchDesktop()));
	g_timela->start(5000);
	
	//splash->finish();
	//delete splash;

	return app.exec();
}

/*end of main.cpp*/

