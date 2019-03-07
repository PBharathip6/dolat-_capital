#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include<QMouseEvent>

#include <QRegExp>
#include<QRegExpValidator>
#include<QIntValidator>
#include<QDoubleValidator>

double dv;
int q;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->tableWidget,SIGNAL(contextMenuEvent()),this,SLOT(providecontextmenu()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableWidget_activated(const QModelIndex &index)
{
}

void MainWindow::on_pushButton_clicked()//add pushbutton
{
  ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    int i=ui->tableWidget->rowCount()-1;
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //to remove the margine
    ui->tableWidget->verticalHeader()->setVisible(false);
   //to select perticular row
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
   //1.relation between table widget and line edit
    QString product=ui->productname->text();
    QString vol=ui->volume->text();
    QString market=ui->marketcapital->text();
    QString le=ui->creditrating->text();

    ui->tableWidget->setItem(i,0,new QTableWidgetItem(product));
    ui->tableWidget->setItem(i,1,new QTableWidgetItem(vol));
    ui->tableWidget->setItem(i,2,new QTableWidgetItem(market));
    ui->tableWidget->setItem(i,3,new QTableWidgetItem(le));
//2. this is for clear the line edit after enter the items into table widget
    ui->productname->setText("");
    ui->volume->setText("");
    ui->marketcapital->setText("");
    ui->creditrating->setText("");
  //entered data is existing or not(compare data)
    if(product.isEmpty() | vol.isEmpty() | market.isEmpty() | le.isEmpty())
    {
        QMessageBox::warning(this,"error","fill all items");
    }
    else
    {
     QFile file("/home/nano/bharathi/project2/myfile1.csv");

     if(file.open(QFile::ReadWrite | QFile::Text))
         return;

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line=in.readLine();

        if(line.contains(product,Qt::CaseSensitive))
        {
            QMessageBox::information(this,"product","product already exist");
            return;
        }
    }
}
  ui->pushButton->setText("add");
}

void MainWindow::on_creditrating_cursorPositionChanged(int, int)
{
    QValidator *validator=new QDoubleValidator();
    ui->creditrating->setValidator(validator);
}

void MainWindow::on_volume_cursorPositionChanged(int, int)
{
    QRegularExpression rx("^[0-9][0-9]*");
    QValidator *validator=new QRegularExpressionValidator(rx,this);
    ui->volume->setValidator(validator);
}

void MainWindow::on_marketcapital_cursorPositionChanged(int, int)
{
    QValidator *validator=new QDoubleValidator(0.0,0.5,2);
    ui->marketcapital->setValidator(validator);
}

void MainWindow::on_productname_cursorPositionChanged(int,int)
{
    QRegularExpression rx("^[A-Za-z][A-Za-z]*");
    QValidator *validator=new QRegularExpressionValidator(rx,this);
    ui->productname->setValidator(validator);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString productnam,volum,marketcapitall,creditratingg;
    QFile file("/home/nano/bharathi/project2/myfile1.csv");

    file.open(QFile::ReadOnly | QFile::Append);
     QTextStream out(&file);
    for(int i=0;i<=q;i++)
    {
        productnam=ui->tableWidget->item(i,0)->text();
        volum=ui->tableWidget->item(i,1)->text();
        marketcapitall=ui->tableWidget->item(i,2)->text();
       creditratingg=ui->tableWidget->item(i,3)->text();
    out<<productnam<<","<<volum<<","<<marketcapitall<<","<<creditratingg<<","<<endl;
    file.flush();
    }
    file.close();
}

void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
  // QString pr=ui->tableWidget
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
  QString k=ui->tableWidget->item(row,0)->text();
  ui->productname->setText(k);
  QString l=ui->tableWidget->item(row,1)->text();
  ui->volume->setText(l);
  QString m=ui->tableWidget->item(row,2)->text();
  ui->marketcapital->setText(m);
  QString n=ui->tableWidget->item(row,3)->text();
  ui->creditrating->setText(n);
ui->pushButton->setText("update");
ui->tableWidget->removeRow((ui->tableWidget->currentRow()));
}

void MainWindow::contextMenuEvent(QContextMenuEvent *e)
{
    QAction *removeaction=new QAction("delete",ui->tableWidget);


    connect(removeaction,SIGNAL(triggered()),this,SLOT(right_clicked()));

    QMenu *contextmenu=new QMenu(this);
    contextmenu->addAction(removeaction);
    contextmenu->exec(e->globalPos());
    delete contextmenu;
    contextmenu=NULL;
}

void MainWindow::providecontextmenu(const QPoint &pos)
{
    QAction *removeaction=new QAction("delete",this);
    QMenu *contextmenu=new QMenu(this);
    contextmenu->addAction(removeaction);
    contextmenu->exec(mapToGlobal(pos));
    delete contextmenu;
    contextmenu=NULL;
}
void MainWindow::right_clicked()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}
