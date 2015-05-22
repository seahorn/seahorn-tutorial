;;
;; {Pre: y >= 0 }
;; xo = x; yo = y;
;; while (y > 0) { x=x+1; y=y-1; }
;; {Post: x = xo + yo}
;;

(declare-rel I (Int Int Int Int))
(declare-rel Pre (Int Int))
(declare-rel Exit (Int Int Int))
(declare-rel Error ())

(declare-var x Int)
(declare-var y Int)
(declare-var xo Int)
(declare-var yo Int)
(declare-var xp Int)
(declare-var yp Int)

(rule (=> (>= y 0) (Pre x y)))
(rule (=> (Pre x y) (I x y x y)))
(rule (=> (and (I x y xo yo) (> y 0) (= xp (+ x 1)) (= yp (- y 1)))
          (I xp yp xo yo)))
(rule (=> (and (I x y xo yo) (<= y 0)) (Exit x xo yo)))
(rule (=> (and (Exit x xo yo) (not (= x (+ xo yo)))) Error))

(query Error)
