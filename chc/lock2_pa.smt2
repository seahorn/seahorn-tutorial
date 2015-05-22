;; tot = *
;; do
;;   if (lck == 0) lck = 1;
;;   old = tot
;;   req = *;
;;   if (req)
;;     if (lck==1) lck = 0;
;;     tot = tot+1;
;; while (tot != old)
;; if (lck == 0) error();

(declare-rel PreLoop (Int Int Int))
(declare-rel PostLoop (Int Int Int))
(declare-rel PreLoopA (Bool Bool))
(declare-rel PostLoopA (Bool Bool))

(declare-rel Tr1 (Int Int Int Int Int Int))
(declare-rel Tr2 (Int Int Int Int Int Int))

(declare-rel Error ())

(declare-var tot Int)
(declare-var old Int)
(declare-var tot_p Int)
(declare-var old_p Int)
(declare-var req Bool)
(declare-var lck Int)
(declare-var lck_0 Int)
(declare-var lck_1 Int)
(declare-var lck_p Int)

;; write modular constraints for the above program
;; where Tr1 and Tr2 predicates abstract program steps

(query Error)

