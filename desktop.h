/*desktop.h*/
#ifndef DESKTOP_H
#define DESKTOP_H
#include <QtGui>
//#include "photoviewer.h"
//#include "musicplayer.h"
//#include "videoplayer.h"
//#include "setting.h"

class PhotoViewer;
class MusicPlayer;
class VideoPlayer;
class Setting;

class Desktop : public QFrame
{
	Q_OBJECT

public:
	Desktop();

private slots:
	void gotoPhoto();
	void gotoMusic();
	void gotoVideo();
	void gotoSetting();

private:
	void createItem();
	void createAction();
	void createLayout();

	QToolButton *m_photoAction;
	QToolButton *m_musicAction;
	QToolButton *m_videoAction;
	QToolButton *m_settingAction;

	QHBoxLayout *m_topLayout;
	QVBoxLayout *m_mainLayout;
	QWidget *m_lastWidget;

	QTimer *m_launchitemtimer;

public slots:
	void createMusic();
};

class MyLaunch : public QWidget
{
	Q_OBJECT
public:
	MyLaunch(void);

public slots:
	void launchDesktop();
};


#endif
/*end of desktop.h*/

