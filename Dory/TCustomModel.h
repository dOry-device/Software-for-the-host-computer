#ifndef _TCUSTOMMODEL_H_
#define _TCUSTOMMODEL_H_
#include "QSqlTableModel"
#include "QModelIndex"
#include "QDateTime"
#include "AppGlobal.h"

class MyTableModel : public QSqlTableModel
{
public:
	MyTableModel(QObject *parent = 0):QSqlTableModel(parent){}
	QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const
	{

		if (role==Qt::TextAlignmentRole)
		{
			return Qt::AlignCenter;
		}
		//if(idx.column() != 0)//只有在上传时间一栏时才自定义显示方式
		//	return QSqlTableModel::data(idx, role);
		if(role == Qt::DisplayRole)
		{
			switch (idx.column())
			{
			case 0:
			{
				qint64 time = QSqlTableModel::data(idx, role).toDouble();
				QDateTime datetime = QDateTime::fromMSecsSinceEpoch(time);
				return datetime.toString("yyyy-MM-dd hh:mm:ss");
			}
			case 2:
				return QSqlTableModel::data(idx, role).toString();
			case 1:
			case 3:
			case 4:
			case 5:
				{
					float tmp = QSqlTableModel::data(idx, role).toFloat();
					if (tmp<INFINITE_DATA_DIFF)
					{
						return QVariant();
					}
					else
						return QString::number(tmp);
				}
			}
		}
		else
			return QSqlTableModel::data(idx, role);
	}
};





#endif//_TCUSTOMMODEL_H_
