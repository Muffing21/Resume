# What does the program do?

### The program is about approximation of serveral formulas instead of using the math library. The program will ask for input of the formula(s) and the program will output approximations by giving the difference of the formula and the math library

# How to build the program?

### Start off by converting the formulas into C code. Have a lot of counters and keep track of them. Usually problem arises when you have to keep track of formulas that involve power or sqrt. Also link all the files together with your Makefile and 

# How to run the program?

### Run the program by typing  ./mathlib-test followed up by any of the following command-line options:
### -a Runs all tests
### -e Runs e approximation test
### -e -b Runs Bailey-Borwein-Plouffe pi approximation test
### -m runs Madhava pi approximation test
### -r Runs Euler sequence pi approximation test
### -v Runs viete pi approximation test
### -n Runs Newton-Raphon square root approximation tests
### -s Enable printing of statistics to see computed terms and factors for each tested function
### -h Display a help message detailng program usage


