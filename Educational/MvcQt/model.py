import abc


class ITestQtModel(abc.ABC):
    """
    The Model interface for the MvcQt application.
    """

    @property
    @abc.abstractmethod
    def message(self) -> str:
        """Gets a message for the user."""
        raise NotImplementedError

    @message.setter
    @abc.abstractmethod
    def message(self, newMessage: str):
        """Updates the model's message to the user."""
        raise NotImplementedError


class BasicTestQtModel(ITestQtModel):
    """Basic implementation of an ITestQtModel."""

    def __init__(self):
        self.GREETING = "Hello!"
        self.FAREWELL = "Goodbye!"
        self._message = self.GREETING

    # Override
    @property
    def message(self) -> str:
        oldMessage = self._message
        self.message = self.GREETING if oldMessage == self.FAREWELL else self.FAREWELL
        return oldMessage

    # Override
    @message.setter
    def message(self, newMessage: str):
        self._message = newMessage

