/**
 * @file dateclass.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Class exercise for meeting
 * @version 1.0.0
 * @date 2022-07-23
 *
 * Adapted from learncpp.com
 */

/**
 * @brief Class to store and print dates
 *
 */
class DateClass
{
public:
    /**
     * @brief Construct a new DateClass object
     *
     * @param year year
     * @param month month
     * @param day day
     */
    DateClass(int year, int month, int day)
    {
        m_year = year;
        m_month = month;
        m_day = day;
    }

    /**
     * @brief Print a DateClass object
     *
     */
    void print()
    {
        Serial.print(m_year);
        Serial.print("/");
        Serial.print(m_month);
        Serial.print("/");
        Serial.println(m_day);
    }

    /**
     * @brief Member variables
     *
     */
private:
    int m_year{};
    int m_month{};
    int m_day{};
};

void setup()
{

    DateClass example_day(2023, 10, 14);
    Serial.begin(115200);
    while (!Serial)
        ;
    example_day.print();
};

void loop(){};