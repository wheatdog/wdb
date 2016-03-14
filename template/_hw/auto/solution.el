(TeX-add-style-hook
 "solution"
 (lambda ()
   (TeX-run-style-hooks
    "$WDL_TOOL/template/solution_common")
   (TeX-add-symbols
    "hmwkID"
    "hmwkTitle"
    "hmwkDueDate"
    "hmwkUniversity"
    "hmwkClass"
    "hmwkClassAlias"
    "hmwkClassSection"
    "hmwkClassInstructor"
    "hmwkAuthorName"
    "hmwkAuthorID")
   (LaTeX-add-environments
    '("homeworkProblem" LaTeX-env-args ["argument"] 1)))
 :latex)

