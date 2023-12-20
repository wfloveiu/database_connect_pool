#include "ConnectionPool.h"


ConnectionPool::ConnectionPool() //构造函数
{
    //加载json配置文件
    if(!pareJsonFile())
        return;
    for(int i=0;i<m_minSize;i++)
        addConnection();
    std::thread producer(&ConnectionPool::producerConnection,this);
    std::thread recycler(&ConnectionPool::recycleConnection,this);
    /*
    detach() 分离线程，让它独立运行，不需要等待其执行结束
    join() 等待线程结束，并获取返回值
    这里直接让线程后台运行
    */ 
    producer.detach();  
    recycler.detach();
}


ConnectionPool::~ConnectionPool() 
{
    while(!m_connectionQ.empty())
    {
        MysqlConn* conn = m_connectionQ.front();
        m_connectionQ.pop();
        delete conn;
    }
}


ConnectionPool* ConnectionPool::getConnectPool()
{
    static ConnectionPool pool;
    return &pool;
}

// 读json文件
bool ConnectionPool::pareJsonFile()
{  
    std::ifstream ifs("dbconfig.json"); 
    if (!ifs) {
        std::cout << "Failed to open the file!" << std::endl;
        // 文件打开失败，进行适当的处理或错误提示
    }
    Json::Reader rd;
    Json::Value root;
    rd.parse(ifs, root);
    if(root.isObject())
    {
        m_ip = root["ip"].asString();
        m_port = root["port"].asInt();
        m_user = root["userName"].asString();
        m_passwd = root["password"].asString();
        m_dbname = root["dbName"].asString();
        m_minSize = root["minSize"].asInt();
        m_maxSize = root["maxSize"].asInt();
        m_maxIdleTime = root["maxIdleTime"].asInt();
        m_timeout = root["timeout"].asInt();
        return true;
    }
    
    return false;
}

void ConnectionPool::addConnection()
{
    MysqlConn* conn = new MysqlConn;
    conn->connect(m_user,m_passwd, m_dbname, m_ip, m_port);
    conn->refreshAliveTime(); //每次新建立一个连接就需要refresh时间戳
    m_connectionQ.push(conn); //添加到连接池中
    // std::cout<<"增加一个连接"<<std::endl;
}

void ConnectionPool::producerConnection() // 一直运行判断
{
    while(true)
    {
        // unique_lock智能锁，
        std::unique_lock<std::mutex> locker(m_mutexQ);
        while(m_connectionQ.size() >= m_minSize)  //注意这里是while循环
        {
            m_cond_produce.wait(locker);  //
        }
        addConnection();
        m_cond_consume.notify_all();// 唤醒消费者对应的阻塞线程
    }
}

void ConnectionPool::recycleConnection()
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));  //休眠1s
        std::lock_guard<std::mutex> locker(m_mutexQ);
        while(int(m_connectionQ.size()) > m_minSize)
        {
            MysqlConn* conn = m_connectionQ.front();//取队首，
            /*
            如果队首连接的空闲时间大于规定时间，就回收
            队首连接空闲时间小于规定时间，那队列后边的也小于，就都不用回收了
            调用getAliveTime返回空闲时间
            */ 
            if(conn->getAliveTime() >= m_maxIdleTime)
            {
                m_connectionQ.pop();
                delete conn;
            }
            else
                break;
        }
    }
}

std::shared_ptr<MysqlConn> ConnectionPool::getConnection()
{
    /*
    1.判断队列中有没有可用连接
    2.没有的话，就阻塞线程一段时间
    */
    std::unique_lock<std::mutex> locker(m_mutexQ);
    while(m_connectionQ.empty())
    {
        /*
        如果在指定时间内条件变量满足，函数返回 std::cv_status::no_timeout
        如果在指定时间内等待超时，函数返回 std::cv_status::timeout
        */
        if(std::cv_status::timeout == m_cond_consume.wait_for(locker, std::chrono::milliseconds(m_timeout)))
        {
            if(m_connectionQ.empty())
                continue; //返回空指针
        }
    }
    /*
    使用智能指针来方便用完之后的回收
    */
    std::shared_ptr<MysqlConn> connptr(m_connectionQ.front(), [this](MysqlConn* conn){
        m_mutexQ.lock();
        conn->refreshAliveTime();
        m_connectionQ.push(conn);
        m_mutexQ.unlock();
    });
    m_connectionQ.pop();
    m_cond_produce.notify_all(); //唤醒生产者
    return connptr;
}
