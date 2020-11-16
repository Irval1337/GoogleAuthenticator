## Desktop GoogleAuthenticator
Исходный код клиент-серверного приложения Google Authenticator'а для ПК. Программа реализована на C++ CLR, поэтому при желании может быть переписана полностью на C#. Большиснтво операций производятся на сервере, поэтому при большом количестве сервисов программа может задерживать обновление (для фикса можно использовать сокетное соединение), вся информация хранится только в указанной базе данных, клиент может быть заменен простой имитацией GET запросов к серверу.
<br>Скриншоты интерфейса клиента: https://imgur.com/gallery/9rmioC8</br>
#### Основной функционал:
- Авторизация по логину и паролю
- Регистрация новых пользователей
- Восстановление пароля
- Работа с почтой
  - Подтверждение
  - Генерация письма с подтверждением
  - Реализация рассылки
  - Проверка верификации (наличия)
- Работа с GoogleAuthentificator
  - Получение значения кода
  - Добавление нового ключа
  - Удаление ключа
  - Изменение login'a у элемента
  - Генерация QR кода существующего элемента

#### Библиотеки и компоненты, необходимые для компиляции проектов
- Для успешной работы с кодом, а в дальнейшем и с самим .exe десктопного приложения необходимо установить:
  - Установить .NET Framework не старше версии 4.7.2 (скорее всего он уже установлен). Сделать это можно с помощью установщика от Microsoft https://support.microsoft.com/ru-ru/help/4054530/microsoft-net-framework-4-7-2-offline-installer-for-windows
  - Добавить необходимые компоненты в вашу сборку VS:
    - Открываем Visual Studio Installer
    - Выбираем необходимую вам версию и жмем `Изменить` (может находится в пункте `Дополнительно`)
    - В группе `Классические и мобильные приложения` ставим галочки напротив `Разработка классических приложений .NET` и `Разработка классических приложений на C++`
    - Нажимаем `Изменить` и ждем завершения установки
- Для корректной работы серверной части приложения необходимо:
  - Обновить версию PHP до версии 7.2+
  - Создать MYSQL базу данных с одной таблицей таблицей следующего формата:
  
    Название колонны | Тип данных | Назначение
    --- | --- | ---
    Id | INT | Id пользователя
    Username | TEXT | Имя пользователя
    Email | TEXT | Электронная почта
    Password | TEXT | Пароль
    SecretKeys | LONGTEXT | Информация о сервисах
  - Не забудьте изменить всю информацию о хостинге в файлах директории /Server/
#### Для работы сканирования QR кода переместите файл `getQR.exe` в директорию со скомпилированным клиентом. В противном случае будут возникать краши.
###### В случае возникновения проблем/вопросов/предложений, прошу вас писать в Telegram (https://t.me/Irval1337) или ВКонтакте (https://vk.com/irval26) разработчику программы.
