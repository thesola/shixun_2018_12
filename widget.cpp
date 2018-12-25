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

}


// 计算规则 7
void Widget::cal7()
{

}


// 计算规则 8
void Widget::cal8()
{

}


// 计算规则 9
void Widget::cal9()
{

}


// 计算规则 10
void Widget::cal10()
{

}


// 计算规则 11
void Widget::cal11()
{

}


// 读取 data.txt
void Widget::on_pb_DataPath_clicked()
{
    m_strDataPath = QFileDialog::getOpenFileName(this,"选择Data文件",".","Text file (data.txt)");
    if( m_strDataPath == "" )
    {
        QMessageBox::warning(this, "警告", "未选择Data文件!");
        return;
    }
    ui->lb_DataPath->setText( m_strDataPath );

    // 读取data.txt文件内容
    QFile file(m_strDataPath);
    if( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QMessageBox::warning(this, "警告", "Data文件打开失败!");
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
    m_strBoundPath = QFileDialog::getOpenFileName(this,"选择边界值文件",".","Text file (边界值.txt)");
    if( m_strBoundPath == "" )
    {
        QMessageBox::warning(this, "警告", "未选择边界值文件!");
        return;
    }
    ui->lb_BoundPath->setText( m_strBoundPath );

    // 读取data.txt文件内容
    QFile file(m_strBoundPath);
    if( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QMessageBox::warning(this, "警告", "边界值文件打开失败!");
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

    // 计算所有与边界值有关的规则
    cal2();
    cal5();
}
