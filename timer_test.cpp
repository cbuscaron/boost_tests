#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include<boost/date_time/posix_time/posix_time.hpp>

using namespace std;

int main(){
  boost::array<int, 4> arr = {{1,2,3,4}};
  cout << "hi" << arr[0] << '\n';


  boost::asio::io_service io;

  boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
  t.wait();
  std::cout << "Hello World"<<std::endl;

  return 0;
}
