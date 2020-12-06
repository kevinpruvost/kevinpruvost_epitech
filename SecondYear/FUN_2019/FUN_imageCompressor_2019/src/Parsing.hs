module Parsing where

import Data.List
import Text.Read
import Data.Maybe
import System.Random

import Structures
import ImageCompressor

myReplace :: String -> String -> String -> String
myReplace _ _ [] = ""
myReplace delimiters repStr (x:xs)
    | findIndex (==x) delimiters == Nothing = [x] ++ myReplace delimiters repStr xs
    | otherwise = repStr ++ myReplace delimiters repStr xs

createPixelFormLine :: [Maybe Int] -> Pixel
createPixelFormLine xs
    | length xs /= 5 = (pixelCstr (-1) (-1) (-1) (-1) (-1))
createPixelFormLine (x:y:r:g:b:[])
    | x == Nothing || y == Nothing || r == Nothing || g == Nothing || b == Nothing = pixelCstr (-1) (-1) (-1) (-1) (-1)
createPixelFormLine (Just x:Just y:Just r:Just g:Just b:[]) = pixelCstr x y r g b

getPixelsFromLines :: [String] -> [Pixel]
getPixelsFromLines [] = []
getPixelsFromLines (x:xs) = [createPixelFormLine $ map (readMaybe :: String -> Maybe Int) $ words $ myReplace "," " " $ myReplace "()" "" x] ++ getPixelsFromLines xs

--Centroid generation

getRandomCentroidsFromPixels :: Int -> [Int] -> [Int] -> [Int] -> [Pixel]
getRandomCentroidsFromPixels k reds greens blues
    | k < length reds = [pixelCstr 0 0 (reds!!k) (greens!!k) (blues!!k)] ++ getRandomCentroidsFromPixels (k+1) reds greens blues
    | otherwise = []

randomList :: Int -> IO([Int])
randomList 0 = return []
randomList n = do
    r  <- randomRIO (0,255)
    rs <- randomList (n-1)
    return (r:rs)

--debug

debugPrint :: Gen -> IO()
debugPrint (Gen pixels centroids _ _) = do
    putStrLn "--Parsing file--"
    printPixels pixels
    putStrLn "-Generating centroids-"
    printPixels centroids
    putStrLn "\n"