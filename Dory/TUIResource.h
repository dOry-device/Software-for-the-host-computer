#ifndef _TUIRESOURCE_H_
#define _TUIRESOURCE_H_

#include "qobject.h"
#include "QPixmap"
#include "QMap"
#include "AppGlobal.h"

enum EResources
{
	BACK_GROUND,
	TITLE_TOAL,
	TITLE_GAS_TEMP,
	TITLE_WATER_TEMP,
	TITLE_CONDUCTOR,
	TITLE_TRANSPARENT,
	TITLE_COMCONFIG
	
};


class TUIResource : public QObject
{
public:
	static TUIResource* getInstance();
	QPixmap& getResource(int index);
private:
	TUIResource();
	TUIResource(const TUIResource&);
	TUIResource& operator=(const TUIResource&);
	static TUIResource* instance;

	QMap<int, QPixmap> m_Rescoures;
};

#define GetResource(index) TUIResource::getInstance()->getResource(index)



#endif//_TUIRESOURCE_H_
