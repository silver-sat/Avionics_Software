/**
 * @file IntPair.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Exercise for meeting from learncpp.com chapter 13.2
 * @version 1.0.0
 * @date 2022-07-23
 * 
 * 
 */

void setup()
{

	class IntPair
	{
	public:
		int m_first;
		int m_second;
		void set(int first, int second)
		{
			m_first = first;
			m_second = second;
		}
		void print()
		{
			Serial.print("Pair("), Serial.print(m_first), Serial.print(", ");
			Serial.print(m_second);
			Serial.println(")");
		}
	};

	IntPair p1;
	p1.set(1, 1); // set p1 values to (1, 1)

	IntPair p2{2, 2}; // initialize p2 values to (2, 2)

	Serial.begin(115200);
	while (!Serial)
		;
	p1.print();
	p2.print();
};

void loop(){};