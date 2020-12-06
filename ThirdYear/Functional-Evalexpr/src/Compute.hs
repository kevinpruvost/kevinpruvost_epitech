module Compute where

--Project imports
import Structure
import Data.Char

makeOperation :: Token -> Token -> Token -> Token
makeOperation ope (Token (Just v1) _) (Token (Just v2) _)
  | isTokenThisChar ope '+' = createTokenNumber $ v1 + v2
  | isTokenThisChar ope '-' = createTokenNumber $ v1 - v2
  | isTokenThisChar ope '*' = createTokenNumber $ v1 * v2
  | isTokenThisChar ope '/' && v2 /= 0 = createTokenNumber $ v1 / v2
  | isTokenThisChar ope '^' = createTokenNumber $ v1 ** v2
  | otherwise = (Token Nothing Nothing)
makeOperation _ _ _ = (Token Nothing Nothing)

compute :: [Token] -> [Token] -> Maybe Double
compute [] [(Token val _)] = val
compute [] _ = Nothing
compute (x:xs) [] = compute xs [x]
compute (x:xs) [s] = compute xs (x:s:[])
compute (x:xs) (s1:s2:st)
  | isTokenChar x = compute xs (makeOperation x s2 s1:st)
  | otherwise = compute xs (x:s1:s2:st)

val :: Token -> Int
val (Token _ (Just '+')) = 1
val (Token _ (Just '-')) = 1
val (Token _ (Just '*')) = 2
val (Token _ (Just '/')) = 2
val (Token _ (Just '^')) = 3
val (Token _ (Just _)) = 0
val _ = (-1)

infToPost :: [Token] -> [Token] -> [Token]
infToPost [] stack = stack
infToPost (x:xs) []
  | isTokenChar x = infToPost xs [x]
  | otherwise = (x:infToPost xs [])
infToPost (x:xs) (s:st)
  | isTokenC x ')' && isTokenC s '(' = infToPost xs st
  | isTokenChar x && (val x > val s || isTokenC x '(') = infToPost xs (x:s:st)
  | isTokenChar x = (s:infToPost (x:xs) st)
  | otherwise = (x:infToPost xs (s:st))