//
//  write_data.cpp
//  terarkdb-api-examples
//
//  Created by Roy Guo on 6/6/59 BE.
//  Copyright © 2559 BE royguo. All rights reserved.
//

#include <iostream>

#include <terark/db/db_table.hpp>
#include <terark/io/DataIO.hpp>
#include <terark/io/MemStream.hpp>
#include <terark/io/RangeStream.hpp>
#include <terark/lcast.hpp>

#include "terarkdb_test.hpp"
#include "user.hpp"

void test_write_data(const char* dbtable) {
    // open table
    terark::db::CompositeTablePtr tab = terark::db::CompositeTable::open(dbtable);
    terark::db::DbContextPtr ctx = tab->createDbContext();

    // create row builder for row data insert
    terark::NativeDataOutput<terark::AutoGrownMemIO> rowBuilder;

    // create 1000 users and insert them into user_table
    test_ns::User u = {};
    
    for(int i = 1; i <= 1000; i++) {
        char szBuf[256];
        u.id = i;
        u.name.assign(szBuf, snprintf(szBuf, sizeof(szBuf), "Test-User-Name-%d", i));
        u.description.assign(szBuf, snprintf(szBuf, sizeof(szBuf), "Description-%d", i));
        u.age = (i + 10);
        u.update_time = (int)1463472964753 + i;
        
        // insert row
        rowBuilder.rewind();
        rowBuilder << u;
        if (ctx->insertRow(rowBuilder.written()) < 0) {
            printf("Insert failed: %s\n", ctx->errMsg.c_str());
        }
    }
    
    printf("data inserted succussfully !\n");

    
    // close table
    tab->safeStopAndWaitForFlush();
    tab = nullptr;
}


