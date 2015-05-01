#include "TUIChart.h"
#include "QLabel"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QGridLayout"
#include "AppGlobal.h"
#include "QHeaderView"
#include "QSqlRecord"
#include "QMap"
#include "qwt_symbol.h"
#include "QTableView"


TUIChart::TUIChart(QString str,tInitModel initModel, QWidget *parent): QWidget(parent),m_InitModel(initModel)
{
	m_filter = str;
	m_pStartTime = new QDateEdit();
	m_pStopTime = new QDateEdit(QDate::currentDate());
	m_pView = new QTableView;
	m_pModel = new MyTableModel(this);
	m_pPlot = new QwtPlot;
	m_pAverage = new QLineEdit;
	m_pMiddle = new QLineEdit;

	QHBoxLayout* topLayout = new QHBoxLayout;
	topLayout->addWidget(new QLabel(MY_STR("Begin data")));
	topLayout->addWidget(m_pStartTime);
	topLayout->addSpacing(20);
	topLayout->addWidget(new QLabel(MY_STR("Stop data")));
	topLayout->addWidget(m_pStopTime);
	topLayout->addStretch();

	QVBoxLayout* leftLayout = new QVBoxLayout;
	leftLayout->addWidget(m_pView);
	
	QGridLayout* gridLayout = new QGridLayout;
	gridLayout->addWidget(new QLabel(MY_STR("Average")),0,0);
	gridLayout->addWidget(m_pAverage,0,1);
	gridLayout->addWidget(new QLabel(MY_STR("Median")),1,0);
	gridLayout->addWidget(m_pMiddle,1,1);

	leftLayout->addLayout(gridLayout);

	QHBoxLayout* bootomLayout = new QHBoxLayout;
	bootomLayout->addLayout(leftLayout,1);
	bootomLayout->addWidget(m_pPlot,3);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(bootomLayout);
	setLayout(mainLayout);

	m_pModel->setTable(DB_TABLE);
	m_pModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_pModel->setSort(0,Qt::AscendingOrder);
	m_InitModel(m_pModel);
	m_pView->setStyleSheet("background:transparent;");
	m_pView->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_pView->horizontalHeader()->setStretchLastSection(true);
	m_pView->horizontalHeader()->setSortIndicatorShown(true);
	m_pView->horizontalHeader()->setHighlightSections(false);
	//m_pView->horizontalHeader()->setDefaultSectionSize(150);
	m_pView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_pView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	m_pView->setModel(m_pModel);
	/*m_pModel->removeColumn(4);
	m_pModel->removeColumn(3);
	m_pModel->removeColumn(2);*/

	//m_pModel->select();
	m_pSymbol = new QwtSymbol( QwtSymbol::Ellipse,
		QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
	m_pPlot->setAutoReplot();
	m_curves[0].setSymbol(m_pSymbol);
	m_curves[0].setStyle( QwtPlotCurve::NoCurve );
	m_curves[0].attach(m_pPlot);
	m_curves[1].attach(m_pPlot);
	m_pPlot->setAxisScaleDraw(QwtPlot::xBottom, new QXAxisScale());
	m_pPlot->setAxisLabelRotation(QwtPlot::xBottom,30);

	connect(m_pStartTime,SIGNAL(dateChanged(const QDate&)),this,SLOT(slotDateChanged(const QDate&)));
	connect(m_pStopTime,SIGNAL(dateChanged(const QDate&)),this,SLOT(slotDateChanged(const QDate&)));
	slotDateChanged(QDate());
	//m_pPlot->setStyleSheet("background:transparent;");
	//m_pPlot->setAttribute(Qt::WA_TranslucentBackground);
	//m_pPlot->setStyleSheet("background:green;");
	m_pPlot->setCanvasBackground(Qt::white);
	//m_pPlot->canvas()->setStyleSheet("background:rgba(255,255,255,10);");
	//m_pPlot->canvas()->setAttribute(Qt::WA_TranslucentBackground,true);
}

TUIChart::~TUIChart()
{

}

void TUIChart::slotDateChanged( const QDate& date )
{
	QDate dateStart = m_pStartTime->date();
	QDate dateStop = m_pStopTime->date();
	if (dateStart>dateStop)
	{
		QDate tmp;
		tmp = dateStart;
		dateStart = dateStop;
		dateStop = tmp;
	}

	quint64 nStart = QDateTime(dateStart).toMSecsSinceEpoch();
	quint64 nStop = QDateTime(dateStop.addDays(1)).toMSecsSinceEpoch()-1;
	
	m_pModel->setFilter(QString("CurMs>=%1 and CurMs<=%2 and %3 > -999").arg(nStart).arg(nStop).arg(m_filter));
	m_pModel->select();

	updatePlot();
}

void TUIChart::slotDateChanged()
{
	slotDateChanged(QDate());
}

QVector<double> simpleX;
QVector<double> simpleY;

typedef struct
{
	double a;
	double b;
	double average;
	double middle;
}TFormula;

static void Calculate(TFormula* pFormula)
{
	double sumXX=0;
	double sumXY=0;
	double sumX=0;
	double sumY=0;
	qDebug()<<simpleX.count()<<simpleY.count();
	for(int i=0; i<simpleX.count(); i++)
	{
		sumXX += simpleX[i]*simpleX[i];
		sumXY += simpleX[i]*simpleY[i];

		sumX += simpleX[i];
		sumY += simpleY[i];
	}

	pFormula->b = (sumXX*sumY - sumX*sumXY)/(simpleX.count()*sumXX-sumX*sumX);
	pFormula->a = (simpleX.count()*sumXY-sumX*sumY)/(simpleX.count()*sumXX-sumX*sumX);

	pFormula->average = sumY/simpleX.count();
	qSort(simpleY.begin(), simpleY.end());

	if (simpleX.count() == 1)
	{
		pFormula->middle = simpleY[0];
	}

	int middle = simpleY.count()/2;
	if (simpleX.count()%2 == 0)
	{
		pFormula->middle = (simpleY[middle]+simpleY[middle-1])/2;
	}
	else
	{
		pFormula->middle = simpleY[middle];
	}
}

void TUIChart::updatePlot()
{
	simpleX.clear();
	simpleY.clear();
#if 1
	for (int i=0; i<m_pModel->rowCount(); i++)
	{
		QDateTime time = QDateTime::fromString(m_pModel->index(i,0).data().toString(),"yyyy-MM-dd hh:mm:ss");
		simpleX.append(time.toMSecsSinceEpoch());
		simpleY.append(m_pModel->index(i,1).data().toFloat());
	}
#else
	for(int i=0; i<10; i++)
	{
		simpleX.append(i);
		simpleY.append(i);
	}
#endif
	
	if (simpleX.count() == 0)
	{
		m_pAverage->setText("");
		m_pMiddle->setText("");
		m_curves[0].setSamples(simpleX,simpleY);
		m_curves[1].setSamples(simpleX,simpleY);
		return;
	}
	m_curves[0].setSamples(simpleX,simpleY);

	TFormula formula;
	Calculate(&formula);

	m_pAverage->setText(QString::number(formula.average));
	m_pMiddle->setText(QString::number(formula.middle));

	QVector<QPointF> point;
	point.append( QPointF(simpleX[0],formula.a*simpleX[0]+formula.b));
	point.append( QPointF(simpleX[simpleX.count()-1],formula.a*simpleX[simpleX.count()-1]+formula.b));
	//qDebug()<<point[0]<<point[1];
	m_curves[1].setSamples(point);
}





QwtText QXAxisScale::label( double v ) const
{
	QDateTime time = QDateTime::fromMSecsSinceEpoch(v);
	return QwtText(time.toString("yy/MM/dd\nhh:mm:ss"));
}
