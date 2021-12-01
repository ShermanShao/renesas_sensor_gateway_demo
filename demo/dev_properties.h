
struct dev_humidity
{
    float data;
    char name[12];// = "humidity";
};

struct dev_temperature
{
    float data;
    char name[12];//= "temperature"
};

struct dev_EtOH
{
    float data;
    char name[12];// = "EtOH";
};

struct dev_CO2
{
    float data;
    char name[12];// = "CO2";
};

struct dev_TVOC
{
    float data;
    char name[12];// = "TVOC";
};

struct dev_IAQ
{
    float data;
    char name[12];//"IAQ"
};

struct dev_properties
{
    struct dev_humidity humidity;
    struct dev_temperature temperature;
    struct dev_EtOH EtOH;
    struct dev_CO2 CO2;
    struct dev_TVOC TVOC;
    struct dev_IAQ IAQ;
};
