module ParsingErrorManagement where

--Project imports

import Structure
import Data.Char

-- Cleaning string

isTokensStringValid :: String -> Bool
isTokensStringValid [] = True
isTokensStringValid (x:xs)
    | (x `elem` "0123456789-*+/^.() \t") == True = isTokensStringValid xs
    | otherwise = False

isTokensStringParenthesisValid :: String -> Int
isTokensStringParenthesisValid [] = 0
isTokensStringParenthesisValid (x:xs)
    | (x `elem` "(") == True = 1 + isTokensStringParenthesisValid xs
    | (x `elem` ")") == True = (-1) + isTokensStringParenthesisValid xs
    | otherwise = isTokensStringParenthesisValid xs

isCharOpeNotMinPlus :: Char -> Bool
isCharOpeNotMinPlus c = (c `elem` "*/^")

isCharOpeNotMinus :: Char -> Bool
isCharOpeNotMinus c = (c `elem` "*+/^")

isCharOperator :: Char -> Bool
isCharOperator c = (c `elem` "-*+/^")

isCharOperatorT :: Token -> Bool
isCharOperatorT (Token Nothing (Just c)) = (c `elem` "-*+/^")
isCharOperatorT _ = False

isCharParenthesis :: Char -> Bool
isCharParenthesis c = (c `elem` "()")

isTokensStringSeparatorValid :: String -> Bool
isTokensStringSeparatorValid [] = True
isTokensStringSeparatorValid [x]
    | (isCharOperator x) == True = False
    | otherwise = True
isTokensStringSeparatorValid (x:y:xs)
    | (x `elem` "." && not (isDigit y)) = False --J'ai utilisé la fonction elem a cause de la norme
    | (y `elem` "." && not (isDigit x)) = False
    | (isCharOpeNotMinPlus x && isCharOpeNotMinPlus y) = False
    | otherwise = isTokensStringSeparatorValid (y:xs)

isTokensParenthesisValid :: String -> Bool
isTokensParenthesisValid [] = True
isTokensParenthesisValid [_] = True
isTokensParenthesisValid (x:y:xs)
    | ((x `elem` "(") == True && (isCharOpeNotMinus y == True)) = False
    | ((x `elem` "(") == True && (isCharOpeNotMinus y == True)) = False
    | otherwise = isTokensParenthesisValid (y:xs)

cleanTokensString :: String -> String
cleanTokensString [] = []
cleanTokensString (x:xs)
    | (x `elem` "0123456789-*+/^.()") == True = x : cleanTokensString xs
    | otherwise = cleanTokensString xs
