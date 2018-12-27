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

const int g_N = 50; // K段神经元被划分为N份

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

    void on_pb_BoundPath_clicked();

    void setStatus(QString status);

    int combine(int nr, int n);

private:
    Ui::Widget *ui;

    QString m_strDataPath;
    QString m_strBoundPath;
    double m_DataTable[ g_nr_m ][ g_nr_n ];
    double m_BoundTable[2][ g_nr_n ]; // 边界值 table[0] 为上界 table[1]为下界
    int m_DataRegTable[ g_nr_m ][ g_nr_n ]; // 将输入规则为 -1/1
};

#endif // WIDGET_H
