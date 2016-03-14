(TeX-add-style-hook
 "solution_common"
 (lambda ()
   (TeX-run-style-hooks
    "latex2e"
    "article"
    "art10"
    "CJKutf8"
    "lastpage"
    "fancyhdr"
    "titlesec"
    "hyperref"
    "listings")
   (LaTeX-add-environments
    '("homeworkProblem" LaTeX-env-args ["argument"] 1)))
 :latex)

