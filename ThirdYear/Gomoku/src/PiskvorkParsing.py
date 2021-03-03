import sys
import collections

from src.GomokuEngine import GomokuEngine

class PiskvorkParser:

  def __init__(self):
    self.gomokuEngine = None

  def sendToPiskvork(self, message):
    print(message)
    sys.stdout.flush()

  def startSlot(self, command):
    if len(command) < 2:
      return False
    boardSize = int(command[1])
    if boardSize <= 0:
      self.sendToPiskvork("ERROR Map of size " + str(boardSize))
      return False
    self.gomokuEngine = GomokuEngine(boardSize, boardSize)
    self.sendToPiskvork("OK")
    return True

  def turnSlot(self, command):
    if self.gomokuEngine is None:
      self.sendToPiskvork("ERROR Brain did not receive the START command")
      return False
    if len(command) < 2:
      return False
    rawCoords = command[1].split(',')
    if len(rawCoords) < 2:
      self.sendToPiskvork("ERROR Can't read the coords")
      return False
    recX, recY = int(rawCoords[0]), int(rawCoords[1])
    if not self.gomokuEngine.makeMove(recX, recY, 2):
      self.sendToPiskvork("ERROR Move not allowed")
      return False
    bestX, bestY, _ = self.gomokuEngine.minimax(2, True, float('-inf'), float('inf'))
    if bestX is None or bestY is None:
      self.sendToPiskvork("ERROR minimax returned None")
      return False
    #self.sendToPiskvork("MESSAGE minimax score: " + str(v))
    if not self.gomokuEngine.makeMove(bestX, bestY, 1):
      self.sendToPiskvork("ERROR minimax couldn't find a good position")
      return False
    self.sendToPiskvork(str(bestX) + "," + str(bestY))
    return True

  def beginSlot(self, command):
    if self.gomokuEngine is None:
      self.sendToPiskvork("ERROR Brain did not receive the START command")
      return False
    openX, openY = self.gomokuEngine.getOpeningMove()
    if not self.gomokuEngine.makeMove(openX, openY, 1):
      self.sendToPiskvork("ERROR couldn't find a good opening move")
      return False
    self.sendToPiskvork(str(openX) + "," + str(openY))
    return True

  def boardSlot(self, command):
    if self.gomokuEngine is None:
      self.sendToPiskvork("ERROR Brain did not receive the START command")
      return False
    self.gomokuEngine.clearBoard()
    while True:
      line = sys.stdin.readline().strip()
      if line == "DONE":
        break
      rawMove = line.split(',')
      if len(rawMove) != 3:
        self.sendToPiskvork("ERROR received invalid position in BOARD command")
        return False
      self.gomokuEngine.makeMove(int(rawMove[0]), int(rawMove[1]), int(rawMove[2]))
    bestX, bestY, _ = self.gomokuEngine.minimax(2, True, float('-inf'), float('inf'))
    if bestX is None or bestY is None:
      self.sendToPiskvork("ERROR minimax couldn't find a good position after BOARD command")
      return False
    if not self.gomokuEngine.makeMove(bestX, bestY, 1):
      self.sendToPiskvork("ERROR minimax couldn't find a good position")
      return False
    self.sendToPiskvork(str(bestX) + "," + str(bestY))
    return True

  def infoSlot(self, command):
    return True

  def endSlot(self, command):
    return False

  def aboutSlot(self, command):
    self.sendToPiskvork('name="michel", version="1.0", author="Kevin Pruvost, Baptiste Martinet, Etienne Miltgen", country="FRA"')
    return True
  
  def rectStartSlot(self, command):
    if not self.gomokuEngine is None:
      self.sendToPiskvork("ERROR Board already initialized")
      return False
    if len(command) < 2:
      self.sendToPiskvork("ERROR Couldn't find where you put the board size")
      return False
    rawSizesXY = command[1].split(',')
    if len(rawSizesXY) < 2:
      self.sendToPiskvork("ERROR Invalid board sizes")
      return False
    width, height = int(rawSizesXY[0]), int(rawSizesXY[1])
    self.gomokuEngine = GomokuEngine(width, height)
    self.sendToPiskvork("OK")
    return True
  
  def restartSlot(self, command):
    if self.gomokuEngine is None:
      self.sendToPiskvork("ERROR Brain did not receive the START command")
      return False
    self.gomokuEngine.clearBoard()
    self.sendToPiskvork("OK")
    return True
  
  def takebackSlot(self, command):
    if self.gomokuEngine is None:
      self.sendToPiskvork("ERROR Brain did not receive the START command")
      return False
    if len(command) < 2:
      self.sendToPiskvork("ERROR Couldn't find where you put the coordinates")
      return False
    rawCoordinates = command[1].split(',')
    if len(rawCoordinates) < 2:
      self.sendToPiskvork("ERROR Invalid coordinates")
      return False
    x, y = int(rawCoordinates[0]), int(rawCoordinates[1])
    if not self.gomokuEngine.undoMove(x, y):
      self.sendToPiskvork("ERROR Couldn't undo given move")
      return False
    self.sendToPiskvork("OK")
    return True

  functions = {
    "START" : startSlot,
    "TURN"  : turnSlot ,
    "BEGIN" : beginSlot,
    "BOARD" : boardSlot,
    "INFO"  : infoSlot ,
    "END"   : endSlot  ,
    "ABOUT" : aboutSlot,
    "RECTSTART" : rectStartSlot,
    "RESTART" : restartSlot,
    "TAKEBACK" : takebackSlot
  }

  def parseAndExecuteCommand(self, line: str):
    command = line.strip().split(' ')
    if len(command) < 1:
      return False
    if command[0] in self.functions:
      self.sendToPiskvork("MESSAGE " + " ".join(command))
      return self.functions[command[0]](self, command)
    self.sendToPiskvork("ERROR Command not recognized : '" + command[0] + '\'')
    return False