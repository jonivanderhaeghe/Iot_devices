// Compile using g++ -std=c++11 main.cpp -o i2c
#include <iostream>
#include <unistd.h>   // close
#include <fcntl.h>    // O_RDWR
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>  // I2C_SLAVE
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<string>

using namespace std;

int main(void) {
  const std::string DEVICE = "/dev/i2c-1";
  const unsigned int BUFFER_SIZE = 10;

  int i2cfile;
  if ((i2cfile = open(DEVICE.c_str(), O_RDWR)) < 0) {
      cout << "Could not open bus" << endl;
      exit(1);
  }
  cout << "Successfully opened the i2c bus" << endl;

  const int SLAVE_ADDRESS = 0x14;          // The I2C address of the slave device
  if (ioctl(i2cfile, I2C_SLAVE, SLAVE_ADDRESS) < 0) {
      cout << "Failed to acquire bus access and/or talk to slave." << endl;
      exit(1);
  }
  cout << "Ready to communicate with slave device" << endl;
  cout << "\n ";

        char hello [] = "hello world, gastjes";
        char buffer [6] = {0X00, 0x04};
        char buffer1 [] = {0x03};
        sleep(1);

        for (int i = 0; i< strlen(hello); i++)
        {
            if ((i%4)==0)
            {
                buffer[1]++;
            }

            buffer [i+2] = hello [i];
            
            // buffer[(i%4)+2] = strlen(hello[i]);
            // buffer [i+2] = hello [i];

            if ((i%4)==3 || i == strlen(hello))
            {
                write(i2cfile, buffer, 6);
                sleep(1);
                write(i2cfile, buffer1, 1);
            }
        
        }
        // sleep(1);
        // char buffer1 [] = {0x03};
        // write(i2cfile, buffer1, 1);

        cout << "De waarde van in het geheugen is: " << endl;
        for(int i = 0; i< strlen(hello)+2; i++)
        {
            cout << (char) buffer [i];

        };
        cout << "\n ";
  // Make sure to close the handle
  close(i2cfile);
  return 0;
}