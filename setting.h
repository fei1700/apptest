/*setting.h*/
#ifndef SETTING_H
#define SETTING_H

#include <QtGui>

class Setting : public QWidget
{
	Q_OBJECT
public:
	Setting(QWidget *parent=0);
private:
	int language;
};

#endif
/*end of setting.h*/
