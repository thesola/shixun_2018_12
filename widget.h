#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}


const int g_nr_m 	= 50;	// 测试用例数目
const int g_nr_l1	= 50;	// 第一层节点数目
const int g_nr_l2 	= 40;	// 第二层节点数目
const int g_nr_l3 	= 30;	// 第三层节点数目
const int g_nr_n 	= g_nr_l1 + g_nr_l2 + g_nr_l3;


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void cal1();
    void cal2();
    void cal3();
    void cal4();
    void cal5();
    void cal6();
    void cal7();
    void cal8();
    void cal9();
    void cal10();
    void cal11();

private slots:
    void on_pb_DataPath_clicked();

private:
    Ui::Widget *ui;

    QString m_strDataPath;
    double m_DataTable[ g_nr_m ][ g_nr_n ];
};

#endif // WIDGET_H
