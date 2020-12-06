module Wolfram where

import System.Environment
import System.Exit
import Data.Char

import Tools

-- (rule, gen start, nb lines, window width, move)

wolframLoop :: (Int, Int, Int, Int, Int) -> [Int] -> IO()
wolframLoop (a, b, c, d, e) z
    | b == 0 && c /= 0 = do
        printLine z d e
        let list = (compute a z)
        wolframLoop (a, b, c - 1, d, e) list
    | b > 0 && c /= 0 = do
        let list = (compute a z)
        wolframLoop (a, b - 1, c, d, e) list
    | c == 0 = return ()
    | otherwise = error "wolframLoop"

wolfram :: (Int, Int, Int, Int, Int) -> IO()
wolfram (a, b, c, d, e) = do
    let list = [1] -- createBaseLine (b, c, d, e)
    wolframLoop (a, b, c, d, e) list