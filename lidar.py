import serial, time
from pprint import pprint ## don't think this is needed anymore
from math import pi,cos,sin
import matplotlib.pyplot as pyplot

com_port  = 'COM11'
baud_rate = 115200
arduino = serial.Serial('COM10', 115200)

scansPerformed = 0

    
def minimum_value(x):
    ##set to maximum range to avoid edge case of first element being -1, because then if statement will not execute
    min_val = 6001 

    for i in x[1:]:
        
        if i < min_val and i >= 0:
            
            min_val = i

    return min_val


##begin
ser = serial.Serial(com_port,baud_rate)
print(ser.name) 
print("Press CTRL+C to stop data collection")

dist_mm_store = [-1]*181

##debug
#print len(dist_mm_store)

while True:
    try:
        b = (ord(ser.read(1))) ##initial read
        dati = []
        #print("initial read")
        
        while True:
            ##250 == FA, FA is the start value - it's constant
            ##Each data packet is 22 bytes, > 20 means len(dati) == at least 21
            if b==(250) and len(dati)>20: 
                break

            ##add data to list, read again
            dati.append(b)
            b = (ord(ser.read(1)))
        
        if len(dati)==21:
            #print(dati)
            ##index data packets go from 0xA0 (160) to 0xF9(359). Subtract 160 to normalize scale of data packets from 0 to 90.
            dati[0]=((dati[0])-160)  
           
            for i in (1,2,3,4):
                ##128 is an error code
                if dati[i*4] != 128:
                    ##if good data, convert value in dati to value in mm. code found online
                    dist_mm = dati[4*i-1] | (( dati[4*i] & 0x3f) << 8) 
                                        
                    ##dati[0] is index of each packet from 0 to 90. *4 for a value from 1 - 360, and cycle through the 4 data packets from that point at index
                    ##e.g. dati[0] is 30. 30 * 4 = 120, then the values being read are 121, 122, 123, 124
                    angle = dati[0]*4+i+1 

                    ##adjust values by 2
                    if angle < 181:
                        dist_mm_store[angle] = dist_mm
                    #print("%s,%s\n" % (angle,dist_mm))

                    ##debug
                    #print(angle,dist_mm)

                    ##plot
                    #plot_data(angle,dist_mm)


            ##debugging the speed of the DC motor, converted to RPM. code found online.
            #speed_rpm = float( dati[1] | (dati[2] << 8) ) / 64.0
            #if speed_rpm < 185 or speed_rpm > 315: # thresh-holds by troubleshooting
                #print "Speed Error:",speed_rpm

        ##finding minimum distance in 180 degrees of vision, split into 45 degree quadrants    
        quad1 = minimum_value(dist_mm_store[0:44])
        quad2 = minimum_value(dist_mm_store[45:89])
        quad3 = minimum_value(dist_mm_store[90:134])
        quad4 = minimum_value(dist_mm_store[135:180])

        #print (dist_mm_store[0:44])

        if (scansPerformed % 360 == 0):
            print (quad1,"\t",quad2,"\t",quad3,"\t",quad4, "\tScan", scansPerformed)

            ##test

            minVal = 6001
            minQuad = 0

            if minVal > quad1:

                minVal = quad1
                minQuad = "Quad1"

            if minVal > quad2:

                minVal = quad2
                minQuad = "Quad2"

            if minVal > quad3:

                minVal = quad3
                minQuad = "Quad3"

            if minVal > quad4:

                minVal = quad4
                minQuad = "Quad4"

            print("The closest point is in", minQuad, "with a distance of", minVal, "mm")
            arduino.write(minVal)
            
            scansPerformed += 1

    except KeyboardInterrupt:

        print ("Data Collection Stopped")
        ser.close()

