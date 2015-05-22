;; //Thread 1
;; 1: take_lock (lock)
;; 2: // critical section
;; 3: release_lock (lock); goto 1;
;; 
;; // Thread 2
;; 1: take_lock (lock, 1)
;; 2: // critical
;; 3: release_lock (lock); goto 1;

;; Monolithic proof.
;; Single Invariant R.

(declare-var pc1 Int)
(declare-var pc2 Int)
(declare-var lock Int)

;               pc1 pc2 lock
(declare-rel R (Int Int Int))

;; write the rules

(query (R 1 1 pc1))
