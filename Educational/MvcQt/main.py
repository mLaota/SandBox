#!/usr/bin/env python3

import sys
from PyQt5.QtWidgets import QApplication

from controller import BasicTestQtController
from model import BasicTestQtModel
from view import BasicTestQtView


class App(QApplication):
    def __init__(self, sys_argv):
        super(App, self).__init__(sys_argv)
        self.model = BasicTestQtModel()
        self.view = BasicTestQtView()
        self.controller = BasicTestQtController(self.model, self.view)
        self.view.show()


if __name__ == '__main__':
    sys.exit(App(sys.argv).exec_())
