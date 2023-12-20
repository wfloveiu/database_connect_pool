#pragma once

#include <iostream>
#include <mysql/mysql.h>
#include <chrono>
// using namespace std;

class MysqlConn
{
public:
    //初始化连接数据库
    MysqlConn();
    //释放数据库连接
    ~MysqlConn();
    // 连接数据库
    bool connect(std::string user, std::string passwd, std::string dbName, std::string ip, unsigned short port);    
    // 更新数据库
    bool update(std::string sql);
    // 查询语句
    bool query(std::string sql);
    
    bool next();  //遍历得到结果集中的每一行

    std::string value(int index);  //查询当前结果行中某一列的值

    bool transaction();

    bool commit();

    bool rollback();

    // 刷新连接的起始空闲时间点
    void refreshAliveTime();
    // 计算存活的总时常
    long long getAliveTime();
private:
    void freeResult();
    MYSQL *m_coon = nullptr; // 在析构函数中释放
    MYSQL_RES *m_result = nullptr; //结果集指针
    MYSQL_ROW m_row = nullptr;
    /*
    c++11中，chrono时间库在std下，steady_clock是绝对时钟
    sysytem_clock是系统时钟
    */ 
    std::chrono::steady_clock::time_point m_alivetime;
};

