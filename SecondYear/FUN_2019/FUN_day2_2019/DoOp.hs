import System.Environment
import System.Exit

myElem :: Eq a => a -> [a] -> Bool
myElem x [] = False
myElem x [y]
    | x == y = True
    | otherwise = False
myElem x (y:ys)
    | x == y = True
    | otherwise = myElem x ys

safeDiv :: Int -> Int -> Maybe Int
safeDiv n1 n2
    | n2 == 0 = Nothing
    | otherwise = Just (n1 `div` n2)

safeNth :: [a] -> Int -> Maybe a
safeNth [] n = Nothing
safeNth [x] n
    | n == 0 = Just x
    | n < 0 = Nothing
    | otherwise = Nothing
safeNth (x:xs) n
    | n == 0    = Just x
    | n < 0     = Nothing
    | otherwise = safeNth xs (n-1)

safeSucc :: Maybe Int -> Maybe Int
safeSucc (Just n) = Just (n + 1)
safeSucc Nothing = Nothing

myLookup :: Eq a => a -> [(a,b)] -> Maybe b
myLookup a [] = Nothing
myLookup a ((x, y):xs)
    | a == x = (Just y)
    | otherwise = myLookup a xs

maybeDo :: (a -> b -> c) -> Maybe a -> Maybe b -> Maybe c
maybeDo z Nothing b = Nothing
maybeDo z a Nothing = Nothing
maybeDo z (Just a) (Just b) = Just (z a b)



isSingleCharInt :: Char -> Bool
isSingleCharInt x
    | x == '0' || x == '1' || x == '2' || x == '3' || x == '4' || x == '5' || x == '6' || x == '7' || x == '8' || x == '9' || x == '-' = True
    | otherwise = False
    
isMultipleCharInt :: [Char] -> Bool
isMultipleCharInt [] = False
isMultipleCharInt [x] = isSingleCharInt x
isMultipleCharInt (x:xs)
    | isSingleCharInt x == False = False
    | otherwise = isMultipleCharInt xs

readInt :: [Char] -> Maybe Int
readInt [] = Nothing
readInt [x] 
    | isSingleCharInt x == False = Nothing
    | otherwise = Just (read [x]::Int)
readInt x
    | isMultipleCharInt x == False = Nothing
    | otherwise = Just (read x::Int)

getLineLength :: IO Int
getLineLength = fmap length getLine --fmap adapte les fonctions à Monad

printAndGetLength :: String -> IO Int
printAndGetLength x = do putStrLn x
                         pure $ length x


buildBoxLine :: Int -> Int -> [Char]
buildBoxLine n len
    | len < 1 = error "out of range"
    | n == len = '|' : buildBoxLine n (len-1)
    | len == 1 = "|"
    | otherwise = ' ' : buildBoxLine n (len-1)

buildBoxLineSide :: Int -> Int -> [Char]
buildBoxLineSide n len
    | len < 1 = error "out of range"
    | n == len = '+' : buildBoxLineSide n (len-1)
    | len == 1 = "+"
    | otherwise = '-' : buildBoxLineSide n (len-1)

printBox' :: Int -> Int -> Int -> IO ()
printBox' n len hei
    | hei == 1 = putStrLn (buildBoxLineSide len len)
    | n == hei = 
        do putStrLn (buildBoxLineSide len len)
           printBox' n len (hei-1)
    | otherwise = 
        do putStrLn (buildBoxLine len len)
           printBox' n len (hei-1)

printBox :: Int -> IO ()
printBox 1 = putStrLn "++"
printBox n 
    | n <= 0 = return ()
    | otherwise = printBox' n (n*2) n


concatLines :: Int -> IO String
concatLines n
    | n <= 0 = return ("")
    | n == 1 = getLine
    | otherwise = do
        a <- getLine
        b <- concatLines (n-1)
        return (a ++ b)

getInt :: IO (Maybe Int)
getInt = do
    a <- getLine
    if (isMultipleCharInt a) == False then
        return (Nothing)
    else
        return (Just (read a::Int))


-- Calculator

getIntFromMaybe :: Maybe Int -> Int
getIntFromMaybe (Just n) = n
getIntFromMaybe Nothing = 0

printMaybe :: Maybe Int -> IO ()
printMaybe (Just a) = print a
printMaybe Nothing = print 0

fromMaybeInt :: Maybe Int -> Int
fromMaybeInt (Just n) = n
fromMaybeInt Nothing = 0

calculatorIdentify :: Int -> [Char] -> Int -> Maybe Int
calculatorIdentify n1 z n2
    | z == "+" = (Just (n1 + n2))
    | z == "-" = (Just (n1 - n2))
    | z == "*" = (Just (n1 * n2))
    | z == "/" && n2 /= 0 = (Just (n1 `div` n2))
    | z == "%" = (Just (n1 `mod` n2))
    | otherwise = Nothing

compute :: [[Char]] -> Maybe Int
compute xs
    | (length xs) /= 3 = Nothing
    | (length (xs !! 1)) /= 1 || (isMultipleCharInt (xs !! 0)) == False || (isMultipleCharInt (xs !! 2)) == False = Nothing
    | otherwise = (calculatorIdentify x1 (xs !! 1) x3)
    where x1 = read (xs !! 0)::Int; x3 = read(xs !! 2)::Int

main = do
    args <- getArgs
    mainExitCode <- pure $ compute args
    if mainExitCode /= Nothing then do
        print (getIntFromMaybe mainExitCode)
        exitWith (ExitSuccess)
    else
        exitWith (ExitFailure 84)