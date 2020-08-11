#!/usr/bin/env python

import sys
sys.path.append('../../agilent-n6700b-power-system')
from N6700B import N6700B
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import *


class Window(QWidget):
    def __init__(self, parent=None):
        super(Window, self).__init__(parent)

        # widgets I want to have control
        self.voltageSwitch = QPushButton(text='Switch On')
        self.voltageSwitch.setCheckable(True)
        # self.voltageSwitch.toggle()
        self.msgBox = QTextEdit()
        self.msgBox.setText('hi')

        grid = QGridLayout()
        grid.addWidget(self.createVoltageControl(), 0, 0, 1, 2)
        # grid.addWidget(self.createExampleGroup(), 1, 0)
        # grid.addWidget(self.createExampleGroup(), 0, 1)
        # grid.addWidget(self.createExampleGroup(), 1, 1)
        grid.addWidget(self.msgBox, 2, 0, 1, 2)
        self.setLayout(grid)

        self.setWindowTitle("MPPC DAQ Control App")
        self.resize(400, 300)

    def createExampleGroup(self):
        groupBox = QGroupBox("Best Food")

        radio1 = QRadioButton("&Radio pizza")
        radio2 = QRadioButton("R&adio taco")
        radio3 = QRadioButton("Ra&dio burrito")

        radio1.setChecked(True)

        vbox = QVBoxLayout()
        vbox.addWidget(radio1)
        vbox.addWidget(radio2)
        vbox.addWidget(radio3)
        vbox.addStretch(1)
        groupBox.setLayout(vbox)

        return groupBox

    def createVoltageControl(self):
        groupBox = QGroupBox("Voltage Control")

        grid = QGridLayout()
        grid.addWidget(QLabel('Voltage Set: '), 0, 0, Qt.AlignRight)
        grid.addWidget(QLineEdit(), 0, 1)
        grid.addWidget(QLabel('Voltage Read: '), 1, 0, Qt.AlignRight)
        grid.addWidget(QLineEdit(), 1, 1)
        grid.addWidget(self.voltageSwitch, 2, 2)

        groupBox.setLayout(grid)

        return groupBox


if __name__ == '__main__':
    app = QApplication(sys.argv)
    clock = Window()
    clock.show()
    sys.exit(app.exec_())
