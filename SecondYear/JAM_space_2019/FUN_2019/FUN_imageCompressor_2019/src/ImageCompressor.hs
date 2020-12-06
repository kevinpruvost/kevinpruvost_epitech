module ImageCompressor where

-- Imports
import Structures
import Text.Printf

--------------------------------- OUTPUT ---------------------------------------

printCentroid :: Pixel -> IO()
printCentroid (Pixel _ _ r g b) = do
    printf "(%d,%d,%d)\n" r g b

printPixel :: Pixel -> IO()
printPixel (Pixel x y r g b) = do
    printf "(%d,%d) (%d,%d,%d)\n" x y r g b

printPixels :: [Pixel] -> IO()
printPixels [] = return ()
printPixels (x:xs) = do
    printPixel x
    printPixels xs

pixelGroupsOutput :: [(Pixel, [Pixel])] -> IO()
pixelGroupsOutput [] = return ()
pixelGroupsOutput ((centroid, pixels):xs) = do
    printf "--\n"
    printCentroid centroid
    printf "-\n"
    printPixels pixels
    pixelGroupsOutput xs

fullOutput :: Gen -> IO()
fullOutput (Gen _ _ pixelGroups _) = pixelGroupsOutput pixelGroups

------------------------------ GROUPING PIXELS ---------------------------------

sortPixelsCentroid :: Pixel -> [Pixel] -> [Pixel]
sortPixelsCentroid _ [] = []
sortPixelsCentroid centroid (x:y:xs)
    | (distance centroid x) > (distance centroid y) = y : (sortPixelsCentroid centroid (x:xs))
    | otherwise = x : (sortPixelsCentroid centroid (y:xs))
sortPixelsCentroid _ (x:xs) = [x]

headPixels :: [Pixel] -> Int -> [Pixel]
headPixels [] _ = []
headPixels xs n = take ((length xs) `div` n) xs

distance :: Pixel -> Pixel -> Double
distance (Pixel _ _ p1r p1g p1b) (Pixel _ _ p2r p2g p2b) = 
    ((p2rf - p1rf) ^ 2 + (p2gf - p1gf) ^ 2 + (p2bf - p1bf) ^ 2) ** (1.0 / 2.0)
    where p2rf = fromIntegral p2r::Double
          p1rf = fromIntegral p1r::Double
          p2gf = fromIntegral p2g::Double
          p1gf = fromIntegral p1g::Double
          p2bf = fromIntegral p2b::Double
          p1bf = fromIntegral p1b::Double

sumDistance :: Pixel -> [Pixel] -> Double
sumDistance centroid [] = 0
sumDistance centroid (p1:ps) = (distance centroid p1) + (sumDistance centroid ps)

closeList :: Pixel -> Int -> [Pixel] -> [Pixel]
closeList centroid nbColors pixels = (headPixels (sortPixelsCentroid centroid pixels) nbColors)

comparePixel :: Pixel -> Pixel -> Bool
comparePixel (Pixel ax ay ar ag ab) (Pixel bx by br bg bb)
    | ax == bx && ay == by && ag == bg && ar == br && ab == bb = True
    | otherwise = False

removeElemFromList :: Pixel -> [Pixel] -> [Pixel]
removeElemFromList _ [] = []
removeElemFromList pixel (pixa:pixs)
    | (comparePixel pixel pixa) == True = pixs
    | otherwise = (pixa:(removeElemFromList pixel pixs))

removePixelsFromGroup :: [Pixel] -> (Pixel, [Pixel]) -> [Pixel]
removePixelsFromGroup pixels (centroid, []) = pixels
removePixelsFromGroup pixels (centroid, (p:ps)) = removePixelsFromGroup (removeElemFromList p pixels) (centroid, ps)

indexToAssignCentroid :: Pixel -> [(Pixel, [Pixel])] -> Double -> Int
indexToAssignCentroid pixel [] _ = 0
indexToAssignCentroid pixel (x@(centroid, _):xs) (-1) = (indexToAssignCentroid pixel xs (distance pixel centroid))
indexToAssignCentroid pixel (x@(centroid, _):xs) cmp
    | (distance pixel centroid) < cmp = 1 + (indexToAssignCentroid pixel xs (distance pixel centroid))
    | otherwise = do
        let res = indexToAssignCentroid pixel xs cmp
        if (res == 0) then
            0
        else
            res + 1

assignToCentroidIndex :: Pixel -> [(Pixel, [Pixel])] -> Int -> [(Pixel, [Pixel])]
assignToCentroidIndex pixel [] _ = []
assignToCentroidIndex pixel ((centroid, xxs):xs) 0 = ((centroid, xxs ++ [pixel]):xs)
assignToCentroidIndex pixel (x:xs) n = x : (assignToCentroidIndex pixel xs (n - 1))

assignToCentroid :: Pixel -> [(Pixel, [Pixel])] -> [(Pixel, [Pixel])]
assignToCentroid _ [] = []
assignToCentroid pixel list@(c1:c2:cs) = do
    let index = indexToAssignCentroid pixel list (-1)
    assignToCentroidIndex pixel list index
assignToCentroid pixel ((centroid, xs):cs) = ((centroid, xs ++ [pixel]):cs)

centroidsToGroup :: [Pixel] -> [(Pixel, [Pixel])]
centroidsToGroup [] = []
centroidsToGroup (c1:cs) = [(c1, [])] ++ (centroidsToGroup cs)

groupPixelsWithCentroids2 :: [(Pixel, [Pixel])] -> [Pixel] -> [(Pixel, [Pixel])]
groupPixelsWithCentroids2 groups [] = groups
groupPixelsWithCentroids2 groups (p1:ps) =
    groupPixelsWithCentroids2 (assignToCentroid p1 groups) ps

groupPixelsWithCentroids :: [Pixel] -> [Pixel] -> [(Pixel, [Pixel])]
groupPixelsWithCentroids [] _ = []
groupPixelsWithCentroids _ [] = []
groupPixelsWithCentroids centroids pixels = groupPixelsWithCentroids2 (centroidsToGroup centroids) pixels

--------------------------- CENTROIDS CORRECTION -------------------------------

averageDistance :: Pixel -> [Pixel] -> Double
averageDistance centroid pixels = (sumDistance centroid pixels) / fromIntegral (length pixels)

addColor :: Pixel -> Pixel -> Pixel
addColor (Pixel x1 y1 r1 g1 b1) (Pixel x2 y2 r2 g2 b2) = (Pixel x1 y1 (r1+r2) (g1+g2) (b1+b2))

sumColor :: [Pixel] -> Pixel
sumColor [] = (Pixel 0 0 0 0 0)
sumColor ((Pixel x y r g b):xs) = addColor (Pixel x y r g b) (sumColor xs)

divColor :: Pixel -> Int -> Pixel
divColor (Pixel x y r g b) d = (Pixel x y (r `div` d) (g `div` d) (b `div` d))

averageDistanceAttained :: [Pixel] -> [Pixel] -> Double -> Bool
averageDistanceAttained _ [] _ = True
averageDistanceAttained [] _ _ = True
averageDistanceAttained (c1a:c1s) (c2a:c2s) convergence
    | (distance c1a c2a) <= convergence = averageDistanceAttained c1s c2s convergence
    | otherwise = False

centroidCorrection :: [Pixel] -> Pixel
centroidCorrection [] = (Pixel 0 0 0 0 0)
centroidCorrection xs = divColor (sumColor xs) (length xs)

centroidsCorrection2 :: [(Pixel, [Pixel])] -> [Pixel]
centroidsCorrection2 [] = []
centroidsCorrection2 ((_, pixels):xs) = [centroidCorrection pixels] ++ (centroidsCorrection2 xs)

centroidsCorrection :: [Pixel] -> [(Pixel, [Pixel])] -> [Pixel]
centroidsCorrection centroids [] = centroids
centroidsCorrection centroids xs = centroidsCorrection2 xs

------------------------------- MAIN FUNCTION ----------------------------------

compressImage :: Int -> Double -> Gen -> IO()
compressImage nbColors convergence gen@(Gen pixels centroids pixelGroups _)
    | otherwise = do
        let newCentroids = (centroidsCorrection centroids pixelGroups)
        let genCompressed = (Gen pixels newCentroids (groupPixelsWithCentroids newCentroids pixels) 0)

        if ((length pixelGroups) /= 0 && (averageDistanceAttained centroids newCentroids convergence) == True) then
            fullOutput gen
        else
            compressImage nbColors convergence genCompressed