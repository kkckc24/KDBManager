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

#ifndef KDBMANAGER_H
#define KDBMANAGER_H

#include <string>
//#include <boost/thread.hpp>
#include "KConnectionPool.h"
#include "KLogger.h"
#include "KMutex.h"


#define ERROR_RETURN -1


class KDBManager {
public:
    typedef std::vector<std::string> ResultRow;
    typedef std::vector<ResultRow> ResultSet;
    
    KDBManager();
    virtual ~KDBManager();

    // Update/Insert Query , Input: Query String , Return: Affected Size or ERROR (-1)
    int UpdateQuery(const char* query);
    
    // Select Query , Input: ResultSet, Query String , Return: Affected Size or ERROR (-1)
    int SelectQuery(char* result, const char* query);
    int SelectQuery(std::string *result, const char* query);
    int SelectQuery(ResultRow *result, const char* query);
    int SelectQuery(ResultSet *result, const char* query);
};

#endif	/* DBMANAGER_H */
