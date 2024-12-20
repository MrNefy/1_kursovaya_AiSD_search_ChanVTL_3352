import matplotlib.pyplot as plt
import numpy as np

# Значения размеров массивов
n_values = np.arange(1, 1000, 1)

# Вычисление функций
theta_n = n_values  # Θ(n)
theta_log_n = np.log2(n_values)  # Θ(log n)
theta_log_log_n = np.log2(np.log2(n_values))  # Θ(log log n)
theta_sqrt_n = np.sqrt(n_values)  # Θ(√n)
theta_n_log_n = n_values * np.log2(n_values)  # Θ(n log n)

# Построение графика
plt.figure(figsize=(10, 6))

# Графики функций
plt.plot(n_values, theta_n, label='1. Линейный поиск  Θ(n)', linestyle='-')
plt.plot(n_values, theta_log_n, label='2. Бинарный поиск  Θ(log n)', linestyle='-')
plt.plot(n_values, theta_log_log_n, label='3. Интерполяционный поискΘ(log log n)', linestyle='-')
plt.plot(n_values, theta_sqrt_n, label='4. Прыжковый поиск Θ(√n)', linestyle='-')
plt.plot(n_values, theta_n_log_n, label='5. Экспоненциальный поискΘ(n log n)', linestyle='-')

# Настройка графика
plt.xlabel('Номер элемента')
plt.ylabel('Время')
plt.title('График сравнения средней сложности')
plt.title('График Теоретической части')
plt.legend()
plt.grid(True)
plt.show()