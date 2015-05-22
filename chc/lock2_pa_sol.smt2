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

(declare-var p0 Bool)
(declare-var p0_p Bool)
(declare-var p1 Bool) 
(declare-var p1_p Bool)

(rule (=> (and
           (=> (= lck 0) (= lck_0 1))
           (=> (not (= lck 0)) (= lck_0 lck))
           (= old_p tot)
           (=> (not req) (and (= tot_p tot) (= lck_1 lck_0)))
           (=> req (and
                    (=> (= lck_0 1) (= lck_1 0))
                    (=> (not (= lck_0 1)) (= lck_1 lck_0))
                    (= tot_p (+ tot 1)))))
          (Tr1 tot old lck tot_p old_p lck_1)))

(rule (=> (not (= tot old))
          (Tr2 tot old lck tot old lck)))
(rule (PreLoop tot old 0))

(rule (=> (and (PreLoop tot old lck)
               (Tr1 tot old lck tot_p old_p lck_1))
          (PostLoop tot_p old_p lck_1)))

(rule (=> (and (PostLoop tot old lck)
               (Tr2 tot old lck tot_p old_p lck_p))
          (PreLoop tot_p old_p lck_p)))

(rule (=> (PostLoop tot tot 0) Error))


(query Error)

;; define-fun PostLoop ((tot Int) (x!2 Int) (lck Int)) Bool
;; (=>
;;     (lck = 0)
;;     (tot >= old+1))
