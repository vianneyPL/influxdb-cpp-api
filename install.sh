git submodule init
git submodule update
mkdir -p build
cd build
cmake -DCPP-NETLIB_BUILD_SHARED_LIBS=OFF -DCPP-NETLIB_BUILD_TESTS=OFF -DCPP-NETLIB_BUILD_EXAMPLES=OFF -DCPP-NETLIB_ENABLE_HTTPS=OFF ..
make influxdb-api-test
cd ..
