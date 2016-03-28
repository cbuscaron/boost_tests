/*
  Simple Thread Function

  * Part of "Threading with Boost - Part I: Creating Threads", published at:

      http://antonym.org/boost

  Copyright (c) 2009 Gavin Baker <gavinb@antonym.org>
  Published under the MIT license, see LICENSE for details
 */

// g++ -o simple simple.cpp -lboost_thread -lboost_system

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include <boost/thread.hpp>
#include <boost/ref.hpp>
#include <boost/date_time.hpp>

void workerFunc(std::vector<std::string>& msgs, int i)
{
    boost::posix_time::seconds workTime(i);

    std::cout << "Worker" << boost::to_string(i) << ": running" << std::endl;

    // Pretend to do something useful...
    boost::this_thread::sleep(workTime);

    std::string words("Worker-" + boost::to_string(i) + ": finished");

    msgs.push_back(words);

    std::cout << words << std::endl;
}



/*

 std::vector<boost::thread *> threads(std::min(CORES, count));

 for (size_t i = 0; i < threads.size(); ++i) { // Start appropriate number of threads
    threads[i] = new boost::thread(threadFunction, i);
  }


  for (size_t i = 0; i < threads.size(); ++i) { // Wait for all threads to finish
    threads[i]->join();
    delete threads[i];
    --count;
  } */


//boost::thread t(boost::bind(&SomeClass::OtherMethod,this, boost::ref(v))
int main(int argc, char* argv[])
{

    std::vector<std::string> msgs;
    std::cout << msgs.capacity() <<std::endl;
    std::cout << msgs.size() <<std::endl;

    msgs.reserve(5);
    std::cout << msgs.capacity() <<std::endl;
    std::vector<boost::thread *> threads(5);

    std::cout << "main: startup" << std::endl;

    //std::vector<boost::thread> workerThread; //(workerFunc);

    for (size_t i = 0; i < threads.size(); i++)
    {
        threads[i] = new boost::thread(workerFunc, boost::ref(msgs), i);
        std::cout << "kicked off thread:" << boost::to_string(i) << std::endl;
    }

    for (size_t i = 0; i < threads.size(); i++)
    {
        std::cout << "waiting to join thread:"  << boost::to_string(i) << std::endl;
        threads[i]->join();
        delete threads[i];
    }

    //std::cout << "main: waiting for thread" << std::endl;

    //workerThread.join();

    std::cout << "main: done" << std::endl;
    std::cout << msgs.size() << std::endl;

    for(size_t i = 0; i < msgs.size(); i++)
    {
        std::cout << msgs.at(i) << std::endl;
    }

    return 0;
}
