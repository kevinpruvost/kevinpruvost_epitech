module Main where

-- Std includes
import System.Exit
import System.Environment
import System.IO

-- Project includes
import Structures
import Compute
import Lexer
import Parser
import Control.Exception
import MyExit

printResultCli :: Expression -> IO ()
printResultCli (Exception str) = myExitWithErrorMessage str
printResultCli expr = print expr

--Handler called when an exception occurs
handler :: SomeException -> IO ()
handler ex = hPutStrLn stderr ("Caught exception: " ++ show ex)
  >> myExitWith 84

main :: IO ()
main = catch identifyCliOrFiles handler >> myExitWith 0

cli :: Environment -> IO ()
cli env = do
        putStr "> "
        hFlush stdout
        line <- getLine
        if line == "quit" then myExitWith 0 else return ()
        let parser = analyzeExprSequence . parseSequence . tokenize
            (newEnv, result) = computeSequence env (parser line)
        printResultCli result
        cli newEnv

loadFiles :: Environment -> [String] -> IO ()
loadFiles _ [] = return ()
loadFiles env (file:otherFiles) = do
    (newEnv, errorCode) <- loadScmFile file env
    (if errorCode then loadFiles newEnv otherFiles else myExitWith 84)
    return ()

identifyCliOrFiles :: IO ()
identifyCliOrFiles = do
    env <- loadBaseEnvironment
    args <- getArgs
    case args of
        [] -> cli env
        args -> loadFiles env args