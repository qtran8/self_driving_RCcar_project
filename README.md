# self_driving_RCcar_project
 ## I. How to open and run the project
### 1. Install library in Arduino IDE
   * In the desciption of each file, you will find "All libraries needed for the RC car project" or "These are Arduino files for each function" or "Valuable Observations and Notes"
   * Download all the libraries with the description of "All libraries needed for the RC car project" and save those files in your prefered directory.
   * Open Arduino IDE, under Sketch, drag your mouse pointer to the "Include library" and then click "Add .zip library". Choose all the libaries to add.
   * It should show up something like "Library named.... successfully added" indicating successful library addition.

### *** Important! Read this carefully!:
1. For the purpose of fixing the missing libraries that should have been in the IMU zip file from the online websites. After install all the libraries in Arduino IDE in the previous step, follow these steps to properly install IMU library with no errors for implementing IMU:
   * Click in Document tab (For Window), you shall see the Arduino folder that contains all the libraries that you just installed from the previous step.
   * Under the file named "Adafruit_BNO055-master", copy the file named "utility" and paste that into the IMU folder in the same "Document/Arduino" directory.
   * Then delete that library file named "Adafruit_BNO055-master"; otherwise, it will conflict headers between "Adafruit_BNO055-master" and "IMU" libraries.


2. Read the file in Github named "colors, pins, ports and parts record" and check if all the pins and ports connects correctly on the chips and Arduino board before powering and running the codes. 
3. Regulator's left pin is 12VDC input, middle pin is 5V output and the right pin is ground. 
4. The code of the library named "modified_SparkFun_TB6612FNG_Arduino_Library-master" was adjusted from the original code from the manufacturers to better turn left and turn right. 

### 2. Read the log journal included in Github to see if any questions answered. 
Log Journal provides many important notes on how different components are used and its limitation.

### 3. Open each function file to test it and then open the most compact file named "Obstacle_Avoidance_GPS__IMU_and_wheels_controls" which includes all the functions in it.

## II. Problems need improvement
   1. Obstacle avoidance algorithm:
      The code to recognize the closest "real" objects does not work properly and it is possibly due to a small number of array elements. This leads to wrongly detect multiple objects and cannot process whichever objects are closer given 2 or more objects on one side.
   2. IMU sensor does not give a correct reading for the North (if compared to the compass). This may be due to the metal chassis right below the breadboard and other running wire that interferes with the magnets inside the IMU causing wrong reading.
   3. The battery mounted on the car needs to be checked again. On December 10, 2021, the battery died out very fast ( less than 30 minutes after being fully charged). It may need to be replaced.
