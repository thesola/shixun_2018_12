#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

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

    void setStatus(QString status);

    int combine(int nr, int n);

private slots:
    void on_pb_DataPath_clicked();

    void on_pb_BoundPath_clicked();

private:
    Ui::Widget *ui;

    QString m_strDataPath;
    QString m_strBoundPath;
    QVector<QVector<double> > m_DataTable;
    QVector<QVector<double> > m_DataRegTable; // 将data转为 -1/1 值
    QVector<QVector<double> > m_BoundTable; // 边界值 table[0] 为上界 table[1]为下界
};

#endif // WIDGET_H
