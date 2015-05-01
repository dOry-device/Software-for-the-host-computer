#ifndef _APPGLOBAL_H_
#define _APPGLOBAL_H_

//#define _TEST_

#define UI_INDEX_TOAL			0
#define UI_INDEX_GAS_TEMP		1
#define UI_INDEX_WATER_TEMP		2
#define UI_INDEX_CONDUCTOR		3
#define UI_INDEX_TRANSPARENT	4
#define UI_INDEX_COMCONFIG		5

#define UI_INDEX_NUM			UI_INDEX_COMCONFIG+1

#define BTN_CLICKED(BTN, FUN) connect(BTN,SIGNAL(clicked()),this, SLOT(FUN()))

#define DB_TABLE "t_info"

#define MY_STR(_str_) QString::fromLocal8Bit(_str_)

#include "QString"
typedef struct
{
	float GasTmp;
	QString GPS_N;
	QString GPS_E;
	float WaterTmp;
	float Conductor;
	float Trans;
	qint64 CurMs;
} TInfoData;

class TInterface;
extern TInterface* g_pTInterface;

#define INFINITE_CHAR QString('N')
#define INFINITE_DATA (-1000)
#define INFINITE_DATA_DIFF (INFINITE_DATA+0.0001)
#endif//_APPGLOBAL_H_