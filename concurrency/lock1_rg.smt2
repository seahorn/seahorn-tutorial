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

;; write the rules

;; Both in critical section
(query (and (R1 1 1 lock) (R2 1 1 lock)))
