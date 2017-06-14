git submodule init
git submodule update
# cp -R thirdparty/cpp-netlib/deps/asio/asio/include/asio* /usr/local/include/.
mkdir -p build
cd build
cmake ..
make influxdb-api-test
cd ..
