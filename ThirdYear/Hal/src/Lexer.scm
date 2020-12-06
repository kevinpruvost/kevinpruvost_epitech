(define length (lambda (x)
  (if (null? x)
      0
      (+ 1 (length (cdr x))))))

(define list? (lambda (x)
  (cond ((null? x) #t)
        ((not (pair? x)) #f)
        (#t (list? (cdr x))))))

(define map (lambda (f x)
  (if (null? x)
      null
      (cons (f (car x)) (map f (cdr x))))))

(define eq? (lambda (a b)
  (cond ((and (null? a) (null? b)) #t)
        ((and (number? a) (and (number? b) (number-equals? a b))) #t)
        ((and (boolean? a) (and (boolean? b) (boolean-equals? a b))) #t)
        ((and (variable? a) (and (variable? b) (variable-equals? a b))) #t)
        ((and (string? a) (and (string? b) (string-equals? a b))) #t)
        (#t #f))))

(define filter (lambda (predicate x)
  (cond ((null? x) null)
        ((predicate (car x)) (cons (car x) (filter predicate (cdr x))))
        (#t (filter predicate (cdr x))))))

(define reduce (lambda (function init x)
  (if (null? x)
      init
      (function (car x) (reduce function init (cdr x))))))

(define sum (lambda (x)
  (reduce + 0 x)))

(define big? (lambda (x)
  (> x 10)))

(define range (lambda (a b)
  (if (> a b)
      null
      (cons a (range (+ a 1) b)))))

(define factorial (lambda (n)
  (if (eq? n 0)
      1
      (* n (factorial (- n 1))))))