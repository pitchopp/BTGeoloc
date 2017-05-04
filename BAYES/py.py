import webbrowser

webbrowser.open("file:///C:/Showcase/BTGeoloc/front/DisplayPosition/index.html?70")
# import serial

# ser = serial.Serial(port = 'COM1:', baudrate = 9600)
# ser.open()

# if not ser.isOpen():
# 	print 'Erreur d\'ouverture du port !'
# 	exit(1)
	
# fo = open('output.txt', 'w')
# if not fo:
# 	print 'Erreur d\'ouverture du fichier !'
# 	exit(1)

# try:
# 	while 1 :
# 		line = ser.readline()
# 		fo.write(line)
# except (KeyboardInterrupt, SystemExit):
# 	ser.close()
# 	fo.close()
# except:
# 	print 'Erreur interne !'