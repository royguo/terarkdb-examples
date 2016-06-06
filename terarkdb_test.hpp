//
//  terarkdb_test.hpp
//  terarkdb-api-examples
//
//  Created by Roy Guo on 3/6/59 BE.
//  Copyright © 2559 BE royguo. All rights reserved.
//

#ifndef terarkdb_test_h
#define terarkdb_test_h

void test_open_close_table(const char* dbtable);

void test_write_data(const char* dbtable);

void test_update_data(const char* dbtable);

void test_range_search(const char* dbtable);

void test_point_search(const char* dbtable);

void test_utils();
#endif /* terarkdb_test_h */
