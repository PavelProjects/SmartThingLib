#ifndef CONFIG_OBJECTS_H
#define CONFIG_OBJECTS_H

#include <functional>
#include <ArduinoJson.h>

#define STATE_TYPE "state"
#define SENSOR_TYPE "sensor"

#define CONFIGURABLE_JS0N_SIZE 64

namespace Configurable {
    template<class T>
    struct ConfigurableObject {
        public:
            ConfigurableObject(const char * objType): type(objType){};
            typedef std::function<T(void)> ValueGeneratorFunction;

            const char * name;
            const char * type;
            
            ValueGeneratorFunction valueGenerator;

            StaticJsonDocument<CONFIGURABLE_JS0N_SIZE> toJson() {
                StaticJsonDocument<CONFIGURABLE_JS0N_SIZE> doc;
                doc["name"] = name;
                doc["type"] = type;
                return doc;
            };
    };

    namespace Sensor {
        enum SensorType {
            TYPE_CUSTOM,
            TYPE_DIGITAL,
            TYPE_ANALOG
        };
        inline const char * sensorTypeName(SensorType type) {
            switch (type) {
                case TYPE_CUSTOM:
                    return "custom";
                case TYPE_DIGITAL:
                    return "digital";
                case TYPE_ANALOG:
                    return "analog";
            }
            return "type_not_found_how";
        };

        struct Sensor: public ConfigurableObject<int16_t> {
            public:
                Sensor(): ConfigurableObject<int16_t>(SENSOR_TYPE) {};
                int pin;
                SensorType type;
        };
    }
    namespace DeviceState {
        struct DeviceState: public ConfigurableObject<String> {
            DeviceState(): ConfigurableObject<String>(STATE_TYPE) {};
        };
    }
}

#endif