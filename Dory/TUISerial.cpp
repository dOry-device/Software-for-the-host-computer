#include "TUISerial.h"
#include "QSerialPortInfo"
#include "AppGlobal.h"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QGridLayout"
#include "QSpacerItem"
#include "QComboBox"
#include "QMessageBox"
#include "QDateTime"
#include "QSettings"


TUISerial::TUISerial( QWidget* parent /*= 0*/ ):QWidget(parent)
{
	//setStyleSheet("border:1px solid red;");
	m_bOpen = false;

	m_pCom = new QComboBox;
	m_pBaudrate = new QComboBox;
	m_pParty = new QComboBox;
	m_pBtnOpen = new QPushButton(MY_STR("OPEN"));

	m_pCom->addItems(AvailablePorts());
	QStringList list;
	list<<"1200"<<"2400"<<"4800"<<"9600"<<"115200";
	m_pBaudrate->addItems(list);
	m_pParty->addItem(MY_STR("NoParity"));
	m_pParty->addItem(MY_STR("EvenParity"));
	m_pParty->addItem(MY_STR("OddParity"));


	QHBoxLayout* layout = new QHBoxLayout;
	layout->addStretch();
	layout->addWidget(m_pBtnOpen);
	layout->addStretch();

	QVBoxLayout* centralLayout = new QVBoxLayout;
	centralLayout->addWidget(m_pCom);
	centralLayout->addWidget(m_pBaudrate);
	centralLayout->addWidget(m_pParty);
	centralLayout->addLayout(layout);


	QHBoxLayout* topLayout = new QHBoxLayout;
	topLayout->addStretch(2);
	topLayout->addLayout(centralLayout,1);
	topLayout->addStretch(2);

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(0,50,0,0);
	mainLayout->setSpacing(20);
	mainLayout->addLayout(topLayout);
	mainLayout->addStretch();

	m_pSerial = new QSerialPort(this);
	BTN_CLICKED(m_pBtnOpen,slotOpenCom);

	connect(&m_TimerInterval,SIGNAL(timeout()),this ,SLOT(slotInterTimeout()));
	connect(m_pSerial, SIGNAL(readyRead()), this, SLOT(readData()));

	serialize(true);
	slotOpenCom();
}


TUISerial::~TUISerial(void)
{
	serialize(false);
}

bool TUISerial::openCom (const QString& name,qint32 baudRate,QSerialPort::Parity parity )
{
	bool ret = false;
	m_pSerial->setPortName(name);
#if QT_VERSION > 0x050200//QT5.2.0以下版本必须先打开再设置参数
	ret = m_pSerial->open(QIODevice::ReadWrite);
#endif
	ret &= m_pSerial->setBaudRate(baudRate);
	ret &=m_pSerial->setParity(parity);
#if QT_VERSION <= 0x050200//QT5.2.0以下版本必须先打开再设置参数
	ret = m_pSerial->open(QIODevice::ReadWrite);
#endif
	return ret;
}

void TUISerial::slotOpenCom()
{
	if (!m_bOpen)
	{
		QString com = m_pCom->currentText();
		int nBaudrate = m_pBaudrate->currentText().toUInt();
		QSerialPort::Parity party;
		if (m_pParty->currentIndex() == 0)
		{
			party = QSerialPort::NoParity;
		}
		else if (m_pParty->currentIndex() == 1)
		{
			party = QSerialPort::EvenParity;
		}
		else if (m_pParty->currentIndex() == 0)
		{
			party = QSerialPort::OddParity;
		}
		if (openCom(com,nBaudrate,party))
		{
			setEnableUI(false);
			m_pBtnOpen->setText(MY_STR("Close"));
			m_bOpen = true;
		}
		else
		{
			QMessageBox::information(this,MY_STR("Fail"),MY_STR("Open Uart Failed！"));
		}
	}
	else
	{
		m_pSerial->close();
		setEnableUI(true);
		m_pBtnOpen->setText(MY_STR("Open"));
		m_bOpen = false;
	}
}

QStringList TUISerial::AvailablePorts()
{
	QList<QSerialPortInfo> PortsList = QSerialPortInfo::availablePorts();
	QStringList strList;
	for (int i=0; i<PortsList.count(); i++)
	{
		strList<<PortsList[i].portName();
	}
	strList.sort();
	return strList;
}

void TUISerial::setEnableUI( bool bEn )
{
	m_pCom->setEnabled(bEn);
	m_pBaudrate->setEnabled(bEn);
	m_pParty->setEnabled(bEn);
}

void TUISerial::slotInterTimeout()
{
	m_TimerInterval.stop();
	m_RxArray.clear();
}

void TUISerial::readData()
{
	if (m_TimerInterval.isActive())
	{
		m_TimerInterval.stop();
	}
	m_TimerInterval.start(ONE_INTERVAL_TIME);
	qint64 nLen = m_pSerial->bytesAvailable();
	QByteArray CacheArray;
	CacheArray.resize(nLen);
	nLen = m_pSerial->read(CacheArray.data(),CacheArray.size());
	m_RxArray.append(CacheArray);
	QList<QByteArray> array = m_RxArray.split(',');

	if(array.count()!= 8)
	{
		return;
	}
	if(!((array.at(0)=="S") && (array.at(array.count()-1) == "E")))
	{
		return;
	}

	TInfoData data;
	if (QString(array.at(1)) == INFINITE_CHAR)
		data.GasTmp = INFINITE_DATA;
	else
		data.GasTmp = array.at(1).toFloat();

	if (QString(array.at(2)) == INFINITE_CHAR)
		data.GPS_N = "";
	else
		data.GPS_N = QString(array.at(2));

	if (QString(array.at(3)) == INFINITE_CHAR)
		data.GPS_E = "";
	else
		data.GPS_E = QString(array.at(3));

	if (QString(array.at(4)) == INFINITE_CHAR)
		data.WaterTmp = INFINITE_DATA;
	else
		data.WaterTmp = array.at(4).toFloat();

	if (QString(array.at(5)) == INFINITE_CHAR)
		data.Conductor = INFINITE_DATA;
	else
		data.Conductor = array.at(5).toFloat();

	if (QString(array.at(6)) == INFINITE_CHAR)
		data.Trans = INFINITE_DATA;
	else
		data.Trans = array.at(6).toFloat();

	data.CurMs = QDateTime::currentMSecsSinceEpoch();
	//emit m_pDataObject->sigRxData(tabData);
	emit sigRxData(data);
}

void TUISerial::serialize( bool bLoad/*=true*/ )
{
	QSettings mySetting("COM.ini",QSettings::IniFormat);
	if (bLoad)
	{
		m_pCom->setCurrentIndex(mySetting.value("COM","0").toUInt());
		m_pBaudrate->setCurrentIndex(mySetting.value("baudrate","0").toUInt());
		m_pParty->setCurrentIndex(mySetting.value("party","0").toUInt());
	}
	else
	{
		mySetting.setValue("COM",m_pCom->currentIndex());
		mySetting.setValue("baudrate",m_pBaudrate->currentIndex());
		mySetting.setValue("party",m_pParty->currentIndex());
	}

}

