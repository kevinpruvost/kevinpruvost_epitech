module Parsing where

--Project imports

import ParsingErrorManagement
import Structure
import Data.Char
import ParsingPriority

-- Morphs it to tokens

numberPartOfString :: String -> (String, String)
numberPartOfString [] = ([], [])
numberPartOfString (x:xs)
    | (isDigit x) == True || (x `elem` ".") == True = (x : following, rest) --J'ai utilié la fonction elem a cause de la norme
    | otherwise = ([], (x:xs))
        where (following, rest) = numberPartOfString xs

morphStrChunkToNumber :: String -> (Token, String)
morphStrChunkToNumber str =
    ((createTokenNumber (read nbStr::Double)), rest)
        where (nbStr, rest) = numberPartOfString str

morphStrToSimpleTokens :: String -> [Token]
morphStrToSimpleTokens [] = []
morphStrToSimpleTokens (x:xs)
    | (isDigit x) == True = token : (morphStrToSimpleTokens rest)
    | otherwise = (createTokenChar x) : (morphStrToSimpleTokens xs)
        where (token, rest) = morphStrChunkToNumber (x:xs)

manageMultiply :: [Token] -> [Token]
manageMultiply [] = []
manageMultiply [x] = [x]
manageMultiply (x:y:xs)
    | (isTokenThisChar x ')') == True && (isTokenThisChar y '(') == True =
        (x:(createTokenChar '*'):(manageMultiply (y:xs)))
    | (isTokenNumber x) == True && (isTokenThisChar y '(') =
        (x:(createTokenChar '*'):(manageMultiply (y:xs)))
    | (isTokenNumber y) == True && (isTokenThisChar x ')') =
        (x:(createTokenChar '*'):(manageMultiply (y:xs)))
    | otherwise = (x:(manageMultiply (y:xs)))

manageAdd2 :: [Token] -> [Token]
manageAdd2 [] = []
manageAdd2 [x] = [x]
manageAdd2 (x:y:z:[]) | isCharOperatorT x && (isTokenThisChar y '+') = (x:z:[])
                     | otherwise = (x:y:z:[])
manageAdd2 (x:y:z:xs) | (isCharOperatorT x) &&
                       (isTokenThisChar y '+') = (manageAdd2 (x:z:xs))
                     | otherwise = (x:(manageAdd2 (y:z:xs)))
manageAdd2 (x:y:xs) | (isTokenThisChar x '+') = (y:xs)
                   | otherwise = (x:y:xs)

mergeMinus :: [Token] -> [Token]
mergeMinus [] = []
mergeMinus [x] = [x]
mergeMinus (x:y:xs)
    | (isTokenThisChar x '-') &&
      (isTokenThisChar y '-') = ((createTokenChar '+'):xs)
    | otherwise = (x:(mergeMinus (y:xs)))

negateTokenNumber :: Token -> Token
negateTokenNumber (Token (Just nb) Nothing) = createTokenNumber (-nb)
negateTokenNumber x = x

nextmMinus :: [Token] -> [Token]
nextmMinus (x:y:z:xs)
    | not (isTokenThisChar x ')') && not (isTokenNumber x) && (isTokenNumber z)
    && (isTokenThisChar y '-') = (x: (negateTokenNumber z) : nextmMinus xs)
    | otherwise = (x: nextmMinus(y:z:xs))
nextmMinus x = x

mMinus :: [Token] -> [Token]
mMinus (x:y:xs)
    | (isTokenThisChar x '-') && (isTokenNumber y) =
        (negateTokenNumber y) : (nextmMinus xs)
mMinus x = nextmMinus x

manageAdd :: [Token] -> [Token]
manageAdd [] = []
manageAdd [x] = [x]
manageAdd (x:xs) | (isTokenThisChar x '+') = manageAdd2 mergedXs
                 | otherwise = manageAdd2 (mergedXxs)
                 where mergedXs = mMinus (mergeMinus xs)
                       mergedXxs = mMinus (mergeMinus (x:xs))

parseEmptyParenthesesRem :: String -> String
parseEmptyParenthesesRem [] = []
parseEmptyParenthesesRem [x] = [x]
parseEmptyParenthesesRem ('(':')':xs) = xs
parseEmptyParenthesesRem (x:xs) = (x: (parseEmptyParenthesesRem xs))

parseEmptyParentheses :: String -> String
parseEmptyParentheses str
    | strRem /= str = parseEmptyParentheses strRem
    | otherwise = str
        where strRem = parseEmptyParenthesesRem str

isEmptyParentheses :: String -> Bool
isEmptyParentheses [] = False
isEmptyParentheses [x] = False
isEmptyParentheses ('(':')':xs) = True
isEmptyParentheses (x:xs) = isEmptyParentheses xs

-- Main functions to call

parseStringToTokens :: String -> [Token]
parseStringToTokens [] = []
parseStringToTokens str
    | (isTokensStringValid str) == False
        || (isEmptyParentheses str)
        || ((isTokensStringParenthesisValid str) /= 0)
        || (isTokensStringSeparatorValid str) == False
        || (((head str) `elem` "0123456789+-( \t") == False) = []
    | otherwise = managePriority (manageMultiply string)
        where string = manageAdd (morphStrToSimpleTokens string1)
              string1 = parseEmptyParentheses (cleanTokensString str)

testParsing :: String -> IO()
testParsing str = printTokens tokens
    where tokens = parseStringToTokens str

testDouble :: String -> IO()
testDouble str = print (read str::Double)