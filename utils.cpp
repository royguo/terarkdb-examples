//
//  utils.cpp
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


void test_utils() {
    terark::fstring str1 = "hello world fstring!";
    terark::fstring str2 = terark::fstring("hello world fstring!");
    
    printf("str1 compare str2 = %d\n", strcmp(str1.data(), str2.data()));
    
    printf(" str1.c_str() = %s \n", str1.c_str());
    
    // convert non-fstring key into fstring
    int i = 100;
    terark::fstring key = terark::db::Schema::fstringOf(&i);
    printf("key(i=100) = %s\n", key.c_str());
}
