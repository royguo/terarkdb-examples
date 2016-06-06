//
//  point_search.cpp
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


// range search test
void test_point_search(const char* dbtable) {
    // open table
    terark::db::CompositeTablePtr tab = terark::db::CompositeTable::open(dbtable);
    terark::db::DbContextPtr ctx = tab->createDbContext();
    
    size_t idIndexId = tab->getIndexId("id");
    terark::valvec<terark::llong> recIdVec;
    int id = 100;
    terark::fstring key = terark::db::Schema::fstringOf(&id);
    // search the record of id = 100
    ctx->indexSearchExact(idIndexId, key, &recIdVec);
    
    // method 1, the simplest way, get fields value seperately.
    printf("method 1 : \n");
    size_t nameColumnId = tab->getColumnId("name");
    size_t descColumnId = tab->getColumnId("description");
    
    terark::valvec<terark::byte> nameVal;
    terark::valvec<terark::byte> descVal;
    // The same key may have multiple records
    for (auto recId : recIdVec) {
        ctx->selectOneColumn(recId, nameColumnId, &nameVal);
        ctx->selectOneColumn(recId, descColumnId, &descVal);
        printf("%.*s  ", (int)nameVal.size(), nameVal.data());
        printf("%.*s\n", (int)descVal.size(), descVal.data());
    }
    
    // method 2, if name and description are in the same colgroup(defined in dbmeta.json)
    printf("method 2 : \n");
    size_t nameDescColGroupId = tab->getColgroupId("name_and_description");
    auto& nameDescColgroupSchema = tab->getColgroupSchema(nameDescColGroupId);
    terark::valvec<terark::byte> nameDescVal;
    terark::db::ColumnVec nameDescCV;
    // The same key may have multiple records
    for (auto recId : recIdVec) {
        ctx->selectOneColgroup(recId, nameDescColGroupId, &nameDescVal);
        nameDescColgroupSchema.parseRow(nameDescVal, &nameDescCV);
        printf("%s  %s\n", nameDescCV[0].c_str(), nameDescCV[1].c_str());
    }
    // close table
    tab->safeStopAndWaitForFlush();
    ctx = nullptr;
    tab = nullptr;
}