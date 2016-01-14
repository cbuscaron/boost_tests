#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include<boost/date_time/posix_time/posix_time.hpp>

using namespace std;

void print(const boost::system::error_code& )
{
 std:cout <<"Hello World Asynch" << std::endl;
}


int main(){
  boost::array<int, 4> arr = {{1,2,3,4}};
  cout << "hi" << arr[0] << '\n';


  boost::asio::io_service io;
  
  //synchronous timer 
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
  //t.wait();
  //std::cout << "Hello World"<<std::endl;

  t.async_wait(&print);

  io.run(); //asio library callbacks handler will only run be called from threads that 
            // currently calling io_service::run()

  return 0;
}
