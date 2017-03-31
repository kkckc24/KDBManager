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

#ifndef KLOGGER_H
#define	KLOGGER_H

#include <stdio.h>
#include <iostream>

#define ANSI_RED "\033[0;40;42m"
#define ANSI_DEFAULT "\033[1;40;0m"

#define CTLOG(fmt, ...) printf(fmt, ## __VA_ARGS__); printf("\n");
#define CDLOG(fmt, ...) printf(fmt, ## __VA_ARGS__); printf("\n");
#define CILOG(fmt, ...) printf(fmt, ## __VA_ARGS__); printf("\n");
#define CWLOG(fmt, ...) printf(fmt, ## __VA_ARGS__); printf("\n");
#define CELOG(KEYWORD, fmt, ...) std::cout << ANSI_RED << KEYWORD << ", " << fmt << ANSI_DEFAULT << "\n"
#define CFLOG(KEYWORD, fmt, ...) std::cout << ANSI_RED << KEYWORD << ", " << fmt << ANSI_DEFAULT << "\n"

//#define TLOG(...) LOG4CXX_TRACE(HistLogger::getInstance()->logger, ## __VA_ARGS__);
//#define DLOG( ...) LOG4CXX_DEBUG(HistLogger::getInstance()->logger, ## __VA_ARGS__);
//#define ILOG(...) LOG4CXX_INFO(HistLogger::getInstance()->logger, ## __VA_ARGS__);
//#define WLOG( ...) LOG4CXX_WARN(HistLogger::getInstance()->logger, ## __VA_ARGS__);
//#define ELOG(KEYWORD, fmt, ...) LOG4CXX_ERROR(HistLogger::getInstance()->logger, ANSI_RED << KEYWORD << ", " << fmt << ANSI_DEFAULT );
//#define FLOG(KEYWORD, fmt, ...) LOG4CXX_FATAL(HistLogger::getInstance()->logger, ANSI_RED << KEYWORD << ", " << fmt << ANSI_DEFAULT);

//#define CTLOG(fmt, ...) LOG4CXX_TRACE(HistLogger::getInstance()->logger, HistLogger::log_format(fmt, ## __VA_ARGS__))
//#define CDLOG(fmt, ...) LOG4CXX_DEBUG(HistLogger::getInstance()->logger, HistLogger::log_format(fmt, ## __VA_ARGS__))
//#define CILOG(fmt, ...) LOG4CXX_INFO(HistLogger::getInstance()->logger, HistLogger::log_format(fmt, ## __VA_ARGS__))
//#define CWLOG(fmt, ...) LOG4CXX_WARN(HistLogger::getInstance()->logger, HistLogger::log_format(fmt, ## __VA_ARGS__))
//#define CELOG(KEYWORD, fmt, ...) LOG4CXX_ERROR(HistLogger::getInstance()->logger, ANSI_RED << KEYWORD << ", " << HistLogger::log_format(fmt, ## __VA_ARGS__) << ANSI_DEFAULT)
//#define CFLOG(KEYWORD, fmt, ...) LOG4CXX_FATAL(HistLogger::getInstance()->logger, ANSI_RED << KEYWORD << ", " << HistLogger::log_format(fmt, ## __VA_ARGS__) << ANSI_DEFAULT)

#endif	/* KLOGGER_H */

