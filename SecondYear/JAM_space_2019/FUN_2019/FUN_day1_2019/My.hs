mySucc :: Int -> Int
mySucc n = n + 1

myIsNeg :: Int -> Bool
myIsNeg n = n < 0

myAbs :: Int -> Int
myAbs n 
    | n < 0     = n * (-1)
    | otherwise = n 

myMin :: Int -> Int -> Int
myMin n1 n2 
    | n1 < n2   = n1
    | otherwise = n2

myMax :: Int -> Int -> Int
myMax n1 n2 
    | n1 < n2   = n2
    | otherwise = n1

myTuple :: a -> b -> (a, b)
myTuple a b = (a, b)

myTruple :: a -> b -> c -> (a, b, c)
myTruple a b c = (a, b, c)

myFst :: (a, b) -> a
myFst (a, b) = a

mySnd :: (a, b) -> b
mySnd (a, b) = b

mySwap :: (a, b) -> (b, a)
mySwap (a, b) = (b, a)

myHead :: [a] -> a
myHead [] = error "empty list"
myHead [x] = x
myHead (x:xs) = x

myTail :: [a] -> [a]
myTail [] = error "empty"
myTail [x] = []
myTail (x:xs) = xs

myLength :: [a] -> Int
myLength [] = 0
myLength [x] = 1
myLength (x:xs) = 1 + myLength xs

myNth :: [a] -> Int -> a
myNth [] n = error "index too large"
myNth [x] n
    | n == 0 = x
    | n < 0 = error "out of range"
    | otherwise = error "index too large"
myNth (x:xs) n
    | n == 0    = x
    | n < 0     = error "out of range"
    | otherwise = myNth xs (n-1)

myTake :: Int -> [a] -> [a]
myTake n [] = []
myTake n [x]
    | n <= 0 = []
    | otherwise = [x]
myTake n (x:xs)
    | n <= 0 = []
    | otherwise = x : myTake (n-1) xs

myDrop :: Int -> [a] -> [a]
myDrop n [] = []
myDrop n [x]
    | n <= 0 = [x]
    | otherwise = []
myDrop n (x:xs)
    | n <= 0 = x : xs
    | otherwise = myDrop (n-1) xs

myAppend :: [a] -> [a] -> [a]
myAppend [] y = y
myAppend [x] y = x : y
myAppend (x:xs) y = x : (myAppend xs y)

myReverse :: [a] -> [a]
myReverse [] = []
myReverse [x] = [x]
myReverse (x:xs) = myAppend (myReverse xs) [x]

myInit :: [a] -> [a]
myInit [] = error "empty list"
myInit [x] = []
myInit (x:xs) = x : (myInit xs)

myLast :: [a] -> a
myLast [] = error "empty list"
myLast [x] = x
myLast (x:xs) = myLast xs

myZip :: [a] -> [b] -> [(a, b)]
myZip [] y          = []
myZip x []          = []
myZip [x] [y]       = [(x, y)]
myZip [x] (y:ys)    = [(x, y)]
myZip (x:xs) [y]    = [(x, y)]
myZip (x:xs) (y:ys) = (x, y) : (myZip xs ys)

myUnzip :: [(a, b)] -> ([a], [b])
myUnzip [] = ([], [])
myUnzip [(a, b)] = ([a], [b])
myUnzip ((a, b):xs) = (a : x, b : y)
    where (x, y) = myUnzip xs

myMap :: (a -> b) -> [a] -> [b]
myMap z [] = []
myMap z [x] = [z x]
myMap z (x:xs) = z x : (myMap z xs)

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter z [] = []
myFilter z [x]
    | (z x) == True = [x]
    | otherwise = []
myFilter z (x:xs)
    | (z x) == True = x : (myFilter z xs)
    | otherwise = (myFilter z xs)

myFoldl :: (b -> a -> b) -> b -> [a] -> b
myFoldl z n []     = n
myFoldl z n [x]    = z n x
myFoldl z n (x:xs) = myFoldl z (z n x) xs

myFoldr :: (a -> b -> b) -> b -> [a] -> b
myFoldr z n []     = n
myFoldr z n [x]    = z x n
myFoldr z n (x:xs) = z x (myFoldr z n xs)

mySpan :: (a -> Bool) -> [a] -> ([a], [a])
mySpan z [] = ([], [])
mySpan z [x]
    | (z x) == True = ([x], [])
    | otherwise     = ([], [x])
mySpan z (x:xs)
    | (z x) == True = (x : a, b)
    | otherwise     = (a, x : b)
    where (a, b) = (mySpan z xs)

myQuickSort :: (a -> a -> Bool) -> [a] -> [a]
myQuickSort z [] = []
myQuickSort z [x] = [x]
myQuickSort z list = lsort list [] z

lsort :: [a] -> [a] -> (a -> a -> Bool) -> [a]
lsort [] sorted z      = sorted
lsort [x] sorted z     = lsort [] sortedNext z where sortedNext = insertlsort x sorted z
lsort (x:xs) sorted z  = lsort xs sortedNext z where sortedNext = insertlsort x sorted z

insertlsort :: a -> [a] -> (a -> a -> Bool) -> [a]
insertlsort a [] z = [a]
insertlsort toInsert [x] z      | (z x toInsert) == False = toInsert : [x]
                                | otherwise = myAppend [x] [toInsert]
insertlsort toInsert (x:xs) z   | (z x toInsert) == False = myAppend (toInsert : [x]) xs
                                | otherwise = x : insertlsort toInsert xs z