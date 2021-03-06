# KDBManager
Licensed under the Apache License, Version 2.0 (the "License");
Written by KwangChun(David) Kang  (kkckc24@gmail.com)

You can rewrite or improve the code, unless do not delete original contributer.
- KwangChun(David) Kang  (kkckc24@gmail.com)

# Properties and Linked Lib.
1. You can simply import the project file from Netbeans or Include and Rewrite some of the file as you want
2. It does not have dependencies except mysql lib.
- Linked Libraries: pthread, mysqlclient_r, crypto, ssl, m, z, rt

# Main Sources
1. KDBManager 
It is very easy to use and flexable.

(1) Using by inheritance
- Please see DBPoolingTest 
```C++
class DBPoolingTest : KDBManager {
           // Your Code
}
```

(2) Using by Variable declaration
- Setup the properties and Variable declaration
```C++
CONFIG->SetDBIP("192.168.3.1");
CONFIG->SetDBID("myid");
CONFIG->SetDBPASSWORD("mypassword");
CONFIG->SetDBPORT(3306);
CONFIG->SetDBSERVICEID("myuser");
CONFIG->SetDBPOOLSIZE(20);
KDBManager dbm;
```

- Update Query
```C++
dbm.UpdateQuery("INSERT INTO TESTDB (STR_SAMPLE, DATE_SAMPLE) VALUES ('HELLO', '2017-03-31')");
```

- Select Query
```C++
KDBManager::ResultRow rr;
if(dbm.SelectQuery(&rr, "SELECT IDX, str_sample, date_sample FROM TESTDB WHERE IDX = 1")) {
  cout << rr.at(0)  << " / " << rr.at(1) << " / " <<  rr.at(2) << "\n";
}
KDBManager::ResultSet rs; 
if(dbm.SelectQuery(&rs, "SELECT IDX, str_sample, date_sample FROM TESTDB")) {
  for(int i=0;i<rs.size();i + +) {
    KDBManager::ResultRow rr = rs.at(i);
    cout << rr.at(0)  << " / " << rr.at(1) << " / " <<  rr.at(2) << "\n";
  }
}
</code></pre>
```

2. KDBConnectionPool 
The class supports Connection Pool and Non-Pooling with MySQL (or MariaDB).
If you do not want to use connection pool. Change the USE_POOL option in the KDBConnectionPool.h
```C++
#define USE_POOL 1    // Pooling Enable
#define USE_POOL 0    // Pooling Disable
```

# Sub Sources
1. KMutex 
```C++
KMutex iMutex; 
iMutex.lock();
#your Code
iMutex.unlock();
```

2. KLogger
<pre>I made the logger by using log4cxx at the first place; however, I changed the code with COUT/PRINTF for your convenience.
You can change your logger or change the code in the KDBManager/KDBConnectionPool</pre>

3. DBConf
It will be used for Database Configuration.
```C++
CONFIG->SetDBIP("IP");
CONFIG->SetDBID("PASSWORD");
CONFIG->SetDBPASSWORD("PASSWORD");
CONFIG->SetDBPORT(3306);
CONFIG->SetDBSERVICEID("SERVICEID");
CONFIG->SetDBPOOLSIZE(20); // Pooling Size
```

# Example
DB Info of Sample Database
```mysql
CREATE TABLE `TESTDB` (
  `IDX` int(11) NOT NULL AUTO_INCREMENT,
  `str_sample` varchar(2000) DEFAULT NULL,
  `date_sample` date DEFAULT NULL,
  PRIMARY KEY (`IDX`)
)
```
1. main.cpp
Sample code of Insert/Select with TESTDB Table.

2. DBPoolingTest.cpp
This Code shows how to inherit KDBManager for using mysql DB.

# Caution
Please setup the timeout parameters in /etc/my.cnf.d/server.cnf; if you want to use connection pools in mysql.
Refer the following setting parameters.
```
[mysqld]
wait_timeout=31536000
skip-name-resolve
max_allowed_packet=128M
interactive_timeout = 31536000
```
