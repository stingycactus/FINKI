# Mock midterm 1.2 – Task 1 (entry)

Define a class `Payroll` for calculating the monthly salaries of the employees in a company. The class should have the following functionalities:

* Constructor `Payroll(double minSalary)` with one argument – the minimum salary that an employee may have.
* Method `public void process(InputStream is, OutputStream os)` which reads from the input stream the data for the employees (for each employee, the information is provided on a separate line in the format `ID NAME HOURS RATE`), and outputs to the output stream the employees with their salaries, sorted in descending order by the salary. Employees with an equal salary are sorted by their ID.
  * The salary is calculated as `HOURS * RATE`. Every hour above 160 is paid 1.5 times the rate.
  * If the salary of an employee is lower than `minSalary`, an exception of type `InvalidSalaryException` should be thrown with the message `Employee [ID] has salary [salary] below the minimum of [minSalary]` (both amounts on 2 decimal places). The message should be printed to the output stream, and **the reading of the employees should not stop**. These employees are not included in the list.
  * Each employee is printed in the format `%-6s %-10s %10.2f`.

The class `PayrollTest` is given (see `src`).

## Examples

Input
```text
30000
E01 Ana 160 250
E02 Marko 100 250
E03 Ivana 180 200
E04 Petar 160 200
E05 Sara 120 300
E06 Bojan 40 500
```
Result
```text
Employee E02 has salary 25000.00 below the minimum of 30000.00
Employee E06 has salary 20000.00 below the minimum of 30000.00
E01    Ana          40000.00
E03    Ivana        38000.00
E05    Sara         36000.00
E04    Petar        32000.00
```

Input
```text
0
b2 Luka 10 100
a1 Elena 200 5
c3 Mia 1 1000
```
Result
```text
a1     Elena         1100.00
b2     Luka          1000.00
c3     Mia           1000.00
```
