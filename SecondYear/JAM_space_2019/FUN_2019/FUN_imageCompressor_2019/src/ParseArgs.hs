module ParseArgs where

-- Std includes
import System.Environment
import System.Exit
import Data.Char
import Text.Read

isSingleCharInt :: Char -> Bool
isSingleCharInt x
    | x == '0' || x == '1' || x == '2' || x == '3' || x == '4' || x == '5' || x == '6' || x == '7' || x == '8' || x == '9' || x == '-' || x == '.' = True
    | otherwise = False

verifyInt :: [Char] -> Bool
verifyInt (x:xs)
    | isSingleCharInt x == False = False
    | otherwise = verifyInt xs
verifyInt [] = True

readInt :: [Char] -> Maybe Int
readInt xs = readMaybe xs :: Maybe Int

readDouble :: [Char] -> Maybe Double
readDouble xs = readMaybe xs :: Maybe Double

just :: (Maybe a) -> a
just Nothing = error "wtf"
just (Just x) = x

parseIsEmpty :: [[Char]] -> Bool
parseIsEmpty [] = False
parseIsEmpty xs = True