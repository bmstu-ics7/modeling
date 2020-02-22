# Лабораторная работа 1

$`\begin{cases} u'(x) = f(x,u) \\ u(\xi) = y  \end{cases}`$

* **Метод Пикара**

    $`\begin{matrix} y^{(s)}(x) = \eta + \int_0^x f(t, y^{(s-1)}(t)) dt\\ \\ y^{(0)} = \eta \\ \end{matrix}`$

* **Численный метод Эйлера**
    - Явная форма

    $`y_{n+1} = y_n + h \cdot f(x_n, y_n`$

    - Неявная форма

    $`y_{n+1} = y_n + h \cdot (f(x_{n+1}, y_{n+1})`$
