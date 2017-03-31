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

#include "DBPoolingTest.h"
#include <string>

using namespace std;

DBPoolingTest::DBPoolingTest() {
}

DBPoolingTest::~DBPoolingTest() {
}

void DBPoolingTest::DBTest() {
    for(int i=0; i<10;i++) {
        UpdateQuery("INSERT INTO TESTDB (STR_SAMPLE, DATE_SAMPLE) VALUES ('HELLO', '2017-03-31')");
    }
    char CharResult[256] = {0x00,};
    SelectQuery(&*CharResult, "SELECT STR_SAMPLE FROM TESTDB WHERE IDX = 1");
    string StrResult ;
    SelectQuery(&StrResult, "SELECT STR_SAMPLE FROM TESTDB WHERE IDX = 1");
    cout << CharResult <<endl;
    cout << StrResult <<endl;
    
    KDBManager::ResultRow rr;
    if(SelectQuery(&rr, "SELECT IDX, str_sample, date_sample FROM TESTDB WHERE IDX = 1")) {
        cout << rr.at(0)  << " / " << rr.at(1) << " / " <<  rr.at(2) <<  "\n";
    }
    
    KDBManager::ResultSet rs; 
    if(SelectQuery(&rs, "SELECT IDX, str_sample, date_sample FROM TESTDB ")) {
        for(int i=0;i<rs.size();i++) {
            ResultRow rr = rs.at(i);
            cout << rr.at(0)  << " / " << rr.at(1) << " / " <<  rr.at(2) << "\n";
        }
    }
}
