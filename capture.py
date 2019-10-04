import serial
from PIL import Image
import time
import sys

if len(sys.argv) > 1:
  port = sys.argv[1]
else:
  port=raw_input("Which serial port to communicate on?")

print("Using port {}".format(port))
width=320
height=240

def read_image(serial):
  print("Reading Image...")
  data = serial.read(width * height)
  print("Received Image...")
  image = Image.frombytes('P', (width, height), data)
  image.save('./image.bmp')

  ok = serial.read_until('***')
  print(("Arduino says {}".format(ok)))

ser = serial.Serial(
  port=port,
  baudrate=1000000,
  parity=serial.PARITY_NONE,
  stopbits=serial.STOPBITS_ONE,
  bytesize=serial.EIGHTBITS)

print('Wait for Arduino to set itself up...')
time.sleep(5)

if ser.isOpen() == False:
  ser.open()
  print('Serial opened')
else:
  print('Serial already open')


while True:
  print("Waiting for RDY from Arduino...")
  print(("Arduino says {}".format(ser.read_until('RDY'))))
  inp = raw_input('Hit enter to fetch image, any other key to exit >')
  if inp == "":
    ser.write('X')
    ser.flush()
    read_image(ser)
  else:
    break

ser.close()
print('Serial closed')