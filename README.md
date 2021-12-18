# self_driving_RCcar_project
 ## I. How to open and run the project
### Install library in Arduino IDE
   * In the desciption of each file, you will find "All libraries needed for the RC car project" or "These are Arduino files for each function" or "Valuable Observations and Notes"
   * Download all the libraries with the description of "All libraries needed for the RC car project" and save those files in your prefered directory.
   * Open Arduino IDE, under Sketch, drag your mouse pointer to the "Include library" and then click "Add .zip library". Choose all the libaries to add.
   * It should show up something like "Library named.... successfully added" indicating successful library addition.

### *** Important! Read this carefully!:
1. We do this for the purpose of fixing the missing libraries that should have been in the IMU zip file from the online websites. After install all the libraries in Arduino IDE in the previous step, follow these steps to properly install IMU library with no errors for implementing IMU:
   * Click in Document tab (For Window), you shall see the Arduino folder that contains all the libraries that you just installed from the previous step.
   * Under the file named "Adafruit_BNO055-master", copy the file named "utility" and paste that into the IMU folder in the same "Document/Arduino" directory.
   * Then delete that library file named "Adafruit_BNO055-master"; otherwise, it will conflict headers between "Adafruit_BNO055-master" and "IMU" libraries.
## II. Problems need improvement
