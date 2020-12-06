module Tools where

import Data.Char

-- Print

lengthMod :: Int -> Int
lengthMod n
    | n `mod` 2 == 1 = (n `div` 2) + 1
    | otherwise = n `div` 2

printQuintuple :: (Int, Int, Int, Int, Int) -> IO()
printQuintuple (a, b, c, d, e) = do
    mapM_ (\x -> putStr $ (show x) ++ "\t") [a, b, c, d, e]
    putStr "\n"

printSpace :: Int -> IO()
printSpace 0 = return ()
printSpace n
    | n <= 0 = return ()
    | otherwise = do
        putStr " "
        printSpace (n - 1)

-- printLine :: Tab -> Width -> Move
printLine2 :: [Int] -> Int -> IO()
printLine2 xs 0 = return ()
printLine2 [] count = return ()
printLine2 (x:xs) count
    | count < 0 = return ()
    | x == 0 = do
        putStr " "
        printLine2 xs (count - 1)
    | x == 1 = do
        putStr "*"
        printLine2 xs (count - 1)
    | otherwise = error "WTF1"

printLineMove :: [Int] -> Int -> Int -> IO()
printLineMove xs 0 width = printLine2 xs width
printLineMove (x:xs) move width 
    | move > 0 = printLineMove xs (move - 1) width
    | move < 0 = printLineMove (init (x:xs)) (move + 1) width

measureFirst :: Int -> Int -> Int
measureFirst width flen
    | width < flen = width
    | otherwise = flen

measureSecond :: Int -> Int -> Int -> Int
measureSecond width mes line
    | mes < 0 = width + mes
    | width < (mes + line) = width
    | otherwise = (mes + line) 

measureThird :: Int -> Int -> Int -> Int
measureThird x y z
    | y < 0 && z < 0 = x
    | y < 0 = x - z
    | z < 0 = x - y
    | otherwise = x - y - z

moveLine :: [Int] -> Int -> Int -> Int -> [Int]
moveLine (x:xs) width flen slen
    | flen < 0 = moveLine xs width (flen + 1) slen
    | flen + (length (x:xs)) > width = moveLine (init (x:xs)) width flen slen
    | otherwise = (x:xs)
moveLine [] _ _ _ = []

printLine :: [Int] -> Int -> Int -> IO()
printLine xs width move
    | (length xs) > (width + (abs move)) = do
        printLineMove xs (((length xs) `div` 2) - (width `div` 2) - move) width
        putStr "\n"
    | otherwise = do
        let flen = ((width `div` 2) + move - (length xs `div` 2))
        printSpace (measureFirst width flen)
        let slen = measureSecond (length xs) flen width
        let newLine = moveLine xs width flen slen
        printLine2 newLine slen
        let tlen = measureThird width flen slen
        printSpace tlen
        putStr "\n"

cmpWolframRuleCreate :: Int -> (Int, Int, Int, Int, Int, Int, Int, Int) -> (Int, Int, Int, Int, Int, Int, Int, Int)
cmpWolframRuleCreate 0 x = x
cmpWolframRuleCreate n (a, b, c, d, e, f, g, h)
    | n >= 128 = cmpWolframRuleCreate (n - 128) (1, b, c, d, e, f, g, h)
    | n >= 64  = cmpWolframRuleCreate (n - 64)  (a, 1, c, d, e, f, g, h)
    | n >= 32  = cmpWolframRuleCreate (n - 32)  (a, b, 1, d, e, f, g, h)
    | n >= 16  = cmpWolframRuleCreate (n - 16)  (a, b, c, 1, e, f, g, h)
    | n >= 8   = cmpWolframRuleCreate (n - 8)   (a, b, c, d, 1, f, g, h)
    | n >= 4   = cmpWolframRuleCreate (n - 4)   (a, b, c, d, e, 1, g, h)
    | n >= 2   = cmpWolframRuleCreate (n - 2)   (a, b, c, d, e, f, 1, h)
    | n >= 1   = cmpWolframRuleCreate (n - 1)   (a, b, c, d, e, f, g, 1)

-- cmpWolframRule :: rule -> (x1, x2, x3) -> 0 | 1
cmpWolframRule1 :: (Int, Int, Int) -> (Int, Int, Int, Int, Int, Int, Int, Int) -> Int
cmpWolframRule1 (1, 1, 1) (a, b, c, d, e, f, g, h) = a
cmpWolframRule1 (1, 1, 0) (a, b, c, d, e, f, g, h) = b
cmpWolframRule1 (1, 0, 1) (a, b, c, d, e, f, g, h) = c
cmpWolframRule1 (1, 0, 0) (a, b, c, d, e, f, g, h) = d
cmpWolframRule1 (0, 1, 1) (a, b, c, d, e, f, g, h) = e
cmpWolframRule1 (0, 1, 0) (a, b, c, d, e, f, g, h) = f
cmpWolframRule1 (0, 0, 1) (a, b, c, d, e, f, g, h) = g
cmpWolframRule1 (0, 0, 0) (a, b, c, d, e, f, g, h) = h

-- cmpWolframRule :: rule -> (x1, x2, x3) -> 0 | 1
cmpWolframRule :: Int -> (Int, Int, Int) -> Int
cmpWolframRule rule nb = cmpWolframRule1 nb (cmpWolframRuleCreate rule (0, 0, 0, 0, 0, 0, 0, 0)) 

-- compute :: rule -> list -> computedList
compute1 :: Int -> [Int] -> [Int]
compute1 rule (x:y:z:xs) = [(cmpWolframRule rule (x, y, z))] ++ (compute1 rule (y:z:xs))
compute1 rule (x:y:xs)   = [(cmpWolframRule rule (x, y, 0))] ++ (compute1 rule (y:xs))
compute1 rule (x:xs)     = [(cmpWolframRule rule (x, 0, 0))] ++ (compute1 rule (xs))
compute1 rule xs = []

compute2 :: Int -> [Int] -> [Int]
compute2 rule (x:y:z:xs) = [(cmpWolframRule rule (0, x, y))] ++ (compute1 rule (x:y:z:xs))
compute2 rule (x:y:xs)   = [(cmpWolframRule rule (0, x, y))] ++ (compute1 rule (x:y:xs))
compute2 rule (x:xs)     = [(cmpWolframRule rule (0, x, 0))] ++ (compute1 rule (x:xs))

compute :: Int -> [Int] -> [Int]
compute rule (x:xs)      = [(cmpWolframRule rule (0, 0, x))] ++ (compute2 rule (x:xs))