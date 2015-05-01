#ifndef _TUISERIAL_H_
#define _TUISERIAL_H_
#include "QWidget"
#include "QComboBox"
#include "QSerialPort"
#include "QPushButton"
#include "QTimer"
#include "QByteArray"
#include "AppGlobal.h"

class TUISerial :public QWidget
{
	#define ONE_INTERVAL_TIME	30
	Q_OBJECT
public:
	explicit TUISerial(QWidget* parent = 0);
	~TUISerial(void);
private:
	QComboBox* m_pCom;
	QComboBox* m_pBaudrate;
	QComboBox* m_pParty;
	QPushButton* m_pBtnOpen;

	QSerialPort* m_pSerial;
	static QStringList AvailablePorts();
	bool openCom (const QString& name,qint32 baudRate,QSerialPort::Parity parity );
	bool m_bOpen;
	QTimer m_TimerInterval;
	QByteArray m_RxArray;

	void serialize(bool bLoad=true);
private slots:
	void slotOpenCom();
	void setEnableUI(bool bEn);
	void slotInterTimeout();
	void readData();
signals:
	void sigRxData(TInfoData);
};



#endif//_TUISERIAL_H_
