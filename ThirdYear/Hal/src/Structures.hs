module Structures where

import qualified Data.Map

type Frame = Data.Map.Map String Expression

data Expression = Null
                | Variable String
                | Chars String
                | Number Int
                | Boolean Bool
                | Pair Expression Expression
                | Exception String
                | If Expression Expression Expression
                | Cond [(Expression, Expression)]
                | Lambda [Expression] Expression
                | Procedure ([Expression] -> Expression)
                | Application Expression [Expression]
                | Definition Expression Expression
                | Quote Expression

data Environment = EmptyEnvironment
                 | Environment Frame Environment

showPairList :: Expression -> String
showPairList Null = ""
showPairList (Pair first Null) = show first
showPairList (Pair first second) = show first ++ " " ++ showPairList second
showPairList _ = ""

instance Show Expression where
  show = showExpr

showExpr :: Expression -> String
showExpr Null = "null"
showExpr (Number number) = show number
showExpr (Chars string) = string
showExpr (Boolean True) = "#t"
showExpr (Boolean False) = "#f"
showExpr (Variable var) = var
showExpr (Exception message) = "#Exception: " ++ "'" ++ message ++ "'"
showExpr x = showExpr2 x

showExpr2 :: Expression -> String
showExpr2 pair@(Pair first second)
  | isList pair = "(" ++ showPairList pair ++ ")"
  | otherwise = "(" ++ show first ++ " . " ++ show second ++ ")"
showExpr2 (Lambda _ _) = "#<procedure>"
showExpr2 (Procedure _) = "#<procedure>"
showExpr2 (Application _ _) = "#<procedure>"
showExpr2 (Definition var val) = "#<definition> : " ++ show var ++ show val
showExpr2 _ = "#Unknown"

showExprArray :: [Expression] -> String
showExprArray [] = ""
showExprArray [x] = showExpr x
showExprArray (x:xs) = showExpr x ++ ", " ++ (showExprArray xs)

--newF == newFrame
addPairToEnv :: Environment -> String -> Expression -> Environment
addPairToEnv EmptyEnvironment _ _ = EmptyEnvironment
addPairToEnv (Environment frame parent) name value = Environment newF parent
  where newF = Data.Map.insert name value frame

searchInEnv :: Environment -> String -> Expression
searchInEnv EmptyEnvironment variable =
  Exception ("Binding not found for variable: " ++ variable)
searchInEnv (Environment frame parent) variable =
  case value of
    Just result -> result
    Nothing -> searchInEnv parent variable
  where value = Data.Map.lookup variable frame

extendEnvironment :: Environment -> [Expression] -> [Expression] -> Environment
extendEnvironment environment parameters arguments =
  let params = map show parameters
  in Environment (Data.Map.fromList (zip params arguments)) environment

pairToList :: Expression -> [Expression]
pairToList Null = []
pairToList (Pair first rest) = first : pairToList rest

isList :: Expression -> Bool
isList Null = True
isList (Pair Null _) = True
isList (Pair _ Null) = True
isList (Pair _ second) = isList second
isList _ = False