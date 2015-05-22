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

;; write the rules

(query (R2 1 1 lock))

