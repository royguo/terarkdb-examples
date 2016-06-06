//
//  range_search.cpp
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
void test_range_search(const char* dbtable) {
    // open table
    terark::db::CompositeTablePtr tab = terark::db::CompositeTable::open(dbtable);
    
    // create iterator on index `id`
    size_t idIndexId = tab->getIndexId("id");
    terark::db::IndexIteratorPtr idIterator = tab->createIndexIterForward(idIndexId);

    // record id and return key
    terark::valvec<terark::byte> retKey;
    terark::llong recId;
    
    // keys ∈ [900, 950)
    printf("keys ∈ [900, 950): \n");
    int low = 900;
    int high = 950;
    terark::fstring key = terark::db::Schema::fstringOf(&low);
    int ret = idIterator->seekLowerBound(key, &recId, &retKey);
    if (ret >= 0) {
        do {
            auto id = terark::db::Schema::numberOf<int>(retKey);
            printf("match recId = %lld, key = %d\n", recId, id);
        } while (idIterator->increment(&recId, &retKey) && terark::db::Schema::numberOf<int>(retKey) < high);
    }
    
    // keys ∈ (0, 100]
    printf("keys ∈ (0, 100] : \n");
    low = 0;
    high = 100;
    key = terark::db::Schema::fstringOf(&high);
    // use backward search for reverse search
    idIterator = tab->createIndexIterBackward(idIndexId);
    ret = idIterator->seekUpperBound(key, &recId, &retKey);
    if(ret >= 0) {
        do{
            auto id = terark::db::Schema::numberOf<int>(retKey);
            printf("match recId = %lld, key = %d\n", recId, id);
        }while(idIterator->increment(&recId, &retKey) && terark::db::Schema::numberOf<int>(retKey) > low);
    }
    
    
    // close table
    tab->safeStopAndWaitForFlush();
    tab = nullptr;
}