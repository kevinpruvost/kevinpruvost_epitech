-- Haskell Std includes
import System.Environment
import System.Exit
import Data.Char

-- Files includes
import Wolfram
import ParseArgs

myExitWith :: Int -> IO a
myExitWith 0 = exitWith (ExitSuccess)
myExitWith n = do
    putStrLn "./wolfram --rule 0--255\n"
    putStrLn "--rule : ruleset to use"
    putStrLn "--start : starting generation (default : 0)"
    putStrLn "--lines : nb of lines to display (default : infinite)"
    putStrLn "--window : cells per line (default : 80)"
    putStrLn "--move : translation applied on the window"
    exitWith (ExitFailure 84)

identifyError :: (Int, Int, Int, Int, Int) -> Int
identifyError (a, b, c, d, e)
    | a < 0 || a > 255 = 84
    | b < 0 = 84
    | c <= 0 && c /= -84 = 84
    | d <= 0 = 84
    | otherwise = 0

main = do
    args <- getArgs

    if ((parseBug args True) == False || (parseIsEmpty args) == False) then
        myExitWith 84
    else
        return ()

    let params = parseParams args (0, 0, -84, 80, 0)

    let mainExitCode = identifyError params

    if (mainExitCode == 0) then
        wolfram params
    else
        return ()

    myExitWith mainExitCode