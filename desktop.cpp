/*desktop.cpp*/
#include <QtGui>
#include "desktop.h"
#include "musicplayer.h"
#include "videoplayer.h"
#include "setting.h"
#include "photoviewer.h"

PhotoViewer *g_photoview;
ImageWidget *g_fullimage;
MusicPlayer *g_musicplay;
VideoPlayer *g_videoplay;
Setting *g_setting;
QVBoxLayout * g_mainlayout;

Desktop::Desktop()
{
	this->setObjectName("desktop");
	createAction();
	createItem();
	createLayout();
}

void Desktop::createAction()
{ 
	char *desktop_style;

	if( (desktop_style = getenv("DESKTOP_STYLE")) == NULL) {
		printf("desktop style = NULL\n");
	}

        QFile file(desktop_style);
        file.open(QFile::ReadOnly);
        QString stylesheet = QLatin1String(file.readAll());

	m_photoAction=new QToolButton;
	m_photoAction->setObjectName("photoAction");
	connect(m_photoAction, SIGNAL(clicked()), this, SLOT(gotoPhoto()));

	m_musicAction=new QToolButton;
	m_musicAction->setObjectName("musicAction");
	connect(m_musicAction, SIGNAL(clicked()), this, SLOT(gotoMusic()));

	m_videoAction=new QToolButton;
	m_videoAction->setObjectName("videoAction");
	connect(m_videoAction, SIGNAL(clicked()), this, SLOT(gotoVideo()));
	
	m_settingAction=new QToolButton;
	m_settingAction->setObjectName("settingAction");
	connect(m_settingAction, SIGNAL(clicked()), this, SLOT(gotoSetting()));
	//m_settingAction->setStyleSheet();	

	qApp->setStyleSheet(stylesheet);
}

void Desktop::createItem()
{
	//g_musicplay=new MusicPlayer;
	g_videoplay=new VideoPlayer;
	g_setting=new Setting;
	g_photoview=new PhotoViewer;
	g_fullimage=new ImageWidget;
	
	m_launchitemtimer=new QTimer;
	connect(m_launchitemtimer,SIGNAL(timeout()), this, SLOT(createMusic()));
	m_launchitemtimer->start(1000);
}

void Desktop::createMusic()
{
	m_launchitemtimer->stop();
	g_musicplay=new MusicPlayer;

}

void Desktop::createLayout()
{
	m_topLayout = new QHBoxLayout;
	m_topLayout->addWidget(m_photoAction);
	m_topLayout->addWidget(m_musicAction);
	m_topLayout->addWidget(m_videoAction);
	m_topLayout->addWidget(m_settingAction);

	m_mainLayout = new QVBoxLayout;
	m_mainLayout->addLayout(m_topLayout);
	QWidget* dummy =new QWidget;
	m_mainLayout->addWidget(dummy);
	//m_mainLayout->addWidget(g_musicplay);

	m_lastWidget=dummy;
	g_mainlayout=m_mainLayout;

	setLayout(m_mainLayout);
	//setCentralWidget(g_photoview);
}

void Desktop::gotoPhoto()
{
	m_mainLayout->removeWidget(m_lastWidget);
	m_mainLayout->addWidget(g_photoview);
	m_lastWidget->hide();
	m_lastWidget=g_photoview;
	g_photoview->show();
	qDebug()<<"goto photo\n";
}

void Desktop::gotoMusic()
{
        m_mainLayout->removeWidget(m_lastWidget);
        m_mainLayout->addWidget(g_musicplay);
	m_lastWidget->hide();
        m_lastWidget=g_musicplay;
	g_musicplay->show();
	qDebug()<<"goto music\n";
}

void Desktop::gotoVideo()
{
        m_mainLayout->removeWidget(m_lastWidget);
        m_mainLayout->addWidget(g_videoplay);
	m_lastWidget->hide();
        m_lastWidget=g_videoplay;
	g_videoplay->show();
	qDebug()<<"goto video\n";
}

void Desktop::gotoSetting()
{
        m_mainLayout->removeWidget(m_lastWidget);
        m_mainLayout->addWidget(g_setting);
	m_lastWidget->hide();
        m_lastWidget=g_setting;
	g_setting->show();
        qDebug()<<"goto setting\n";
}

/*end of desktop.cpp*/

