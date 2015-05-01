#include "TUIResource.h"

TUIResource* TUIResource::instance = NULL;

TUIResource* TUIResource::getInstance()
{
	if (instance == NULL)
	{
		if (instance == NULL)
		{
			instance = new TUIResource();
		}
	}
	return instance;
}

TUIResource::TUIResource()
{
	m_Rescoures[BACK_GROUND] = QPixmap("Resource\\bkPic.jpg");
	m_Rescoures[TITLE_TOAL] = QPixmap("Resource\\0.png");
	m_Rescoures[TITLE_GAS_TEMP] = QPixmap("Resource\\1.png");
	m_Rescoures[TITLE_WATER_TEMP] = QPixmap("Resource\\2.png");
	m_Rescoures[TITLE_CONDUCTOR] = QPixmap("Resource\\3.png");
	m_Rescoures[TITLE_TRANSPARENT] = QPixmap("Resource\\4.png");
	m_Rescoures[TITLE_COMCONFIG] = QPixmap("Resource\\5.png");
}

QPixmap& TUIResource::getResource( int index )
{
	return m_Rescoures[index];
}
