#!/usr/bin/env python3

import sys
import collections

from src.PiskvorkParsing import PiskvorkParser

def main():
  piskvorkParser = PiskvorkParser()

  while True:
    line = sys.stdin.readline()
    if not piskvorkParser.parseAndExecuteCommand(line):
      break
  return 0

if __name__ == "__main__":
  main()