#include "TInterface.h"
#include "TUITitleWidget.h"
#include "TUISerial.h"
#include "TUIToal.h"
#include "QStackedWidget"

TInterface::TInterface(void)
{
}


TInterface::~TInterface(void)
{

}

void TInterface::createSlots()
{
	connect(m_pTitleWidget,SIGNAL(sigClicked(int)),m_pStackedWidget,SLOT(setCurrentIndex(int)));
	connect(m_pSerial,SIGNAL(sigRxData(TInfoData)),m_pToal,SLOT(slotAddData(TInfoData)));
}

TInterface* g_pTInterface;