module Structure where

-- Std includes
import Data.Char
import Text.Read

data Token = Token { nb :: Maybe Double, ope :: Maybe Char} deriving (Show)

createTokenNumberC :: Char -> Token
createTokenNumberC n = Token { nb = Just (read [n]::Double), ope = Nothing}

createTokenNumber :: Double -> Token
createTokenNumber n = Token { nb = Just n, ope = Nothing}

createTokenNumberFromMaybe :: Maybe Double -> Token
createTokenNumberFromMaybe n = Token { nb = n, ope = Nothing}

createTokenChar :: Char -> Token
createTokenChar ch = Token { nb = Nothing, ope = Just ch}

printToken :: Token -> IO()
printToken (Token (Just nb) Nothing) = print nb
printToken (Token Nothing (Just ch)) = print ch

printTokens :: [Token] -> IO()
printTokens [] = return ()
printTokens (x:xs) = printToken x >> printTokens xs

isTokenNumber :: Token -> Bool
isTokenNumber (Token (Just _) Nothing) = True
isTokenNumber _ = False

isTokenChar :: Token -> Bool
isTokenChar (Token Nothing (Just _)) = True
isTokenChar _ = False

isTokenThisChar :: Token -> Char -> Bool
isTokenThisChar (Token Nothing (Just ch)) comp = (ch == comp)
isTokenThisChar _ _ = False

isTokenC :: Token -> Char -> Bool
isTokenC (Token Nothing (Just ch)) comp = (ch == comp)
isTokenC _ _ = False

mergeTokenNumber :: Token -> Token -> Token
mergeTokenNumber (Token (Just nb1) Nothing) (Token (Just nb2) Nothing) =
    (Token (Just (nb1 * 10 + nb2)) Nothing)