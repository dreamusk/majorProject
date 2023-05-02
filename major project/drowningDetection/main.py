import cv2 as cv #importing libraries
import numpy as np
import telegram
import time
import requests
import serial

ser = serial.Serial('COM4',9600)
time.sleep(2)

videoCapture = cv.VideoCapture(0) #capturing video from webcam
prevCircle = None 
dist = lambda x1,y1,x2,y2: (x1-x2)**2 + (y1-y2)**2 #defining distance function

while True: 
    ret, frame = videoCapture.read() #reading frame
    if not ret: break 

    grayFrame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY) #converting frame to grayscale
    blueFrame = cv.GaussianBlur(grayFrame, (17,17), 0) #blurring frame

    circles = cv.HoughCircles(blueFrame, cv.HOUGH_GRADIENT, 1.2, 100,param1=100, param2=30, minRadius=75, maxRadius=400) #detecting circles
    
    if circles is not None: 
        circles = np.uint16(np.around(circles)) #rounding circles
        circles1 = np.round(circles[0,:]).astype("int")
        global no
        no = len(circles1)
        print(no)
        b = ser.readline()
        print(b.decode())
        if no < int(b):
            ser.write("lift".encode())
            time.sleep(10)
            # 5883766043:AAEWt8VrR_-pMehPe1FYd1zOKf_oMMY33Ug
            telegram = "https://api.telegram.org/bot5883766043:AAEWt8VrR_-pMehPe1FYd1zOKf_oMMY33Ug/sendMessage?chat_id=1124761529&text="+"Alert! Alert!! Alert!!! \nSomeone is drowning"
            requests.post(telegram)
        chosen = None 
        for i in circles[0,:]: 
            if chosen is None: chosen = i 
            if prevCircle is not None: 
                if dist(chosen[0], chosen[1], prevCircle[0], prevCircle[1]) > dist(i[0], i[1], prevCircle[0], prevCircle[1]): 
                    chosen = i 
        #if distance between current circle and previous circle is less than distance between chosen circle and previous circle, set chosen circle to current circle
        cv.circle(frame,(chosen[0],chosen[1]), 1, (0,100,100), 3) #draw circle point
        cv.circle(frame,(chosen[0],chosen[1]), chosen[2], (255,0,0), 3) #draw circle
        prevCircle = chosen
    
    cv.imshow("circles", frame) #show frame

    if cv.waitKey(1) & 0xFF == ord('q'): break

videoCapture.release()
cv.destroyAllWindows() 