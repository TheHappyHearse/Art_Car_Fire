import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)


latchPin = 27
clockPin = 17
dataPin = 22

oneUp = 0
twoUp = 5
thrUp = 6
oneDn = 13
twoDn = 19
thrDn = 26

fireBtn = 21

GPIO.setup(latchPin,GPIO.OUT)
GPIO.setup(clockPin,GPIO.OUT)
GPIO.setup(dataPin,GPIO.OUT)

#Init Fire Button
GPIO.setup(fireBtn, GPIO.IN)
#TODO: Map to event listener, tried 3/1/2020 no luck


GPIO.setup(oneUp,GPIO.IN)
GPIO.setup(oneDn,GPIO.IN)
GPIO.setup(twoUp,GPIO.IN)
GPIO.setup(twoDn,GPIO.IN)
GPIO.setup(thrUp,GPIO.IN)
GPIO.setup(thrDn,GPIO.IN)

LOW = 0
HIGH = 1

#GPIO.output(oneUp,LOW)
#GPIO.output(oneDn,LOW)
#GPIO.output(twoUp,LOW)
#GPIO.output(twoDn,LOW)
#GPIO.output(thrUp,LOW)
#GPIO.output(thrDn,LOW)

#Contents to be pushed to shift register
#This acts as a memory of on/off values. If for example, an Indicator LED is activated, unless cleared, each subsequent push will maintain the on selection
seq = [ 0,0,0,0,
        0,0,0,0,
        0,0,0,0,
	0, #Solenoid 1
        0, #Solenoid 2
        0, #Indicator LED 1
        0 ] #Indicator LED 2


LIGHTPIN = dataPin
def togglePin():
  GPIO.output(LIGHTPIN,LOW)
  time.sleep(1)
  GPIO.output(LIGHTPIN,HIGH)
  time.sleep(1)

def test1():
  print('Test')
  GPIO.output(latchPin,LOW)
  GPIO.output(clockPin,LOW)
  GPIO.output(dataPin,HIGH)
  GPIO.output(clockPin,HIGH)
  GPIO.output(clockPin,LOW)
  GPIO.output(latchPin,HIGH)
  GPIO.output(latchPin,LOW)
  time.sleep(1)
  GPIO.output(dataPin,LOW)
  GPIO.output(clockPin,HIGH)
  GPIO.output(clockPin,LOW)
  GPIO.output(latchPin,HIGH)
  GPIO.output(latchPin,LOW)
  time.sleep(1)

def latch():  #Commit pending changes, i.e. fire
  GPIO.output(latchPin,HIGH)
  GPIO.output(latchPin,LOW)

def clock(): #Accept data pin value into register
  GPIO.output(clockPin,HIGH)
  GPIO.output(clockPin,LOW)

def push():
  for x in range(16): #16 GPIO outputs on ShiftRegister board
    GPIO.output(dataPin,seq[x])
    clock() #Push value to register
  latch() #Activate it

def clearRegisters():
  for x in range(16):
    seq[x] = LOW

def fireLeft(length):
  seq[12] = HIGH
  seq[14] = HIGH
  push()
  time.sleep(length)
  seq[14] = LOW
  seq[12] = LOW
  push()

def fireRight(length):
  seq[15] = HIGH
  seq[13] = HIGH
  push()
  time.sleep(length)
  seq[15] = LOW
  seq[13] = LOW
  push()

def fireBoth(length):
  seq[15] = HIGH
  seq[14] = HIGH
  seq[13] = HIGH
  seq[12] = HIGH
  push()
  time.sleep(length)
  seq[15] = LOW
  seq[14] = LOW
  seq[13] = LOW
  seq[12] = LOW
  push()

def sequence1():
  fireLeft(1)
  fireRight(1)

def sequence2():
  fireLeft(1)
  time.sleep(.25)
  fireLeft(1)
  time.sleep(.25)
  fireLeft(1)
  time.sleep(.25)

def sequence3():
  fireRight(1)
  time.sleep(.25)
  fireRight(1)
  time.sleep(.25)
  fireRight(1)
  time.sleep(.25)

def sequence4():
  fireRight(1)
  fireLeft(1)
  time.sleep(.25)
  fireBoth(1)
  time.sleep(.25)
  fireBoth(1)
  time.sleep(.25)

#All sequences must preceed this statement
def detectInput():
  input = 'NNN'
  one = 'N'
  two = 'N'
  three = 'N'

  if(GPIO.input(oneUp) == GPIO.HIGH):
    one = 'U'
  elif(GPIO.input(oneDn) == GPIO.HIGH):
    one = 'D'

  if(GPIO.input(twoUp) == GPIO.HIGH):
    two = 'U'
  elif(GPIO.input(twoDn) == GPIO.HIGH):
    two = 'D'

  if(GPIO.input(thrUp) == GPIO.HIGH):
    three = 'U'
  elif(GPIO.input(thrDn) == GPIO.HIGH):
    three = 'D'
  input = one + two + three
#  print('In method ' + input)

  if(input == 'NNN'):
    print('All neutral')
    sequence1()
  elif(input == 'DNN'):
    print('Down N N')
    sequence2()
  elif(input == 'DDN'):
    print('DDN')
    sequence3()
  elif(input == 'DDD'):
    print('DDD')
  elif(input == 'NDD'):
    print('NDD')
  elif(input == 'NND'):
    print('NND')
    sequence3()
  elif(input == 'NDN'):
    print('NDN')
    sequence2()
  elif(input == 'UUU'):
    print('UUU')
  elif(input == 'UUN'):
    print('UUN')
  elif(input == 'UNN'):
    print('UNN')
  elif(input == 'UDN'):
    print('UDN')
  elif(input == 'UND'):
    print('UND')
  elif(input == 'UDD'):
    print('UDD')
  elif(input == 'DUN'):
    print('DUN')
  elif(input == 'DUU'):
    print('DUU')
  elif(input == 'DNU'):
    print('DNU')
  else:
    print('Unsupported ' + input)

def detectAndFire():
  if(GPIO.input(fireBtn) == GPIO.HIGH):
    detectInput()
#    digitalwrite(fireBtn, GPIO.LOW)
    time.sleep(3)

#Additional setup code
clearRegisters()
push()

while(1):
#  test1()
#  sequence1()
#  togglePin()
  detectAndFire()

GPIO.cleanup()
