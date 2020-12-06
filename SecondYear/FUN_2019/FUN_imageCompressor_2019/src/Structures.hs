module Structures where

-- Haskell Std includes
import Foreign.C
import System.IO
import System.Exit

data Pixel = Pixel { x :: Int, y :: Int, r :: Int, g :: Int, b :: Int }
data Gen = Gen { pixels :: [Pixel], centroids :: [Pixel] , pixelGroups :: [(Pixel, [Pixel])], error :: Int}

basePixel :: Pixel
basePixel = Pixel { x = 0, y = 0, r = 0, g = 0, b = 0 }

pixelCstr :: Int -> Int -> Int -> Int -> Int -> Pixel
pixelCstr x y r g b = (Pixel x y r g b)

myExitWith :: Int -> IO a
myExitWith 0 = exitWith (ExitSuccess)
myExitWith n = do
    exitWith (ExitFailure 84)

myExitWithErrorMessage :: String -> IO a
myExitWithErrorMessage str = hPutStrLn stderr str >> myExitWith 84

verifyPixel :: Pixel -> Bool
verifyPixel (Pixel x y r g b)
    | r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255 || x < 0 || y < 0 = False
    | otherwise = True

verifyPixels :: [Pixel] -> Bool
verifyPixels [] = True
verifyPixels (x:xs)
    | verifyPixel x == False = False
    | otherwise = verifyPixels xs

verifyGen :: Gen -> Bool
verifyGen (Gen pixels centroids _ errorCode)
    | errorCode /= 0 || (verifyPixels pixels) == False || (verifyPixels centroids) == False = False
    | otherwise = True