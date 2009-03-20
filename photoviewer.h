/*photo.h*/
#ifndef PHOTOVIEWER_H
#define PHOTOVIEWER_H

#include <QtGui>
#include "pictureflow.h"

class ImageWidget;
class TreeshowWidget;

enum photoslidepatt
{
	photoslidepatt_static,
	photoslidepatt_left2right,
	photoslidepatt_right2left,
	photoslidepatt_top2bottom,
	photoslidepatt_bottom2top,
	photoslidepatt_turnright,
	photoslidepatt_moveright,
	photoslidepatt_blindvertical,
	photoslidepatt_blindhorizontal,

	photoslidepatt_none,	
	photoslidepatt_turnnext,
	photoslidepatt_turnprev,
};

class PhotoViewer : public QWidget
{
    	Q_OBJECT

public:
    	PhotoViewer(QWidget *parent = 0);


public slots:
	void showList(void);
	void showFlow(void);
	void showFileInfo(void);
	void showImage(void);

private:
        //QTreeView *m_treeview;
        //QDirModel *m_model;
        //QListView *m_listview;
        QLabel *m_fileinfo;
        QLabel *m_filepath;
        QLabel *m_filename;
	QToolButton *m_treebutton;
	QToolButton *m_nextbtn;
	QToolButton *m_prevbtn;
	QToolButton *m_fscrnbtn;

	//QPushButton *m_listbutton;
        //QPushButton *m_flowbutton;
        QPainter *m_painter;
        //char* m_photodir;
	ImageWidget *m_imgpreview;
	TreeshowWidget* m_treeshowWidget; 
	
};

class ImageWidget : public QWidget
{
	Q_OBJECT

public:
	ImageWidget(QWidget *parent=0);
	void paintEvent(QPaintEvent *event);
	
    	void addImage(QString filename);
    	void addImageDir(QString dirName);
    	void clearImages();
	void setCurrentSlide(QString filename);
	void setCurrentSlide(int slidenum);

	void movStop(void);
	void movLoadImage(void);
	void movStatic(void);
	void movLeft2Right(void);
	void movRight2Left(void);
	void movTop2Bottom(void);
	void movBottom2Top(void);
	void movTurnRight(void);
	void movMoveRight(void);
	void movBlindVertical(void);
	void movBlindHorizontal(void);

	void movNone(void);
	void movTurnNext(void);
	void movTurnPrev(void);
	void showNextConnect(void);
	void showPrevConnect(void);

	void preview2full(void);
	void full2preview(void);
	void showToolbar(void);
	void mayshowtool(void);

	QStringList imagePaths;
	QTimer *m_movtimer;
	QTimer *m_slidetimer;
	QTimer *m_tooltimer;
	bool m_toolbarhide;
	int m_slidedelta;
	int currentSlide;
	int m_moving;
	int m_movstep;
	int m_movpatt;
	QImage *m_img;
	QImage *m_imgstandby;

	int m_x;
	int m_y;
	int m_width;
	int m_height;

	bool m_pendown;
	int m_pixelDistanceMoved;
  	QPoint m_previousPos;
	
public slots:

	void showNext(void);
	void showPrev(void);
	void showFScrn(void);
	void slideshow(void);
	void toolhide(void);

protected:

  	void mouseMoveEvent(QMouseEvent* event);
  	void mousePressEvent(QMouseEvent* event);
  	void mouseReleaseEvent(QMouseEvent* event);

};

class TreeshowWidget : public QWidget
{
	Q_OBJECT
public:
	TreeshowWidget(QWidget *parent=0);
	
	QTreeView *m_treeview;
        QDirModel *m_model;
	QToolButton *m_showbutton;
	char *m_photodir;
};

#endif
/*end of photo.h*/

