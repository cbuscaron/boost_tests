#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include<boost/date_time/posix_time/posix_time.hpp>

using namespace std;

void print(const boost::system::error_code& )
{
 std:cout <<"Hello World Asynch" << std::endl;
}

//pointer to a timer object & counter to stop program

void print(const boost::system::error_code& /*e*/,
    boost::asio::deadline_timer* t, int* count)
{
  if (*count < 5)
  {
    std::cout << *count << std::endl;
    ++(*count);

    t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
    t->async_wait(boost::bind(print,
          boost::asio::placeholders::error, t, count));
  }
}

int main()
{
  boost::asio::io_service io;

  int count = 0;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
  t.async_wait(boost::bind(print,
        boost::asio::placeholders::error, &t, &count));

  io.run();

  std::cout << "Final count is " << count << std::endl;

  /*
  //synchronous timer 
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
  //t.wait();
  //std::cout << "Hello World"<<std::endl;

  t.async_wait(&print);

  io.run(); //asio library callbacks handler will only run be called from threads that 
            // currently calling io_service::run()
  */

  return 0;
}
