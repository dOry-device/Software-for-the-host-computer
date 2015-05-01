#include <QtWidgets/QApplication>
#include "TUIMainWindow.h"

#include "QSqlDatabase"
#include "QDebug"
#include "QSqlQuery"
#include "QFile"
#include "TInterface.h"


static void ConnectDB(QApplication* app)
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("data.db");     //创建数据库
	if(!db.open())
	{
		qDebug()<< "database is error";
		app->quit();
	}
	else
	{
		qDebug()<<"database is ok";
		QSqlQuery query;
		QString sql("select count(*) from sqlite_master where type='table' and name='t_info';");
		query.exec(sql );
		if(query.next())
		{
			if(query.value(0).toInt() == 0)  //not exist
			{
				QSqlQuery query1;
				query1.exec("create table t_info (CurMs double, GasTemp float,GPS TEXT, WaterTemp float,"
					"Conductor float,Transparent float)");   //创建一个表
				qDebug()<<"create t_info ok!";
			}
		}
	}
}
//设置皮肤样式
static void SetStyle()
{
	QFile file(QString("Resource\\skin.qss"));
	file.open(QFile::ReadOnly);
	QString qss = QLatin1String(file.readAll());
	qApp->setStyleSheet(qss);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ConnectDB(&a);
	SetStyle();
	g_pTInterface = new TInterface;
	TUIMainWindow w;
	w.resize(800,600);
	w.show();
	int ret = a.exec();
	delete g_pTInterface;
	return ret;
}
