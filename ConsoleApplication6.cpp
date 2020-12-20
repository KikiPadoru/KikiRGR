#include <iostream>
using namespace std;

struct Pair
{
	int arg;
	int value;
	Pair(int arg = int(), int value = int()) {
		this->arg = arg;
		this->value = value;
	}
	Pair(const Pair& p) {
		this->arg = p.arg;
		this->value = p.value;
	}
	Pair& operator=(Pair& p) {
		this->arg = p.arg;
		this->value = p.value;
		return *this;
	}
	Pair operator+(Pair& p)
	{
		Pair r;
		r.arg = arg + p.arg;
		r.value = value + p.value;
		return r;
	}
	Pair operator-(Pair& p)
	{
		Pair r;
		r.arg = arg - p.arg;
		r.value = value - p.value;
		return r;
	}
	Pair operator/(Pair& p)
	{
		Pair r;
		r.arg = arg / p.arg;
		r.value = value / p.value;
		return r;
	}
	Pair operator*(Pair& p)
	{
		Pair r;
		r.arg = arg * p.arg;
		r.value = value * p.value;
		return r;
	}
	bool operator<(Pair& p) {
		if (this->arg < p.arg) return true;
		else return false;
	}
	bool operator>(Pair& p) {
		if (this->arg > p.arg) return true;
		else return false;
	}
	friend istream& operator>>(istream& is,Pair& cob)
	{
		char c = '\0';
		int y = 0;
		bool minus = false;
			for (int i = 0; c!=')'; ++i)
			{
				c = is.get();
				if (isdigit(c))
				{
					 y = y+ (c - '0');
					 y *= 10;
				}else if(c == '-')
				{
					minus = true;
					continue;
				}else if(c == '+')
				{
					continue;
				}
				else if(c=='(')
				{
					y /= 10;
					if (minus)y *= -1;
					cob.value = y;
					y = 0;
					minus = false;
				}else if(c==')')
				{
					y /= 10;
					if (minus)y *= -1;
					cob.arg = y;
				}
				else {
					 throw;
				}
			}
			return is;
	}
	friend ostream& operator<<(ostream& os, const Pair& p) {
		return os << p.value << "(" << p.arg << ")";
	}
	bool operator ==(const Pair& cob)
	{
		if (arg != cob.arg && value != cob.value)return 0;
		return 1;
	}

	bool operator !=(const Pair& cob)
	{
		return !(*this == cob);
	}

};


//otobrazhenie
class Mass
{
private:

	int maxsize;
	Pair* array;
public:
	class Iterator
	{
	public:
		Pair* u; friend class Mass;
		Iterator()
		{
			u = nullptr;
		}
		Iterator(const Iterator& y)
		{
			u = y.u;
		}

		bool operator==(Iterator& y)
		{
			return (u == y.u);
		}
		bool operator!=(Iterator& y)
		{
			return (u != y.u);
		}
		Pair& operator*()
		{
			return *u;
		}
		Pair* operator->()
		{
			return u;
		}
		Iterator& operator =(const Iterator& d)
		{
			this->u = d.u;
			return *this;
		}
		Iterator operator ++()
		{
			u++;
			return *this;
		}
		Iterator operator ++(int)
		{
			Iterator y = *this;
			u++;
			return y;
		}
		Iterator operator --()
		{
			u--;
			return *this;
		}
		Iterator operator --(int)
		{
			Iterator y = *this;
			u--;
			return  y;
		}

		
	};
	Mass(int size)
	{
		this->maxsize = size;
		array = new Pair[maxsize];
	}
	Mass()
	{
		this->maxsize = 0;
		array = new Pair[0];
	}
	Mass(const Mass& cop)
	{
		this->maxsize = cop.maxsize;
		delete[] array;
		array = new Pair[maxsize];
		for(int i =0;i< maxsize;i++)
		{
			array[i] = cop.array[i];
		}
	}
	~Mass() //деструктор
	{
		delete[] array;
	}
	Pair& operator[](int index)
	{
		return array[index];
	}
	friend ostream& operator<<(ostream& os, const Mass& p)
	{
		os << '[';
		for (int i = 0; i < p.maxsize; i++)
		{
			os << p.array[i];
			if (i != p.maxsize - 1)os << ", ";
		}
		os << ']' << endl;
		return os;
	}
	friend istream& operator>>(istream& is, Mass& cob)
	{
		char c='\0';
		try
		{
			for (int i = 0; i < cob.maxsize;)
			{
				c = is.get();
				if (c == '[')
				{
					is >> cob.array[i++];
					continue;
				}
				else if (c == ',') {
					continue;
				}
				else if (c == ' ')
				{
					is >> cob.array[i++];
					continue;
				}else if(c == ']')
				{
					break;
				}
				else {
					throw;
				}
			}
			while (is.get() != '\n');
		}
		catch (const char* i)
		{
			cerr << "Error";
		}
		return is;
	}
	bool operator!()
	{
		return !maxsize;
	}
	bool operator ==(Mass& cob)
	{
		if (maxsize != cob.maxsize)return 0;
		for (int i = 0; i < maxsize; i++)if (array[i] != cob.array[i])return 0;
		return 1;
	}
	int valueSearch(int value)
	{
		for (int i = 0; i < maxsize; i++)
		{
			if (value == array[i].value)return i;
		}
		return -1;
	}
	int argSearchBuValue(int value)
	{
		for (int i = 0; i < maxsize; i++)
		{
			if (value == array[i].value)return array[i].arg;
		}
		return -1;
	}

	void unite(Mass& cob)//обьединение
	{
		int max = maxsize + cob.maxsize;
		Pair* help = new Pair[max];
		for (int i = 0; i < max; i++)
		{
			if (i < maxsize)
			{
				help[i] = array[i];
			}
			else
			{
				help[i] = cob.array[i - maxsize];
			}

		}
		maxsize = max;
		delete[]array;
		array = help;
	}
	Iterator beg()
	{
		Iterator ptr;
		ptr.u = array;
		return ptr;
	}
	Iterator end()
	{
		Iterator ptr;
		ptr.u = array + maxsize-1;
		return ptr;
	}
	Mass& operator =(const Mass& cop)
	{
		maxsize = cop.maxsize;
		delete[] array;
		array = new Pair[maxsize];
		for(int i = 0; i<maxsize;i++)
		{
			array[i]= cop.array[i];
		}
		return *this;
	}
	void checkArg()
	{
		for(int i =0;i<maxsize;i++)
		{
			int arg = array[i].arg;
			for(int j = i+1;j<maxsize;j++)
			{
				if(arg==array[j].arg)
				{
					cout <<"\033[7;31mError\033[0m"<<endl;
					return;
				}
			}
		}
	}
	Mass& composit( Mass&e, Mass&a)
	{
		e.checkArg();
		a.checkArg();
		Mass R(a.maxsize);//количество композиций не привысит количество пар в одном из массивов
		int kol = 0;//количество парочек
		
		for(int i=0;i < a.maxsize;i++)
		{
			int avalue = a.array[i].value;
			bool flag = false;
			int j;
			for(j = 0;j<e.maxsize;j++)
			{
				if (avalue == e.array[j].arg) { flag = true; break;}
			}
			if (flag)
			{
				R[kol].arg = a.array[i].arg;
				R[kol++].value = e.array[j].value;
			}
		}
		maxsize = kol;
		delete[]array;
		array = new Pair[kol];
		for(int i =0;i<kol;i++)
		{
			array[i] = R.array[i];
		}
		return *this;
	}
};

//[2(1), -5(3), 17(4), 0(9)][5(1), 9(2), -5(17), 0(0), 3(3)]
int main()
{
	Mass F(4), G(5);
	cin >> G;
	cout << G;
	cin >> F;
	cout <<F;
	
	//cout << (B == A) << endl;
	//Mass::Iterator i = A.beg();
	//Mass::Iterator u = A.end();
	//for(i;i!=u;i++)
	//{
	//	cout << *i;
	//}
	Mass S;
	S.composit(G, F);
	cout <<"\033[1;33m"<< S;
	S.composit(F, G);
	cout << S<< "\033[0m";
	//cout << A.valueSearch(5) << '\n' << A.argSearchBuValue(5) << endl;
	//A.unite(B);
	//cout << A;
}