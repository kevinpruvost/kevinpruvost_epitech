module ParseArgs where

import System.Environment
import System.Exit
import Data.Char

isSingleCharInt :: Char -> Bool
isSingleCharInt x
    | x == '0' || x == '1' || x == '2' || x == '3' || x == '4' || x == '5' || x == '6' || x == '7' || x == '8' || x == '9' || x == '-' = True
    | otherwise = False

verifyInt :: [Char] -> Bool
verifyInt (x:xs)
    | isSingleCharInt x == False = False
    | otherwise = verifyInt xs
verifyInt [] = True

readInt :: [Char] -> Int
readInt xs
    | verifyInt xs == False = -1
    | otherwise = read xs::Int

parseParams :: [[Char]] -> (Int, Int, Int, Int, Int) -> (Int, Int, Int, Int, Int)
parseParams ("--rule":x:xs) (a, b, c, d, e)   = parseParams xs (readInt x, b, c, d, e)
parseParams ("--start":x:xs) (a, b, c, d, e)  = parseParams xs (a, readInt x, c, d, e)
parseParams ("--lines":x:xs) (a, b, c, d, e)  = parseParams xs (a, b, readInt x, d, e)
parseParams ("--window":x:xs) (a, b, c, d, e) = parseParams xs (a, b, c, readInt x, e)
parseParams ("--move":x:xs) (a, b, c, d, e)   = parseParams xs (a, b, c, d, readInt x)
parseParams (x:xs) (a, b, c, d, e) = (-1, b, c, d, e)
parseParams xs z = z

parseBug :: [[Char]] -> Bool -> Bool
parseBug xs False = False
parseBug ("--rule":x:xs)   bool = parseBug xs (verifyInt x)
parseBug ("--start":x:xs)  bool = parseBug xs (verifyInt x)
parseBug ("--lines":x:xs)  bool = parseBug xs (verifyInt x)
parseBug ("--window":x:xs) bool = parseBug xs (verifyInt x)
parseBug ("--move":x:xs)   bool = parseBug xs (verifyInt x)
parseBug (x:xs) _ = False
parseBug xs z = z

parseIsEmpty :: [[Char]] -> Bool
parseIsEmpty [] = False
parseIsEmpty xs = True