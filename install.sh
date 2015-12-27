BOOST_VERSION=1_60_0

# platform_manager() {
#     if command -v apt-get >/dev/null 2>&1; then
#         apt-get update
#         apt-get install git gcc g++ cmake jsoncpp
#     } else if command -v dnf >/dev/null 2>&1; then
#         #
#     } else if command -v yum >/dev/null 2>&1; then
#         #
#     } else {
#         exit 1
#     }
#     fi
# }

apt-get update
apt-get install git gcc g++ cmake libicu-dev

wget http://skylineservers.dl.sourceforge.net/project/boost/boost/1.60.0/boost_$BOOST_VERSION.tar.gz && tar zxvf boost_$BOOST_VERSION.tar.gz
cd boost_$BOOST_VERSION
./bootstrap.sh --with-libraries=program_options,test,system,regex,date_time,thread,filesystem,chrono,atomic
sudo ./b2 install
cd ~

git clone https://github.com/cpp-netlib/cpp-netlib.git
cd cpp-netlib
git submodule init && git submodule update
mkdir ~/cpp-netlib-build
cd ~/cpp-netlib-build
cmake ~/cpp-netlib
make -j4 && make install
cd ~


git clone https://github.com/christopher-henderson/Simple-CPP-Server.git
cd Simple-CPP-Server/example
export BOOST_ROOT=/usr/local/include
g++ server.cpp -I$BOOST_ROOT -I. -I$BOOST_ROOT/stage/lib -L/usr/local/lib -lboost_system -ljsoncpp -pthread
