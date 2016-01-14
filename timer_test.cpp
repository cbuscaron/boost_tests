#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
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

/*
class printer
{
public:
  printer(boost::asio::io_service& io) : strand_(io),
                                         timer1_(io, boost::posix_time::seconds(1)),
                                         timer2_(io, boost::posix_time::seconds(1)),
                                         count_(0)
  {
    timer1_.async_wait(strand_.wrap(boost::bind(&printer::print_one, this)));
    timer2_.async_wait(strand_.wrap(boost::bind(&printer::print_two, this)));
  }

  ~printer()
  {
    std::cout << "Final count is " << count_ <<std::endl;
  }

  //in mltithreaded programs the handlers for asynchronous operations should be synchronised if
  // they access shared resources as in the case of std::cout and count_ in the handlers/functions below

  void print_one()
  {
    if (count_ < 10)
    {
      std::cout << "Timer 1: " << count_ << std::endl;
      ++count_;
      
      timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
      timer1_.async_wait(strand_.wrap(boost::bind(&printer::print_one, this)));
    }
  }

  void print_two()
  {
    if(count_ < 10)
    {
      std::cout << "Timer 2: " << count_ << std::endl;
      ++count_;

      timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
      timer2_.async_wait(strand_.wrap(boost::bind(&printer::print_two, this)));
    }
  }

private:
  boost::asio::io_service::strand strand_;
  boost::asio::deadline_timer timer1_;
  boost::asio::deadline_timer timer2_;
  int count_;
 
  }; */


class printer
{
public:
  printer(boost::asio::io_service& io)
    : strand_(io),
      timer1_(io, boost::posix_time::seconds(1)),
      timer2_(io, boost::posix_time::seconds(1)),
      count_(0)
  {
    timer1_.async_wait(strand_.wrap(boost::bind(&printer::print1, this)));
    timer2_.async_wait(strand_.wrap(boost::bind(&printer::print2, this)));
  }

  ~printer()
  {
    std::cout << "Final count is " << count_ << std::endl;
  }

  void print1()
  {
    if (count_ < 10)
    {
      std::cout << "Timer 1: " << count_ << std::endl;
      ++count_;

      timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
      timer1_.async_wait(strand_.wrap(boost::bind(&printer::print1, this)));
    }
  }

  void print2()
  {
    if (count_ < 10)
    {
      std::cout << "Timer 2: " << count_ << std::endl;
      ++count_;

      timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
      timer2_.async_wait(strand_.wrap(boost::bind(&printer::print2, this)));
    }
  }

private:
  boost::asio::io_service::strand strand_;
  boost::asio::deadline_timer timer1_;
  boost::asio::deadline_timer timer2_;
  int count_;
};


int main()
{
  boost::asio::io_service io;
  
  printer p(io);

  boost::thread t(boost::bind(&boost::asio::io_service::run, &io));
  
  io.run();
  t.join();


  /*
  int count = 0;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
  t.async_wait(boost::bind(print,
        boost::asio::placeholders::error, &t, &count));

  io.run();

  std::cout << "Final count is " << count << std::endl;
  */


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
