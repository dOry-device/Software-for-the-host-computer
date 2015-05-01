#include "TUIMainWindow.h"
#include "QToolBar"
#include "QStackedWidget"
#include "QVBoxLayout"
#include "QPushButton"
#include "TUITitleWidget.h"
#include "TUIResource.h"
#include "AppGlobal.h"
#include "assert.h"
#include "QPainter"
#include "TUISerial.h"
#include "TInterface.h"
#include "TUIChart.h"
#include "TCustomModel.h"

//void (*tInitModel)(MyTableModel* model);

static void GasTemp(MyTableModel* model)
{
	model->setHeaderData(0, Qt::Horizontal, MY_STR("Data"));
	model->setHeaderData(1, Qt::Horizontal, MY_STR("Air Temp(¡æ)"));
	model->removeColumns(2,4);
}

static void WaterTemp(MyTableModel* model)
{
	model->setHeaderData(0, Qt::Horizontal, MY_STR("Data"));
	model->setHeaderData(1, Qt::Horizontal, MY_STR("Water Temp(¡æ)"));
	model->removeColumn(5);
	model->removeColumn(4);
	model->removeColumn(2);
	model->removeColumn(1);
}

static void Conductor(MyTableModel* model)
{
	model->setHeaderData(0, Qt::Horizontal, MY_STR("Data"));
	model->setHeaderData(1, Qt::Horizontal, MY_STR("Conductivity(S¡ñm-1)"));
	model->removeColumn(5);
	model->removeColumn(3);
	model->removeColumn(2);
	model->removeColumn(1);
}

static void Transparent(MyTableModel* model)
{
	model->setHeaderData(0, Qt::Horizontal, MY_STR("Data"));
	model->setHeaderData(1, Qt::Horizontal, MY_STR("Transparence(mm)"));
	model->removeColumn(4);
	model->removeColumn(3);
	model->removeColumn(2);
	model->removeColumn(1);
}



TUIMainWindow::TUIMainWindow( QWidget* parent /*= 0*/ ):QWidget(parent)
{
	//setStyleSheet("border:1px solid red;");
	m_pTitle = new TUITitleWidget;

	m_pToal = new TUIToal;
	m_pGasTemp = new TUIChart("GasTemp",GasTemp);
	m_pWaterTemp = new TUIChart("WaterTemp",WaterTemp);
	m_pConductor = new TUIChart("Conductor",Conductor);
	m_pTransparent = new TUIChart("Transparent",Transparent);
	m_pComConfig = new TUISerial;
	m_pStackedWidget = new QStackedWidget;

	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(m_pTitle);
	mainLayout->addWidget(m_pStackedWidget);

	m_WidgetList<<m_pToal<<m_pGasTemp<<m_pWaterTemp<<m_pConductor<<m_pTransparent<<m_pComConfig;
	assert(m_WidgetList.count() == UI_INDEX_NUM);
	for (int i=0; i<UI_INDEX_NUM; i++)
	{
		m_pStackedWidget->addWidget(m_WidgetList[i]);
	}
	for(int i=UI_INDEX_GAS_TEMP; i<=UI_INDEX_TRANSPARENT; i++)
	{
		connect(m_pToal,SIGNAL(UpdateDB()),m_WidgetList[i],SLOT(slotDateChanged()));
	}

	m_pStackedWidget->setObjectName("StackedWidget");
	m_pStackedWidget->setStyleSheet("QStackedWidget#StackedWidget{background: rgba(0, 0, 0, 50);}");

	g_pTInterface->m_pStackedWidget = m_pStackedWidget;
	g_pTInterface->m_pTitleWidget = m_pTitle;
	g_pTInterface->m_pToal = m_pToal;
	g_pTInterface->m_pSerial = m_pComConfig;
	g_pTInterface->createSlots();

	setWindowIcon(QIcon("Resource\\icon.ico"));
	setWindowTitle("dOry");
	
}


TUIMainWindow::~TUIMainWindow(void)
{

}

void TUIMainWindow::paintEvent( QPaintEvent* event )
{
	QPainter painter(this);
	/*QPen pen(Qt::NoBrush,0);
	painter.setPen(pen);
	painter.setBrush(QColor(38,157,55));
	painter.drawRect(rect());*/
	QPixmap pix = GetResource(BACK_GROUND);
	pix = pix.scaled(size(), Qt::KeepAspectRatioByExpanding);

	QPixmap pixMap(size());
	pixMap.fill(Qt::transparent);
	QPainter painterPic(&pixMap);
	painterPic.setCompositionMode(QPainter::CompositionMode_Source);
	painterPic.drawPixmap(0,0,pix);
	painterPic.setCompositionMode(QPainter::CompositionMode_DestinationIn);
	painterPic.fillRect(pix.rect(), QColor(0, 0, 0, 150));

	painter.drawPixmap(0,0,pixMap);
}
