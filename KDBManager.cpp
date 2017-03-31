/*
 * Copyright 2017 kkckc24@gmail.com.
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

#include "KDBManager.h"

using namespace std;

KDBManager::KDBManager() {
}

KDBManager::~KDBManager() {
}


/**
 * Update/Insert Query 
 * @param query Query String
 * @return Affected Size or ERROR (-1)
 */
int KDBManager::UpdateQuery(const char* query) {
    int RtValue=0;
    MYSQL *CONN=ConnectionPool::getInstance()->getConnection();   
    
    REUSE_UPDATE_QUERY(query, RtValue);
    if(RtValue==ERROR_RETURN) {
        CELOG("QUERY_ERROR", "SQL ERROR FOR QUERY: %s", query);
    }
    
    DISCONNECT();
    //iMutex.unlock();
    return RtValue;
}

/**
 * Select Query
 * @param result Single Result String (OUT)
 * @param query Query String 
 * @return Returned Size or ERROR (-1)
 */
int KDBManager::SelectQuery(char* result, const char* query) {
    MYSQL_RES *sql_result = NULL;
    int RtValue = 0;
    SELECT_QUERY(query, sql_result);
    if(sql_result!=NULL) {    
        int fields=mysql_num_fields(sql_result);
        if (fields>0 && (sql_row = mysql_fetch_row(sql_result)) != NULL) {
            strcpy(result, sql_row[0]);
            RtValue=mysql_num_rows(sql_result);
        } else {
            //RtValue=-1;
        }
    }
    END_QUERY(sql_result);
    return RtValue;
}

/**
 * Select Query
 * @param sresult Single Result String (OUT)
 * @param query Query String 
 * @return Returned Size or ERROR (-1)
 */
int KDBManager::SelectQuery(string* sresult, const char* query) {
    MYSQL_RES *sql_result = NULL;
    int RtValue = 0;
    SELECT_QUERY(query, sql_result);
    if(sql_result!=NULL) {
        int fields=mysql_num_fields(sql_result);
        if (fields>0 && (sql_row = mysql_fetch_row(sql_result)) != NULL) {
            if(sql_row[0]!=NULL) {
                *sresult=sql_row[0];
                RtValue=1;
            }
        } else {
            //RtValue=-1;
        }
    }
    END_QUERY(sql_result);
    return RtValue;
}

/**
 * Select Query
 * @param result Single Row / Multi Col Array (OUT)
 * @param query Query String 
 * @return Returned Size or ERROR (-1)
 */
int KDBManager::SelectQuery(ResultRow *result, const char* query) {
    MYSQL_RES *sql_result = NULL;
    MYSQL *CONN=ConnectionPool::getInstance()->getConnection();   
    //mysql_ping(CONN);
    MYSQL_ROW   sql_row=NULL; 
    int       query_stat = 0;  
    int RtValue = 0;
    
    if (CONN!=NULL) { 
        query_stat = mysql_query(CONN, query); 
        if (query_stat == 0) { 
            sql_result= mysql_store_result(CONN); 
            if(sql_result==NULL) {
                CELOG("DB_ERROR", "DB error :" << mysql_error(CONN)[0]);
                return ERROR_RETURN;
            }
            if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                int fields=mysql_num_fields(sql_result);
                for(int i=0; i<fields;i++) {
                    string value=(sql_row[i]==NULL)?"":sql_row[i];
                    result->push_back(value);
                } 
                RtValue++;
            }
            END_QUERY(sql_result);    
        } else { 
            CELOG("DB_ERROR", "DB error :" << mysql_error(CONN)[0]); 
        }
    } 
    return RtValue;
}

/**
 * Select Query
 * @param result Multi Row / Multi Col Array (OUT)
 * @param query Query String 
 * @return Returned Size or ERROR (-1)
 */
int KDBManager::SelectQuery(ResultSet *result, const char* query) {
    MYSQL_RES *sql_result = NULL;
    int RtValue = 0;
    CTLOG("Query: %s", query);
    
    SELECT_QUERY(query, sql_result);
    if(sql_result==NULL) {
        CELOG("DB_ERROR", "DB error :" << mysql_error(CONN)[0]);
        return ERROR_RETURN;
    }
    int fields=mysql_num_fields(sql_result);    
/*    if (sql_row==NULL) {
        RtValue=-1;
    } else {*/
        if(fields>0) {
            while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
                ResultRow resultRow;
                for(int i=0; i<fields;i++) {
                    string value=(sql_row[i]==NULL)?"":sql_row[i];
                    resultRow.push_back(value);
                } 
                result->push_back(resultRow);
                RtValue++;
            }
        }
    //}
    END_QUERY(sql_result);    
    return RtValue;
}
