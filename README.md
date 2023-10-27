# SmartCalc
Вesktop learning project, calculator

## Instruction for Makefile:
### Все make цели выполняются из директории src!

Make all: build an app
создать приложение

Make uninstall: uninstall an app
удалить приложение

Make dvi: open this documentation
открыть эту документацию

Make dist: tar an app
архивировать приложение

Make test: run unit tests for model part of an app
запустить модульные тесты для модельной части приложения

Make gcov_report: run tests and get report about code coverage
запустить тесты и получить отчет о покрытии кода

Make format: reformat all code
переформатировать весь код

Make format_check: check format all code
проверить форматирование всего кода

Make clean: clear the project of excess
очистить проект от лишнего

## SmartCalc v1.0 by Opresspa


### Описание проекта:


Эта программа представляет собой универсальный калькулятор, который позволяет пользователям выполнять различные вычисления, включая вычисление арифметических выражений, построение графиков функций, расчет кредитов и депозитов.

Программа предоставляет интуитивно понятный пользовательский интерфейс для ввода выражений и просмотра результатов.

Калькулятор предлагает большую гибкость и точность, что делает его пригодным для различных математических расчетов и финансовых расчетов.

Пользователи могут эффективно оценивать сложные арифметические выражения, визуализировать графики функций и принимать обоснованные финансовые решения, используя режим кредитного калькулятора.

Благодаря удобному интерфейсу и точным результатам программа удовлетворяет широкий спектр математических и финансовых потребностей.


### Вычисление арифметического выражения:

Пользователи могут вводить произвольные арифметические выражения в квадратных скобках в инфиксной нотации, используя распространенные арифметические операторы, такие как сложение, вычитание, умножение, деление, степень и модуль.

Калькулятор точно вычисляет выражения до 7 знаков после запятой и может обрабатывать выражения до 255 символов.

Он поддерживает математические функции, такие как косинус, синус, тангенс, арккосинус, арксинус, арктангенс, квадратный корень, натуральный логарифм и десятичный логарифм.

### Построение графика:

Пользователи могут строить графики функций, заданных в инфиксной нотации с переменной «x».

Программа предоставляет удобную систему координат с нанесенными шкалами и адаптивной сеткой.

Пользователь может использовать колесо прокрутки для увеличения и уменьшения масштаба и перетаскивания изображения для перемещения по сетке.

Домен и кодовый домен функции ограничены диапазоном от -1 000 000 до 1 000 000, но пользователь может указать отображаемый домен и кодовый домен для построения графика.

Чтобы создать изображение графика, пользователь должен ввести уравнение, щелкнуть кнопку "GRAPH" и нажать кнопку "отрисовать" или также есть возможность ввода в окне гафики и вывода по нажатию на энтер.

### Кредитный калькулятор:

В программу включен специальный режим, известный как "Кредитный калькулятор".

Пользователи могут вводить такие данные, как общая сумма кредита, срок (длительность), процентная ставка и тип кредита (аннуитетный или дифференцированный).

На основе введенных данных калькулятор предоставляет такую ​​информацию, как ежемесячный платеж, переплата по кредиту и общая сумма платежа.

### Депозитный калькулятор:

В программу включен специальный режим, известный как "Депозитный калькулятор".

Пользователи могут вводить такие данные, как общая сумма вклада, срок (длительность), процентная ставка, налоговая ставка, переодичность выплат, капитализация и также есть опции пополнения и снятия.

На основе введенных данных калькулятор предоставляет такую ​​информацию, сумма начислений, сумма вклада с процентами и сумма уержанных налогов.


### Description of the project:


This program is a universal calculator that allows users to perform various calculations, including calculating arithmetic expressions, plotting functions, calculating loans and deposits.

The program provides an intuitive user interface for entering expressions and viewing results.

The calculator offers great flexibility and accuracy, making it suitable for a variety of mathematical calculations and financial calculations.

Users can efficiently evaluate complex arithmetic expressions, visualize function graphs, and make informed financial decisions using the loan calculator mode.

With a user-friendly interface and accurate results, the program satisfies a wide range of mathematical and financial needs.

### Evaluation of an arithmetic expression:

Users can enter arbitrary arithmetic expressions in square brackets in infix notation using common arithmetic operators such as addition, subtraction, multiplication, division, power, and modulus.

The calculator accurately calculates expressions up to 7 decimal places and can handle expressions up to 255 characters.

It supports math functions such as cosine, sine, tangent, arccosine, arcsine, arctangent, square root, natural logarithm, and decimal logarithm.

### Plotting:

Users can plot functions given in infix notation with the variable "x".

The program provides a convenient coordinate system with applied scales and an adaptive grid.

The user can use the scroll wheel to zoom in and out and drag the image to move around the grid.

The function domain and code domain are limited to -1,000,000 to 1,000,000, but the user can specify the display domain and code domain for plotting.

To create a graph image, the user must enter an equation, click the "GRAPH" button and press the "draw" button, or there is also the option to enter in the graph window and output by pressing enter.

### Credit calculator:

The program includes a special mode, known as the "Loan Calculator".

Users can enter data such as total loan amount, term (duration), interest rate, and type of loan (annuity or differentiated).

Based on the data entered, the calculator provides information such as monthly payment, loan overpayment, and total payment amount.

### Deposit calculator:

The program includes a special mode known as "Deposit Calculator".

Users can enter data such as the total amount of the deposit, term (duration), interest rate, tax rate, payment frequency, capitalization, and there are also deposit and withdrawal options.

Based on the data entered, the calculator provides such information, the amount of accruals, the amount of the deposit with interest and the amount of taxes withheld.
