/*photoviewer.cpp*/
#include <QtGui>
#include "photoviewer.h"
#include <qpainter.h>

PhotoViewer::PhotoViewer(QWidget *parent)
{
//treeshow
        m_treeshowWidget =new TreeshowWidget;

//filepath
	m_filepath=new QLabel;
	m_filepath->setObjectName("filepath");
	m_filepath->setText(m_treeshowWidget->m_photodir);
//treeview button
	m_treebutton=new QToolButton;
	m_treebutton->setObjectName("treebutton");

	QHBoxLayout *filetreeLay=new QHBoxLayout;
	filetreeLay->addWidget(m_filepath);
	filetreeLay->addWidget(m_treebutton);

//fileinfo
	m_fileinfo=new QLabel(this);
	m_fileinfo->setText("fileinfo");

//painter
	m_imgpreview=new ImageWidget;

//preview button
	m_nextbtn = new QToolButton;
	m_nextbtn->setObjectName("photonext");
	m_prevbtn = new QToolButton;
	m_prevbtn->setObjectName("photoprev");
	m_fscrnbtn = new QToolButton;
	m_fscrnbtn->setObjectName("photofull");

//connect signal
	connect(m_treebutton,SIGNAL(clicked()),this,SLOT(showList()));
	connect(m_treeshowWidget->m_showbutton,SIGNAL(clicked()),this,SLOT(showFlow()));
	connect(m_nextbtn, SIGNAL(clicked()),m_imgpreview,SLOT(showNext()));
	connect(m_prevbtn, SIGNAL(clicked()),m_imgpreview,SLOT(showPrev()));
	connect(m_fscrnbtn, SIGNAL(clicked()),m_imgpreview,SLOT(showFScrn()));

	QHBoxLayout *btnlay=new QHBoxLayout;
	btnlay->addWidget(m_prevbtn);
	btnlay->addWidget(m_nextbtn);
	btnlay->addWidget(m_fscrnbtn);

        QVBoxLayout *picLay=new QVBoxLayout(this);
        picLay->addLayout(filetreeLay);
	picLay->addWidget(m_imgpreview);
	picLay->addLayout(btnlay);
}

extern QVBoxLayout* g_mainlayout;

void PhotoViewer::showList(void)
{
	g_mainlayout->removeWidget(this);
	g_mainlayout->addWidget(m_treeshowWidget);
	this->hide();
	m_treeshowWidget->show();	
	qDebug()<<"show list";	
}

void PhotoViewer::showFlow(void)
{
	g_mainlayout->removeWidget(m_treeshowWidget);
	g_mainlayout->addWidget(this);
	m_treeshowWidget->hide();

	qDebug() << m_treeshowWidget->m_model->filePath(m_treeshowWidget->m_treeview->currentIndex());
	QDir dirname(m_treeshowWidget->m_model->filePath(m_treeshowWidget->m_treeview->currentIndex()));
	qDebug() << dirname.path();
	qDebug() << dirname.dirName();
	
	QString dirstring(dirname.path());

	QFileInfo file(dirname.path());
	
	if(!file.isDir())
	{
		dirstring.chop(dirname.dirName().size());
		qDebug() << "is not dir";
		qDebug() << dirstring;	
	
		qDebug() << m_imgpreview->currentSlide;
	}
	
	m_imgpreview->addImageDir(dirstring);

	if(!file.isDir())	
		m_imgpreview->setCurrentSlide(dirname.path());
	else
		m_imgpreview->setCurrentSlide(0);
	
	this->show();
	qDebug()<<"show flow";
}

void PhotoViewer::showFileInfo(void)
{
}

void PhotoViewer::showImage(void)
{
}

ImageWidget::ImageWidget(QWidget *parent)
{
	currentSlide=0;
	clearImages();
	
	m_img = 0;
	m_imgstandby = 0;
	m_movstep = 20;
	m_movpatt = photoslidepatt_static;
	m_movtimer = new QTimer;
	connect(m_movtimer,SIGNAL(timeout()), this,SLOT(update()));
	m_slidetimer = new QTimer;
	connect(m_slidetimer,SIGNAL(timeout()), this,SLOT(slideshow()));
	m_slidedelta = 3000;
	m_tooltimer = new QTimer;
	connect(m_tooltimer,SIGNAL(timeout()), this,SLOT(toolhide()));
	m_toolbarhide = false;
}

void ImageWidget::setCurrentSlide(QString filename)
{
	currentSlide=imagePaths.indexOf(filename);
}

void ImageWidget::setCurrentSlide(int slidenum)
{
	currentSlide=slidenum;
}

void ImageWidget::addImage(QString filename)
{
	imagePaths << filename;
}

void ImageWidget::clearImages()
{
	imagePaths.clear();
}

void ImageWidget::addImageDir(QString dirname)
{
	clearImages();

	QDir dir(dirname);
	QStringList filenames = dir.entryList(QDir::Files);
	QStringList filters;
	filters << "*.jpg" << "*.png" << "*.bmp";
	dir.setNameFilters(filters);

	for(int i=0; i<filenames.count();i++)
	{
		imagePaths << dir.absoluteFilePath(filenames[i]);
		qDebug() << dir.absoluteFilePath(filenames[i]);
	}

	m_movpatt = photoslidepatt_static;
}

void ImageWidget::showNext()
{
	movStop();

	currentSlide++;
    	if (currentSlide >= imagePaths.size())
      		currentSlide = 0;

	m_movpatt = photoslidepatt_static;

	update();
	qDebug() << "show next";
}


void ImageWidget::showPrev()
{
	movStop();

    	if (currentSlide == 0)
      		currentSlide = imagePaths.size()-1;
	else
		currentSlide--;

	m_movpatt = photoslidepatt_static;

	update();
	qDebug() << "show prev";
}

extern ImageWidget* g_fullimage;
void ImageWidget::preview2full(void)
{
	g_fullimage->imagePaths = imagePaths;
	g_fullimage->m_moving = m_moving;
	g_fullimage->m_movstep = m_movstep;
	g_fullimage->m_img = m_img;
	g_fullimage->m_imgstandby = m_imgstandby;
	g_fullimage->currentSlide = currentSlide;
}

void ImageWidget::full2preview(void)
{
	imagePaths = g_fullimage->imagePaths;
	m_moving = g_fullimage->m_moving;
	m_movstep = g_fullimage->m_movstep;
	m_img = g_fullimage->m_img;
	m_imgstandby = g_fullimage->m_imgstandby;
	currentSlide = g_fullimage->currentSlide;
}

void ImageWidget::slideshow(void)
{
	movStop();

	m_movpatt = qrand()%photoslidepatt_none;
//	m_movpatt = photoslidepatt_moveright;

	currentSlide++;
    	if (currentSlide >= imagePaths.size())
      		currentSlide = 0;

	update();
	qDebug() << "slideshow";
}

/*------------------------------------------------------------*/
#define TOOLSIZE	30
#define TOOLY		290
#define TOOLY_BOTTOMDELTA	(size().height() - TOOLY)
#define TOOLNUM		(sizeof(imgname)/sizeof(imgname[0]))
#define TOOLX_DELTA	(size().width() / ((TOOLNUM << 1)+1))
#define TOOLX(i)	(TOOLX_DELTA*((i<<1)+1))

char* imgname[]= {"images/033.png","images/036.png","images/042.png"};
 
/*------------------------------------------------------------*/

void ImageWidget::showToolbar()
{
	if(m_toolbarhide == true)
		return;

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect srcrect(0,0,TOOLSIZE, TOOLSIZE);

	for(int i=0; i<TOOLNUM; i++)
	{
		QImage tmptoolimg(imgname[i]);
		QRect dstrect(TOOLX(i),TOOLY,TOOLSIZE,TOOLSIZE);
		painter.drawImage(dstrect, tmptoolimg,srcrect,Qt::AutoColor);
	}
}

void ImageWidget::toolhide()
{
	m_toolbarhide = true;
	
	if(!(m_movtimer->isActive()))
	{
		m_movpatt = photoslidepatt_static;
		update();
	}
}

void ImageWidget::mayshowtool()
{
	qDebug() << m_toolbarhide;
	if(m_toolbarhide == true)
	{
		m_toolbarhide = false;
		m_movpatt = photoslidepatt_static;
		update();
	}
}

void ImageWidget::showFScrn()
{
	qDebug() << "show full screen";

	preview2full();
	g_fullimage->m_slidetimer->start(m_slidedelta);
	g_fullimage->showFullScreen();
}

void ImageWidget::movLoadImage(void)
{
	static QString lastimg;   
	
	if(lastimg != imagePaths[currentSlide])
	{
        	//QImage slide = QImage(imagePaths[currentSlide]);
		if(m_img)
			free(m_img);

		m_img = new QImage(imagePaths[currentSlide]);
		lastimg = imagePaths[currentSlide];

        	QSize slideSize = m_img->size();
        	QSize scaledSize = QSize(qMin(slideSize.width(), size().width()),
            		qMin(slideSize.height(), size().height()));
        	if (slideSize != scaledSize)
		{
			QImage *tmpimg;
            		tmpimg = new QImage((m_img->scaled(scaledSize, Qt::KeepAspectRatio)));
			free(m_img);

			m_img = tmpimg;
		}

		qDebug() << "load image";
	}
}

void ImageWidget::movLeft2Right()
{
    	QPainter painter(this);
    	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect rect(0,0,size().width(),size().height());
	painter.fillRect(rect, Qt::black);
	
	QRect srcrect(0,0,m_width, m_img->height());
		
	QRect dstrect(qMax( (size().width() - m_img->width())/2, 0),
		qMax( (size().height() - m_img->height())/2, 0),
		m_width, 
		m_img->height());

	painter.drawImage(dstrect, *m_img ,srcrect,Qt::AutoColor);
	
	if(m_width < m_img->width())
	   	m_movtimer->start(m_movstep);
	else
		movStop();
	
	m_width += 5;        
}

void ImageWidget::movRight2Left()
{
    	QPainter painter(this);
    	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect rect(0,0,size().width(),size().height());
	painter.fillRect(rect, Qt::black);
	
	QRect srcrect(m_img->width()-m_width,0,m_width, m_img->height());
		
	int tmp_x;
	tmp_x = qMax( (size().width() + m_img->width())/2, 0) - m_width;
	QRect dstrect(tmp_x,
		qMax( (size().height() - m_img->height())/2, 0),
		m_width, 
		m_img->height());

	painter.drawImage(dstrect, *m_img ,srcrect,Qt::AutoColor);
	
	if(m_width < m_img->width())
	   	m_movtimer->start(m_movstep);
	else
		movStop();
	
	m_width += 5;        
}

void ImageWidget::movStatic(void)
{
    	QPainter painter(this);
    	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect rect(0,0,size().width(),size().height());
	painter.fillRect(rect, Qt::black);
	
        QRect imageRect( qMax( (size().width() - m_img->width())/2, 0),
                         qMax( (size().height() - m_img->height())/2, 0),
                         m_img->width(),
                         m_img->height());
	
	painter.drawImage(imageRect, *m_img);
	m_movtimer->stop();
}

void ImageWidget::movTop2Bottom(void)
{
    	QPainter painter(this);
    	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect rect(0,0,size().width(),size().height());
	painter.fillRect(rect, Qt::black);
	
	QRect srcrect(0,0,m_img->width(), m_height);
		
	QRect dstrect(qMax( (size().width() - m_img->width())/2, 0),
		qMax( (size().height() - m_img->height())/2, 0),
		m_img->width(), 
		m_height);

	painter.drawImage(dstrect, *m_img ,srcrect,Qt::AutoColor);
	
	if(m_height < m_img->height())
	   	m_movtimer->start(m_movstep);
	else
		movStop();
	
	m_height += 5;
}

void ImageWidget::movBottom2Top(void)
{
    	QPainter painter(this);
    	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect rect(0,0,size().width(),size().height());
	painter.fillRect(rect, Qt::black);
	
	QRect srcrect(0,m_img->height()-m_height,m_img->width(), m_height);
		
	int tmp_y;
	tmp_y = qMax( (size().height() + m_img->height())/2, 0) - m_height;
	QRect dstrect(qMax( (size().width() - m_img->width())/2, 0),
		tmp_y,
		m_img->width(), 
		m_height);

	painter.drawImage(dstrect, *m_img ,srcrect,Qt::AutoColor);
	
	if(m_height < m_img->height())
	   	m_movtimer->start(m_movstep);
	else
		movStop();
	
	m_height += 5;
}


void ImageWidget::movTurnRight(void)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect rect(0,0,size().width(),size().height());
	painter.fillRect(rect, Qt::black);
	
	QRect srcrect(0,0,m_img->width(), m_img->height());
	
	QRect dstrect(qMax( (size().width() - m_img->width())/2, 0),
		qMax( (size().height() - m_img->height())/2, 0),
		m_width, 
		m_img->height());

	painter.drawImage(dstrect, *m_img ,srcrect,Qt::AutoColor);
	
	if(m_width < m_img->width())
	   	m_movtimer->start(m_movstep);
	else
	{
	    m_width = 0;
	    m_movtimer->stop();
	}
	
	m_width += 5;
}

void ImageWidget::movMoveRight(void)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect rect(0,0,size().width(),size().height());
	painter.fillRect(rect, Qt::black);

	QRect srcrect(m_img->width()-m_width,0,m_width, m_img->height());
	
	QRect dstrect(qMax( (size().width() - m_img->width())/2, 0),
		qMax( (size().height() - m_img->height())/2, 0),
		m_width, 
		m_img->height());

	painter.drawImage(dstrect, *m_img ,srcrect,Qt::AutoColor);
	
	if(m_width < m_img->width())
	   	m_movtimer->start(m_movstep);
	else
		movStop();
	
	m_width += 5;
}

void ImageWidget::movBlindVertical(void)
{
    	QPainter painter(this);
    	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect rect(0,0,size().width(),size().height());
	painter.fillRect(rect, Qt::black);

#define BLIND_HSTEP	2
#define BLIND_HSHIFT	3

	QRect srcrect[1<<BLIND_HSHIFT];
	QRect dstrect[1<<BLIND_HSHIFT];
	for(int i=0; i < (1<<BLIND_HSHIFT); i++)
	{	
		srcrect[i].setRect(0,i*(m_img->height()>>BLIND_HSHIFT),m_img->width(), m_height);
		
		dstrect[i].setRect(qMax( (size().width() - m_img->width())/2, 0),
			qMax( (size().height() - m_img->height())/2, 0)+i*(m_img->height()>>BLIND_HSHIFT),
			m_img->width(), 
			m_height);

		painter.drawImage(dstrect[i], *m_img ,srcrect[i],Qt::AutoColor);
	}

	if(m_height < (m_img->height()>>BLIND_HSHIFT))
	   	m_movtimer->start(m_movstep);
	else
		movStop();
	
	m_height += BLIND_HSTEP;
}

void ImageWidget::movBlindHorizontal(void)
{
    	QPainter painter(this);
    	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect rect(0,0,size().width(),size().height());
	painter.fillRect(rect, Qt::black);

#define BLIND_HSTEP	2
#define BLIND_HSHIFT	3

	QRect srcrect[1<<BLIND_HSHIFT];
	QRect dstrect[1<<BLIND_HSHIFT];
	for(int i=0; i < (1<<BLIND_HSHIFT); i++)
	{	
		srcrect[i].setRect(i*(m_img->width()>>BLIND_HSHIFT),0, m_width, m_img->height());
		
		dstrect[i].setRect(qMax( (size().width() - m_img->width())/2, 0)+i*(m_img->width()>>BLIND_HSHIFT),
			qMax( (size().height() - m_img->height())/2, 0),
			m_width, 
			m_img->height());

		painter.drawImage(dstrect[i], *m_img ,srcrect[i],Qt::AutoColor);
	}

	if(m_width < (m_img->width()>>BLIND_HSHIFT))
	   	m_movtimer->start(m_movstep);
	else
		movStop();
	
	m_width += BLIND_HSTEP;
}

void ImageWidget::movTurnNext(void)
{
	static QString lastimg;   

	qDebug() << "move turn next";	
	if(lastimg != imagePaths[currentSlide])
	{
		lastimg = imagePaths[currentSlide];

		if(m_imgstandby)
			free(m_imgstandby);
		 
		m_imgstandby = new QImage(imagePaths[currentSlide]);
		
        	QSize slideSize = m_imgstandby->size();
        	QSize scaledSize = QSize(qMin(slideSize.width(), size().width()),
            		qMin(slideSize.height(), size().height()));
        	if (slideSize != scaledSize)
		{
			QImage *tmpimg;
            		tmpimg = new QImage((m_imgstandby->scaled(scaledSize, Qt::KeepAspectRatio)));
			free(m_imgstandby);

			m_imgstandby = tmpimg;
		}

		//change normal with standby
		QImage *exchangeimg = m_img;
		m_img = m_imgstandby;
		m_imgstandby = exchangeimg;

		qDebug() << "load image";
	}

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect rect(0,0,size().width(),size().height());
	painter.fillRect(rect, Qt::black);

	//img(next)	
	//m_width(frame move)
	int imgdelta = (qAbs(size().width() - m_img->width())) >> 1;

	if(m_width < imgdelta)
	{
		//do nothing
	}
	else if(m_width < (imgdelta + m_img->width()))
	{
		QRect srcrect(m_img->width() - (m_width-imgdelta),0,m_width-imgdelta, m_img->height());
	
		QRect dstrect(0,
			qMax( (size().height() - m_img->height())/2, 0),
			m_width-imgdelta, 
			m_img->height());
	
		painter.drawImage(dstrect, *m_img ,srcrect,Qt::AutoColor);
	}
	else
	{	
		QRect srcrect(0,0,
			m_img->width(),
		       	m_img->height());
	
		QRect dstrect(m_width - (imgdelta + m_img->width()),
			qMax( (size().height() - m_img->height())/2, 0),
			m_img->width(), 
			m_img->height());
		
		painter.drawImage(dstrect, *m_img ,srcrect,Qt::AutoColor);
	}
	
	//img_standby(now) 
	int standbydelta = qAbs( (size().width() - m_imgstandby->width())) >> 1;
	if(m_width < standbydelta)
	{
		QRect srcrect(0,0,m_imgstandby->width(), m_imgstandby->height());
	
		QRect dstrect(standbydelta + m_width,
			qMax( (size().height() - m_imgstandby->height())/2, 0),
			m_imgstandby->width(), 
			m_imgstandby->height());
	
		painter.drawImage(dstrect, *m_imgstandby ,srcrect,Qt::AutoColor);
	}
	else
	{
		QRect srcrect(0,0,
			m_imgstandby->width() - m_width + standbydelta, 
			m_imgstandby->height());
	
		QRect dstrect(standbydelta + m_width,
			qMax( (size().height() - m_imgstandby->height())/2, 0),
			m_imgstandby->width() - m_width + standbydelta, 
			m_imgstandby->height());
		painter.drawImage(dstrect, *m_imgstandby ,srcrect,Qt::AutoColor);
	}
	
	if(m_width < size().width())
	   	m_movtimer->start(m_movstep);
	else
		movStop();

	m_width += 20;
}

void ImageWidget::movTurnPrev(void)
{
	static QString lastimg;   

	qDebug() << "move turn next";	
	if(lastimg != imagePaths[currentSlide])
	{
		lastimg = imagePaths[currentSlide];

		if(m_imgstandby)
			free(m_imgstandby);
		 
		m_imgstandby = new QImage(imagePaths[currentSlide]);
		
        	QSize slideSize = m_imgstandby->size();
        	QSize scaledSize = QSize(qMin(slideSize.width(), size().width()),
            		qMin(slideSize.height(), size().height()));
        	if (slideSize != scaledSize)
		{
			QImage *tmpimg;
            		tmpimg = new QImage((m_imgstandby->scaled(scaledSize, Qt::KeepAspectRatio)));
			free(m_imgstandby);

			m_imgstandby = tmpimg;
		}

		//change normal with standby
		QImage *exchangeimg = m_img;
		m_img = m_imgstandby;
		m_imgstandby = exchangeimg;

		qDebug() << "load image";
	}

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect rect(0,0,size().width(),size().height());
	painter.fillRect(rect, Qt::black);

	//img(next)	
	//m_width(frame move)
	int imgdelta = (qAbs(size().width() - m_img->width())) >> 1;

	if(m_width < imgdelta)
	{
		//do nothing
	}
	else if(m_width < (imgdelta + m_img->width()))
	{
		QRect srcrect(0,0,m_width-imgdelta, m_img->height());
	
		QRect dstrect(size().width()-m_width+imgdelta,
			qMax( (size().height() - m_img->height())/2, 0),
			m_width-imgdelta, 
			m_img->height());
	
		painter.drawImage(dstrect, *m_img ,srcrect,Qt::AutoColor);
	}
	else
	{	
		QRect srcrect(0,0,
			m_img->width(),
		       	m_img->height());
	
		QRect dstrect(size().width()-m_width+imgdelta,
			qMax( (size().height() - m_img->height())/2, 0),
			m_img->width(), 
			m_img->height());
		
		painter.drawImage(dstrect, *m_img ,srcrect,Qt::AutoColor);
	}
	
	//img_standby(now) 
	int standbydelta = qAbs( (size().width() - m_imgstandby->width())) >> 1;
	if(m_width < standbydelta)
	{
		QRect srcrect(0,0,m_imgstandby->width(), m_imgstandby->height());
	
		QRect dstrect(standbydelta - m_width,
			qMax( (size().height() - m_imgstandby->height())/2, 0),
			m_imgstandby->width(), 
			m_imgstandby->height());
	
		painter.drawImage(dstrect, *m_imgstandby ,srcrect,Qt::AutoColor);
	}
	else
	{
		QRect srcrect(m_width-standbydelta,0,
			m_imgstandby->width() - m_width + standbydelta, 
			m_imgstandby->height());
	
		QRect dstrect(0,
			qMax( (size().height() - m_imgstandby->height())/2, 0),
			m_imgstandby->width() - m_width + standbydelta, 
			m_imgstandby->height());
		painter.drawImage(dstrect, *m_imgstandby ,srcrect,Qt::AutoColor);
	}
	
	if(m_width < size().width())
	   	m_movtimer->start(m_movstep);
	else
		movStop();

	m_width += 20;
}

void ImageWidget::movStop(void)
{
	m_width = 0;
	m_height = 0;
	m_x = 0;
	m_y = 0;

	m_movtimer->stop();
	m_movpatt = photoslidepatt_none;
}

void ImageWidget::movNone(void)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, false);

	QRect rect(0,0,size().width(),size().height());
	painter.fillRect(rect, Qt::black);
}

void ImageWidget::paintEvent(QPaintEvent *event)
{	
    //qDebug() << currentSlide;

    if (this->imagePaths.size() > 0) 
    {
	if(m_movpatt == photoslidepatt_static)
	{
		movLoadImage();//load 1 img
		movStatic();
		return;
	}

	if(m_movpatt < photoslidepatt_none)
    		movLoadImage();//load 1 img

	switch(m_movpatt)
	{
		case photoslidepatt_left2right:
			movLeft2Right();
			break;
		case photoslidepatt_right2left:
			movRight2Left();
			break;
		case photoslidepatt_top2bottom:
			movTop2Bottom();
			break;
		case photoslidepatt_bottom2top:
			movBottom2Top();
			break;
		case photoslidepatt_moveright:
			movMoveRight();
			break;
		case photoslidepatt_turnright:
			movTurnRight();
			break;
		case photoslidepatt_blindvertical:
			movBlindVertical();
			break;
		case photoslidepatt_blindhorizontal:
			movBlindHorizontal();
			break;
	
		case photoslidepatt_none:
			movNone();
			break;
		case photoslidepatt_turnnext:
			movTurnNext();
			break;
		case photoslidepatt_turnprev:
			movTurnPrev();
			break;
		default:
			break;
    	}

	showToolbar();
	g_fullimage->m_slidetimer->start(m_slidedelta);
    }
}

void ImageWidget::showNextConnect(void)
{
	movStop();
	m_movpatt = photoslidepatt_turnnext;
	currentSlide = (currentSlide+1)%(imagePaths.size()); 
	update();
}

void ImageWidget::showPrevConnect(void)
{
	movStop();
	m_movpatt = photoslidepatt_turnprev;
	currentSlide = currentSlide >= imagePaths.size() ? 0 : (currentSlide -1); 
		
	update();
}


void ImageWidget::mouseMoveEvent(QMouseEvent* event)
{
  	int distanceMovedSinceLastEvent = event->pos().x() - m_previousPos.x();
  	m_previousPos = event->pos();

	// Increment the distance moved for this event
	m_pixelDistanceMoved += distanceMovedSinceLastEvent;
}

void ImageWidget::mousePressEvent(QMouseEvent* event)
{
	m_pixelDistanceMoved = 0;
	m_previousPos = event->pos();
	
	mayshowtool();
	m_tooltimer->stop();
	m_tooltimer->start(3000);
}

void ImageWidget::mouseReleaseEvent(QMouseEvent* event)
{
	#define MOUSEMOVENEXT_THRESHOLD 	40
	#define MOUSEMOVEPREV_THRESHOLD 	-40

	//void(*imgfuncp[])(void) = {full2preview, full2preview, full2preview};
	

	if(m_toolbarhide == false)
	{
		for(int i=0; i < TOOLNUM; i++)
		{
			if(event->pos().x() > TOOLX(i) && event->pos().x() < (TOOLX(i)+TOOLSIZE)
			&& event->pos().y() > TOOLY && event->pos().y() < (TOOLY+TOOLSIZE))
			{
				qDebug() << event->pos().x();
				qDebug() << event->pos().y();
				//imgfuncp[i]();
				full2preview();
				g_fullimage->hide();
			}
		}
	}

	// Check against threshold
	if (m_pixelDistanceMoved > MOUSEMOVENEXT_THRESHOLD)
		showNextConnect();

	if (m_pixelDistanceMoved < MOUSEMOVEPREV_THRESHOLD)
		showPrevConnect();

	m_pixelDistanceMoved = 0;


}

TreeshowWidget::TreeshowWidget(QWidget *parent)
{
//treeview
	m_model = new QDirModel;
        m_model->setReadOnly(false);
        m_model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

        QStringList list;
        list << "*.jpg" << "*.cpp" << "*.png";
        //m_model->setNameFilters(list);

        m_treeview = new QTreeView;
        m_treeview->setModel(m_model);
        m_treeview->header()->setStretchLastSection(true);
        m_treeview->header()->setSortIndicator(0, Qt::AscendingOrder);
        m_treeview->header()->setSortIndicatorShown(true);
        m_treeview->header()->setClickable(true);

        m_photodir=getenv("PHOTOTREE_DIR");
        QModelIndex index = m_model->index(QLatin1String(m_photodir));
        m_treeview->setRootIndex(index);
        m_treeview->hideColumn(1);
        m_treeview->hideColumn(2);
        m_treeview->hideColumn(3);
        m_treeview->expand(index);
        m_treeview->scrollTo(index);
        m_treeview->resizeColumnToContents(0);

//treeshow button
	
        m_showbutton=new QToolButton;
        m_showbutton->setObjectName("showbutton");

        QVBoxLayout *treeLayout=new QVBoxLayout(this);
        treeLayout->addWidget(m_treeview);
        treeLayout->addWidget(m_showbutton);

	//this->setLayout(treeLayout);

}
/*end of photoviewer.cpp*/

