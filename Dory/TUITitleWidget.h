#ifndef _TUITILEWIDGET_H_
#define _TUITILEWIDGET_H_
#include "qwidget.h"
#include "QToolButton"
#include "QList"

class TUIToolButton;

class TUITitleWidget :
	public QWidget
{
	Q_OBJECT
public:
	explicit TUITitleWidget(QWidget* parent = 0);
	~TUITitleWidget(void);
protected:
	void paintEvent(QPaintEvent* event);
private:
	QList<TUIToolButton*> m_BtnList;
	int m_nCurIndex;
private slots:
	void onBtnClicked();
signals:
	void sigClicked(int);
};



#endif//_TUITILEWIDGET_H_
