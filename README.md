# Сократитель ссылок на C++ (API)
Проект представляет собой API для сокращения ссылок, реализованное на C++ с использованием библиотеки Poco.  Он позволяет пользователям генерировать короткие ссылки для длинных URL, облегчая  их  использование  и  отслеживание.
# Пример работы
* [Документация](http://kologermit.ru:8001/)
* [АПИ](http://kologermit.ru:8000/)
# Функциональность
* Генерирует короткие ссылки для длинных URL-адресов.
* Предоставляет API для работы с сервисом (создание, получение, удаление ссылок).
* Оснащен системой логгирования для отслеживания событий.
## Необходимые программы
* Docker-compose версии 3+
## Первый запуск
### Для первого запуска необходимо создать файл .env, в котором указать переменные окружения:
* API_PORT - внешний порт для API. Пример (по умолчанию) ```8000```
* API_HOST - хост для API вместе с портом. Пример (по умолчанию) ```http://localhost:8000```
* API_DOC_PORT - внешний порт для документации. Пример (по умолчанию) ```8001```
* API_DOC_HOST - хост для документации вместе с портом. Пример (по умолчанию) ```http://localhost:8001```
### Выполнить команду при запущенном Docker в корневой папке проекта
```bash
docker compose up -d
```
### На первом запуске проект собирается около 20 минут
## Перезапуск
```bash
docker compose restart
```
## Остановка
```bash
docker compose stop
```
## Удаление проекта из Docker
```bash
docker compose rm -f -s
```
## Просмотр логов
```bash
docker compose logs --tail 100 -f
```
### Чтобы выйти из просмотра логов CTRL+C
# Использованные технологии
- Библиотека: Poco
  * Взаимодествие с БД
  * Реализация веб-сервера
  * Формирование ответа в JSON формате
  * Логгирование
- Пакетный менеджер: Conan2
  * Загрузка файлов библиотек
  * Установка зависимостей
- Сборщик: CMAKE
  * Сборка зависимостей
  * Сборка исполняемого файла
- БД: SQLITE
- Документация: Swagger-UI
- Клиент: Swagger-UI
- Запуск: Docker-compose
