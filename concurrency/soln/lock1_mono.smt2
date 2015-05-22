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

(rule (R 0 0 0))
(rule (=> (and (R 0 0 0)
               (or
                (and (= pc1 1) (= pc2 0) (= lock 1))
                (and (= pc1 0) (= pc2 1) (= lock 1)))
               ) 
          (R pc1 pc2 lock)))
(rule (=> (R 1 pc2 lock) (R 0 pc2 0)))
(rule (=> (R pc1 1 lock) (R pc1 0 0)))
(query (R 1 1 pc1))
