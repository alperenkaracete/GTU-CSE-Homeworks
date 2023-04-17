
(defvar nums (list "1" "2" "3" "4" "5" "6" "7" "8" "9" "0"))
(defvar operator (list "+" "-" "/" "*" "**" "(" ")" "\"" ","))

(defun delete-spaces-and-split-line (line) ;delete spaces split lines
	(let ((words) (flag 0) (temp-words))
		(setq line (string-trim '(#\Space #\Tab #\Newline) line))
		(setq words (split-string-to-words line))
		(loop for word in words
			do
			(progn
				
				(setq temp-words (string-trim '(#\Space #\Tab #\Newline) word))
				(setq flag (find-words-and-find-tokens temp-words))
				
			)
		)
		flag			
	)
)

(defun split-string-to-words (string &optional (separator " ")(r nil)) ;assign li
  (let ((i (position separator string
		     :from-end t
		     :test #'(lambda (x y)
			       (find y x :test #'string=)))))
    (if i
	(split-string-to-words(subseq string 0 i) separator (cons (subseq string (1+ i)) r))
      (cons string r))
	)
)

(defun find-words-and-find-tokens (temp-words)

	(setq len (length temp-words)) ;take length of line
	(setq temp-letter nil)	;take one letter
	(setq temp-word nil)	;take word
	(setq j 1)	;j value
	(setq mult-control nil)	;if there is a * take it
	(setq temp-num nil)	;value of number
	(setq float-flag 0)	;if tere is a "f" in number then that is a float number
	(setq float-control nil)	;if there is a f in number for store it
	(setq string-flag 0)	;if tere is a string, with this flag i decided which " is OP_OC OR OP_CC
	(setq dbl-mlt-counter 0)	;count number of * operator for double mult
	(setq after-char nil)	;takes char after pointed char
	(format t "(")
	(loop for i from 0 to len
		do
			(progn
				(setq temp-letter(subseq temp-words i j))	;take temp letter
				(if (> i 0)
					(setq before-char(subseq temp-words (- i 1) i)))
				(if(and(< (+ i 1) len)(< j len))
					(progn
					(setq after-char(subseq temp-words  (+ i 1) (+ i 2)))
					
					)
				)
				(if(and(equal temp-letter "*")(/= j len))	;find * and look if * operator is double
					(progn
						(setq mult-control(subseq temp-words j))
						(if (equal mult-control "*")
							(setq dbl-mlt-counter 2)
						)				
					)
					(if (and(equal temp-letter "*")(string/= before-char "*"))	
						(setq dbl-mlt-counter 1)
					)				
				)

				(if(and(equal temp-letter "f")(find before-char nums :test #'string-equal))	;look if number is float
					(progn
						(setq float-control(subseq temp-words i j))
						(setq float-flag 1)))
				(if (equal temp-letter ";")	;for comment lines
					(progn
					(setq temp-comment(subseq temp-words i len))
					(setq i len)	
					(format t "(~s ~s)" temp-comment "COMMENT")				
					))
				(if (< j len)
					(setq j (+ j 1)))	
				(if (and(every #'alpha-char-p temp-letter)(= float-flag 0)) ;control if char is between a-z
					(progn
					(if (equal temp-word nil)
						
						(setq temp-word(subseq temp-letter 0 ))
						(progn	

							(setq temp-word(concatenate 'string temp-word temp-letter))
							(if (or(find after-char operator :test #'string-equal)(= i j))
							(cond ;for printing keywords
							((string= temp-word "and") (format t "(~s ~s)" temp-word "KW_AND")(setq temp-word nil))
							((string= temp-word "or") (format t "(~s ~s)" temp-word "KW_OR")(setq temp-word nil))
        					((string= temp-word "not") (format t "(~s ~s)" temp-word "KW_NOT")(setq temp-word nil))
        					((string= temp-word "equal") (format t "(~s ~s)" temp-word "KW_EQUAL")(setq temp-word nil))
        					((string= temp-word "less") (format t "(~s ~s)" temp-word "KW_LESS")(setq temp-word nil))
        					((string= temp-word "nil") (format t "(~s ~s)" temp-word "KW_NIL")(setq temp-word nil))
        					((string= temp-word "list") (format t "(~s ~s)" temp-word "KW_LIST")(setq temp-word nil))
        					((string= temp-word "append") (format t "(~s ~s)" temp-word "KW_APPEND")(setq temp-word nil))
        					((string= temp-word "concat") (format t "(~s ~s)" temp-word "KW_CONCAT")(setq temp-word nil))
        					((string= temp-word "set") (format t "(~s ~s)" temp-word "KW_SET")(setq temp-word nil))
        					((string= temp-word "deffun") (format t "(~s ~s)" temp-word "KW_DEFFUN")(setq temp-word nil))
        					((string= temp-word "for") (format t "(~s ~s)" temp-word "KW_FOR")(setq temp-word nil))
        					((string= temp-word "if") (format t "(~s ~s)" temp-word "KW_IF")(setq temp-word nil))
        					((string= temp-word "exit") (format t "(~s ~s)" temp-word "KW_EXIT")(setq temp-word nil))
        					((string= temp-word "load") (format t "(~s ~s)" temp-word "KW_LOAD")(setq temp-word nil))
        					((string= temp-word "disp") (format t "(~s ~s)" temp-word "KW_DISP")(setq temp-word nil))
        					((string= temp-word "true") (format t "(~s ~s)" temp-word "KW_TRUE")(setq temp-word nil))
        					((string= temp-word "false") (format t "(~s ~s)" temp-word "KW_FALSE")(setq temp-word nil))
							(T nil)))
							(if (and(= i len)(not(string= temp-word nil)))	;determine identifier or valuestr
								(progn
									(if(= string-flag 0)
										(progn 
											(format t "(~s ~s)" temp-word "IDENTIFIER")
											(setq temp-word nil)
										)
										(progn
											(format t "(~s ~s)" temp-word "VALUESTR")
											(setq temp-word nil)
											(setq string-flag 2)
										)
									)
								)
									
							)
						)
					))
						(progn

							(if (not(string= temp-word nil))
								(progn
									
									(if(= string-flag 0)
										(progn 
											(format t "(~s ~s)" temp-word "IDENTIFIER")
											(setq temp-word nil)
										)
										(progn
											(format t "(~s ~s)" temp-word "VALUESTR")
											(setq temp-word nil)
											(setq string-flag 2)
										)
									)
								)
							)
							(if(find temp-letter nums :test #'string-equal)
								(progn
									(if (equal temp-num nil)
										(progn
										(setq temp-num temp-letter)
											(if (and(= j len)(= float-flag 0))
												(progn
												(if (find "f" temp-num :test #'string-equal)
													(progn
														(format t "(~s ~s)" temp-num "VALUE_F")
														(setq temp-num nil)		)
													(progn
														(format t "(~s ~s)" temp-num "VALUE_I")
														(setq temp-num nil)		)
													))
											)
										)
										(progn
											(if (equal temp-num "0")
												(error "0 Can not in run-interpreter of number")
											)
											(setq temp-num(concatenate 'string temp-num temp-letter))
											(if (and(= j len)(= (+ i 1) j))
												(progn
												(if (find "f" temp-num :test #'string-equal)
													(progn	
														(format t "(~s ~s)" temp-num "VALUE_F")
														(setq temp-num nil)		)
													(progn
														(format t "(~s ~s)" temp-num "VALUE_I")
														(setq temp-num nil)		)
													))
											)
										)
									)	
								)
								(progn
								
									(if (and(and(not(equal temp-num nil))(equal float-control "f"))(= float-flag 1))
										(progn
										
											(setq temp-num(concatenate 'string temp-num float-control))
											(setq float-flag 0)
										)

									)
									(if (and(not(equal temp-num nil))(not(equal float-control "f")))
											(progn
												(if (find "f" temp-num :test #'string-equal)
													(progn	
													(format t "(~s ~s)" temp-num "VALUE_F")
													(setq temp-num nil)		)
													(progn
													(format t "(~s ~s)" temp-num "VALUE_I")
													(setq temp-num nil)		)
													))	)

									(if (and(not(equal temp-num nil))(equal temp-letter ")"))
										(progn
												(if (find "f" temp-num :test #'string-equal)
													(progn													
														(format t "(~s ~s)" temp-num "VALUE_F")
														(setq temp-num nil)		)
													(progn
														(format t "(~s ~s)" temp-num "VALUE_I")
														(setq temp-num nil)		)
													))
									)
								)
							)
						)													
				)
				(cond
        		((string= temp-letter "+") (format t "(~s ~s)" "+" "OP_PLUS"))
        		((string= temp-letter "-") (format t "(~s ~s)" "-" "OP_MINUS"))
        		((string= temp-letter "/") (format t "(~s ~s)" "/" "OP_DIV"))
				((string= temp-letter "(") (format t "(~s ~s)" "(" "OP_OP"))
        		((string= temp-letter ")") (format t "(~s ~s)" ")" "OP_CP"))
        		((string= temp-letter "\"") (if(= string-flag 0)(progn	(format t "(~s ~s)" "\"" "OP_OC")(setq string-flag 1))(progn (format t "(~s ~s)" t"\"" "OP_CC")(setq string-flag 0))))
        		((string= temp-letter ",") (format t "(~s ~s)" temp-word "OP_COMMA"))
        		((and(string= temp-letter "*")(= dbl-mlt-counter 2)) (format t "(~s ~s)" "**" "DBL_MULT")(setq dbl-mlt-counter 0))
        		((and(string= temp-letter "*")(= dbl-mlt-counter 1)) (format t "(~s ~s)" "*" "OP_MULT")(setq dbl-mlt-counter 0))
        		(T nil)
				)
    		)	
			
		)
		(format t ")~%")
		
	)

(defun run-interpreter ()
    (if *args* (gppinterpreter (car *args*)) (gppinterpreter))
)

(defun gppinterpreter (&optional (filename -1))
	(if (equal filename -1)
		(let ((line) (check))
			(loop 
			   (setq line (read-line))
			   (setq check (delete-spaces-and-split-line line))
			   (terpri)
			   (when (= check -1) (return))
			)
		)
		(let ((in (open filename :if-does-not-exist nil)))
   			(when in
      			(loop for line = (read-line in nil)
      
      			while line do (delete-spaces-and-split-line line))
      			(close in)
   			)
		)
	)
)(run-interpreter)