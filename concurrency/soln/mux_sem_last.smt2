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

(declare-rel R1 (Int Int Int))
(declare-rel R2 (Int Int Int))

(rule (R1 0 0 0))
(rule (R2 0 0 0))

;; local steps of R1
(rule (=> (R1 0 0 last) (R1 1 1 1)))
(rule (=> (R1 1 lock last) (R1 0 0 last)))

;; local steps of R2
(rule (=> (R2 0 0 last) (R2 1 1 2)))
(rule (=> (R2 1 lock last) (R2 0 0 last)))

;; R2 does not interfere with R1
(rule (=> (and (R1 pc1 0 last) (R2 0 0 last)) (R1 pc1 1 2)))
(rule (=> (and (R1 pc1 lock last) (R2 1 lock last)) (R1 pc1 0 last)))

;; R1 does not interfere with R2
(rule (=> (and (R1 0 0 last) (R2 pc2 0 last)) (R2 pc2 1 1)))
(rule (=> (and (R1 1 lock last) (R2 pc2 lock last)) (R2 pc2 0 last)))

;; both R1 and R2 are in their critical sections
(query (and (R1 1 lock last) (R2 1 lock last)))

;; (define-fun R1 ((pc1 Int) (lock Int) (last Int)) Bool
;;   (and (=> (>= pc1 1) (>= lock 1)
;;        (=> (>= pc1 1) (= last 1))))
;; (define-fun R2 ((pc2 Int) (lock Int) (last Int)) Bool
;;   (and (=> (>= pc2 1) (>= lock 1))
;;        (=> (>= pc2 1) (>= last 2)))

