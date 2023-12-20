#include <iostream>
#include <memory>
#include "MysqlConn.h"
#include "ConnectionPool.h"


// 不使用连接池
void op1(int begin, int end)
{
    for(int i=begin;i<end;i++)
    {
        MysqlConn conn;
        conn.connect("root", "wf140039", "testdb", "127.0.0.1",3306);
        char insert_sql[1024]={0};
        sprintf(insert_sql,"insert into person values(%d, 25, 'man', 'tom')",i+1);
        conn.update(insert_sql);
    }
}
//使用连接池
void op2(ConnectionPool* pool, int begin, int end)
{
    for(int i=begin;i<end;i++)
    {
        std::shared_ptr<MysqlConn> conn = pool->getConnection();
        char insert_sql[1024]={0};
        sprintf(insert_sql,"insert into person values(%d, 25, 'man', 'tom')",i+1);
        conn->update(insert_sql);
    }
}

void test1()
{
#if 0 
    // 25s
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    op1(0,5000);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto length = end-begin;
    std::cout<<"单线程不使用连接池，运行时间："<<length.count()/1000000000<<"秒"<<std::endl;
#else
    //2s
    ConnectionPool* pool = ConnectionPool::getConnectPool();
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    op2(pool,0,5000);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto length = end-begin;
    std::cout<<"单线程使用连接池，运行时间："<<length.count()/1000000000<<"秒"<<std::endl;
#endif
}

void test2()
{
#if 0
    // 31s
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // 5个子线程
    std::thread t1(op1,0,1000);
    std::thread t2(op1,1000,2000);
    std::thread t3(op1,2000,3000);
    std::thread t4(op1,3000,4000);
    std::thread t5(op1,4000,5000);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto length = end-begin;
    std::cout<<"多线程不使用连接池，运行时间："<<length.count()/1000000000<<"秒"<<std::endl;
#else  //使用线程池，当写入数据库后，最后会卡那里，不知道为啥
    // 806毫秒
    ConnectionPool* pool = ConnectionPool::getConnectPool();
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // 5个子线程
    std::thread t1(op2,pool,0,1000);
    std::thread t2(op2,pool,1000,2000);
    std::thread t3(op2,pool,2000,3000);
    std::thread t4(op2,pool,3000,4000);
    std::thread t5(op2,pool,4000,5000);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto length = end-begin;
    std::cout<<"多线程使用连接池，运行时间："<<length.count()/1000000<<"毫秒"<<std::endl;
#endif
}

// 测试数据库能否联通
void query()
{
    MysqlConn conn;
    conn.connect("root", "wf140039", "testdb", "127.0.0.1",3306);
    std::string insert_sql = "insert into person values(6, 25, 'man', 'tom')";
    bool flag = conn.update(insert_sql);
    std::cout<<"flag value: "<<flag<<std::endl;

    std::string query_sql = "select * from person;";
    conn.query(query_sql);  //
    while(conn.next())  //遍历每一行
    {
        std::cout<<conn.value(0)<<","
                 <<conn.value(1)<<","
                 <<conn.value(2)<<","
                 <<conn.value(3)<<std::endl;
    }
}

int main()
{
    // query();
    // test1(); 
    test2();
    return 0;
}