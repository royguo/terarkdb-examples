#include <iostream>

#include <terark/db/db_table.hpp>
#include <terark/io/MemStream.hpp>
#include <terark/io/DataIO.hpp>
#include <terark/io/RangeStream.hpp>
#include <terark/lcast.hpp>


#include "user.hpp"
#include "terarkdb_test.hpp"

int main(int argc, char* argv[]){
    test_ns::User user = {};
    user.id = 100;
    user.name = "Roy Guo";
    std::cout<<user.id<<" "<<user.name<<std::endl;
    
    
    const char* dbtable = "/Users/royguo/RoysData/terark/terarkdb-api-examples/terarkdb-api-examples/db/user_table";
    
//    test_open_close_table(dbtable);
    
//    test_write_data(dbtable);
    
    test_update_data(dbtable);
    
//    test_range_search(dbtable);
    
//    test_point_search(dbtable);
    
//    test_utils();
    
    return 0;
}
