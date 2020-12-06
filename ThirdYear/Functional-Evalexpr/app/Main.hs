module Main where

--Lib imports

import System.Environment
import System.Exit
import Structure
import Compute
import Parsing
import ParsingPriority

--Std imports
import System.Environment ( getArgs )
import System.Exit ()
import Text.Printf ( printf )
import Foreign.C
import System.IO
import System.Exit
--import Text.Read ( readMaybe )

myExitWith :: Int -> IO a
myExitWith 0 = exitWith (ExitSuccess)
myExitWith n = exitWith (ExitFailure n)

myExitWithErrorMessage :: String -> IO a
myExitWithErrorMessage str = hPutStrLn stderr str >> myExitWith 84

printDouble :: Maybe Double -> IO()
printDouble Nothing = putStrLn "Error: program returned with: Nothing"
printDouble (Just val) = printf "%.2f\n" val

checkNothing :: [Token] -> Bool
checkNothing [] = True
checkNothing ((Token Nothing Nothing):xs) = False
checkNothing (x:xs) = checkNothing xs

main :: IO ()
main = do
    args <- getArgs

    if ((length args) /= 1) then
        myExitWithErrorMessage "Arguments are wrong."
    else
        return ()

    let tokens = (parseStringToTokens (args !! 0))

    if ((length tokens) == 0 || (checkNothing tokens) == False) then
        myExitWithErrorMessage "Can't create tokens (Syntax error)"
    else
        return ()

    --printTokens tokens

    let ret = compute tokens []

    if (ret == Nothing) then
      myExitWithErrorMessage "Compute function returned Nothing (Syntax error)"
    else
      return ()
    printDouble ret
    myExitWith 0