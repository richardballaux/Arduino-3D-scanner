# Arduino-3D-scanner
This was a project for my Principles of Engineering Class during my fall semester in 2018 at Olin College of Engineering, Boston.

Me and my partner Viktor Deturck created a 3D scanner. We used an Arduino to read data from an IR sensor, which we first calibrated. Next we sent over the array of data to a MATLAB-script that plotted it live.

A video of the project working can be found with this [link ](https://youtu.be/TDlxW20hSGY "YouTube Video").


## The full development process:

### The connection to the sensor
The first thing we did when we started the project was to check how we needed to connect the sensor to the Arduino. To do this in a safe way, without breaking the Arduino or the sensor, we first read in the datasheet provided. It was stated that the sensor was operable with an input-voltage of 5V and consumes only up to 33mA which the Arduino can supply. The output of the sensor was an analog voltage value under 5V which the Arduino can easily measure.



*Figure 1: Getting function of datasheet*
![alt text](https://github.com/richardballaux/Arduino-3D-scanner/blob/master/Pictures/Calibration.png "Getting function of datasheet")

To calibrate the sensor we took the datapoints from the graph in the datasheet of the sensor and made numerical values for them. (Figure 1)
Next we fitted an exponential curve to the values with the curve fitting tool of MATLAB. (Figure 2)

With that function we could calculate a distance out of an input voltage. We calculated the voltage out of the numerical analogRead-value with our self-made mapping function. We did this because the built-in mapping returns integers and this was not precise enough. Later on we would give these distances to the computer.

After the coding we compared our values with actual distances we measured with a ruler as calibration. We found a slight calibration error, which wouldn’t have that much of an influence on the actual plotting of the points. The graph can be seen in figure 3.

![alt text](https://github.com/richardballaux/Arduino-3D-scanner/blob/master/Pictures/fittingFunction.png "Fitting a function")
*Figure 2: Exponential function in MATLAB*



![alt text](https://github.com/richardballaux/Arduino-3D-scanner/blob/master/Pictures/measureError.png "Measurement error")
*Figure 3: Error on measurements*

The design of the setup
Next we started to design the setup for the pan and tilt mechanism. We decided to go for a 3D-printed design because we didn’t 3D-print a lot yet and we really wanted to try it. We succeeded rather easily in this task, the prints were good enough from the first try. The spacing for the holes was not always ideal, but this was easily fixed with a bit of filing. We used the same setup for both the first 1 line-scanner, not using the servo controlling the vertical position of the sensor, because this was the most convenient way to do it. We designed a base with a hole for the ‘horizontal’ servo, an L-bracket to put on the first servo with a hole for the second, ‘vertical’ sensor, and a final L-bracket to mount the sensor on this last servo. We put everything together with screws, nuts and bolts.

![alt text](https://github.com/richardballaux/Arduino-3D-scanner/blob/master/Pictures/finalScanner.png "Final scanner")
*Figure 4: Finalized scanner*

![alt text](https://github.com/richardballaux/Arduino-3D-scanner/blob/master/Pictures/finalRender.png "Final render")
*Figure 5: 3D rendering of the scanner in SolidWorks*

Also the design of the circuit was straight forward. We connected the output of the sensor to analog pin A0 and the datapins of the servo’s to PWM-enabled pin 10 and 11 of the Arduino. In the datasheet was also stated that a fast change of distance could cause a rather high current, so we put also put in a condensator to compensate for this. This also helps to make the servo’s move smoother. The 5V and ground terminals of the components can be connected to the 5V and ground pins of the Arduino directly.

### The visualization of the data with MATLAB
We chose to visualize our data in MATLAB because we knew that it has a built in 3D plotting function. First we tried to get the Serial data from the Arduino into MATLAB. We did this by using the example code that was provided. Through serial data the Arduino passed: the measured distance ( an integer in centimeter, the horizontal angle ( where 90 degrees is straight ahead and 0 degrees is totally to the left) and the vertical angle (where 90 degrees is straight ahead and 0 degrees is straight up). All these values are separated by a comma and by a newline at the end. Every time a new value came into the computer in MATLAB, we calculated the x,y,z-coordinates and stored them into a vector-array. And finally every loop in MATLAB the vector-arrays are plotted in a ‘scatter3’-plot, which gave us a live plotting of our letter.



### The final result
Here we scanned an R made out of cardboard which stood in front of a flat carboard sheet. Here the x-axis is flipped in the wrong direction.

[![Youtube Video](https://img.youtube.com/vi/TDlxW20hSGY/0.jpg)](https://www.youtube.com/watch?v=TDlxW20hSGY)
