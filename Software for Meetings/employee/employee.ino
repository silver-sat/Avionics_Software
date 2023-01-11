/**
 * @file Employee.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Demonsrate an Employee class
 * @version 1.0.0
 * @date 2022-12-04
 *
 * Adapted from learncpp.com
 */

/**
 * @brief Employee class
 *
 */
class Employee
{
public:
    /**
     * @brief Construct a new Employee object
     *
     * @param name name
     * @param id id number
     * @param wage hourly wage
     */
    Employee(String name, int id, double wage)
    {
        m_name = name;
        m_id = id;
        m_wage = wage;
    }

    /**
     * @brief Print an employee
     *
     */
    void print()
    {
        Serial.print("Name: ");
        Serial.print(m_name);
        Serial.print(" Id: ");
        Serial.print(m_id);
        Serial.print(" Wage: $");
        Serial.println(m_wage);
    }

private:
    String m_name{};
    int m_id{};
    double m_wage{};
};

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Employee alex{"Alex", 1, 25.00};
    Employee joe("Joe", 2, 22.25);

    alex.print();
    joe.print();
}

void loop() {}