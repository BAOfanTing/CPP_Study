#include "cell_standui.h"
#include "ui_cell_standui.h"

cell_Standui::cell_Standui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cell_Standui)
{
    ui->setupUi(this);
    initUI();
}

cell_Standui::~cell_Standui()
{
    delete ui;
}

void cell_Standui::initUI()
{
    //1、把所有的按钮放到一个按钮组里边
    QButtonGroup * buttonGroup = new QButtonGroup(this);
    auto btnList = findChildren<QPushButton*>();
    for(auto btn : btnList)
    {
        buttonGroup->addButton(btn);
    }

    //2、关联按钮组的点击信号
    connect(buttonGroup,&QButtonGroup::buttonClicked,this,&cell_Standui::onButtonGroupClicked);
    vec.resize(5);
}

void cell_Standui::onButtonGroupClicked(QAbstractButton *btn)
{
    //获取按钮的名称
    // qDebug()<<btn->objectName();

    //首先把框里的数赋值
    auto val1 = ui->le_result->text().toFloat();
    QStringList nameList = btn->objectName().split('_');
    QString name = nameList[1];


    if(name >="0" && name <= "9" || name == "point" )
    {
        //把一开始的0清除
        if(name != "point" && ui->le_result->text() == "0")
        {
            ui->le_result->clear();
        }
        //如果点击数字键的时候输入框有数据，而且表达式框只有两个数据，则重置为刚刚输入的
        if(preBtn == "add" || preBtn == "multiplication" ||preBtn == "subtraction" || preBtn == "divide")
        {
            ui->le_result->clear();
        }
        else if(preBtn == "result" || preBtn == "squareroot" || preBtn == "square" || preBtn == "quarter")
        {
            //判断上次的按钮是不是=，如果是那么一次计算就算完成了，清空所有内容
            ui->le_result->clear();
            ui->le_history->clear();
            vec.clear();
            vec.resize(5);
        }
        //输入数字
        ui->le_result->insert(btn->text());
    }
    else if(name == "ce")
    {
        //清空
        ui->le_result->clear();
    }
    else if(name == "c")
    {
        //清空
        ui->le_result->clear();
        ui->le_history->clear();
        vec.clear();
        vec.resize(5);
    }
    else if(name == "del")
    {
        //删除
        //先让光标的位置移动到前一位
        ui->le_result->setCursorPosition(ui->le_result->cursorPosition()-1);
        ui->le_result->del();
    }
    //输入符号
    else if(name == "add")
    {
        if(vec.size() != 2)
        {
            //把左操作数和运算符保存起来
            vec[0] = val1;
            vec[1] = "+";
        }
    }
    else if(name == "subtraction")
    {
        if(vec.size() != 2)
        {
            //把左操作数和运算符保存起来
            vec[0] = val1;
            vec[1] = "-";
        }
    }
    else if(name == "multiplication")
    {
        if(vec.size() != 2)
        {
            //把左操作数和运算符保存起来
            vec[0] = val1;
            vec[1] = "×";
        }
    }
    else if(name == "divide")
    {
        if(vec.size() != 2)
        {
            //把左操作数和运算符保存起来
            vec[0] = val1;
            vec[1] = "÷";
        }
    }
    else if(name == "result")
    {
        vec[2] = val1;
        vec[3] = "=";
        if(vec[1] == "+")
        {
            vec[4] = vec[0].toFloat()+vec[2].toFloat();
        }
        else if(vec[1] == "-")
        {
            vec[4] = vec[0].toFloat()-vec[2].toFloat();
        }
        else if(vec[1] == "×")
        {
            vec[4] = vec[0].toFloat()*vec[2].toFloat();
        }
        else if(vec[1] == "÷")
        {
            vec[4] = vec[0].toFloat()/vec[2].toFloat();
        }
        ui->le_result->clear();
        ui->le_result->setText(vec[4].toString());
    }
    else if(name == "squareroot")
    {

        //把左操作数和运算符保存起来
        vec[0] = "√ ";
        vec[1] = val1;
        vec[2] = "=" ;
        vec[3] = sqrt(val1);
        ui->le_result->clear();
        ui->le_result->setText(vec[3].toString());
    }
    else if(name == "square")
    {

        //把左操作数和运算符保存起来
        vec[0] = val1;
        vec[1] = "²";
        vec[2] = "=" ;
        vec[3] = val1*val1;
        ui->le_result->clear();
        ui->le_result->setText(vec[3].toString());
    }
    else if(name == "quarter")
    {

        //把左操作数和运算符保存起来
        vec[0] = "1/";
        vec[1] = val1;
        vec[2] = "=" ;
        vec[3] = 1/val1;
        ui->le_result->clear();
        ui->le_result->setText(vec[3].toString());
    }
    else if(name == "mod")
    {

        //把左操作数和运算符保存起来
        vec[0] = val1;
        vec[1] = "%";
        vec[2] = "=" ;
        vec[3] = val1/100;
        ui->le_result->clear();
        ui->le_result->setText(vec[3].toString());
    }

    //显示表达式，每次都清空重新显示
    ui->le_history->clear();
    for(auto var : vec)
    {
        ui->le_history->insert(var.toString());
    }

    preBtn = name;
}


