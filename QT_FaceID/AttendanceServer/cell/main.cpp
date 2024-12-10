#include "attendancewindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "register_ui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // 连接到 SQLite 数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // 设置数据库文件名
    db.setDatabaseName("server.db");

    // 检查数据库连接是否成功
    if(!db.open())
    {
        qDebug()<< db.lastError().text();
        return -1;  // 程序退出并返回错误代码
    }

    // 创建员工信息表 (if not exists: 如果不存在)
    QString createstr  = "create table if not exists employee(employeeID integer primary key autoincrement, name text , sex text,"
                        "birthday text, address text, phone text, faceID integer unique, headfile text)";

    // 创建 SQL 查询对象
    QSqlQuery query;
    if(!query.exec(createstr))
    {
         qDebug()<< query.lastError().text();
    }

     // 创建考勤记录表 (if not exists: 如果不存在则创建)
    createstr  = "create table if not exists attendance(attendenceID integer primary key autoincrement, employeeID integer,"
                        "attendanceTime TimeStamp NOT NULL DEFAULT(datetime('now','localtime')))";

    if(!query.exec(createstr))
    {
        qDebug()<< query.lastError().text();
    }

    AttendanceWindow w;
    w.show();
    return a.exec();
}
