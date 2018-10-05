// #include <iostream>

// int main (void)
// {
// while(!kbhit())
// {
//   //do your work
// }
// }

// Compile using g++ -std=c++11 main.cpp -o i2c
#include <iostream>
#include <unistd.h>   // close
#include <fcntl.h>    // O_RDWR
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>  // I2C_SLAVE
#include <chrono> // tijd
#include <thread>

using namespace std;

int main(void) {
    while (1)
    {
  const std::string DEVICE = "/dev/i2c-1";
  const unsigned int BUFFER_SIZE = 10;

  int i2cfile;
  if ((i2cfile = open(DEVICE.c_str(), O_RDWR)) < 0) {
      cout << "Could not open bus" << endl;
      exit(1);
  }
  cout << "Successfully opened the i2c bus" << endl;

  const int SLAVE_ADDRESS = 0x48;          // The I2C address of the slave device
  if (ioctl(i2cfile, I2C_SLAVE, SLAVE_ADDRESS) < 0) {
      cout << "Failed to acquire bus access and/or talk to slave." << endl;
      exit(1);
  }
  cout << "Ready to communicate with slave device" << endl;

  char buffer[BUFFER_SIZE] = { 0 };
  if (read(i2cfile, buffer, 2) != 2) {
      cout << "Failed to read from the i2c device." << endl;
  } else {
      cout << "Read from device: ";
      double temperature = ((buffer[0] << 8) | (buffer[1])) / 256.0;
      cout << "The current temperature is " << temperature << " degrees Celsius" << endl;
  }

  // Make sure to close the handle
  close(i2cfile);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  return 0;
}