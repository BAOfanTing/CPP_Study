#include "cell_main.h"
#include "ui_cell_main.h"

Cell_main::Cell_main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cell_main)
{
    ui->setupUi(this);
}

Cell_main::~Cell_main()
{
    delete ui;
}
