/* C++ exception handling example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "main.h"

#include <iostream>
#include <cstdlib>
#include <thread>
#include "esp_log.h"
#include "gpio_cxx.hpp"

using std::cout;
using std::endl;
using std::runtime_error;
using namespace idf;

/* A simple class which may throw an exception from constructor */
class Throwing
{
public:
  Throwing(int arg)
      : m_arg(arg)
  {
    cout << "In constructor, arg=" << arg << endl;
    if (arg == 0)
    {
      throw runtime_error("Exception in constructor");
    }
  }

  ~Throwing()
  {
    cout << "In destructor, m_arg=" << m_arg << endl;
  }

protected:
  int m_arg;
};

/* Inside .cpp file, app_main function must be declared with C linkage */
extern "C" void app_main(void)
{
  cout << "app_main starting" << endl;

  try
  {
    Throwing obj1(42); /* This will succeed */
    Throwing obj2(0); /* This will throw an exception */

    cout << "This will not be printed" << endl;
  }
  catch (const runtime_error &e)
  {
    cout << "Exception caught: " << e.what() << endl;
  }

  try
  {
    GPIO_Output gpio(GPIONum(4)); // Exception when pin parameter is invalid

    while (true)
    {
      printf("LED ON\n");
      gpio.set_high();
      std::this_thread::sleep_for(std::chrono::seconds(1));

      printf("LED OFF\n");
      gpio.set_low();
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }
  catch (GPIOException &e)
  {
    printf("GPIO exception occurred: %s\n", esp_err_to_name(e.error));
    printf("stopping.\n");
  }

  cout << LOG_TAG << ": app_main done" << endl;
}