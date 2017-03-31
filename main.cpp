/* 
 * File:   main.cpp
 * Author: root
 *
 * Created on 2017년 3월 28일 (화), 오전 2:42
 */

#include <string>
#include "KLogger.h"
#include "KDBManager.h"
#include "DBConf.h"
#include "DBPoolingTest.h"

using namespace std;

int main(int argc, char** argv) {
    // Database  Configuration
    CONFIG->SetDBIP("192.168.3.8");
    CONFIG->SetDBID("fdpu");
    CONFIG->SetDBPASSWORD("fdpu");
    CONFIG->SetDBPORT(3306);
    CONFIG->SetDBSERVICEID("FDPU");
    CONFIG->SetDBPOOLSIZE(20);
    
    DBPoolingTest DBT;
    DBT.DBTest();
          
    // Usage No. 2
    KDBManager dbm;
    for(int i=0; i<10;i++) {
        dbm.UpdateQuery("INSERT INTO TESTDB (STR_SAMPLE, DATE_SAMPLE) VALUES ('HELLO', '2017-03-31')");
    }
    char CharResult[256] = {0x00,};
    dbm.SelectQuery(&*CharResult, "SELECT STR_SAMPLE FROM TESTDB WHERE IDX = 1");
    string StrResult ;
    dbm.SelectQuery(&StrResult, "SELECT STR_SAMPLE FROM TESTDB WHERE IDX = 1");
    cout << CharResult <<endl;
    cout << StrResult <<endl;
    
    KDBManager::ResultRow rr;
    if(dbm.SelectQuery(&rr, "SELECT IDX, str_sample, date_sample FROM TESTDB WHERE IDX = 1")) {
        cout << rr.at(0)  << " / " << rr.at(1) << " / " <<  rr.at(2) <<  "\n";
    }
    
    KDBManager::ResultSet rs; 
    if(dbm.SelectQuery(&rs, "SELECT IDX, str_sample, date_sample FROM TESTDB ")) {
        for(int i=0;i<rs.size();i++) {
            KDBManager::ResultRow rr = rs.at(i);
            cout << rr.at(0)  << " / " << rr.at(1) << " / " <<  rr.at(2) << "\n";
        }
    }
    return 0;
}

