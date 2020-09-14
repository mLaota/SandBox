import abc
from typing import Callable

from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QWidget, QSizePolicy, QLabel, QPushButton, \
    QVBoxLayout, QMainWindow, QHBoxLayout


class ITestQtView(abc.ABC):
    """
    Interface for a TestQtView.
    """

    @abc.abstractmethod
    def show(self):
        """Renders the view."""
        raise NotImplementedError

    @abc.abstractmethod
    def hide(self):
        """Hides the view."""
        raise NotImplementedError

    @abc.abstractmethod
    def registerUpdateMessageRequest(self, callback: Callable):
        """Connects a callback to the appropriate signal of the view.

        Args:
            callback: Callback to run when the user wants to doSomething.
        """
        raise NotImplementedError


def _createExpandingSizePolicy(horizontal=True, vertical=True) -> QSizePolicy:
    """Creates a size policy that expands based on the given parameters

    Args:
        horizontal: When 'True', the returned size policy expands horizontally
        vertical: When 'True', the returned size policy expands vertically.

    Returns:
        A QSizePolicy representative of the given parameters.
    """
    sizePolicy = QSizePolicy()
    if horizontal:
        sizePolicy.setHorizontalPolicy(QSizePolicy.Expanding)
    if vertical:
        sizePolicy.setVerticalPolicy(QSizePolicy.Expanding)
    return sizePolicy


class MessageDisplay(QWidget):
    """Widget for displaying a message to the user."""

    def __init__(self):
        super().__init__()
        self._layout = QHBoxLayout()
        self.setLayout(self._layout)
        self._lblCaption = QLabel('Current message: ')
        self._lblMessage = QLabel('N/A')
        self._layout.addWidget(self._lblCaption)
        self._layout.addWidget(self._lblMessage)
        self._layout.setAlignment(Qt.AlignCenter)

    def setMessage(self, newMessage: str):
        self._lblMessage.setText(newMessage)


class BasicTestQtView(ITestQtView):
    """Main view for the MvcQt application. Inherits from QMainWindow
    and implements ITestQtView.
    """

    def __init__(self):
        """Constructor."""
        super().__init__()

        # Constants.
        self._WINDOW_WIDTH: int = 250
        self._WINDOW_HEIGHT: int = self._WINDOW_WIDTH

        # Initialize the main window
        self._mainWindow = QMainWindow()
        self._mainWindow.setFixedSize(self._WINDOW_WIDTH, self._WINDOW_HEIGHT)
        self._mainWindow.setWindowTitle('MvcQt')

        # Set the central widget. This is the parent of all widgets.
        self._centralWidget = QWidget(self._mainWindow)
        self._mainWindow.setCentralWidget(self._centralWidget)
        self._layout = QVBoxLayout()
        self._centralWidget.setLayout(self._layout)

        # Creates a widget to display messages from the model.
        self._messageWidget = MessageDisplay()
        self._layout.addWidget(self._messageWidget)
        self.displayMessage('N/A')

        # Create a "Press Me!" button for signaling a message update request.
        self._btnPressMe = self._createUpdateMessageButton()
        self._layout.addWidget(self._btnPressMe)

    @staticmethod
    def _createUpdateMessageButton() -> QPushButton:
        """Add a button that prints "Hello!

        Returns:
            A button that says "Press me!"
        """
        prompt: str = 'Press me!'
        button = QPushButton(prompt)
        button.setSizePolicy(_createExpandingSizePolicy())
        return button

    def displayMessage(self, message: str):
        """Displays a message to the user.

        Args:
            message: The message to display to the user.
        """
        self._messageWidget.setMessage(message)
        print(message)

    # Override
    def show(self):
        self._mainWindow.show()

    # Override
    def hide(self):
        self._mainWindow.hide()

    # Override
    def registerUpdateMessageRequest(self, callback: Callable):
        self._btnPressMe.clicked.connect(callback)
