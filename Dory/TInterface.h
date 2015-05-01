#ifndef _TINTERFACE_H_
#define _TINTERFACE_H_

#include "qobject.h"
#include "QStackedWidget"

class TUITitleWidget;
class QStackedWidget;
class TUISerial;
class TUIToal;


class TInterface : public QObject
{
	Q_OBJECT
public:
	TInterface(void);
	void createSlots();
	~TInterface(void);
public:
	TUITitleWidget* m_pTitleWidget;
	QStackedWidget* m_pStackedWidget;
	TUISerial* m_pSerial;
	TUIToal* m_pToal;
};




#endif//_TINTERFACE_H_
