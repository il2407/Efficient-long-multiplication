#pragma once
#include "programEx.h"


using namespace exStack;
string strReverse(string str);
bool inputCheck(string x, string y, string n);


int main()
{

	string x, y, n1;
	cin >> n1;
	cin >> x;
	cin >> y;
	if (!inputCheck(x, y, n1))
	{
		cout << "wrong output" << endl;
	}
	else
	{
		int n = stoi(n1);
		int* xArr = stringToInt(x);
		int* yArr = stringToInt(y);

		measureLongMulti(xArr, yArr, n);
		measureKaratsubaRecursive(x, y);
		measureKaratsubaIterative(x, y);

		delete[]xArr;
		delete[]yArr;
	}
}
bool inputCheck(string x, string y,string n)
{
	if (n[0] == '0')return false;
	int num = stoi(n);
	if (x.length() != num) return false;
	if (y.length() != num)return false;
	for (int i = 0; i < num; i++)
	{
		if (!isdigit(x[i]-'0'))return false;
		if (!isdigit(y[i]-'0'))return false;
	}
	return true;
}

int* stringToInt(string x)
{
	int* arr = new int[x.length()];
	for (int i = 0; i < x.length(); i++)
		arr[i] = x[i]-'0';
	return arr;
}

void printArray(int* numArr, int n)
{
	int flag = 0;
	for (int i = 0; i < n; i++)
	{
		if (numArr[i] != 0)flag = 1;
		if(flag==1) cout << numArr[i];
	}
	if(flag==0)cout << "0";
	cout << endl;
}

int* longMultiplication(int n, int* xArr, int* yArr)
{
	int currArrIndex = n + 1;
	int finalArrIndex = n * 2;
	int currNum = 0;
	int addNext = 0;
	int zeroCounter = 0;
	int* finalArr = new int[n * 2];
	arrInit(finalArr, n * 2);
	for (int j = n - 1; j >= 0; j--)
	{
		finalArrIndex = n * 2;
		addNext = 0;
		int* currArr = (longMultiplicationPerDigit(xArr, yArr[j], n, zeroCounter));
		zeroCounter++;
		for (int i = 0; i < n * 2; i++)
		{
			currNum = finalArr[finalArrIndex - 1] + currArr[finalArrIndex - 1] + addNext;
			if (currNum < 10) { finalArr[finalArrIndex - 1] = currNum; addNext = 0; }
			else { finalArr[finalArrIndex - 1] = currNum % 10; addNext = (currNum / 10) % 10; }
			finalArrIndex--;
			currArrIndex--;
		}
		if (addNext != 0)finalArr[finalArrIndex] = addNext;

	}

	return finalArr;
}

int* longMultiplicationPerDigit(int* currXArr, int currYdigit, int n, int numOfZero)
{
	int currNum;
	int addNext = 0;
	int* currResult = new int[n * 2];
	arrInit(currResult, n * 2);
	int index = (n * 2) - numOfZero - 1;
	int xIndex = n - 1;
	for (int i = 0; i < n; i++)
	{
		currNum = currYdigit * currXArr[xIndex] + addNext;
		if (currNum > 9) { currResult[index] = currNum % 10; addNext = currNum / 10 % 10; }
		else { currResult[index] = currNum; addNext = 0; }
		index--;
		xIndex--;
	}
	if (addNext != 0)currResult[index] = addNext;
	else currResult[index] = 0;
	return currResult;
}

void arrInit(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = 0;
	}
}

string RecursionKaratsuba(string x, string y)
{

	int len = max(x.size(), y.size());

	while (x.size() < len)
		x.insert(0, "0");

	while (y.size() < len)
		y.insert(0, "0");

	if (len == 1)
		return to_string((x[0] - '0') * (y[0] - '0'));

	string a, b, c, d;
	string aPb, cPd;
	string ac, aPbcPd, bd;
	string res;
	a = x.substr(0, len / 2);
	b = x.substr(len / 2, len-(len/2));
	c = y.substr(0, len / 2);
	d = y.substr(len / 2, len - (len / 2));
	if (len > 2)
	{
		aPb = strSum(a, b);
		cPd = strSum(c, d);
		ac = (RecursionKaratsuba(a, c));
		aPbcPd = (RecursionKaratsuba(aPb, cPd));
		bd = (RecursionKaratsuba(b, d));
	
	}
	else
	{
		int aNum, bNum, cNum, dNum;
		aNum = a[0] - '0';
		bNum = b[0] - '0';
		cNum = c[0] - '0';
		dNum = d[0] - '0';
		int res;
		res = ((aNum*cNum) * 100) + (((bNum*cNum) + (aNum*dNum)) * 10) + (bNum*dNum);
		return to_string(res);
	}
	string middle;
	middle = strSub(strSub(aPbcPd, ac),bd);
	for(int i=0;i< 2 * (len - len / 2);i++) ac.append("0");
	for (int i = 0; i < (len - len / 2); i++)middle.append("0");
	res = strSum(strSum(ac,middle),bd);
	int i = 0;
	int counter = 0;
	while (res[i] == '0') {  i++;  counter++;}
	if (counter == res.length())counter--;
	res.erase(0, counter);
	return res;
}

string strSum(string a, string b)
{
	if (a.size() < b.size())
		swap(a, b);

	int j = a.size() - 1;
	for (int i = b.size() - 1; i >= 0; i--, j--)
		a[j] += (b[i] - '0');

	for (int i = a.size() - 1; i > 0; i--)
	{
		if (a[i] > '9')
		{
			int d = a[i] - '0';
			a[i - 1] = ((a[i - 1] - '0') + d / 10) + '0';
			a[i] = (d % 10) + '0';
		}
	}
	if (a[0] > '9')
	{
		string k;
		k += a[0];
		a[0] = ((a[0] - '0') % 10) + '0';
		k[0] = ((k[0] - '0') / 10) + '0';
		a = k + a;
	}
	return a;
}

bool isSmaller(string str1, string str2)
{
	// Calculate lengths of both string
	int n1 = str1.length(), n2 = str2.length();

	if (n1 < n2)
		return true;
	if (n2 < n1)
		return false;

	for (int i = 0; i < n1; i++)
		if (str1[i] < str2[i])
			return true;
		else if (str1[i] > str2[i])
			return false;

	return false;
}

string strSub(string str1, string str2)
{

	if (isSmaller(str1, str2))
		swap(str1, str2);

	string str = "";	
	int n1 = str1.length(), n2 = str2.length();
	str1=strReverse(str1);
	str2=strReverse(str2);
	//reverse(str1.begin(), str1.end());
	//reverse(str2.begin(), str2.end());

	int carry = 0;
	for (int i = 0; i < n2; i++) {

		int sub
			= ((str1[i] - '0') - (str2[i] - '0') - carry);


		if (sub < 0) {
			sub = sub + 10;
			carry = 1;
		}
		else
			carry = 0;

		str.push_back(sub + '0');
	}

	for (int i = n2; i < n1; i++) {
		int sub = ((str1[i] - '0') - carry);

		
		if (sub < 0) {
			sub = sub + 10;
			carry = 1;
		}
		else
			carry = 0;

		str.push_back(sub + '0');
	}

	
	str=strReverse(str);
	//reverse(str.begin(), str.end());

	return str;
}

string iterativeKaratsuba(string x, string y)
{
	int flag=0;
	int line = 0;
	stack round;
	Item curr, next;
	string result;
	curr.x = x;
	curr.y = y;
	curr.line = START;
	round.push(curr);

	while (flag == 0) {

		curr = round.pop();
		line = curr.line;
		switch (line) {
		case START:
		{

			curr.len = max(curr.x.size(), curr.y.size());
			while (curr.x.size() < curr.len)
				curr.x.insert(0, "0");
			while (curr.y.size() < curr.len)
				curr.y.insert(0, "0");

			if (curr.len == 1)
			{
				result = to_string((curr.x[0] - '0') * (curr.y[0] - '0'));
				break;
			}

			else {

				curr.line = AFTER_FIRST;
				curr.a = curr.x.substr(0, curr.len / 2);
				curr.b = curr.x.substr(curr.len / 2, curr.len - curr.len / 2);
				curr.c = curr.y.substr(0, curr.len / 2);
				curr.d = curr.y.substr(curr.len / 2, curr.len - curr.len / 2);
				round.push(curr);
				next.x = curr.a;
				next.y = curr.c;
				next.line = START;
				round.push(next);

				break;
			}
		}
		case AFTER_FIRST:	
		{

			curr.ac = result;

			curr.line = AFTER_SECOND;
			round.push(curr);
			next.x = curr.b;
			next.y = curr.d;
			next.line = START;
			round.push(next);

			break;
		}

		case AFTER_SECOND:
		{
	
			curr.bd = result;
			curr.line = AFTER_THIRD;
			round.push(curr);
			next.x = strSum(curr.a, curr.b);
			next.y = strSum(curr.c, curr.d);
			next.line = START;
			round.push(next);

			break;
		}
		case AFTER_THIRD:
		{
			
			curr.ex01 = result;
			curr.ex02 = strSub(curr.ex01, strSum(curr.ac, curr.bd));		
			for (int i = 0; i < 2 * (curr.len - curr.len / 2); i++) 
				curr.ac.append("0");

			for (int i = 0; i < curr.len - curr.len / 2; i++) //10^ (n/2)
				curr.ex02.append("0");

			curr.result = strSum(strSum(curr.ac, curr.bd), curr.ex02);
			int j = 0;
			int counter = 0;
			while (curr.result[j] == '0') { j++;  counter++; }
			if (counter == curr.result.length())counter--;
			result=curr.result.erase(0, counter);
			break;
		}
		}
		if (round.isEmpty() == true)
			flag = 1;
	}
	return result;
}

void measureKaratsubaIterative(string Sx, string Sy)
{
	auto start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++.
	ios_base::sync_with_stdio(false);

	cout << "Karatsuba (iterative): x * y = " << iterativeKaratsuba(Sx, Sy) << endl;

	auto end = chrono::high_resolution_clock::now();
	// Calculating total time taken by the program.
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	ofstream myfile("Measure3.txt"); // The name of the file
	myfile << "Time taken by function Karatsuba (iterative) is : " << fixed << time_taken << setprecision(9);
	myfile << " sec" << endl;
	myfile.close();

}

void measureKaratsubaRecursive(string Sx, string Sy)
{
	auto start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++.
	ios_base::sync_with_stdio(false);

	cout << "Karatsuba(recursive) : x * y = " << RecursionKaratsuba(Sx, Sy) << endl;

	auto end = chrono::high_resolution_clock::now();
	// Calculating total time taken by the program.
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	ofstream myfile("Measure2.txt"); // The name of the file
	myfile << "Time taken by function Karatsuba(recursive) is : " << fixed << time_taken << setprecision(9);
	myfile << " sec" << endl;
	myfile.close();
}

void measureLongMulti(int* x,int* y,int n)
{
	auto start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++.
	ios_base::sync_with_stdio(false);

	int* arr;
	arr = longMultiplication(n, x, y);
	cout << "Long multiplication : x * y = ";
	printArray(arr, n * 2);

	auto end = chrono::high_resolution_clock::now();
	// Calculating total time taken by the program.
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	ofstream myfile("Measure1.txt"); // The name of the file
	myfile << "Time taken by function <longMultiplication is : " << fixed << time_taken << setprecision(9);
	myfile << " sec" << endl;
	myfile.close();

}

string strReverse(string str)
{
	int len = str.length();
	int n = len - 1;
	for (int i = 0; i < (len / 2); i++) {
		swap(str[i], str[n]);
		n = n - 1;
	}
	return str;
}