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

;;
;; write constraints for the above program
;; 

(query Error)
