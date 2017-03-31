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

#ifndef DBCONF_H
#define	DBCONF_H

#include <string>

#define GETTER(T,member) const T& Get##member() const { return member; }
#define SETTER(T, member) void Set##member(const T & value) { member =value; } // std::string, BAR
#define GSETTER(T, member) private: T member;  SETTER(T,member) public: GETTER(T,member) 
#define PGSETTER(T, member) private: T member;  public: SETTER(T,member) GETTER(T,member) private:

#define CONFIG DBConf::getInstance()

class DBConf {
private:
    DBConf() {}
    virtual ~DBConf() { } 
public:
    PGSETTER(std::string, DBIP)
    PGSETTER(int, DBPORT)
    PGSETTER(std::string, DBID)
    PGSETTER(std::string, DBPASSWORD)
    PGSETTER(std::string, DBSERVICEID)
    PGSETTER(int, DBPOOLSIZE)
public:
    static DBConf* getInstance() {
        static DBConf dbc;
        return &dbc;
    }
};

#endif	/* DBCONF_H */

