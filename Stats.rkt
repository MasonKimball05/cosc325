#lang racket

; --- Test lists ---
(define listA '(3 7 12 5 9 12 4 8 6 12 10 2 14 12 1 11 13 12 15 12 16))
(define listB '(25 18 30 22 25 17 19 25 21 20 18 24 23 25 26 27 18 29 28 25))

; --- Mean ---
; Sum all elements and divide by the count
(define (mean lis)
  (/ (foldl + 0 lis) (length lis)))

; --- Median ---
; Sort the list, then return the middle element (odd length)
; or the average of the two middle elements (even length)
(define (median lis)
  (define sorted (sort lis <))
  (define n (length sorted))
  (define mid (quotient n 2))
  (if (odd? n)
      (list-ref sorted mid)
      (/ (+ (list-ref sorted (- mid 1))
            (list-ref sorted mid))
         2)))

; --- Mode ---
; Count occurrences of each element, return the one with the highest count
(define (count-occurrences x lis)
  (length (filter (lambda (a) (= a x)) lis)))

(define (mode lis)
  (define (find-mode remaining best-val best-count)
    (if (empty? remaining)
        best-val
        (let ((cnt (count-occurrences (car remaining) lis)))
          (if (> cnt best-count)
              (find-mode (cdr remaining) (car remaining) cnt)
              (find-mode (cdr remaining) best-val best-count)))))
  (find-mode lis (car lis) 0))

; --- Minimum ---
(define (minimum lis)
  (foldl (lambda (a b) (if (< a b) a b)) (car lis) (cdr lis)))

; --- Maximum ---
(define (maximum lis)
  (foldl (lambda (a b) (if (> a b) a b)) (car lis) (cdr lis)))

; --- Display results ---
(define (print-stats name lis)
  (printf "~a:~n" name)
  (printf "  mean   = ~a~n" (exact->inexact (mean lis)))
  (printf "  median = ~a~n" (exact->inexact (median lis)))
  (printf "  mode   = ~a~n" (mode lis))
  (printf "  min    = ~a~n" (minimum lis))
  (printf "  max    = ~a~n" (maximum lis))
  (newline))

(print-stats "listA" listA)
(print-stats "listB" listB)