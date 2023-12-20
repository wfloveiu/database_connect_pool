#pragma once
#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>
#include "MysqlConn.h"
#include <jsoncpp/json/json.h>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>

class ConnectionPool
{
public:
    //提供一个公开的静态方法，使得外部使用者可以访问类的唯一实例
    static ConnectionPool* getConnectPool();  
    //删除的拷贝构造函数
    ConnectionPool(const ConnectionPool& obj) = delete; 
    //删除的赋值构造函数
    ConnectionPool& operator= (const ConnectionPool& obj) = delete; 
    //用户调用接口，获取连接池中的连接
    std::shared_ptr<MysqlConn> getConnection();
    ~ConnectionPool();
private:
    /*
    单例类的构造函数必须是私有的，这样才能将类的创建权控制在类的内部，
    从而使得类的外部不能创建类的实例。
    */ 
    ConnectionPool(); 

    bool pareJsonFile();
    void addConnection(); //添加连接

    void producerConnection();  //监控数据库连接是否满足最小值
    /*
    *数据库中的连接大于最小值时，可能会存在一些连接的空闲时间较长
    *我们认为空闲时间较长的连接需要被回收（因为它存在也没有意义）
    */ 
    void recycleConnection(); 

    std::string m_ip;
    std::string m_user;
    std::string m_passwd;
    std::string m_dbname;
    unsigned short m_port;
    int m_minSize;
    int m_maxSize;
    int m_timeout;  // 当连接池中没有空闲时，需要让线程等待这么多时间
    int m_maxIdleTime; //数据库连接的最大空闲时间
    std::mutex m_mutexQ;   //互斥锁，控制互斥地访问队列
    std::queue<MysqlConn *> m_connectionQ;  
    std::condition_variable m_cond_produce;  //生产者条件变量，即连接池中可用线程数不足minSize时，才能生产
    std::condition_variable m_cond_consume;  //消费者条件变量，即有连接可用时，才能消费
};