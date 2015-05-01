#include "TUIToolButton.h"

TUIToolButton::TUIToolButton(QPixmap& pic, QWidget *parent)
	:QToolButton(parent)
{
	//设置文本颜色
	QPalette text_palette = palette();
	//text_palette.setColor(QPalette::ButtonText, QColor(230, 230, 230));
	text_palette.setColor(QPalette::ButtonText, Qt::black);
	setPalette(text_palette);

	//设置文本粗体
	QFont &text_font = const_cast<QFont &>(font());
	text_font.setWeight(QFont::Bold);

	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	//设置图标
	pic = pic.scaled(PIX_SIZE,PIX_SIZE);
	setIcon(pic);
	setIconSize(pic.size());

	//设置大小
	setFixedSize(pic.width()+25, pic.height()+25);
	setAutoRaise(true);
	setFocusPolicy(Qt::NoFocus);
	//setObjectName("transparentToolButton");
	setStyleSheet("background:transparent;");
	m_bHover = false;
	m_bPressed = false;
}

TUIToolButton::~TUIToolButton()
{

}

void TUIToolButton::enterEvent(QEvent *)
{
	m_bHover = true;
}

void TUIToolButton::leaveEvent(QEvent *)
{
	m_bHover = false;
}

void TUIToolButton::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		emit clicked();
	}
}

void TUIToolButton::setMousePress(bool mouse_press)
{
	this->m_bPressed = mouse_press;
	update();
}

void TUIToolButton::paintEvent(QPaintEvent *event)
{
	if(m_bHover)
	{
		//绘制鼠标移到按钮上的按钮效果
		painterInfo(100, 100, 200);
	}
	else
	{
		if(m_bPressed)
		{
			painterInfo(100, 100, 200);
		}
	}

	QToolButton::paintEvent(event);
}

void TUIToolButton::painterInfo(int top_color, int middle_color, int bottom_color)
{
	QPainter painter(this);
	QPen pen(Qt::NoBrush, 1);
	painter.setPen(pen);
	QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	//linear.setColorAt(0, QColor(230, 230, 230, top_color));
	linear.setColorAt(0, QColor(109,198,70, top_color));
	linear.setColorAt(0.5, QColor(109,198,70, middle_color));
	linear.setColorAt(1, QColor(109,198,70, bottom_color));
	painter.setBrush(linear);
	painter.drawRect(rect());
}
