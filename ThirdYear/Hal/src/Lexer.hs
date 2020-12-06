module Lexer
( loadBaseEnvironment
, loadScmFile
, createList
) where
  
import System.IO
import qualified Data.Map as Map

import Structures
import Compute
import Parser
import MyExit

baseEnv :: [([Char], Expression)]
baseEnv = [
  ("+", Procedure addNumbers),
  ("add", Procedure addNumbers),
  ("-", Procedure subtractNumbers),
  ("sub", Procedure subtractNumbers),
  ("*", Procedure multiplyNumbers),
  ("mult", Procedure multiplyNumbers),
  ("/", Procedure divideNumbers),
  ("div", Procedure divideNumbers)] ++ baseEnvSecond

baseEnvSecond :: [([Char], Expression)]
baseEnvSecond = [
  ("mod", Procedure modulusNumbers),
  ("null", Null),
  ("null?", Procedure isNull),
  ("number?", Procedure isNumber),
  ("boolean?", Procedure isBoolean),
  ("variable?", Procedure isVariable),
  ("string?", Procedure isStringHal),
  ("pair?", Procedure isPair)] ++ baseEnvThird

baseEnvThird :: [([Char], Expression)]
baseEnvThird = [
  ("number-equals?", Procedure numberEquals),
  ("boolean-equals?", Procedure booleanEquals),
  ("variable-equals?", Procedure variableEquals),
  ("string-equals?", Procedure stringEquals),
  ("atom?", Procedure atomEquals),
  ("list", Procedure createList),
  ("not", Procedure notBoolean),
  ("and", Procedure andBoolean)] ++ baseEnvForth

baseEnvForth :: [([Char], Expression)]
baseEnvForth = [
  ("or", Procedure orBoolean),
  ("cons", Procedure createPair),
  ("car", Procedure pairFirst),
  ("cdr", Procedure pairSecond),
  ("<", Procedure numberLessThan),
  (">", Procedure numberGreaterThan),
  ("let", Procedure stopProgram)]

stopProgram :: [Expression] -> Expression
stopProgram _ = Exception "Let not taken"

isVariable :: [Expression] -> Expression
isVariable [Variable _] = Boolean True
isVariable _ = Boolean False

isStringHal :: [Expression] -> Expression
isStringHal [Chars _] = Boolean True
isStringHal _ = Boolean False

isNumber :: [Expression] -> Expression
isNumber [Number _] = Boolean True
isNumber _ = Boolean False

isNull :: [Expression] -> Expression
isNull [Null] = Boolean True
isNull _ = Boolean False

isBoolean :: [Expression] -> Expression
isBoolean [Boolean _] = Boolean True
isBoolean _ = Boolean False

isPair :: [Expression] -> Expression
isPair [Pair _ _] = Boolean True
isPair _ = Boolean False

--Comparisions

booleanEquals :: [Expression] -> Expression
booleanEquals [Boolean val1, Boolean val2] = Boolean (val1 == val2)
booleanEquals _ = Boolean False

atomEquals :: [Expression] -> Expression
atomEquals (Pair _ _ : _) = Boolean False
atomEquals _ = Boolean True

numberEquals :: [Expression] -> Expression
numberEquals [Number val1, Number val2] = Boolean (val1 == val2)
numberEquals _ = Boolean False

variableEquals :: [Expression] -> Expression
variableEquals [Variable var1, Variable var2] = Boolean (var1 == var2)
variableEquals _ = Boolean False

stringEquals :: [Expression] -> Expression
stringEquals [Chars var1, Chars var2] = Boolean (var1 == var2)
stringEquals _ = Boolean False

numberLessThan :: [Expression] -> Expression
numberLessThan [Number val1, Number val2] = Boolean (val1 < val2)
numberLessThan _ = Exception "Can't compare non-numbers."

numberGreaterThan :: [Expression] -> Expression
numberGreaterThan [Number val1,Number val2] = Boolean (val1 > val2)
numberGreaterThan _ = Exception "Can't compare non-numbers."

--Math
multiplyNumbers :: [Expression] -> Expression
multiplyNumbers (Number val1:y:xs) = Number (val1 * val2)
  where (Number val2) = multiplyNumbers (y:xs)
multiplyNumbers [Number val] = Number val
multiplyNumbers _ = Exception "Can only add two numbers"

divideNumbers :: [Expression] -> Expression
divideNumbers (Number _:Number 0:_) = Exception "Divide ERROR: second arg 0"
divideNumbers (Number val1:Number val2:[]) = Number (val1 `quot` val2)
divideNumbers (Number val1:Number val2:xs) =
  divideNumbers (Number (val1 `quot` val2):xs)
divideNumbers [Number val] = Number (1 `quot` val)
divideNumbers _ = Exception "Divide ERROR: 2 numbers needed"

addNumbers :: [Expression] -> Expression
addNumbers (Number val1:y:xs) = Number (val1 + val2)
  where (Number val2) = addNumbers (y:xs)
addNumbers [Number val] = Number (val)
addNumbers _ = Exception "Add ERROR: 2 numbers needed"

subtractNumbers :: [Expression] -> Expression
subtractNumbers (Number val1:Number val2:[]) = Number (val1 - val2)
subtractNumbers (Number val1:Number val2:xs) =
  subtractNumbers (Number (val1 - val2):xs)
subtractNumbers [Number val] = Number (-val)
subtractNumbers _ = Exception "Substract ERROR: 2 numbers needed"

modulusNumbers :: [Expression] -> Expression
modulusNumbers [Number val1, Number val2] = Number (val1 `mod` (abs val2))
modulusNumbers _ = Exception "Modulus ERROR: 2 numbers needed"

--Logic
notBoolean :: [Expression] -> Expression
notBoolean [Boolean value] = Boolean (not value)
notBoolean _ = Exception "notBoolean ERROR: Value is not a boolean"

andBoolean :: [Expression] -> Expression
andBoolean [Boolean value1, Boolean value2] = Boolean (value1 && value2)
andBoolean _ = Exception "andBoolean ERROR: Value is not a boolean"

orBoolean :: [Expression] -> Expression
orBoolean [Boolean value1, Boolean value2] = Boolean (value1 || value2)
orBoolean _ = Exception "orBoolean ERROR: Value is not a boolean"

--Pairs
createPair :: [Expression] -> Expression
createPair [first, second] = Pair first second
createPair _ = Exception "createPair ERROR: two args needed"

pairSecond :: [Expression] -> Expression
pairSecond [Pair _ second] = second
pairSecond _ = Exception "pairSecond ERROR: second arg is not a pair"

pairFirst :: [Expression] -> Expression
pairFirst [Pair first _] = first
pairFirst _ = Exception "pairFirst ERROR: first arg is not a pair"

createList :: [Expression] -> Expression
createList = foldr Pair Null

getBaseEnvironment :: Environment 
getBaseEnvironment = Environment (Map.fromList baseEnv) EmptyEnvironment

loadBaseEnvironment :: IO Environment
loadBaseEnvironment =
  do core <- readFile "src/Lexer.scm"
     let parser = analyzeExprSequence . parseSequence . tokenize
         (environment, _) = computeSequence getBaseEnvironment (parser core)
     return environment

printResult :: Expression -> IO ()
printResult (Exception str) = myExitWithErrorMessage str
printResult expr = print expr

loadScmFile :: String -> Environment -> IO (Environment, Bool)
loadScmFile fileName env =
  do core <- readFile fileName
     let parser = analyzeExprSequence . parseSequence . tokenize
         (environment, res) = computeSequence env (parser core)
     printResult res --not sure about printing here
     return (environment, True)