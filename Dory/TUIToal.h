#ifndef _TUITOAL_H_
#define _TUITOAL_H_

#include "qwidget.h"
#include "QComboBox"
#include "QDateEdit"
#include "QSqlTableModel"
#include "QTableView"
#include "QPushButton"

#include "AppGlobal.h"
#include "TCustomModel.h"

class TUIToal :
	public QWidget
{
	Q_OBJECT
public:
	explicit TUIToal(QWidget *parent = 0);
	~TUIToal(void);
private:
	QComboBox* m_pCombox;//时间排序
	QDateEdit* m_pDate;//时间排序
	QTableView* m_pView;
	MyTableModel* m_pModel;
	QPushButton* m_pBtnDel;
	QPushButton* m_pBtnClear;
#ifdef _TEST_
	QPushButton* m_pBtnAdd;
	QPushButton* m_pBtnSubmit;
private slots:
	void SlotAdd();
	void SlotSubmit();
#endif

private slots:
	void slotAddData(TInfoData data);
	void slotSelectChanged(int index);
	void slotDateChanged(const QDate& date);
	void slotDel();
	void slotClear();
signals:
	void UpdateDB();
};


#endif//_TUITOAL_H_


