;; 
;; Mux-Sem-Last from "Local proofs for global safety properties"
;; 
;; adding last variable makes the proof go through without the need to share pc
;;
;; //Thread 1
;; 1: take_lock (lock)
;; 2: last = 1 // critical section
;; 3: release_lock (lock); goto 1;
;; 
;; // Thread 2
;; 1: take_lock (lock, 1)
;; 2: last = 2 // critical
;; 3: release_lock (lock); goto 1;


(declare-var pc Int)
(declare-var pc1 Int)
(declare-var pc2 Int)
(declare-var lock Int)
(declare-var last Int)

;                 pc lock last
(declare-rel R1 (Int Int Int))
;                pc  lock last
(declare-rel R2 (Int Int Int))


;; write the rules for a modular proof. The proof should treat pc of
;; each thread as local

;; both R1 and R2 are in their critical sections
(query (and (R1 1 lock last) (R2 1 lock last)))

