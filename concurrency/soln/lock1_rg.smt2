;; //Thread 1
;; 1: take_lock (lock)
;; 2: // critical section
;; 3: release_lock (lock); goto 1;
;; 
;; // Thread 2
;; 1: take_lock (lock, 1)
;; 2: // critical
;; 3: release_lock (lock); goto 1;


;; Relay-Guarantee proof
;; Find inductive invariants R1 or thread 1 and R2 of thread 2
;; and Environment E1 for R1 and E2 for R2 such that
;; E1 captures all interferences FOR R1
;; E2 captures all interferences FOR R2
;; R1 and R2 are inductive under interferences E1 and E2, respectively

(declare-var pc1 Int)
(declare-var pc2 Int)
(declare-var lock Int)
(declare-var pc1_p Int)
(declare-var pc2_p Int)
(declare-var lock_p Int)

(declare-rel R1 (Int Int Int))
(declare-rel R2 (Int Int Int))
(declare-rel E1 (Int Int Int Int))
(declare-rel E2 (Int Int Int Int))

;; local steps of T1
(rule (R1 0 0 0))
(rule (=> (R1 0 pc2 0) (R1 1 pc2 1)))

;; local steps of T2
(rule (R2 0 0 0))
(rule (=> (R2 pc1 0 0) (R2 pc1 1 1)))

;; R1 is inductive under interference E1
(rule (=> (and (R1 pc1 pc2 lock) (E1 pc2 lock pc2_p lock_p)) 
          (R1 pc1 pc2_p lock_p)))

;; R2 is inductive under interference E2
(rule (=> (and (R2 pc1 pc2 lock) (E2 pc1 lock pc1_p lock_p))
          (R2 pc1_p pc2 lock_p)))

;; E1 capture interference from R2
(rule (=> (R2 pc1 0 0) (E1 0 0 1 1))) 
;; E2 captures interference from R1
(rule (=> (R1 0 pc2 0) (E2 0 0 1 1)))

;(query (R1 1 1 lock))
;(query (R2 1 1 lock))
;; Both in critical section
(query (and (R1 1 1 lock) (R2 1 1 lock)))
