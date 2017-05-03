#include "api.hpp"

using api = idb::api::api;
using tag = idb::api::measurement::tag;
using field = idb::api::measurement::field;
using measurement = idb::api::measurement::measurement;

int main(int argc, char *argv[])
{
    try {
        api idb("http://localhost:8086", "benchmark");

        idb.create();

        measurement mes("test");
        mes << field("value", "3")
            << field("value2", "4")
            << tag("tag_key", "tag_value");

        idb.create(mes);

        idb.select(mes);

        // idb.drop(mes);
        
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}