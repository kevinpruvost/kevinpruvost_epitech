module MyExit where

import System.Exit
import System.Environment
import System.IO

myExitWith :: Int -> IO a
myExitWith 0 = exitWith (ExitSuccess)
myExitWith n = exitWith (ExitFailure n)

myExitWithErrorMessage :: String -> IO a
myExitWithErrorMessage str = hPutStrLn stderr str >> myExitWith 84