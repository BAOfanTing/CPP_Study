#include "selectwindow.h"
#include "ui_selectwindow.h"

selectwindow::selectwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::selectwindow)
{
    ui->setupUi(this);
    model = new QSqlTableModel();

}

selectwindow::~selectwindow()
{
    delete ui;
}

void selectwindow::on_btn_check_clicked()
{
    if(ui->btn_employee->isChecked())
    {
        model->setTable("employee");
    }
    else
    {
        model->setTable("attendance");
    }
    //查询数据
    model->select();
    ui->tv_message->setModel(model);
}

