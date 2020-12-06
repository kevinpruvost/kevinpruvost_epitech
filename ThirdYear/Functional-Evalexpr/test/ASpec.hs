module ASpec where

import Test.Hspec
import Parsing
import Structure
import Compute

hSpecParsingC :: [Token] -> String
hSpecParsingC [] = ""
hSpecParsingC ((Token (Just nb) Nothing):xs) =
    (show nb) ++ hSpecParsingC xs
hSpecParsingC ((Token Nothing (Just ch)):xs) = [ch] ++ hSpecParsingC xs
hSpecParsingC (_:xs) = "" ++ hSpecParsingC xs

hSpecParsing :: String -> String
hSpecParsing str = hSpecParsingC (parseStringToTokens str)

spec :: Spec
spec = do
    describe "Prelude.head" $ do
        it "Classical error" $ do
            (hSpecParsing "xd") `shouldBe` ""
            (hSpecParsing "oeuf") `shouldBe` ""
            (hSpecParsing "   ") `shouldBe` ""
            (hSpecParsing "\t") `shouldBe` ""
            (hSpecParsing "x x x ") `shouldBe` ""
            (hSpecParsing "()") `shouldBe` ""
            (hSpecParsing "") `shouldBe` ""
        it "Tabs test" $ do
            (hSpecParsing "4+\t-4") `shouldBe` "4.0-4.0+"
            (hSpecParsing "1 4 7 2 5 \t\t8 3  \t\t") `shouldBe` "1472583.0"
        it "Basic computation tests" $ do
            (compute (parseStringToTokens "2+2") []) `shouldBe` (Just 4)
            (compute (parseStringToTokens "2-2") []) `shouldBe` (Just 0)
            (compute (parseStringToTokens "2*2") []) `shouldBe` (Just 4)
            (compute (parseStringToTokens "2/2") []) `shouldBe` (Just 1)
            (compute (parseStringToTokens "2^2") []) `shouldBe` (Just 4)
            (compute (parseStringToTokens "4+2*3") []) `shouldBe` (Just 10)
            (compute (parseStringToTokens "(2*2)") []) `shouldBe` (Just 4)
            (compute (parseStringToTokens "2*(2-2)") []) `shouldBe` (Just 0)
            (compute (parseStringToTokens "1^2^3^4^5") []) `shouldBe` (Just 1)
        it "Test with syntax error" $ do
            (compute (parseStringToTokens "8/0") []) `shouldBe` Nothing
            (compute (parseStringToTokens "2-(2/0)+4") []) `shouldBe` Nothing
            (compute (parseStringToTokens "2+(-4)*8/16*52+(4-10)/0+24*7") []) `shouldBe` Nothing
            (compute (parseStringToTokens "salut moi c baptite et toi ?") []) `shouldBe` Nothing
        it "Random calculous" $ do
            (compute (parseStringToTokens "2+2") []) `shouldBe` (Just 4)
            (compute (parseStringToTokens "2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2+2") []) `shouldBe` (Just 40)
            (compute (parseStringToTokens "2+((2-2)*4") []) `shouldBe` Nothing
            (compute (parseStringToTokens "2+(4-2)*3") []) `shouldBe` (Just 8)
            (compute (parseStringToTokens "1000*1000/100") []) `shouldBe` (Just 10000)
            (compute (parseStringToTokens "10/5/2") []) `shouldBe` (Just 1)
            (compute (parseStringToTokens "3^2^4") []) `shouldBe` (Just 6561)
            (compute (parseStringToTokens "12*2+4*3/4/8/4-2") []) `shouldBe` (Just 22.09375)
            (compute (parseStringToTokens "3+4*2/(1-5)^2^3") []) `shouldBe` (Just 3.001953125)
            (compute (parseStringToTokens "8+2+3+4-8*2+4/6") []) `shouldBe` (Just 1.6666666666666665)
            (compute (parseStringToTokens "(2+2-(4/2)*(4+(7*3)+2-4)^2)") []) `shouldBe` (Just (-1054))
