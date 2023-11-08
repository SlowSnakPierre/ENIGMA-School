import sys
from PyQt5 import QtWidgets,QtGui,QtCore
from PyQt5.QtWebEngineWidgets import *
app=QtWidgets.QApplication([])
app.setWindowIcon(QtGui.QIcon("icon.png"))
app.setApplicationName("Jeu de l'oie")
w=QWebEngineView()
w.settings().setAttribute(QWebEngineSettings.PluginsEnabled, True)
w.settings().setAttribute(QWebEngineSettings.JavascriptEnabled, True)
w.settings().setAttribute(QWebEngineSettings.FullScreenSupportEnabled, True)
w.load(QtCore.QUrl('https://hole-io.com')) ## load google on startup
w.showMaximized()
app.exec_()