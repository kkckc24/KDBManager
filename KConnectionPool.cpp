/*
 * Copyright 2017 David Kang (kkckc24@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http: *www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "KConnectionPool.h"
#include <stdarg.h>
#include "./DBConf.h"
#include "./KLogger.h"

ConnectionPool *ConnectionPool::pInstance = NULL;
KMutex ConnectionPool::iMutex ;

// Caution: If you want to use database pooling, please setup the timeout parameters from my.ini
// interactive_timeout = 31536000
// wait_timeout = 31536000

ConnectionPool::ConnectionPool() {    
    mysql_library_init(0, NULL, NULL);

    if(SET_MULTI_QUERY) ConnOption=MYSQL_OPTION_MULTI_STATEMENTS_ON;
    else ConnOption=0;
#if USE_POOL
    for(int i=0;i<CONFIG->GetDBPOOLSIZE();i++) {
        pPoolList.push(makeANewConnection());
    }
#endif
}

ConnectionPool::~ConnectionPool() {
#if USE_POOL
    MYSQL *conn = NULL; int count=0;
    while((conn=getConnection())!=NULL) {
        CILOG("Connection Pool Memory Released %d", count);
        mysql_close(conn); conn=NULL;
    }
    //delete pMutex;
    mysql_library_end();
#endif    
    delete pInstance; pInstance=0;
}

MYSQL* ConnectionPool::getConnection() {   
#if USE_POOL    
    if(!pPoolList.empty()) {
        iMutex.lock();
        MYSQL*CONN = pPoolList.front();
        pPoolList.pop();
        iMutex.unlock();
        
        if(CONN!=NULL && mysql_errno(CONN)!=0) {
            CILOG("Trying to Reset the Connection, DB ERROR OR WARNING: %s, %d", mysql_error(CONN), mysql_warning_count(CONN)); 
            mysql_close(CONN); 
            CONN=NULL;
        }
        if(CONN==NULL) {
            CONN=makeANewConnection();
        }
        return CONN;
    }
    else {
        return NULL;
    }
#else
    MYSQL *connection = mysql_init(NULL);    
    while(connection==NULL) {
        CELOG("DB_ERROR","CONNECTION Is NULL, WAITING");
        usleep(1000*10);  // 1000*1000 1sec
        connection = mysql_init(NULL);    
    }
    if(mysql_real_connect(connection, CONFIG->GetDBIP().c_str(), CONFIG->GetDBID().c_str(), 
            CONFIG->GetDBPASSWORD().c_str(), CONFIG->GetDBSERVICEID().c_str(), CONFIG->GetDBPORT(), NULL, ConnOption)!=NULL) {
       // iMutex.unlock();
        return connection;
    }
#endif
}

void ConnectionPool::release(MYSQL*& conn) {
#if USE_POOL        
    pPoolList.push(conn);
#else
    mysql_close(conn); conn=NULL;
#endif    
}

MYSQL* ConnectionPool::makeANewConnection() {
    MYSQL*CONN = NULL;
    int RetryCount = 0;
    while(CONN==NULL && !mysql_error(CONN)[0]) {
        CILOG("Making a New Connection of the MySQL");
        CONN = mysql_init(NULL);    
        if(RetryCount>0) usleep(RECONN_WAIT_TIME);  // 1000*1000 1sec
        unsigned int TIMEOUT_LIMIT_OPT= 31536000;
        //my_bool RECONNCT_OPT= 1;
        mysql_options(CONN, MYSQL_OPT_CONNECT_TIMEOUT, &TIMEOUT_LIMIT_OPT);
        mysql_options(CONN, MYSQL_OPT_READ_TIMEOUT, &TIMEOUT_LIMIT_OPT);
        mysql_options(CONN, MYSQL_OPT_WRITE_TIMEOUT, &TIMEOUT_LIMIT_OPT);
        //mysql_options(CONN, MYSQL_OPT_RECONNECT, &RECONNCT_OPT);

        if(CONN!=NULL) {
            if (mysql_real_connect(CONN, CONFIG->GetDBIP().c_str(), CONFIG->GetDBID().c_str(), 
                CONFIG->GetDBPASSWORD().c_str(), CONFIG->GetDBSERVICEID().c_str(), CONFIG->GetDBPORT(), NULL, ConnOption)==NULL) {
                CELOG("MYSQL_INIT_ERROR", "MYSQL POOL INSTANCE REALLOCATE ERROR");
            } else {
                // Okay 
            }        
        }
        RetryCount++;
    }   
    return CONN;
}
