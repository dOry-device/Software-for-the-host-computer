#include "TUIToal.h"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QSqlRecord"
#include "QHeaderView"
#include "QDateTime"
#include "QDate"
#include "QCalendarWidget"
#include "QDebug"

TUIToal::TUIToal( QWidget *parent /*= 0*/ ):QWidget(parent)
{
	m_pCombox = new QComboBox;
	m_pDate = new QDateEdit;
	
	m_pView = new QTableView;
	m_pModel = new MyTableModel(this);
	m_pModel->setTable(DB_TABLE);
	m_pView->setModel(m_pModel);
	
	QHBoxLayout* topLayout = new QHBoxLayout;
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	topLayout->addWidget(m_pCombox);
	topLayout->addWidget(m_pDate);
	topLayout->addWidget(m_pBtnDel = new QPushButton(MY_STR("Del")));
	topLayout->addWidget(m_pBtnClear = new QPushButton(MY_STR("Clear all")));
	BTN_CLICKED(m_pBtnDel,slotDel);
	BTN_CLICKED(m_pBtnClear,slotClear);
#ifdef _TEST_
	topLayout->addWidget(m_pBtnAdd = new QPushButton("add"));
	topLayout->addWidget(m_pBtnSubmit = new QPushButton("submit"));
	BTN_CLICKED(m_pBtnAdd,SlotAdd);
	BTN_CLICKED(m_pBtnSubmit,SlotSubmit);
#endif
	topLayout->addStretch();
	mainLayout->addLayout(topLayout);
	mainLayout->addWidget(m_pView);

	m_pDate->setDate(QDate::currentDate());
	m_pDate->setCalendarPopup(true);
	m_pDate->setStyleSheet("");
	m_pDate->calendarWidget()->setLocale(QLocale::English);

	m_pCombox->addItem(MY_STR("All"));
	m_pCombox->addItem(MY_STR("Year"));
	m_pCombox->addItem(MY_STR("Month"));
	m_pCombox->addItem(MY_STR("Day"));

	m_pModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_pView->setSelectionBehavior(QAbstractItemView::SelectRows);
	//自定义表头
	m_pModel->setHeaderData(0, Qt::Horizontal, MY_STR("Data"));
	m_pModel->setHeaderData(1, Qt::Horizontal, MY_STR("Air Temp(℃)"));
	m_pModel->setHeaderData(2, Qt::Horizontal, MY_STR("GPS"));
	m_pModel->setHeaderData(3, Qt::Horizontal, MY_STR("Water Temp(℃)"));
	m_pModel->setHeaderData(4, Qt::Horizontal, MY_STR("Conductivity(S●m-1)"));
	m_pModel->setHeaderData(5, Qt::Horizontal, MY_STR("Transparence(mm)"));
	
	m_pView->setStyleSheet("background:transparent;");
	m_pView->horizontalHeader()->setDefaultSectionSize(150);
	m_pView->horizontalHeader()->setStretchLastSection(true);
	//m_pView->horizontalHeader()->setSortIndicatorShown(true);
	m_pView->horizontalHeader()->setHighlightSections(false);
	//m_pView->horizontalHeader()->setSectionsMovable(true);
	m_pView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_pView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pModel->select();

	connect(m_pCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSelectChanged(int)));
	connect(m_pDate,SIGNAL(dateChanged(const QDate&)),this,SLOT(slotDateChanged(const QDate&)));
}


TUIToal::~TUIToal(void)
{
}
#ifdef _TEST_

void TUIToal::SlotAdd()
{
	QSqlRecord record = m_pModel->record();
	record.setValue("GasTemp", 11);
	m_pModel->insertRecord(-1,record);
}


void TUIToal::SlotSubmit()
{
	m_pModel->submitAll();
	m_pModel->select();
}
#endif
void TUIToal::slotDel()
{
	qDebug()<<"sqltab::delRecord()";
	QItemSelectionModel * selectModel = m_pView->selectionModel();
	// 通过选中的数据结构，获取这些格子的ModelIndex
	QModelIndexList indexList =  selectModel->selectedIndexes();

	// QModelIndexList  * indexList = _view->selectedIndexes();
	QSet<int> delRow;
	for(int i=0; i<indexList.count(); i++)
	{
		QModelIndex index = indexList.at(i);
		delRow.insert(index.row());
	}
	//得到表的行数然后逆序，保证按从大到小的顺序依次删除数据
	QList<int> list = delRow.toList();
	qSort(list.begin(), list.end(), qGreater<int>());

	for(int i=0; i<list.count(); i++)
	{
		m_pModel->removeRow(list.at(i));
		qDebug()<<list.at(i);
	}
	m_pModel->submitAll();
	emit UpdateDB();
}



void TUIToal::slotAddData( TInfoData data )
{
	QSqlRecord record = m_pModel->record();
	record.setValue("GasTemp", data.GasTmp);
	QString strGPS;
	strGPS = data.GPS_N+data.GPS_E;
	record.setValue("GPS", strGPS);
	record.setValue("WaterTemp", data.WaterTmp);
	record.setValue("Conductor", data.Conductor);
	record.setValue("Transparent", data.Trans);
	record.setValue("CurMs",data.CurMs);
	m_pModel->insertRecord(-1,record);
	m_pModel->submitAll();
	emit UpdateDB();
}

void TUIToal::slotSelectChanged( int index )
{
	switch(index)
	{
	case 0://全部
	{
		m_pModel->setFilter("");
		m_pModel->select();
		break;
	}
	case 1://年
	{
		QDate date = m_pDate->date();
		qint64 nStart = QDateTime(QDate(date.year(),1,1)).toMSecsSinceEpoch();
		qint64 nStop = QDateTime(QDate(date.year()+1,1,1)).toMSecsSinceEpoch()-1;
		m_pModel->setFilter(QString("CurMs>=%1 and CurMs<=%2").arg(nStart).arg(nStop));
		m_pModel->select();
		break;
	}
	case 2://月
	{
		QDate date = m_pDate->date();
		qint64 nStart = QDateTime(QDate(date.year(),date.month(),1)).toMSecsSinceEpoch();
		date = date.addMonths(1);
		qint64 nStop = QDateTime(QDate(date.year(),date.month(),1)).toMSecsSinceEpoch()-1;
		m_pModel->setFilter(QString("CurMs>=%1 and CurMs<=%2").arg(nStart).arg(nStop));
		m_pModel->select();
		break;
	}
	case 3://日
	{
		QDate date = m_pDate->date();
		qint64 nStart = QDateTime(date).toMSecsSinceEpoch();
		date = date.addDays(1);
		qint64 nStop = QDateTime(date).toMSecsSinceEpoch()-1;
		m_pModel->setFilter(QString("CurMs>=%1 and CurMs<=%2").arg(nStart).arg(nStop));
		m_pModel->select();
		break;
	}
	default:
		break;
	}
}

void TUIToal::slotDateChanged( const QDate& date )
{
	slotSelectChanged(m_pCombox->currentIndex());
}

void TUIToal::slotClear()
{
	//m_pModel->clear();
	m_pModel->removeRows(0,m_pModel->rowCount());
	m_pModel->submitAll();
	emit UpdateDB();
}
