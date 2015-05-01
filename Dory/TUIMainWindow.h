#ifndef _TUIMAINWINDEOW_H_
#define _TUIMAINWINDEOW_H_
#include "qwidget.h"
#include "QList"
#include "TUIToal.h"

class QStackedWidget;
class TUITitleWidget;
class TUISerial;
class TUIChart;

class TUIMainWindow :
	public QWidget
{
	Q_OBJECT
public:
	explicit TUIMainWindow(QWidget* parent = 0);
	~TUIMainWindow(void);
protected:
	void paintEvent(QPaintEvent* event);
private:
	TUITitleWidget* m_pTitle;
	TUIToal* m_pToal;
	TUIChart* m_pGasTemp;
	TUIChart* m_pWaterTemp;
	TUIChart* m_pConductor;
	TUIChart* m_pTransparent;
	TUISerial* m_pComConfig;

	QStackedWidget* m_pStackedWidget;
	QList<QWidget*> m_WidgetList;
};
#endif //_TUIMAINWINDEOW_H_


