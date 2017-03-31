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

#ifndef KCONNECTIONPOOL_H
#define KCONNECTIONPOOL_H

#include <stddef.h>
#include <mysql.h>
#include <queue>
#include <iostream>
#include <string>
#include "KMutex.h"

#define QUERY_BUF 512

#define GET_SIMPLE_QUERY(RESULT, QUERY)  ConnectionPool::getInstance()->SimpleQuery(RESULT, QUERY);

#define CONNECT() MYSQL *CONN=ConnectionPool::getInstance()->getConnection(); 
#define UPDATE_QUERY(QUERY, STAT) MYSQL *CONN=ConnectionPool::getInstance()->getConnection();   \
                                                            REUSE_UPDATE_QUERY(QUERY, STAT);

#define REUSE_UPDATE_QUERY(QUERY, STAT) if(CONN!=NULL) { \
                                                                        STAT = mysql_query(CONN, QUERY);  \
                                                                if(STAT!=0) { \
                                                                        CILOG("DB ERROR OR WARNING %s, %d] %s", mysql_error(CONN), mysql_warning_count(CONN), QUERY);  \
                                                                } else {  STAT=mysql_affected_rows(CONN);     \
                                                                }}

#define DISCONNECT()  if(CONN!=NULL) { ConnectionPool::getInstance()->release(CONN); CONN=NULL; }

#define SELECT_QUERY(QUERY, RESULT) MYSQL *CONN=ConnectionPool::getInstance()->getConnection();   \
                                                        MYSQL_ROW   sql_row=NULL; \
                                                        int       query_stat = 0;  \
                                                        if (CONN!=NULL) { \
                                                        query_stat = mysql_query(CONN, QUERY); \
                                                        if (query_stat == 0) { \
                                                                RESULT= mysql_store_result(CONN); \
                                                        } else { \
                                                                CELOG("DB_ERROR", "DB error :" << mysql_error(CONN)); \
                                                        }} 

#define REUSE_SELECT_QUERY(QUERY, RESULT)  \
                                                        if (CONN!=NULL) { \
                                                                query_stat = mysql_query(CONN, QUERY); \
                                                        if (query_stat != 0) { \
                                                                CELOG("DB_ERROR", "Mysql query error :" << mysql_error(CONN)); \
                                                        } else { \
                                                                RESULT= mysql_store_result(CONN); \
                                                        }} 

#define END_QUERY(RESULT)  mysql_free_result(RESULT); \
                            if(CONN!=NULL) ConnectionPool::getInstance()->release(CONN); CONN=NULL; RESULT=NULL;

#define NOT_NULL(DATA)    (DATA==NULL||strlen(DATA)<1)?" ":DATA


#define USE_POOL 1 // Connection Pool Size
#define SET_MULTI_QUERY 0   // Multi Query Option (Not Tested)
#define RECONN_WAIT_TIME 1000*10    // Reconnection time when the connection lost

class ConnectionPool {
private: 
    static ConnectionPool *pInstance; // singleton static var
    ConnectionPool() ;
    virtual ~ConnectionPool();
    
    inline MYSQL* makeANewConnection();
    
    std::queue<MYSQL*> pPoolList;
    static KMutex iMutex; // Mutex Lock
    int ConnOption;
public:    
    static ConnectionPool* getInstance() {
            if(pInstance == NULL) {
               ConnectionPool::iMutex.lock();
               if(pInstance == NULL) {
                    pInstance = new ConnectionPool();
               }
               ConnectionPool::iMutex.unlock();
            }
            return pInstance;
    }    
public:
    MYSQL* getConnection(); 
    void release(MYSQL*& conn);
    int getCurrentSize() {
        return pPoolList.size();
    }
};
#endif	/* KCONNECTIONPOOL_H */
