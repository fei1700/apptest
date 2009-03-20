#include <QtGui>
#include "musicplayer.h"

extern void hello(void);

MusicPlayer::MusicPlayer(QWidget *parent)
{
	qDebug()<<"enter";
	
	m_play_pause=new QToolButton;
	m_play_pause->setObjectName("play_pause");
		
        m_play_pause->setIcon(QIcon("images/play.png"));
        m_play_pause->setIconSize(QSize(40,40));

	connect(m_play_pause,SIGNAL(clicked()),this,SLOT(playToggle()));

	m_prev=new QToolButton;
	m_prev->setObjectName("prev");
	connect(m_prev,SIGNAL(clicked()),this,SLOT(playPrev()));
	m_next=new QToolButton;
	m_next->setObjectName("next");
	connect(m_next,SIGNAL(clicked()),this,SLOT(playNext()));
	m_rotate=new QToolButton;
	m_rotate->setObjectName("rotate");
	connect(m_rotate,SIGNAL(clicked()),this,SLOT(playRotate()));
	
	m_time_slider=new QSlider(Qt::Horizontal);
	m_time_slider->setObjectName("time_slider");
	m_time_slider->setRange(0,64);
	m_time_slider->setValue(0);
	connect(m_time_slider,SIGNAL(valueChanged(int)),this, SLOT(setposition(int)));

	m_timelabel=new QLabel("            ");
	m_timelabel->setStyleSheet("background-color: yellow");
		
	//m_timelabel->resize(50,20);
	//m_timelabel->setAlignment(Qt::AlignBottom | Qt::AlignRight);
	//m_timelabel->setFixedHeight(sizeHint().height());
	m_volume_slider=new QSlider(Qt::Horizontal);
	m_volume_slider->setObjectName("volume_slider");
	m_volume_slider->setRange(0,255);
	m_volume_slider->setValue(255);
	connect(m_volume_slider,SIGNAL(valueChanged(int)),this,SLOT(ossSetVolume(int)));
	
	m_dirpath="/mmc/media";
	m_musicdir=new QDir(m_dirpath);
        QStringList list;
        list << "*.mp3" << "*.wav" << "*.mp4" << "*.gif" << "*.flv" << "*.avi" << "*.3gp" << "*.wmv";
        m_musicdir->setNameFilters(list);

	m_play_state = 0;	
	m_musicpicture=new PictureFlow;
	QRect screen_size = QApplication::desktop()->screenGeometry();

        m_musicpicture->setSlideSize(QSize( (screen_size.width())>>2, (screen_size.height())>>2 ));
	//m_musicpicture->setFixedWidth(120);
	m_musicpicture->setFixedHeight(200);
	addMusicPicture();

	qDebug()<<"end";

	QHBoxLayout *timeslider = new QHBoxLayout;
	timeslider->addWidget(m_time_slider);
	timeslider->addWidget(m_timelabel);

	m_buttonLay=new QHBoxLayout;
	m_buttonLay->addWidget(m_prev);
	m_buttonLay->addWidget(m_play_pause);
	m_buttonLay->addWidget(m_next);
	m_buttonLay->addWidget(m_rotate);
	m_buttonLay->addWidget(m_volume_slider);
	
	m_playerLay=new QVBoxLayout(this);
	m_playerLay->addWidget(m_musicpicture);
	//m_playerLay->addWidget(m_time_slider);
	m_playerLay->addLayout(timeslider);
	//m_playerLay->addWidget(m_timelabel);
	m_playerLay->addLayout(m_buttonLay);

	m_pause=false;
	gstinit();
	qDebug()<<"out";
}
void MusicPlayer::setProgress(void)
{
	qDebug()<<"setProgress\n";
}

void MusicPlayer::playPrev(void)
{
//	m_musicpicture->slidePrev();
	m_musicpicture->showPrevious();
		
	if(m_play_state)
		playfile();
}

void MusicPlayer::playNext(void)
{
//	m_musicpicture->slideNext();
	m_musicpicture->showNext();
		
	if(m_play_state)
		playfile();
}

void MusicPlayer::playRotate(void)
{
	qDebug()<<"rotate\n";
	rotatefile();
}

void MusicPlayer::playToggle(void)
{
	if(!m_play_state)
	{
		m_play_pause->setIcon(QIcon("images/pause.png"));
		m_play_pause->setIconSize(QSize(40,40));
		
		playfile();
		m_play_state++;
	}
	else
	{	
		m_play_pause->setIcon(QIcon("images/play.png"));
		m_play_pause->setIconSize(QSize(40,40));
		
		pausefile();
		m_play_state=0;
	}
}

void MusicPlayer::addMusicPicture(void)
{
        QImage* musicimg=new QImage("images/music.png");
	QStringList lst=m_musicdir->entryList(QDir::Files);
	
	m_musicpicture->setSlideCount(m_musicdir->count());
	qDebug()<<m_musicdir->count();

	qint32 count=0;
	foreach(QString file,lst)
	{
		qDebug()<<file;
		m_musicpicture->setSlide(count,*musicimg);
		m_musicpicture->setSlideCaption(count,file);
		count++;
	}
	m_musicpicture->setCurrentSlide(0);
}

