module Parser
( tokenize,
parseSequence,
analyzeExpr,
analyzeExprSequence
) where

import Structures

createListParsing :: [Expression] -> Expression
createListParsing = foldr Pair Null

isSymbolCharacter :: Char -> Bool
isSymbolCharacter ch =
  ch `elem` "ABCDEFGHIJKLMNOPQRSTUVWXYZ\
  \abcdefghijklmnopqrstuvwxyz'`0123456789_!?-+*/%<>#"

isNumberCharacter :: Char -> Bool
isNumberCharacter ch = ch `elem` "0123456789-"

isStringSymbol :: String -> Bool
isStringSymbol = all isSymbolCharacter

isStringNumber :: String -> Bool
isStringNumber "-" = False
isStringNumber str = all isNumberCharacter str

tokenize :: String -> [String]
tokenize [] = []
tokenize ('(':xs) = "(" : tokenize xs
tokenize (')':xs) = ")" : tokenize xs
tokenize ('\'':xs) = "'" : tokenize xs
tokenize ('`':xs) = "'" : tokenize xs
tokenize (x:xs)
  | isNumberCharacter x = tokenizeNumber (x:xs) ""
  | isSymbolCharacter x = tokenizeSymbol (x:xs) ""
  | otherwise = tokenize xs

tokenizeNumber :: String -> String -> [String]
tokenizeNumber [] number = [number]
tokenizeNumber (x:xs) number
  | isNumberCharacter x = tokenizeNumber xs (number ++ [x])
  | otherwise = number : tokenize (x:xs)

tokenizeSymbol :: String -> String -> [String]
tokenizeSymbol [] symbol = [symbol]
tokenizeSymbol (x:xs) number
  | isSymbolCharacter x = tokenizeSymbol xs (number ++ [x])
  | otherwise = number : tokenize (x:xs)

parse :: [String] -> (Expression, [String])
parse [] = (Null, [])
parse ("(":"quote":"(":xs) = parseQuoteSpecialList xs
parse ("'":"(":xs) = parseQuoteList xs
parse ("(":"quote":xs:")":xss) = parseQuote (xs:xss)
parse ("'":xs) = parseQuote xs
parse ("(":xs) = parseList xs
parse xs = parseOtherCases xs

parseOtherCases :: [String] -> (Expression, [String])
parseOtherCases ("(":xs) = parseList xs
parseOtherCases ("#t":xs) = (Boolean True, xs)
parseOtherCases ("#f":xs) = (Boolean False, xs)
parseOtherCases ("null":xs) = (Null, xs)
parseOtherCases (x:xs)
  | isStringNumber x = (Number (read x :: Int), xs)
  | isStringSymbol x = (Variable x, xs)
  | otherwise = (Null, [])

parseQuote :: [String] -> (Expression, [String])
parseQuote [] = (Null, [])
parseQuote ("(":xs) = parseQuoteList xs
parseQuote ("#t":xs) = (Boolean True, xs)
parseQuote ("#f":xs) = (Boolean False, xs)
parseQuote ("null":xs) = (Null, xs)
parseQuote (x:xs)
  | isStringNumber x = (Number (read x :: Int), xs)
  | isStringSymbol x = (Chars x, xs)
  | otherwise = (Null, [])

parseQuoteList :: [String] -> (Expression, [String])
parseQuoteList [] = (Null, [])
parseQuoteList ("(":xs) = parseQuoteList xs
parseQuoteList (")":xs) = (Null, xs)
parseQuoteList tokens = ((Pair expr1 expr2), rest2)
  where (expr1, rest1) = parseQuote tokens
        (expr2, rest2) = parseQuoteList rest1

parseQuoteSpecialList :: [String] -> (Expression, [String])
parseQuoteSpecialList [] = (Null, [])
parseQuoteSpecialList ("(":xs) = parseQuoteList xs
parseQuoteSpecialList (")":")":xs) = (Null, xs)
parseQuoteSpecialList tokens = ((Pair expr1 expr2), rest2)
  where (expr1, rest1) = parseQuote tokens
        (expr2, rest2) = parseQuoteSpecialList rest1


parseList :: [String] -> (Expression, [String])
parseList [] = (Null, [])
parseList (")":xs) = (Null, xs)
parseList tokens = (Pair expr1 expr2, rest2)
                where (expr1, rest1) = parse tokens
                      (expr2, rest2) = parseList rest1

parseSequence :: [String] -> [Expression]
parseSequence [] = []
parseSequence tokens = expr : parseSequence rest
                       where (expr, rest) = parse tokens

analyzeExpr :: Expression -> Expression
analyzeExpr pair@(Pair _ _)
  | isIfExpr pair = buildIfExpr pair
  | isLambdaExpr pair = buildLambdaExpr pair
  | isDefinitionExpr pair = buildDefinitionExpr pair
  | isCondExpr pair = buildCondExpr pair
  | isLetExpr pair = buildLetExpr pair
  | otherwise = buildApplicationExpr pair
analyzeExpr expr = analyzeExpr2 expr

analyzeExpr2 :: Expression -> Expression
analyzeExpr2 Null = Null
analyzeExpr2 (Number number) = Number number
analyzeExpr2 (Boolean bool) = Boolean bool
analyzeExpr2 (Variable variable) = Variable variable
analyzeExpr2 (Chars str) = Chars str
analyzeExpr2 _ = Null

isIfExpr :: Expression -> Bool
isIfExpr (Pair (Variable value) _) = value == "if"
isIfExpr _ = False

isLetExpr :: Expression -> Bool
isLetExpr (Pair (Variable value) _) = value == "let"
isLetExpr _ = False

buildLetExpr :: Expression -> Expression
buildLetExpr x = error "let not done"

buildIfExpr :: Expression -> Expression
buildIfExpr (Pair _ (Pair predicate
  (Pair thenClause (Pair elseClause Null)))) =
  If (analyzeExpr predicate) (analyzeExpr thenClause) (analyzeExpr elseClause)

isLambdaExpr :: Expression -> Bool
isLambdaExpr (Pair (Variable value) _) = value == "lambda"
isLambdaExpr _ = False

buildLambdaExpr :: Expression -> Expression
buildLambdaExpr (Pair _ (Pair parameters (Pair body Null))) =
  Lambda (pairToList parameters) (analyzeExpr body)

isDefinitionExpr :: Expression -> Bool
isDefinitionExpr (Pair (Variable value) _) = value == "define"
isDefinitionExpr _ = False

buildDefinitionExpr :: Expression -> Expression
buildDefinitionExpr (Pair _ (Pair (Pair name rest) (Pair value Null))) =
  Definition name (Lambda (pairToList rest) (analyzeExpr value))
buildDefinitionExpr (Pair _ (Pair variable (Pair value Null))) =
  Definition variable (analyzeExpr value)

isCondExpr :: Expression -> Bool
isCondExpr (Pair (Variable value) _) = value == "cond"
isCondExpr _ = False

buildCondExpr :: Expression -> Expression
buildCondExpr (Pair _ second) = buildCondExpr2 second

buildCondExpr2 :: Expression -> Expression
buildCondExpr2 Null = Cond []
buildCondExpr2 (Pair (Pair predicate (Pair expression Null)) other) =
  Cond ((analyzeExpr predicate, analyzeExpr expression) : cases)
  where (Cond cases) = buildCondExpr2 other

buildApplicationExpr :: Expression -> Expression
buildApplicationExpr pair@(Pair operator operands)
  | isNumExpr pair = Pair operator operands
  | isCharsExpr pair = Pair operator operands
  | isBoolExpr pair = Pair operator operands
  | otherwise =
    Application (analyzeExpr operator) (map analyzeExpr (pairToList operands))

isNumExpr :: Expression -> Bool
isNumExpr (Pair (Number value) _) = True
isNumExpr _ = False

isCharsExpr :: Expression -> Bool
isCharsExpr (Pair (Chars value) _) = True
isCharsExpr _ = False

isBoolExpr :: Expression -> Bool
isBoolExpr (Pair (Boolean value) _) = True
isBoolExpr _ = False

analyzeExprSequence :: [Expression] -> [Expression]
analyzeExprSequence list = (map analyzeExpr (checkExprArrayError list))

checkExprArrayError :: [Expression] -> [Expression]
checkExprArrayError [] = []
checkExprArrayError (x:xs) = (checkExprError x) : (checkExprArrayError xs)

checkExprError :: Expression -> Expression
checkExprError pair@(Pair val1 val2)
  | isPairError pair = error "let not done"
  | otherwise = pair
checkExprError x = x

isPairError :: Expression -> Bool
isPairError pair@(Pair val1 val2)
  | isLetExpr pair = True
  | isPairError val1 = True
  | isPairError val2 = True
  | otherwise = False
isPairError x = False