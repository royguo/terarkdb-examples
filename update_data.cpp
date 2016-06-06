//
//  update_data.cpp
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

void test_update_data(const char* dbtable) {
    // open table
    terark::db::CompositeTablePtr tab = terark::db::CompositeTable::open(dbtable);
    terark::db::DbContextPtr ctx = tab->createDbContext();

    // inplace update : reset user(id = 150)'s age
    terark::valvec<terark::llong> recIdvec;
    size_t idIndexId = tab->getIndexId("id");
    int id = 150;
    terark::fstring key = terark::db::Schema::fstringOf(&id);
    ctx->indexSearchExact(idIndexId, key, &recIdvec);
    for(auto recId : recIdvec) {
        uint8_t age = 101;
        terark::fstring newAge = terark::db::Schema::fstringOf(&age);
        tab->updateColumn(recId, "age", newAge);
    }
    
    // non-inplace update
    // 1. this table can only have one unqiue column
    // 2. new data will be inserted into writable segment and old data will be marked as deleted
    id = 140;
    key = terark::db::Schema::fstringOf(&id);
    ctx->indexSearchExact(idIndexId, key, &recIdvec);
    for(auto recId : recIdvec) {
        uint8_t age = 101;
//        tab->upsertRow(<#fstring row#>, ctx.get());
    }
    
    // close table
    tab->safeStopAndWaitForFlush();
    tab = nullptr;
}
