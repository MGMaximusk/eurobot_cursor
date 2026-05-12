import serial
import csv

# open CSV file
logging = open('r0_64_4ma_1.csv', mode='w', newline='')
# use DictWriter to write a header and dict dicts
header = ["F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "Clear", "NIR"]
writer = csv.DictWriter(logging, fieldnames=header)
writer.writeheader()

ser = serial.Serial('/dev/ttyACM1')
ser.flushInput()

count = 0
dict = {k: 0 for k in header}
while True:
	ser_bytes = ser.readline()
	decoded = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
	message = decoded.split(':')
	vals = [message[0]]
	if (len(message) > 1):
		tmp = message[1].split(',')
		for i in range(len(tmp)):
			vals.append(tmp[i])
		#print(vals)

		for i in range(len(header)):
			if (header[i] in vals[0]):
				dict[header[i]] = vals[1]
				count += 1
		
		if count >= 10:
			count = 0
			writer.writerow(dict)
			dict = {k: 0 for k in header}
			continue
		print(dict)
	
ser.close()
logging.close()
