#include "api.hpp"

#include <string>

using api = idb::api::api;
using tag = idb::api::measurement::tag;
using str_field = idb::api::measurement::field<std::string>;
using double_field = idb::api::measurement::field<double>;
using int_field = idb::api::measurement::field<int>;
using measurement = idb::api::measurement::measurement;

int main(int argc, char *argv[])
{
    try {
        api idb("http://localhost:8086", "benchmark");

        idb.create();

        measurement mes("test");
        mes
            << tag("tag_key", "tag_value")
            << str_field("str_value", "3")
            << int_field("int_value", 4)
            << double_field("double_value", 4.4);

        measurement mes2("test");
        mes2
            << tag("tag_key", "tag_value")
            << str_field("str_value", "3")
            << int_field("int_value", 4)
            << double_field("double_value", 6.6);

        idb.create(mes);
        idb.create(mes2);

        idb.select(mes);

        // idb.drop(mes);
        
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}