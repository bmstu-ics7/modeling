import Text.Layout.Table
import System.Environment

pikara :: Int -> Double -> Double
pikara 1 x = (1 / 3) * (x^3)
pikara 2 x = pikara 1 x + (1 / 63) * (x^7)
pikara 3 x = pikara 2 x + (2 / 2079) * (x^8) + (1 / 59535) * (x^15)
pikara 4 x = pikara 3 x +
    (2 / 93555)        * (x^15) +
    (2 / 3393495)      * (x^19) +
    (2 / 2488563)      * (x^19) +
    (2 / 86266215)     * (x^23) +
    (1 / 99411543)     * (x^23) +
    (2 / 3341878155)   * (x^27) +
    (1 / 109876902975) * (x^31)

explicit :: Int -> Double -> [Double]
explicit 0 _ = [0]
explicit n h = arr ++ [prev + h * (x^2 + prev^2)]
  where arr  = explicit ((fromIntegral n) - 1) h
        prev = last arr
        x    = (fromIntegral n) * h

implicit :: Int -> Double -> [Double]
implicit 0 _ = [0]
implicit n h
    | plus <= 0  = arr ++ [minus]
    | minus <= 0 = arr ++ [plus]
    | otherwise  = arr ++ [min plus minus]
  where arr   = implicit ((fromIntegral n) - 1) h
        c     = (last arr) + h * (((fromIntegral n) * h)^2)
        discr = sqrt (1 - 4 * h * c)
        plus  = (1 + discr) / (2 * h)
        minus = (1 - discr) / (2 * h)

makeZip :: [a] -> [b] -> [c] -> [d] -> [e] -> [(a, b, c, d, e)]
makeZip [] _ _ _ _ = []
makeZip _ [] _ _ _ = []
makeZip _ _ [] _ _ = []
makeZip _ _ _ [] _ = []
makeZip _ _ _ _ [] = []
makeZip (x:xs) (pi3:pi3s) (pi4: pi4s) (ex:exs) (im:ims) = (x, pi3, pi4, ex, im) : makeZip xs pi3s pi4s exs ims

makeRow :: [a] -> [b] -> [c] -> [d] -> [e] -> [(a, b, c, d, e)]
makeRow x pi3 pi4 ex im = reverse (makeZip (reverse x) (reverse pi3) (reverse pi4) (reverse ex) (reverse im))

truncate' :: Double -> Int -> Double
truncate' x n = (fromIntegral (floor (x * t))) / t
  where t = 10 ^ n

main :: IO ()
main = do
    [start, step, end] <- getArgs
    let xstart = read start :: Double
        xstep  = read step :: Double
        xend   = read end :: Double
     in putStrLn $ tableString [def, def, def, def, def]
                       unicodeRoundS
                       (titlesH ["x", "Пикар (3)", "Пикар (4)", "Явная схема", "Неявная схема"])
                       [ rowG [
                                show (truncate' x 6),
                                show (truncate' pi3 6),
                                show (truncate' pi4 6),
                                show (truncate' ex 6),
                                show (truncate' im 6)
                              ] | (x, pi3, pi4, ex, im) <- makeRow
                                                                [xstart, (xstart + xstep) .. xend]
                                                                [pikara 3 x | x <- [xstart, (xstart + xstep) .. xend]]
                                                                [pikara 4 x | x <- [xstart, (xstart + xstep) .. xend]]
                                                                (explicit (round (xend / xstep)) xstep)
                                                                (implicit (round (xend / xstep)) xstep)
                       ]
