/*videoplayer.h*/
#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QtGui>

class VideoPlayer : public QWidget
{
        Q_OBJECT
public:
        VideoPlayer(QWidget *parent=0 );
private:
        QPushButton *play;
        QPushButton *next;
        QPushButton *prev;
};

#endif

/*end of videoplayer.h*/
