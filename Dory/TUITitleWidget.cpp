#include "QHBoxLayout"
#include "TUITitleWidget.h"
#include "TUIResource.h"
#include "TUIToolButton.h"

TUITitleWidget::TUITitleWidget( QWidget* parent /*= 0*/ ):QWidget(parent)
{
	//const char* btnText[] = {"记录查询","大气温度","水中温度","导电程度","透明程度","串口配置"};
	const char* btnText[] = {"Record","Air Temp","Water Temp","Conductivity","Transparence","UART"};
	m_BtnList<<new TUIToolButton(GetResource(TITLE_TOAL));
	m_BtnList<<new TUIToolButton(GetResource(TITLE_GAS_TEMP));
	m_BtnList<<new TUIToolButton(GetResource(TITLE_WATER_TEMP));
	m_BtnList<<new TUIToolButton(GetResource(TITLE_CONDUCTOR));
	m_BtnList<<new TUIToolButton(GetResource(TITLE_TRANSPARENT));
	m_BtnList<<new TUIToolButton(GetResource(TITLE_COMCONFIG));

	QHBoxLayout* mainLayout = new QHBoxLayout(this);
	mainLayout->setContentsMargins(10,0,10,0);
	mainLayout->setSpacing(0);

	for (int i=0; i<m_BtnList.count(); i++)
	{
		mainLayout->addWidget(m_BtnList[i]);
		if (i!=m_BtnList.count()-1)
		{
			mainLayout->addStretch();
		}
		m_BtnList[i]->setText(QString::fromLocal8Bit(btnText[i]));
		BTN_CLICKED(m_BtnList[i],onBtnClicked);
		m_BtnList[i]->setObjectName(QString::number(i));
	}
	m_BtnList[0]->setMousePress(true);
	m_nCurIndex = 0;
}


TUITitleWidget::~TUITitleWidget(void)
{
}

void TUITitleWidget::paintEvent( QPaintEvent* event )
{
	QWidget::paintEvent(event);
}

void TUITitleWidget::onBtnClicked()
{
	TUIToolButton* btn = qobject_cast<TUIToolButton *>(sender());
	int index = btn->objectName().toUInt();
	if ( index>=UI_INDEX_NUM )
	{
		return;
	}
	m_BtnList[m_nCurIndex]->setMousePress(false);
	m_BtnList[index]->setMousePress(true);
	m_nCurIndex = index;
	emit sigClicked(index);
}
