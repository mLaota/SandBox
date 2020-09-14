from model import ITestQtModel
from view import BasicTestQtView


class BasicTestQtController:
    """
    Controller for the MvcQt application.
    """
    def __init__(self, model: ITestQtModel, view: BasicTestQtView):
        self._model = model
        self._view = view
        self._view.show()
        self._connectSignals()

    def _updateMessage(self):
        """Updates the message in the view and model."""
        self._view.displayMessage(self._model.message)

    def _connectSignals(self):
        """Connect signals and slots."""
        self._view.registerUpdateMessageRequest(self._updateMessage)
