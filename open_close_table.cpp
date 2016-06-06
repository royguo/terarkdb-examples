//
//  open_close_table.cpp
//  terarkdb-api-examples
//
//  Created by Roy Guo on 3/6/59 BE.
//  Copyright © 2559 BE royguo. All rights reserved.
//
#include <terark/db/db_table.hpp>
#include <iostream>
#include "terarkdb_test.hpp"


void test_open_close_table(const char* dbtable) {
    std::cout<<"test open close table"<<std::endl;
    
    // method 1
    // open table defined by `db/user_table/dbmeta.json`
    terark::db::CompositeTablePtr tab1 = terark::db::CompositeTable::open(dbtable);
    // wait for compression thead finish before close table
    terark::db::CompositeTable::safeStopAndWaitForCompress();
    printf("safe stop and wait for compress\n");
    tab1 = nullptr;

    
    // method 2
    terark::db::CompositeTablePtr tab2 = terark::db::CompositeTable::open(dbtable);
    // wait for data flush before close table
    terark::db::CompositeTable::safeStopAndWaitForFlush();
    printf("safe stop and wait for flush\n");
    tab2 = nullptr;
}