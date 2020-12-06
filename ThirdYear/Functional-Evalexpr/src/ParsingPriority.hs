module ParsingPriority where

--Project imports

import ParsingErrorManagement
import Structure
import Data.Char

import Compute
-- Manage priority

{-
opePriority :: Token -> Int
opePriority (Token Nothing (Just ch))
    | ch == '^' = 3
    | ch == '/' || ch == '*' = 2
    | ch == '+' || ch == '-' = 1
    | otherwise = 0
opePriority _ = -1

cutStackLimited :: [Token] -> ([Token], [Token])
cutStackLimited [] = ([], [])
cutStackLimited (r:rStack)
    | (isTokenThisChar r '(') = ([], rStack)
    | otherwise = (r : left, right)
    where (left, right) = cutStackLimited rStack

isFill :: Token -> Token -> Bool
isFill t1 t2 | (isTokenThisChar t1 '(') = True
             | (opePriority t1) > (opePriority t2) = True
             | otherwise = False

isUnFill :: Token -> Token -> Bool
isUnFill t1 t2
    | (isTokenNumber t1) || (isTokenThisChar t1 '(') = False
    | (opePriority t1) <= (opePriority t2) = True
    | otherwise = False

mergeToRev :: [Token] -> [Token] -> [Token]
mergeToRev [] stack = stack
mergeToRev (x:xs) []
    | (opePriority x) >= 1 || (isTokenThisChar x '(') = (mergeToRev xs [x])
    | otherwise = [x] ++ (mergeToRev xs [])
mergeToRev (x:xs) (s:stack)
    | (isFill x s) == True = (mergeToRev xs (x:s:stack))
    | (isTokenThisChar x ')') = bStack ++ mergeToRev xs eStack
    | (isUnFill x s) = bStack ++ mergeToRev xs (x:eStack)
    | otherwise = [x] ++ (mergeToRev xs (s:stack))
        where (bStack, eStack) = cutStackLimited (s:stack)
-}

cleanParentheses :: [Token] -> [Token]
cleanParentheses [] = []
cleanParentheses (x:xs)
    | (isTokenThisChar x ')') || (isTokenThisChar x '(') = cleanParentheses xs
    | otherwise = (x : (cleanParentheses xs))

managePriority :: [Token] -> [Token]
managePriority [] = []
managePriority [x] = [x]
managePriority x = (cleanParentheses (infToPost x [])) --mergeToRev