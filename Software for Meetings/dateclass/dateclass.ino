/**
 * @file dateclass.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Class exercise for meeting
 * @version 1.0.0
 * @date 2022-07-23
 *
 *
 */

void setup()
{

    class DateClass
    {
    public:
        DateClass(int year, int month, int day)
        {
            m_year = year;
            m_month = month;
            m_day = day;
        }
        void print()
        {
            Serial.print(m_year);
            Serial.print("/");
            Serial.print(m_month);
            Serial.print("/");
            Serial.println(m_day);
        }

    private:
        int m_year{};
        int m_month{};
        int m_day{};
    };

    DateClass example_day(2022, 10, 14);
    Serial.begin(115200);
    while (!Serial)
        ;
    example_day.print();
};

void loop(){};