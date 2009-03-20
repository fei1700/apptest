/*musicplayer.h*/
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QtGui>
#include "pictureflow.h"
#include <gst/gst.h>

class MusicPlayer : public QWidget
{
	Q_OBJECT
public:
	MusicPlayer(QWidget *parent=0 );
	void addMusicPicture(void);
	int gstinit(void);
	void playfile();
	void pausefile(void);
	void rotatefile(void);
	void preplayfile();
	//gboolean playbin_bus_callback (GstBus *bus,GstMessage *message,gpointer data);
	
	QToolButton *m_dirview;
	QToolButton *m_play_pause;
	qint32 m_play_state;
	QToolButton *m_next;
	QToolButton *m_prev;
	QToolButton *m_rotate;
	QSlider *m_time_slider;
	QAbstractSlider *m_time_abslider;
	QSlider *m_volume_slider;
	char* m_dirpath;
	QDir *m_musicdir;
	QLabel *m_timelabel;

	bool m_pause;

	QHBoxLayout *m_buttonLay;
	QVBoxLayout *m_playerLay;

	PictureFlow *m_musicpicture;
	GstElement *m_playbin;
	GstElement *m_vibin;
	GstElement *m_playuri;
	GstElement *m_vcaps;
	GstElement *m_vflip;
	GstElement *m_vscale;
	GstElement *m_ffcolor;

public slots:
	void playToggle(void);
	void setProgress(void);
	void playNext();
	void playPrev();
	void playRotate(void);
	void setposition(int);
	void ossSetVolume(int);
};

#endif
/*end of musicplayer.h*/
