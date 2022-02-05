#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <functional>
#include <list>
#include <chrono>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

//infinite recursion

class Async
{
private:
	boost::asio::io_service io_service_;
public:
	void start()
	{
		//io_service_.post(boost::bind(func2, 123)); right
		//io_service_.post(&Async::proc1, this); wrong

		io_service_.post(boost::bind(&Async::proc1, this));

		io_service_.run();	
	}

	void proc1()
	{
		std::cout<<"hello\n";
		io_service_.post(boost::bind(&Async::proc2, this));
	}

	void proc2()
	{
		std::cout<<"not\n";
		io_service_.post(boost::bind(&Async::proc1, this));
	}

};



int main()
{
	
	Async obj;
	obj.start();

	return 0;
}