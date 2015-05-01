#ifndef TUICHART_H
#define TUICHART_H

#include <QWidget>
#include "QDateEdit"
#include "QTableView"
#include "QDateEdit"
#include "QLineEdit"
#include "Qwt_Plot.h"
#include "TCustomModel.h"
#include "qwt_plot_curve.h"
#include <qwt_scale_draw.h>

class QwtSymbol;
class QwtPlotCurve;

class QXAxisScale : public QwtScaleDraw
{
public:
	QXAxisScale(){};
	~QXAxisScale(){};
	virtual QwtText label(double v) const;
	/*virtual void drawSymbols( QPainter *p, const QwtSymbol &,
		const QwtScaleMap &xMap, const QwtScaleMap &yMap,
		const QRectF &canvasRect, int from, int to ) const;*/
};

typedef void (*tInitModel)(MyTableModel* model);

class TUIChart : public QWidget
{
	Q_OBJECT
public:
	explicit TUIChart(QString str, tInitModel initModel, QWidget *parent=0);
	~TUIChart();

private:
	QDateEdit* m_pStartTime;
	QDateEdit* m_pStopTime;
	QTableView* m_pView;
	MyTableModel* m_pModel;
	QLineEdit* m_pAverage;
	QLineEdit* m_pMiddle;
	QwtPlot *m_pPlot;
	QwtSymbol* m_pSymbol;
	QwtPlotCurve m_curves[2];

	tInitModel m_InitModel;
	QString m_filter;
	void updatePlot();
public slots:
	void slotDateChanged(const QDate& date);
	void slotDateChanged();

};

#endif // TUICHART_H
