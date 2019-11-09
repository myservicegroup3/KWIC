#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#include<filter.h>
#include <QMainWindow>

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
  //  static string Input;
    //string Output;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int h=0;
private slots:
    void enter();
    void search();
    void enter_2();
    void on_changed();
    void on_changed_1();
    void on_pushButton_clicked(bool checked);
};

#endif // MAINWINDOW_H
