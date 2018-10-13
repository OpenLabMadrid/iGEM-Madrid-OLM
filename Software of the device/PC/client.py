import sys
import glob
import serial
import time
import csv
import threading

from PyQt5 import QtWidgets,QtCore,QtGui
from PyQt5.QtWidgets import QTableWidget,QTableWidgetItem
from MainWindow import Ui_MainWindow
import json


def adjustSpeed (obj, obj2, obj3, int):
	
	obj.MSG["motors"][int]["speed"] = obj2.value()
	obj.MSG["motors"][int]["steps"] = obj3.value() * obj.CONFIG_["motors"][int]["m/s"]
	
def SerialSelector (obj,ser):

	ser.baudrate = 115200
	if ser.port != obj.SerialSelect.currentText():
		ser.close()
		ser.port = obj.SerialSelect.currentText()
		ser.open()
	
	if ser.is_open:
		obj.label_41.setText(ser.port + " opened")
	else:
		obj.label_41.setText("Error opening " + ser.port)
	
	ports = serial_ports()
	obj.SerialSelect.clear()
	obj.SerialSelect.addItems(ports)
	print(ser.port);
	
def SerialSend (obj, MSG, ser):
	if ser.is_open:
		string = json.dumps(MSG)
		ser.write(string.encode())
		
		obj.textEdit.moveCursor(QtGui.QTextCursor.End)
		obj.textEdit.insertPlainText(string + '\n')
	
		response = ""
		
		time.sleep(1)
		
		myFont = QtGui.QFont()
		
		obj.textEdit.insertHtml("<html><b>" + time.asctime() + " Hardware response:</b></html>\n")
		obj.textEdit.insertPlainText("\n")
		
		
		while (ser.in_waiting > 0):
			response = ser.readline()
				
		
			if response != "":
				obj.textEdit.moveCursor(QtGui.QTextCursor.End)
				obj.textEdit.insertPlainText(response.decode("utf-8"))
				response = ""
	else:
		print("ERROR: port is not open")
		
def configMotor (int, obj, obj2, string):
	obj.CONFIG_["motors"][int][string] = obj2.value()
	
def ManualSerialSend (obj, obj2, ser):
	SerialSend(obj, json.loads(obj2.text()), ser)
	obj2.clear()
	
def getFiles(obj):
	dlg = QtWidgets.QFileDialog()
	dlg.setNameFilter("csv(*.csv)")
	dlg.setFileMode(QtWidgets.QFileDialog.ExistingFile)
		
	if dlg.exec_():
		filenames = dlg.selectedFiles()
		obj.lineEdit_2.clear()
		obj.lineEdit_2.setText(str(filenames[0]))
		f = open(str(filenames[0]), 'r')
		with f:
			reader = csv.reader(f)
			rownum = 0
			obj.tableWidget.setColumnCount(3)
			for row in reader:
				if rownum != 0:
					obj.tableWidget.setRowCount(rownum+1)
					colnum = 0
					for col in row:
						obj.tableWidget.setItem(rownum-1,colnum, QTableWidgetItem(row[colnum]))
						colnum += 1
				else:
					colnum = 0
					for col in row:
						obj.tableWidget.setHorizontalHeaderItem(colnum, QTableWidgetItem(row[colnum]))
						colnum += 1
				rownum += 1
		obj.max_rows = rownum	
										
def B10click (obj,ser):
	if obj.waiting_ == True:
		obj.SendPause = -1
		obj.pushButton_11.setText("Send")
		obj.pushButton_10.setEnabled(True)
		obj.tabWidget.setTabEnabled(0,True)
		obj.tabWidget.setTabEnabled(1,True)
		obj.tabWidget.setTabEnabled(3,True)
		obj.SerialSelect.setEnabled(True)
		obj.t.cancel()
		obj.waiting_ = False
	else:
		SendProtocol(obj,ser)
	
def SendProtocol (obj, ser):

	if obj.lineEdit_2.text() != "":
	
		obj.pushButton_11.setText("Stop")
		obj.pushButton_10.setEnabled(False)
		obj.tabWidget.setTabEnabled(0,False)
		obj.tabWidget.setTabEnabled(1,False)
		obj.tabWidget.setTabEnabled(3,False)
		obj.SerialSelect.setEnabled(False)
					
		if obj.waiting_ == False:
			obj.row = 0
			obj.motor_counter=0
			obj.previous_motor = 9
			obj.progressBar.setValue(0)

		if isinstance(obj.tableWidget.item(obj.row,0), QTableWidgetItem):
			obj.waiting_ = True
			while (obj.tableWidget.item(obj.row,0).text() != "Wait"):
			
				header1 = obj.tableWidget.horizontalHeaderItem(0)
				header2 = obj.tableWidget.horizontalHeaderItem(1)
				header3 = obj.tableWidget.horizontalHeaderItem(2)
				#motor read
				
				if (str(header1.text()).upper() != "MOTOR") & (str(header2.text()).upper() != "SPEED") & (str(header3.text()).upper() != "ML"):
					print("ERROR: The .csv file hasn't the correct format")
					return
					
				else:
				
					if int(obj.tableWidget.item(obj.row,1).text()) < 101:
						obj.MSG["motors"][int(obj.tableWidget.item(obj.row,0).text())-1]["speed"] = int(obj.tableWidget.item(obj.row,1).text())
					else:
						obj.MSG["motors"][int(obj.tableWidget.item(obj.row,0).text())-1]["speed"] = 100
						print ("WARNING: A speed greater than 100% have been corrected to the maximun possible")
						
						
					if int(obj.tableWidget.item(obj.row,2).text()):
						obj.MSG["motors"][int(obj.tableWidget.item(obj.row,0).text())-1]["steps"] = int(obj.tableWidget.item(obj.row,2).text()) * int(obj.CONFIG_["motors"][int(obj.tableWidget.item(obj.row,0).text())]["m/s"])
						
						
					if int(obj.tableWidget.item(obj.row,0).text()) != obj.previous_motor:
						obj.motor_counter += 1
						obj.previous_motor = int(obj.tableWidget.item(obj.row,0).text())
					obj.row+=1
			else:
				SendAndWait (obj,ser)
		
		else:
			obj.waiting_ = False
			obj.progressBar.setValue(100)

		if obj.waiting_ == False:
			obj.SendPause = -1
			obj.pushButton_11.setText("Send")
			obj.pushButton_10.setEnabled(True)
			obj.tabWidget.setTabEnabled(0,True)
			obj.tabWidget.setTabEnabled(1,True)
			obj.tabWidget.setTabEnabled(3,True)
			obj.SerialSelect.setEnabled(True)
			obj.waiting_ == False
			
			return
	
	if(obj.waiting_):
		obj.t = threading.Timer(2.0, SendProtocol,[obj,obj.ser])
		obj.t.start()

def SendAndWait (obj,ser):
	if ser.is_open:
		
		if obj.sended_ == False:
			string = json.dumps(obj.MSG)
			ser.write(string.encode())
			print(obj.MSG)
			obj.sended_ = True
		
		response = ""
		
		time.sleep(0.1)
		if (obj.motor_counter > 0):

			while (ser.in_waiting > 0):
				response = ser.readline()
				print(response)
				if (str(response).find("stopped")>0):
					obj.motor_counter = obj.motor_counter - 1
					if obj.motor_counter == 0:
						obj.row+=1
						obj.sended_ = False
						obj.progressBar.setValue((obj.row/obj.max_rows) * 100)
				response = ""
						

							
	else:
		print("ERROR: port is not open")
		obj.SendPause = -1
		obj.waiting_=False

def serial_ports():

    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result
		
class ProgGUI (Ui_MainWindow):

	CONFIG_string = '''{"motors":
						[
							{"m/s":1,"s/r":2000},
							{"m/s":1,"s/r":2000},
							{"m/s":1,"s/r":2000},
							{"m/s":1,"s/r":2000},
							{"m/s":1,"s/r":2000},
							{"m/s":1,"s/r":2000},
							{"m/s":1,"s/r":2000},
							{"m/s":1,"s/r":2000}
							]
					}'''
	
	CONFIG_ = json.loads (CONFIG_string)

	MSG_string = '''{"motors": 
				[
					{"steps":0,"speed":0},
					{"steps":0,"speed":0},
					{"steps":0,"speed":0},
					{"steps":0,"speed":0},
					{"steps":0,"speed":0},
					{"steps":0,"speed":0},
					{"steps":0,"speed":0},
					{"steps":0,"speed":0}	
				],
			"potentiostat":""}'''
	MSG = json.loads (MSG_string)
	
	
	ser = serial.Serial(timeout=1)
	
	waiting_ = False	
	SendPause = -1
	sended_=False
	max_rows=0
	row = 0
	motor_counter=0
	previous_motor = 9

	t = threading.Timer(2.0, SendProtocol)
				
	def __init__(self,MW):
	
		Ui_MainWindow.__init__(self)
		self.setupUi(MW)

		ports = serial_ports()
		self.SerialSelect.addItems(ports)
		
		self.SerialSelect.activated.connect(lambda: SerialSelector(self, self.ser))
		
		self.pushButton.clicked.connect(lambda: ManualSerialSend(self, self.lineEdit, self.ser))
		
		self.pushButton_10.clicked.connect(lambda: getFiles(self))
		
		self.pushButton_11.clicked.connect(lambda: B10click(self, self.ser))
		
		self.pushButton_2.clicked.connect(lambda: adjustSpeed(self, self.Speed, self.doubleSpinBox, 0))
		self.pushButton_3.clicked.connect(lambda: adjustSpeed(self, self.Speed_2, self.doubleSpinBox_2, 1))
		self.pushButton_4.clicked.connect(lambda: adjustSpeed(self, self.Speed_3, self.doubleSpinBox_3, 2))
		self.pushButton_5.clicked.connect(lambda: adjustSpeed(self, self.Speed_4, self.doubleSpinBox_4, 3))
		self.pushButton_6.clicked.connect(lambda: adjustSpeed(self, self.Speed_5, self.doubleSpinBox_5, 4))
		self.pushButton_7.clicked.connect(lambda: adjustSpeed(self, self.Speed_6, self.doubleSpinBox_6, 5))
		self.pushButton_8.clicked.connect(lambda: adjustSpeed(self, self.Speed_7, self.doubleSpinBox_7, 6))
		self.pushButton_9.clicked.connect(lambda: adjustSpeed(self, self.Speed_8, self.doubleSpinBox_8, 7))
		
		self.pushButton_17.clicked.connect(lambda: SerialSend (self, self.MSG, self.ser))
		
		
		self.spinBox.valueChanged.connect(lambda: configMotor(0, self, self.spinBox, "m/s"))
		self.spinBox_2.valueChanged.connect(lambda: configMotor(0, self, self.spinBox_2, "s/r"))
		
		self.spinBox_5.valueChanged.connect(lambda: configMotor(1, self, self.spinBox_5, "m/s"))
		self.spinBox_6.valueChanged.connect(lambda: configMotor(1, self, self.spinBox_6, "s/r"))
		
		self.spinBox_7.valueChanged.connect(lambda: configMotor(2, self, self.spinBox_7, "m/s"))
		self.spinBox_8.valueChanged.connect(lambda: configMotor(2, self, self.spinBox_8, "s/r"))
		
		self.spinBox_9.valueChanged.connect(lambda: configMotor(3, self, self.spinBox_9, "m/s"))
		self.spinBox_10.valueChanged.connect(lambda: configMotor(3, self, self.spinBox_10, "s/r"))
		
		self.spinBox_11.valueChanged.connect(lambda: configMotor(4, self, self.spinBox_11, "m/s"))
		self.spinBox_12.valueChanged.connect(lambda: configMotor(4, self, self.spinBox_12, "s/r"))
		
		self.spinBox_13.valueChanged.connect(lambda: configMotor(5, self, self.spinBox_13, "m/s"))
		self.spinBox_14.valueChanged.connect(lambda: configMotor(5, self, self.spinBox_14, "s/r"))
		
		self.spinBox_15.valueChanged.connect(lambda: configMotor(6, self, self.spinBox_15, "m/s"))
		self.spinBox_16.valueChanged.connect(lambda: configMotor(6, self, self.spinBox_16, "s/r"))
		
		self.spinBox_17.valueChanged.connect(lambda: configMotor(7, self, self.spinBox_17, "m/s"))
		self.spinBox_18.valueChanged.connect(lambda: configMotor(7, self, self.spinBox_18, "s/r"))

if __name__ == '__main__':	
	
	app = QtWidgets.QApplication(sys.argv)

	MW = QtWidgets.QMainWindow()
 
	prog = ProgGUI(MW)
 
	MW.show()
	
	app.exec()


