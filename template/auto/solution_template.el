(TeX-add-style-hook
 "solution_template"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("article" "11pt")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("algorithm" "plain") ("url" "hyphens")))
   (add-to-list 'LaTeX-verbatim-environments-local "lstlisting")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "lstinline")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "lstinline")
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art11"
    "fancyhdr"
    "extramarks"
    "enumitem"
    "amsmath"
    "amsthm"
    "amsfonts"
    "tikz"
    "algorithm"
    "algpseudocode"
    "listings"
    "lastpage"
    "color"
    "CJKutf8"
    "url")
   (TeX-add-symbols
    '("pending" ["argument"] 0)
    '("pderiv" 2)
    '("deriv" 1)
    '("alg" 1)
    '("subqest" 1)
    "dx"
    "solution"
    "E"
    "Var"
    "Cov"
    "Bias")
   (LaTeX-add-environments
    '("homeworkProblem" LaTeX-env-args ["argument"] 1))
   (LaTeX-add-counters
    "partCounter"
    "homeworkProblemCounter"))
 :latex)

