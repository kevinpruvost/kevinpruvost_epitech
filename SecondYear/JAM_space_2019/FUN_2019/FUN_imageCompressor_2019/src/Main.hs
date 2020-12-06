-- Haskell Std includes
import System.Environment
import System.Exit
import Data.Char

-- Files includes
import ImageCompressor
import Structures
import Parsing
import ParseArgs

main = do
    args <- getArgs

    if ((length args) /= 3) then
        myExitWithErrorMessage "Arguments are wrong."
    else
        return ()

    let colorNumbers = readInt (args !! 0)
    let convergence = readDouble (args !! 1)

    if (colorNumbers == Nothing || just colorNumbers <= 0 || convergence == Nothing || just convergence < 0) then
        myExitWithErrorMessage "Arguments are wrong."
    else
        return ()

    let fileName = (args !! 2)

    file <- readFile fileName
    let filePixels = getPixelsFromLines $ lines file
    reds <- randomList $ just colorNumbers
    greens <- randomList $ just colorNumbers
    blues <- randomList $ just colorNumbers
    let centroids = getRandomCentroidsFromPixels 0 reds greens blues

    let gen = Gen filePixels centroids [] 0

    --debugPrint gen -- DEBUG

    if (not $ verifyGen gen) then
        myExitWithErrorMessage "Error while parsing file."
    else
        return ()

    fullOutput gen
    compressImage (just colorNumbers) (just convergence) gen

    myExitWith 0