#include "MysqlConn.h"

MysqlConn::MysqlConn()
{
    m_coon = mysql_init(nullptr); // 如果mysql是NULL指针，该函数将分配、初始化、并返回新的MYSQL对象指针
    mysql_set_character_set(m_coon,"utf8");
}

MysqlConn::~MysqlConn()
{
    if(m_coon != nullptr)
    {
        mysql_close(m_coon);  //关闭连接，释放m_coon
    }
    freeResult();
}

bool MysqlConn::connect(std::string user, std::string passwd, std::string dbName, std::string ip, unsigned short port = 3306)
{
    MYSQL *ptr = mysql_real_connect(m_coon,ip.c_str(),user.c_str(),passwd.c_str(), dbName.c_str(), port, NULL, 0);
    return ptr != nullptr;
}

bool MysqlConn::update(std::string sql)  //增删改操作
{
    if(mysql_query(m_coon, sql.c_str()) != 0)
    {
        std::cerr << "update error: " << mysql_error(m_coon) << std::endl;
        return false;
    }
    return true;
}

bool MysqlConn::query(std::string sql)  //select查询操作
{
    freeResult(); 
    if(mysql_query(m_coon, sql.c_str()) != 0)
    {
         std::cerr << "Query error: " << mysql_error(m_coon) << std::endl;
         return false;
    }
    m_result = mysql_store_result(m_coon); //结果集保存到本地
    return true;
    
}

bool MysqlConn::next()
{
    if(m_result != nullptr)
    {
        if((m_row = mysql_fetch_row(m_result)) != NULL)//得到一行结果并保存,char *数组
            return true;
        else
            return false;
    }
    return false;
}

std::string MysqlConn::value(int index)
{
    int colnumber = mysql_num_fields(m_result); //查询结果有多少列
    // mysql_num_rows,查询结果有多少行
    if(index >= colnumber||index < 0)
    {
        return std::string();
    }
    char *val = m_row[index]; 
    unsigned long length = mysql_fetch_lengths(m_result)[index];//返回值是一个数组指针，数组中是结果集内当前行的每个字段的长度
    return std::string(val,length);
}

bool MysqlConn::transaction()
{
    return mysql_autocommit(m_coon,false); //设置事务的提交类型，这里为手动提交
}

bool MysqlConn::commit()
{
    return mysql_commit(m_coon);
}

bool MysqlConn::rollback()
{
    return mysql_rollback(m_coon);
}

void MysqlConn::refreshAliveTime()  //每次将使用完成的连接放回队列尾部时，都要刷新这个时间
{
    m_alivetime = std::chrono::steady_clock::now(); //调用得到当前时间
}

long long MysqlConn::getAliveTime()
{
    // res单位是ns
    std::chrono::nanoseconds res = std::chrono::steady_clock::now() - m_alivetime;
    // 精度转换，将ns转换成ms
    std::chrono::milliseconds millsec = std::chrono::duration_cast<std::chrono::milliseconds>(res);
    return millsec.count();  
}

void MysqlConn::freeResult()
{
    if(m_result)
    {
        mysql_free_result(m_result);  // 释放结果集使用的内存
    }
}