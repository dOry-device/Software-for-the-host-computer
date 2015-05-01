#ifndef _TUITOOLBUTTON_H_
#define _TUITOOLBUTTON_H_

#include <QToolButton>
#include <QMouseEvent>
#include <QPainter>

class TUIToolButton : public QToolButton
{
#define PIX_SIZE 70
	Q_OBJECT
public:
	explicit TUIToolButton(QPixmap& pic, QWidget *parent = 0);
	~TUIToolButton();
	void setMousePress(bool mouse_press);
protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	void painterInfo(int top_color, int middle_color, int bottom_color);
private:
	bool m_bHover; //鼠标是否移过
	bool m_bPressed; //鼠标是否按下
};

#endif //_TUITOOLBUTTON_H_
