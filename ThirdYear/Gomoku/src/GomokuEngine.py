#
# Gomoku AI
#

import sys
import collections

from src.PatternTree import PatternBranch

class GomokuEngine:
  def __init__(self, sizeX, sizeY):
    self.width = sizeX
    self.height = sizeY
    self.board = [[0 for i in range(self.width)] for j in range(self.height)]
    self.patterns = [
      {'vals': [1, 1, 1, 1, 1], 'score': 9999}, {'vals': [0, 1, 1, 1, 1, 0], 'score': 1000},
      {'vals': [0, 1, 1, 1, 1], 'score': 300}, {'vals': [1, 1, 1, 1, 0], 'score': 300},
      {'vals': [0, 1, 1, 1, 1, 2], 'score': 100}, {'vals': [2, 1, 1, 1, 1, 0], 'score': 100},
      {'vals': [0, 1, 0, 1, 1, 1, 0], 'score': 100}, {'vals': [0, 1, 1, 1, 0, 1, 0], 'score': 100},
      {'vals': [0, 1, 1, 0, 1, 1, 0], 'score': 100}, {'vals': [2, 1, 1, 1, 1, 2], 'score': -5},
      {'vals': [0, 1, 1, 1, 0], 'score': 200}, {'vals': [0, 1, 0, 1, 1, 0], 'score': 200}, {'vals': [0, 1, 1, 0, 1, 0], 'score': 200},
      {'vals': [2, 1, 1, 1, 0], 'score': 150}, {'vals': [0, 1, 1, 1, 2], 'score': 150},
      {'vals': [0, 0, 1, 1, 1, 2], 'score': 50},  {'vals': [2, 1, 1, 1, 0, 0], 'score': 50},
      {'vals': [0, 1, 0, 1, 1, 2], 'score': 50}, {'vals': [2, 1, 1, 0, 1, 0], 'score': 50},
      {'vals': [0, 1, 1, 0, 1, 2], 'score': 50}, {'vals': [2, 1, 0, 1, 1, 0], 'score': 50},
      {'vals': [1, 0, 0, 1, 1], 'score': 50}, {'vals': [1, 1, 0, 0, 1], 'score': 50},
      {'vals': [1, 0, 1, 0, 1], 'score': 50}, {'vals': [2, 0, 1, 1, 1, 0, 2], 'score': 50},
      {'vals': [0, 1, 1, 0], 'score': 25}, {'vals': [2, 1, 1, 0], 'score': 3}, {'vals': [0, 1, 1, 2], 'score': 3},
      {'vals': [2, 1, 1, 1, 2], 'score': -5}, {'vals': [0, 0, 1, 1, 0], 'score': 5},
      {'vals': [0, 1, 0, 1, 0], 'score': 5},
      {'vals': [0, 1, 0, 0, 1, 0], 'score': 5}, {'vals': [0, 0, 0, 1, 1, 2], 'score': 3}, {'vals': [2, 1, 1, 0, 0, 0], 'score': 3},
      {'vals': [0, 0, 1, 0, 1, 2], 'score': 3}, {'vals': [2, 1, 0, 1, 0, 0], 'score': 3},
      {'vals': [0, 1, 0, 0, 1, 2], 'score': 3}, {'vals': [1, 0, 0, 0, 1], 'score': 3},
      {'vals': [2, 0, 1, 0, 1, 0, 2], 'score': 3},
      {'vals': [2, 0, 1, 1, 0, 0, 2], 'score': 3}, {'vals': [2, 1, 1, 2], 'score': -5},

      {'vals': [2, 2, 2, 2, 2], 'score': -9999}, {'vals': [0, 2, 2, 2, 2, 0], 'score': -1000},
      {'vals': [0, 2, 2, 2, 2], 'score': -300}, {'vals': [2, 2, 2, 2, 0], 'score': -300},
      {'vals': [0, 2, 2, 2, 2, 1], 'score': -100}, {'vals': [1, 2, 2, 2, 2, 0], 'score': -100},
      {'vals': [0, 2, 0, 2, 2, 2, 0], 'score': -100}, {'vals': [0, 2, 2, 2, 0, 2, 0], 'score': -100},
      {'vals': [0, 2, 2, 0, 2, 2, 0], 'score': -100}, {'vals': [1, 2, 2, 2, 2, 1], 'score': 5},
      {'vals': [0, 2, 2, 2, 0], 'score': -200}, {'vals': [0, 2, 0, 2, 2, 0], 'score': -200}, {'vals': [0, 2, 2, 0, 2, 0], 'score': -200},
      {'vals': [1, 2, 2, 2, 0], 'score': -150}, {'vals': [0, 2, 2, 2, 1], 'score': -150},
      {'vals': [0, 0, 2, 2, 2, 1], 'score': -50},  {'vals': [1, 2, 2, 2, 0, 0], 'score': -50},
      {'vals': [0, 2, 0, 2, 2, 1], 'score': -50}, {'vals': [1, 2, 2, 0, 2, 0], 'score': -50},
      {'vals': [0, 2, 2, 0, 2, 1], 'score': -50}, {'vals': [1, 2, 0, 2, 2, 0], 'score': -50},
      {'vals': [2, 0, 0, 2, 2], 'score': -50}, {'vals': [2, 2, 0, 0, 2], 'score': -50},
      {'vals': [2, 0, 2, 0, 2], 'score': -50}, {'vals': [1, 0, 2, 2, 2, 0, 1], 'score': -50},
      {'vals': [0, 2, 2, 0], 'score': -25}, {'vals': [1, 2, 2, 0], 'score': -3}, {'vals': [0, 2, 2, 1], 'score': -3},
      {'vals': [1, 2, 2, 2, 1], 'score': 5}, {'vals': [0, 0, 2, 2, 0], 'score': -5},
      {'vals': [0, 2, 0, 2, 0], 'score': -5},
      {'vals': [0, 2, 0, 0, 2, 0], 'score': -5}, {'vals': [0, 0, 0, 2, 2, 1], 'score': -3}, {'vals': [1, 2, 2, 0, 0, 0], 'score': -3},
      {'vals': [0, 0, 2, 0, 2, 1], 'score': -3}, {'vals': [1, 2, 0, 2, 0, 0], 'score': -3},
      {'vals': [0, 2, 0, 0, 2, 1], 'score': -3}, {'vals': [2, 0, 0, 0, 2], 'score': -3},
      {'vals': [1, 0, 2, 0, 2, 0, 1], 'score': -3},
      {'vals': [1, 0, 2, 2, 0, 0, 1], 'score': -3}, {'vals': [1, 2, 2, 1], 'score': 5}
    ]
    self.patternTree = PatternBranch(self.patterns, 7)
    self.dirs = [(1, 0), (0, 1), (1, -1), (1,1)]
    self.scoringDirs = [(1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1), (0, -1), (1, -1)]

  
  def printBoard(self):
    print("\n--Printing board--")
    for line in self.board:
      print(line)
  
  def clearBoard(self):
    for y in range(self.height):
      for x in range(self.width):
        self.board[y][x] = 0
  
  def __isPosInBounds(self, x, y):
    return 0 <= x and x < self.width and 0 <= y and y < self.height

  def __isMovePosible(self, x, y):
    if not self.__isPosInBounds(x, y):
      return False
    if self.board[y][x] != 0:
      return False
    return True
  
  def getOpeningMove(self):
    return (int(self.width/2), int(self.height/2))
  
  def makeMove(self, x, y, color):
    if not self.__isMovePosible(x, y):
      return False
    self.board[y][x] = color
    return True

  def undoMove(self, x, y):
    if not self.__isPosInBounds(x, y):
      return False
    self.board[y][x] = 0
    return True

  def evaluateBoard(self):
    score = 0

    for y in range(self.height):
      for x in range(self.width):
        for patternLen in range(4, 8):
          for dir in self.dirs:
            offsetX = dir[0]
            offsetY = dir[1]
            if not self.__isPosInBounds(x + offsetX * (patternLen-1), y + offsetY * (patternLen-1)):
              continue
            if patternLen == 2:
              score += self.patternTree[self.board[y + offsetY * 0][x + offsetX * 0]][self.board[y + offsetY * 1][x + offsetX * 1]].score
            elif patternLen == 3:
              score += self.patternTree[self.board[y + offsetY * 0][x + offsetX * 0]][self.board[y + offsetY * 1][x + offsetX * 1]][self.board[y + offsetY * 2][x + offsetX * 2]].score
            elif patternLen == 4:
              score += self.patternTree[self.board[y + offsetY * 0][x + offsetX * 0]][self.board[y + offsetY * 1][x + offsetX * 1]][self.board[y + offsetY * 2][x + offsetX * 2]][self.board[y + offsetY * 3][x + offsetX * 3]].score
            elif patternLen == 5:
              score += self.patternTree[self.board[y + offsetY * 0][x + offsetX * 0]][self.board[y + offsetY * 1][x + offsetX * 1]][self.board[y + offsetY * 2][x + offsetX * 2]][self.board[y + offsetY * 3][x + offsetX * 3]][self.board[y + offsetY * 4][x + offsetX * 4]].score
            elif patternLen == 6:
              score += self.patternTree[self.board[y + offsetY * 0][x + offsetX * 0]][self.board[y + offsetY * 1][x + offsetX * 1]][self.board[y + offsetY * 2][x + offsetX * 2]][self.board[y + offsetY * 3][x + offsetX * 3]][self.board[y + offsetY * 4][x + offsetX * 4]][self.board[y + offsetY * 5][x + offsetX * 5]].score
            elif patternLen == 7:
              score += self.patternTree[self.board[y + offsetY * 0][x + offsetX * 0]][self.board[y + offsetY * 1][x + offsetX * 1]][self.board[y + offsetY * 2][x + offsetX * 2]][self.board[y + offsetY * 3][x + offsetX * 3]][self.board[y + offsetY * 4][x + offsetX * 4]][self.board[y + offsetY * 5][x + offsetX * 5]][self.board[y + offsetY * 6][x + offsetX * 6]].score
    return score

  def __hasNeighbors(self, x, y):
    for i in range(-1, 2):
      if y + i < 0 or y + i >= self.height:
        continue
      for j in range(-1, 2):
        if x + j < 0 or x + j >= self.width:
          continue
        if (not (i == 0 and j == 0) and self.board[y + i][x + j] != 0):
          return True
    return False
  
  def __getMoveScore(self, x, y):
    score = 0
    lastNum = -1

    for dir in self.scoringDirs:
      lastNum = -1
      for i in range(1, 6):
        if not self.__isPosInBounds(x + dir[0] * i, y + dir[1] * i) or self.board[y + dir[1] * i][x + dir[0] * i] == 0:
          break
        if lastNum == -1:
          lastNum = self.board[y + dir[1] * i][x + dir[0] * i]
        elif self.board[y + dir[1] * i][x + dir[0] * i] == lastNum:
          score += 1
        else:
          break
    return score
  
  def __getAllPosibleMoves(self):
    moves = []

    for y in range(self.height):
      for x in range(self.width):
        if (self.board[y][x] == 0 and self.__hasNeighbors(x, y)):
          moves.append((x, y, self.__getMoveScore(x, y)))
    return moves

  def isTerminalState(self):
    for y in range(self.height):
      for x in range(self.width):
        for i in range(1, 3):
          if x + 4 < self.width and (self.board[y][x] == i and self.board[y][x + 1] == i and self.board[y][x + 2] == i and self.board[y][x + 3] == i and self.board[y][x + 4] == i):
            return True
          if y + 4 < self.height and (self.board[y][x] == i and self.board[y+1][x] == i and self.board[y+2][x] == i and self.board[y+3][x] == i and self.board[y+4][x] == i):
            return True
          if x + 4 < self.width and y + 4 < self.height and (self.board[y][x] == i and self.board[y+1][x+1] == i and self.board[y+2][x+2] == i and self.board[y+3][x+3] == i and self.board[y+4][x+4] == i):
            return True
          if x + 4 < self.width and y - 4 >= 0 and (self.board[y][x] == i and self.board[y-1][x+1] == i and self.board[y-2][x+2] == i and self.board[y-3][x+3] == i and self.board[y-4][x+4] == i):
            return True
    return False

  def minimax(self, depth, isMaximising, alpha, beta):
    if depth == 0 or self.isTerminalState():
      return None, None, self.evaluateBoard()
    
    allMoves = self.__getAllPosibleMoves()
    bestScore = 0
    bestMove = (None, None, None)

    allMoves.sort(reverse=True, key=lambda item : item[2])

    if isMaximising:
      bestScore = float('-inf')
      for move in allMoves:
        self.makeMove(move[0], move[1], 1)
        _, _, val = self.minimax(depth-1, False, alpha, beta)
        self.undoMove(move[0], move[1])
        if val >= bestScore:
          bestScore = val
          bestMove = move
        alpha = max(alpha, val)
        if beta <= alpha:
          break
    else:
      bestScore = float('inf')
      for move in allMoves:
        self.makeMove(move[0], move[1], 2)
        _, _, val = self.minimax(depth-1, True, alpha, beta)
        self.undoMove(move[0], move[1])
        if val <= bestScore:
          bestScore = val
          bestMove = move
        beta = min(beta, val) 
        if beta <= alpha:
          break  
    return bestMove[0], bestMove[1], bestScore

def main():
  gomoku = GomokuEngine(19, 19)

  gomoku.makeMove(6, 6, 2)
  gomoku.makeMove(7, 7, 2)
  gomoku.makeMove(8, 8, 2)
  gomoku.makeMove(9, 9, 2)
  gomoku.makeMove(10, 10, 2)


  gomoku.printBoard()
  print("Board score: ", gomoku.evaluateBoard())


if __name__ == "__main__":
  main()