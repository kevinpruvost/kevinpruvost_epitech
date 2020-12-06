module ASpec where

import Test.Hspec
import Parser
import Structures
import Compute
import Lexer
import Data.List

spec :: Spec
spec = do
    describe "Prelude.head" $ do
        it "Basic parsing tests" $ do
          intercalate  "," (tokenize "(add 5 2)") `shouldBe` "(,add,5,2,)"
          intercalate  "," (tokenize "(sub 1 54)") `shouldBe` "(,sub,1,54,)"
          intercalate  "," (tokenize "(div 2 12)") `shouldBe` "(,div,2,12,)"
          intercalate  "," (tokenize "(mult 5 2)") `shouldBe` "(,mult,5,2,)"
          intercalate  "," (tokenize "(mod 25 5)") `shouldBe` "(,mod,25,5,)"
          intercalate  "," (tokenize "(* 5 2)") `shouldBe` "(,*,5,2,)"
          intercalate  "," (tokenize "(- 5 2)") `shouldBe` "(,-,5,2,)"
          intercalate  "," (tokenize "(+ -45 2 8)") `shouldBe` "(,+,-45,2,8,)"
          intercalate  "," (tokenize "(+ 58 2)") `shouldBe` "(,+,58,2,)"
        it "Basic parsing logic tests" $ do
          intercalate  "," (tokenize "(null? '(1 2 3))") `shouldBe` "(,null?,',(,1,2,3,),)"
          intercalate  "," (tokenize "(null? '(1 2 3))") `shouldBe` "(,null?,',(,1,2,3,),)"
          intercalate  "," (tokenize "(number? '(1 2 3))") `shouldBe` "(,number?,',(,1,2,3,),)"
          intercalate  "," (tokenize "(boolean? '(1 2 3))") `shouldBe` "(,boolean?,',(,1,2,3,),)"
          intercalate  "," (tokenize "(variable? '(1 2 3))") `shouldBe` "(,variable?,',(,1,2,3,),)"
          intercalate  "," (tokenize "(string? '(1 2 3))") `shouldBe` "(,string?,',(,1,2,3,),)"
          intercalate  "," (tokenize "(pair? (cons 1 2))") `shouldBe` "(,pair?,(,cons,1,2,),)"
          intercalate  "," (tokenize "(boolean-equals? (cons 1 2))") `shouldBe` "(,boolean-equals?,(,cons,1,2,),)"
          intercalate  "," (tokenize "(atom? '())") `shouldBe` "(,atom?,',(,),)"
        it "Expression parsing tests" $ do
          intercalate "," (map show (parseSequence (tokenize "(define x 12)      (add x 5)"))) `shouldBe` "(define x 12),(add x 5)"
          intercalate "," (map show (analyzeExprSequence $ parseSequence (tokenize "(define x 12)      (add x 5)"))) `shouldBe` "#<definition> : x12,#<procedure>"
          length (parseSequence (tokenize "(sub 12 21) (add 21 1)")) `shouldBe` 2