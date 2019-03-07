#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_tableWidget_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_creditrating_cursorPositionChanged(int arg1, int arg2);

    void on_volume_cursorPositionChanged(int arg1, int arg2);

    void on_marketcapital_cursorPositionChanged(int arg1, int arg2);

    void on_productname_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_2_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_tableWidget_cellDoubleClicked(int row, int column);
    void contextMenuEvent(QContextMenuEvent *e);
    void providecontextmenu(const QPoint &pos);
    void right_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
