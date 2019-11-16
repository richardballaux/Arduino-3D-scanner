%      ******************************************************************
%      *                                                                *
%      *                                                                *
%      *    Example MATLAB program that receives data from an Arduino   *
%      *                                                                *
%      *                                                                *
%      ******************************************************************


%
% NOTE: While this is running, you can not re-program the Arduino.  You must exit 
% this MATLAB program before downloading a sketch to the Arduino.
%


%
% Set the name of the serial port.  Determine the name as follows:
%	1) From Arduino's "Tools" menu, select "Port"
%	2) It will show you which Port is used to connect to the Arduino 
%
% For Windows computers, the name is formatted like: "COM6"
% For Apple computers, the name is formatted like: "/dev/tty.usbmodemfa141" 
%
arduinoComPort = 'COM8';


%
% Set the baud rate
% NOTE1: The baudRate for the sending and receiving programs must be the same!
% NOTE2: Set the baudRate to 115200 for faster communication
%
baudRate = 9600;


%
% open the serial port, close it first in case it was previously open
%
fclose(instrfind({'Port','Status'},{arduinoComPort,'open'}));
serialPort = serial(arduinoComPort, 'BAUD', baudRate);
fopen(serialPort);
fprintf(serialPort, '\n');



%
% initialize a timeout in case MATLAB cannot connect to the arduino
%
timeout = 0;

figure;
ylabel('y-axis');
xlabel('x-axis');
zlabel('z-axis');
title('plot1');
xvalues = [];
yvalues = [];
zvalues = [];

%
% main loop to read data from the Arduino, then display it
%
while timeout < 500

    %
    % check if data was received
    %
    while serialPort.BytesAvailable > 0
        %
        % reset timeout
        %
        timeout = 0;
        
        %
        % data was received, convert it into array of integers
        %
        %input = fscanf(serialPort)
        values = eval(strcat('[',fscanf(serialPort),']'));

        %
        % if you want to store the integers in four variables
        %
        distance = values(1);
        angleHor = values(2);
        angleVer = values(3);
        
        xcoor = distance*sind(angleVer)*cosd(angleHor)
        ycoor = -distance*sind(angleVer)*sind(angleHor)
        zcoor = distance*cosd(angleVer)
        
        xvalues = [xvalues , xcoor];
        yvalues = [yvalues , ycoor];
        zvalues = [zvalues , zcoor];
        
        %
        % print the results
        %
        %disp(sprintf('distance,angleHor,angleVer = %d,%d,%d\n',[distance,angleHor,angleVer]));
        
    end
    pause(0.05);
    timeout = timeout + 1;
    scatter3(xvalues,yvalues,zvalues);

   
end


