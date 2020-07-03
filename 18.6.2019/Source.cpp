#include<iostream>
#include<string>

using namespace std;

//1.
template<typename Tip>
int findLongestRepetition(Tip *array, int size)
{
	int longestRepetition = 0;
	int repetitionForElement;
	for (int i = 0; i < size; i++)
	{
		repetitionForElement = 1;
		for (int j = i + 1; j < size; j++)
		{
			if (array[j] == array[j-1])
			{
				if (array[i] == array[j])
					repetitionForElement++;
			}
			else
			{
				break;
			}
		}
		if (repetitionForElement > longestRepetition)
		{
			longestRepetition = repetitionForElement;
		}
	}
	return longestRepetition;
}

//2. zadatak
class FootballCard
{
	int mNumber;
	string mName;
public:
	FootballCard() : mNumber(0), mName("Unknown") {}
	FootballCard(int number, string name) : mNumber(number), mName(name) {}
	friend bool operator== (const FootballCard&, const FootballCard&);
};

bool operator== (const FootballCard& f1, const FootballCard& f2)
{
	return f1.mNumber == f2.mNumber && f1.mName == f2.mName;
}


//3. zadatak
class Cooler
{
protected:
	double mDesiredTemperature;
	double mDegreesPerHour;
	double mLossFactor;
public:
	Cooler(double desiredTemperature, double degreesPerHour, double lossFactor) :
		mDesiredTemperature(desiredTemperature), mDegreesPerHour(degreesPerHour), mLossFactor(lossFactor)
	{
		if (mDegreesPerHour < 0)
		{
			mDegreesPerHour *= -1;
		}
		if (mLossFactor < 0 || mLossFactor > 0.2)
		{
			mLossFactor = 0.2;
		}
	}
	void setDesiredTemperature(double desiredTemperature)
	{
		mDesiredTemperature = desiredTemperature;
	}
	friend ostream& operator<< (ostream&, Cooler&);

	double timeToCoolDown(double temperature)
	{
		if (temperature <= mDesiredTemperature)
		{
			return 0;
		}
		return temperature / (mDegreesPerHour * (1 - mLossFactor));
	}
};
ostream& operator<< (ostream& izlaz, Cooler& cooler)
{
	izlaz << cooler.mDesiredTemperature << ", " << cooler.mDegreesPerHour << ", " << cooler.mLossFactor << endl;
	return izlaz;
}

double timeToCoolDownAll(Cooler cooler, double *temperatures, int size)
{
	double maxTemp = temperatures[0];
	for (int i = 0; i < size; i++)
	{
		if (temperatures[i] > maxTemp)
		{
			maxTemp = temperatures[i];
		}
	}
	return cooler.timeToCoolDown(maxTemp);
}

class TurboCooler : Cooler
{
private:
	double mTurboFactor;
public:
	TurboCooler(double desiredTemperature, double degreesPerHour, double lossFactor, double turboFactor) :
		Cooler(desiredTemperature, degreesPerHour, lossFactor), mTurboFactor(turboFactor)
	{
		if (mTurboFactor < 1.1 || mTurboFactor > 2.0)
		{
			mTurboFactor = 1.1;
		}
	}
	void setTurboFactor(double turboFactor)
	{
		mTurboFactor = turboFactor;
	}
	double timeToCoolDown(double temperature)
	{
		double temperatureAfterTwoHours = (mDegreesPerHour * mTurboFactor) * 2;
		return timeToCoolDown(temperature - temperatureAfterTwoHours);
	}
};


int main()
{
	int array[5] = { 1, 2, 2, 2, 3};
	cout << findLongestRepetition(array, 5) << endl;

	FootballCard data[] = { FootballCard(), FootballCard(1, "Hart"), FootballCard(10, "Modric"), FootballCard(10, "Modric") };
	cout << findLongestRepetition(data, 4) << endl;
	
	Cooler yeti(6.0, 1.7, 0.02);
	yeti.setDesiredTemperature(5.0);
	cout << "In stock: " << yeti << "3pcs" << endl;
	
	cout << yeti.timeToCoolDown(30) << endl;

	system("pause");
}