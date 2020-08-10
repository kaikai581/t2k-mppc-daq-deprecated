#!/usr/bin/env python

import sys
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import *


class Window(QWidget):
    def __init__(self, parent=None):
        super(Window, self).__init__(parent)

        grid = QGridLayout()
        grid.addWidget(self.createExampleGroup(), 0, 0, 1, 2)
        grid.addWidget(self.createExampleGroup(), 1, 0)
        # grid.addWidget(self.createExampleGroup(), 0, 1)
        grid.addWidget(self.createExampleGroup(), 1, 1)
        grid.addWidget(QTextEdit(), 2, 0, 1, 2)
        self.msgBox = grid.itemAt(3).widget()
        self.msgBox.setText('hi')
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


if __name__ == '__main__':
    app = QApplication(sys.argv)
    clock = Window()
    clock.show()
    sys.exit(app.exec_())
