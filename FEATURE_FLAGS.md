Фичи флаги для отключения функционала библиотеки. Пример использования для platformio:
`
build_flags = 
	'-D__VERSION="1.0"'
	'-DLOGGING_LEVEL=10'
`

- ENABLE_WEB_PAGE - включить полную версию веб страницы;
- ENABLE_ACTIONS - включить функционал действий;
- ENABLE_ACTIONS_SCHEDULER - включить функционал переодического вызова действий. Отключается, если ENABLE_ACTIONS == 0;
- ENABLE_NUMBER_SENSORS - включить функционал числовых сенсоров;
- ENABLE_TEXT_SENSORS - включить функционал текстовых сенсоров;
- ENABLE_HOOKS - включить функционал хуков. Автоматически отключается, если ENABLE_NUMBER_SENSORS == 0 && ENABLE_TEXT_SENSORS == 0;
- ENABLE_CONFIG - включить функционал конфигурации устройства;
- ENABLE_OTA - включить ArduinoOTA;
- ENABLE_LOGGER - включить логи;
- LOGGER_TYPE - выбора реализации логгера. Есть две основные реализации:
	- 1 - сетевой tcp логгер (по умолчанию);
	- 3 - сериал логгер;
- LOGGING_LEVEL - уровень логгера:
	- DEBUG - 10;
	- INFO - 20;
	- WARN - 30;
	- ERROR - 40.
  
Так же в параметрах сборки разработчик может указать версию прошивки с помощью параметра `__VERSION`.