# 数据库连接池

## 数据库连接基础知识

### 数据库连接步骤

1. 初始化连接环境
2. 连接MySQL服务器，提供以下数据
   - 服务器IP
   - 监听端口，默认3306
   - 用户名，密码
   - 数据库名
3. 对数据库的增删改查
4. 如果是进行增加、删除、修改，需要进行事务处理
   - 成功：提交事务
   - 失败：事务回滚
5. 数据库的读操作->查询->得到结果集
6. 便利结果集->得到数据
7. 释放资源

### 相关的API

#### 初始化连接环境

```c++
/* 
初始化传入的MYSQL对象
返回值：失败返回NULL
*/
MYSQL *mysql_init(MYSQL *mysql)
```

#### 连接mysql服务器

```c++
/*
返回值：失败返回NULL
*/
MYSQL *mysql_real_connect(
	MYSQL *mysql, //mysql对象句柄
	const char *host, //ip
	const char *user, 
	const char *passwd, 
	const char *db, 
	unsigned int port, //0-默认端口3306；非0-即设置为port
	const char *unix_socket, //本地套接字，不使用指定为NULL
	unsigned long client_flag) //通常为 0
```

#### 执行sql语句

```c++
/*
执行sql语句，增删改查都可以
query为执行的SQL语句对应的字符长串
执行成功返回0，执行失败返回非0
特殊：如果是查询语句的话，还会得到一个结果集MYSQL_RES中
*/
int mysql_query(MYSQL *mysql, const char *query) 
```

#### 获取结果集

```c++
/*
将mysql_query()查询的全部结果读取到客户端,失败返回NULL
*/
MYSQL_RES *mysql_store_result(MYSQL *mysql) 
```

#### 得到结果集的列数

```c++
// 返回结果集中有多少列
unsigned int mysql_num_fields(MYSQL_RES *result)
```

#### 从结果集中获取下一行数据

```c++
//MYSQL_ROW开篇已经说明，char ** 类型，下一行没有数据返回NULL
// 这一行数据组成的二维数组，遍历即可取出每一个字段的数据
MYSQL_ROW mysql_fetch_row(MYSQL_RES* result)
```

#### 获取结果集列名

```c++
// 返回MYSQL_FIELD结构体数组的指针
MYSQL_FIELD *mysql_fetch_fields(MYSQL_RES *result) 
```

```c++
typedef struct st_mysql_field {
  char *name;                 /* 列名 */
  char *org_name;             /* Original column name, if an alias */
  char *table;                /* Table of column if column was a field */
  char *org_table;            /* Org table name, if table was an alias */
  char *db;                   /* Database for table */
  char *catalog;          /* Catalog for table */
  char *def;                  /* Default value (set by mysql_list_fields) */
  unsigned long length;       /* Width of column (create length) */
  unsigned long max_length;   /* Max width for selected set */
  unsigned int name_length;
  unsigned int org_name_length;
  unsigned int table_length;
  unsigned int org_table_length;
  unsigned int db_length;
  unsigned int catalog_length;
  unsigned int def_length;
  unsigned int flags;         /* Div flags */
  unsigned int decimals;      /* Number of decimals in field */
  unsigned int charsetnr;     /* Character set */
  enum enum_field_types type; /* Type of field. See mysql_com.h for types */
  void *extension;
} MYSQL_FIELD;
```

#### 释放结果集

```c++
void mysql_free_result(MYSQL_RES *result) 
```

#### 关闭数据库连接

```c++
void mysql_close(MYSQL *mysql) 
```

## 数据库连接池

### 参考链接

[基于C++11的数据库连接池]([1. 数据库连接池概述_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1Fr4y1s7w4?p=1&vd_source=4d8f38d509aec992e4fd21510d06c9cd))

### 环境配置

#### Linux版本

```
ubuntu 22.04
```

#### Mysql

```shell
# 安装mysql
sudo apt upgrade && sudo apt install mysql-server mysql-client libmysqlclient-dev
# 更改数据库root用户的密码为自己定义的密码

# 调整用户身份验证（默认使用的不是密码验证），参考链接：https://www.51cto.com/article/718700.html

# 设置远程访问地址，进入mysql数据库
UPDATE user SET host = '%' WHERE user = 'root';

# 更改mysql配置文件
sudo vim /etc/mysql/mysql.conf.d/mysqld.cnf
将bind-address = 127.0.0.1注释掉

# 重启mysql服务
sudo service mysql restart

# 检验是否可以远程连接
```

#### jsoncpp

```shell
# 安装jsoncpp
sudo apt upgrade && sudo apt install libjsoncpp-dev
```

#### cmake

```shell
sudo apt upgrade && sudo apt install cmake    
```

[学习视频]([基于VSCode和CMake实现C/C++开发 | Linux篇_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1fy4y1b7TC/?spm_id_from=333.1007.top_right_bar_window_custom_collection.content.click&vd_source=4d8f38d509aec992e4fd21510d06c9cd))

该项目下`CMakeList_model.txt`为常用的cmake指令

### 编译

```shell
# 在build文件夹下，执行指令
cmake .. # 生成makefiel
make  # 在bin文件夹下生成可执行程序
```

### 调试

该项目由于使用vscode作为编辑器，因此在`.vscode`文件夹下配置了调试文件`launch.jsoon`和`task.json`，如果你也是使用过vscode并且配置好了调试这两个文件。

直接`F5`就可自动化地执行编译任务，并且打开调试，不用每次手动编译。具体教程参照上边**cmake的学习视频**

### 运行

```shell
# 在bin/文件夹下
./test
```

### 一些小疑问

1. 在使用连接池的情况下，程序在往数据库中添加完数据，并且输出时间后，不会自己结束（卡在那里），调试时发现卡在析构函数那里。这点我不是很理解
2. 在`ConnectionPool.cpp`文件的`bool ConnectionPool::pareJsonFile()`函数中，使用`std::ifstream ifs("dbconfig.json");`读取`json`文件中的数据。参数使用的是相对路径。这里的相对路径改怎么写我有疑问。刚开始我将这个`json`文件放在bin目录下，想着让它和可执行文件test在一个目录下，但是这样的话会出错；后来尝试将它放在项目的根目录下，就不会出错。因此这里我猜测，这里应该是相对于项目工作目录的相对路径，而不是相对于可执行文件test的相对路径