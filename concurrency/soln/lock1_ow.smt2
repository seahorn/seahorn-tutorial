;; //Thread 1
;; 1: take_lock (lock)
;; 2: // critical section
;; 3: release_lock (lock); goto 1;
;; 
;; // Thread 2
;; 1: take_lock (lock, 1)
;; 2: // critical
;; 3: release_lock (lock); goto 1;

;; Owicki-Gries proof
;; Find local invariants R1 and R2 such that
;; (a) R_i is an inductive invariant of thread i
;; (b) R_2 does not interfere with R_1
;; (c) R_1 does not interfere with R_2

(declare-var pc Int)
(declare-var pc1 Int)
(declare-var pc2 Int)
(declare-var lock Int)

;;               pc1 pc2 lock
(declare-rel R1 (Int Int Int))
(declare-rel R2 (Int Int Int))

;; initial states
(rule (R1 0 0 0))
(rule (R2 0 0 0))

;; steps of R1
(rule (=> (R1 0 pc2 0) (R1 1 pc2 1)))
(rule (=> (R1 1 pc2 lock) (R1 0 pc2 0)))

;; steps of R2
(rule (=> (R2 pc1 0 0) (R2 pc1 1 1)))
(rule (=> (R2 pc1 1 lock) (R2 pc1 0 0)))

;; non-interference of R2
(rule (=> (and (R1 pc1 0 0) (R2 pc1 0 0)) (R1 pc1 1 1)))
(rule (=> (and (R1 pc1 1 lock) (R2 pc1 1 lock)) (R1 pc1 0 0)))

;; non-interference of R1
(rule (=> (and (R1 0 pc2 0) (R2 0 pc2 0)) (R2 1 pc2 1)))
(rule (=> (and (R1 1 pc2 lock) (R2 1 pc2 lock)) (R2 0 pc2 0)))

;(query (and (R1 1 1 lock) (R2 1 1 lock)))
;;(query (R1 1 1 lock))

;; model
;; (define-fun R1 ((pc1 Int) (pc2 Int) (lock Int)) Bool
;;   (and (or (<= pc2 0) (<= pc1 0)) 
;;        (=> (>= pc2 1) (>= lock 1))))

;; (define-fun R2 ((pc1 Int) (pc2 Int) (lock Int)) Bool
;;   (=> (>= pc1 1) (>= lock 1)))


 (query (R2 1 1 lock))

;; (define-fun R1 ((pc1 Int) (pc2 Int) (lock Int)) Bool true)

;; (define-fun R2 ((pc1 Int) (pc2 Int) (lock Int)) Bool
;;   (and (or (<= pc2 0) (<= pc1 0))
;;        (=> (>= pc2 1) (>= lock 1))
;;        (=> (>= pc1 1) (>= lock 1))))
