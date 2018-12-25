#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}


Widget::~Widget()
{
    delete ui;
}


// 计算规则 1
void Widget::cal1()
{
    setStatus("正在计算 神经元 覆盖率");

    // 统计 n 个神经元中活跃神经元的数量
    int nr_active = 0;

    for ( int i=0; i<g_nr_n ; i++ )
    {
        for( int j=0; j<g_nr_m ; j++ )
        {
            if( m_DataTable[j][i] > 0.0f )
            {
                nr_active++;
                break;
            }
        }
    }

    ui->lb_cal1_active->setText( QString::number(nr_active) );
    ui->lb_cal1_n->setText( QString::number(g_nr_n) );
    ui->lb_cal1_rate->setText( QString::number( nr_active/(double)g_nr_n ) );

    setStatus(" 神经元 覆盖率计算完毕");
}


// 计算规则 2
void Widget::cal2()
{

}


// 计算规则 3
void Widget::cal3()
{

}


// 计算规则 4
void Widget::cal4()
{

}


// 计算规则 5
void Widget::cal5()
{

}


// 计算规则 6
void Widget::cal6()
{
    setStatus("正在计算 组合稀疏 覆盖率");

    /*
     * 要求组合的所有状态都被覆盖到，既要求组合的每个元素均有（0,1）两种状态
     *  方案1. 遍历所有组合，判断是否每个元素都有两种状态
     *  方案2. 找出所有有两状态的元素，计算功能构成多少种组合 √
    */

#define getNR(nr_lx, beg_layer, end_layer) do\
                    {\
                    \
                        int nr = 0;\
                        \
                        for(int i=(beg_layer); i<(end_layer) ; i++)\
                        {\
                            bool positive=false, negative=false;\
                            for(int j=0; j<g_nr_m ; j++)\
                            {\
                                if( m_DataTable[j][i] > 0 )\
                                {\
                                    positive = true;\
                                }\
                                else\
                                {\
                                    negative = true;\
                                }\
                                \
                                if( positive && negative )\
                                {\
                                    break;\
                                }\
                            }\
                            \
                            if( positive && negative )\
                            {\
                                nr++;\
                            }\
                        }\
                        \
                        nr_lx = nr;\
                    }while(0);

    int nr_l1, nr_l2, nr_l3; // 各层拥有两种状态的节点的统计
    getNR(nr_l1, 0, g_nr_l1);
    getNR(nr_l2, g_nr_l1, g_nr_l1+g_nr_l2);
    getNR(nr_l3, g_nr_l1+g_nr_l2, g_nr_n);

#undef getNR

#define magic(n) do\
                    {\
                        int t##n##_fz = combine(nr_l1, n) + combine(nr_l2, n) + combine(nr_l3, n); \
                        int t##n##_fm = combine(g_nr_l1, n) + combine(g_nr_l2, n) + combine(g_nr_l3, n); \
                        double t##n##_rate = t##n##_fz/(double)t##n##_fm; \
                        \
                        ui->lb_cal6_t##n##_nr_fz->setText(QString::number(t##n##_fz));\
                        ui->lb_cal6_t##n##_nr_fm->setText(QString::number(t##n##_fm));\
                        ui->lb_cal6_t##n##_nr_rate->setText(QString::number(t##n##_rate));\
                    } while(0);

    magic(2);
    magic(3);
    magic(4);

#undef magic

    setStatus(" 组合稀疏 覆盖率计算完毕");
}


// 计算规则 7
void Widget::cal7()
{
    setStatus("正在计算 组合密集 覆盖率");

    /*
     * 要计算有多少种状态被覆盖到
     * t=2 11*1 12*2 22*4
     * t=3 111*1 112*2 122*4 222*8
     * t=4 1111*1 1112*2 1122*4 1222*8 2222*16
    */

#define getNR(nr_lx, beg_layer, end_layer) do\
                    {\
                    \
                        int nr = 0;\
                        \
                        for(int i=(beg_layer); i<(end_layer) ; i++)\
                        {\
                            bool positive=false, negative=false;\
                            for(int j=0; j<g_nr_m ; j++)\
                            {\
                                if( m_DataTable[j][i] > 0 )\
                                {\
                                    positive = true;\
                                }\
                                else\
                                {\
                                    negative = true;\
                                }\
                                \
                                if( positive && negative )\
                                {\
                                    break;\
                                }\
                            }\
                            \
                            if( positive && negative )\
                            {\
                                nr++;\
                            }\
                        }\
                        \
                        nr_lx = nr;\
                    }while(0);

    int nr_l1_2, nr_l2_2, nr_l3_2; // 各层拥有两种状态的节点的统计
    getNR(nr_l1_2, 0, g_nr_l1);
    getNR(nr_l2_2, g_nr_l1, g_nr_l1+g_nr_l2);
    getNR(nr_l3_2, g_nr_l1+g_nr_l2, g_nr_n);
    int nr_l1_1, nr_l2_1, nr_l3_1; // 各层拥有一种状态的节点的统计
    nr_l1_1 = g_nr_l1 - nr_l1_2;
    nr_l2_1 = g_nr_l2 - nr_l2_2;
    nr_l3_1 = g_nr_l3 - nr_l3_2;

#undef getNR

    // t=2
    int t2_fz = 0;
    t2_fz += combine( nr_l1_1, 2 ) + nr_l1_1 * nr_l1_2 *2 + combine( nr_l1_2, 2 ) *4;
    t2_fz += combine( nr_l2_1, 2 ) + nr_l2_1 * nr_l2_2 *2 + combine( nr_l2_2, 2 ) *4;
    t2_fz += combine( nr_l3_1, 2 ) + nr_l3_1 * nr_l3_2 *2 + combine( nr_l3_2, 2 ) *4;
    int t2_fm = combine( g_nr_l1, 2 ) + combine( g_nr_l2, 2 ) + combine( g_nr_l3, 2 );
    t2_fm *= 1U<<2; // 乘以2的2次幂
    double t2_rate = t2_fz/(double)t2_fm;

    // t=3
    int t3_fz = 0;
    t3_fz += combine( nr_l1_1, 3 ) + combine( nr_l1_1, 2 ) * nr_l1_2 *2 \
            + combine( nr_l1_2, 2 ) * nr_l1_1 *4 + combine( nr_l1_2, 3 ) *8;
    t3_fz += combine( nr_l2_1, 3 ) + combine( nr_l2_1, 2 ) * nr_l2_2 *2 \
            + combine( nr_l2_2, 2 ) * nr_l2_1 *4 + combine( nr_l2_2, 3 ) *8;
    t3_fz += combine( nr_l3_1, 3 ) + combine( nr_l3_1, 2 ) * nr_l3_2 *2 \
            + combine( nr_l3_2, 2 ) * nr_l3_1 *4 + combine( nr_l3_2, 3 ) *8;
    int t3_fm = combine( g_nr_l1, 3 ) + combine( g_nr_l2, 3 ) + combine( g_nr_l3, 3 );
    t3_fm *= 1U<<3; // 乘以2的3次幂
    double t3_rate = t3_fz/(double)t3_fm;

    // t=4
    int t4_fz = 0;
    t4_fz += combine( nr_l1_1, 4 ) + combine( nr_l1_1, 3 ) * nr_l1_2 *2 \
            + combine( nr_l1_1, 2 ) * combine( nr_l1_2, 2 ) *4 \
            + combine( nr_l1_2, 3 ) * nr_l1_1 *8 + combine( nr_l1_2, 4 ) *16;
    t4_fz += combine( nr_l2_1, 4 ) + combine( nr_l2_1, 3 ) * nr_l2_2 *2 \
            + combine( nr_l2_1, 2 ) * combine( nr_l2_2, 2 ) *4 \
            + combine( nr_l2_2, 3 ) * nr_l2_1 *8 + combine( nr_l2_2, 4 ) *16;
    t4_fz += combine( nr_l3_1, 4 ) + combine( nr_l3_1, 3 ) * nr_l3_2 *2 \
            + combine( nr_l3_1, 2 ) * combine( nr_l3_2, 2 ) *4 \
            + combine( nr_l3_2, 3 ) * nr_l3_1 *8 + combine( nr_l3_2, 4 ) *16;
    int t4_fm = combine( g_nr_l1, 4 ) + combine( g_nr_l2, 4 ) + combine( g_nr_l3, 4 );
    t4_fm *= 1U<<4; // 乘以2的4次幂
    double t4_rate = t4_fz/(double)t4_fm;


#define magic(n)  do\
                    {\
                        ui->lb_cal7_t##n##_nr_fz->setText(QString::number(t##n##_fz));\
                        ui->lb_cal7_t##n##_nr_fm->setText(QString::number(t##n##_fm));\
                        ui->lb_cal7_t##n##_nr_rate->setText(QString::number(t##n##_rate));\
                    }while(0);

    magic(2);
    magic(3);
    magic(4);

#undef magic


    setStatus(" 组合密集 覆盖率计算完毕");
}


// 计算规则 8
void Widget::cal8()
{
    setStatus("正在计算 Sign-sign 覆盖率");



    setStatus(" Sign-sign 覆盖率计算完毕");
}


// 计算规则 9
void Widget::cal9()
{
    setStatus("正在计算 Distance-sign 覆盖率");



    setStatus(" Distance-sign 覆盖率计算完毕");
}


// 计算规则 10
void Widget::cal10()
{
    setStatus("正在计算 Sign-value 覆盖率");



    setStatus(" Sign-value 覆盖率计算完毕");
}


// 计算规则 11
void Widget::cal11()
{
    setStatus("正在计算 Distance-value 覆盖率");



    setStatus(" Distance-value 覆盖率计算完毕");
}


// 读取 data.txt
void Widget::on_pb_DataPath_clicked()
{
    m_strDataPath = QFileDialog::getOpenFileName(this,"选择Data文件",".","Text file (data.txt)");
    if( m_strDataPath == "" )
    {
        QMessageBox::warning(this, "警告", "未选择Data文件!");
        setStatus("Data文件未选择");
        return;
    }
    ui->lb_DataPath->setText( m_strDataPath );

    // 读取data.txt文件内容
    QFile file(m_strDataPath);
    if( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QMessageBox::warning(this, "警告", "Data文件打开失败!");
        setStatus("Data文件打开失败");
        return;
    }

    memset( m_DataTable, 0, sizeof m_DataTable ); // 清空已有数据

    // 逐行读取数据存入 m_DataTable 中
    QTextStream data(&file);
    int nr_line = 0;
    while( !data.atEnd() )
    {
        QString line = data.readLine();
        QStringList tmp = line.split("],");
        tmp[0].remove(0,2); // 移除 "[["
        tmp[1].remove(0,2); // 移除 " ["
        tmp[2].remove(0,2); // 移除 " ["
        tmp[2].remove( tmp[2].indexOf(']'), 2 ); // 移除 "]]"

        QStringList lineData = tmp[0].split(",") + tmp[1].split(",") + tmp[2].split(",");
        for( int i=0, n=lineData.length() ; i<n ; i++ )
        {
            m_DataTable[nr_line][i] = lineData[i].trimmed().toDouble();
        }

        nr_line++;
    }

    file.close();

    ui->lb_status->setText("读取Data成功");

    // 计算所有与边界值无关的规则
    cal1();
    cal3();
    cal4();
    cal6();
    cal7();
    cal8();
    cal9();
    cal10();
    cal11();
}


// 读取 边界值.txt
void Widget::on_pb_BoundPath_clicked()
{
    // 判断是否先选中了data.txt
    if( m_strDataPath == "" )
    {
        QMessageBox::warning(this, "警告", "请先选择Data文件!");
        setStatus("未选择Data文件");
        return;
    }

    m_strBoundPath = QFileDialog::getOpenFileName(this,"选择边界值文件",".","Text file (边界值.txt)");
    if( m_strBoundPath == "" )
    {
        QMessageBox::warning(this, "警告", "未选择边界值文件!");
        setStatus("未选择边界值文件");
        return;
    }
    ui->lb_BoundPath->setText( m_strBoundPath );

    // 读取data.txt文件内容
    QFile file(m_strBoundPath);
    if( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QMessageBox::warning(this, "警告", "边界值文件打开失败!");
        setStatus("边界值文件打开失败");
        return;
    }

    memset( m_BoundTable, 0, sizeof m_BoundTable ); // 清空已有数据

    // 逐行读取数据存入 m_DataTable 中
    QTextStream data(&file);
    int nr_line = 0;
    while( !data.atEnd() )
    {
        QString line = data.readLine();
        QStringList tmp = line.split("],");
        tmp[0].remove(0,2); // 移除 "[["
        tmp[1].remove(0,2); // 移除 " ["
        tmp[2].remove(0,2); // 移除 " ["
        tmp[2].remove( tmp[2].indexOf(']'), 2 ); // 移除 "]]"

        QStringList lineData = tmp[0].split(",") + tmp[1].split(",") + tmp[2].split(",");
        for( int i=0, n=lineData.length() ; i<n ; i++ )
        {
            m_BoundTable[nr_line][i] = lineData[i].trimmed().toDouble();
        }

        nr_line++;
    }

    file.close();

    ui->lb_status->setText("读取边界值成功");

    // 计算所有与边界值有关的规则
    cal2();
    cal5();
}


// 设置状态
void Widget::setStatus(QString status)
{
    ui->lb_status->setText(status);
}


// 求组合值
int Widget::combine(int nr, int n)
{
    if( nr < n )
    {
        return 0;
    }

    int fz=1, fm=1;

    while( n )
    {
        fz *= nr--;
        fm *= n--;
    }

    return fz / fm;
}
