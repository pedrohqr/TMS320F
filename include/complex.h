//	Copyright <2023> <Pedro Henrique de Queiroz Ramos>
// 
//	Permission is hereby granted, free of charge, to any 
//	person obtaining a copy of this software and 
//	associated documentation files(the “Software”), to 
//	deal in the Software without restriction, including 
//	without limitation the rights to use, copy, modify, 
//	merge, publish, distribute, sublicense, and /or sell 
//	copies of the Software, and to permit persons to whom
//  the Software is furnished to do so, subject to the 
//	following conditions :
//
//	The above copyright notice and this permission notice 
//	shall be included in all copies or substantial 
//  portions of the Software.
//
//	THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF 
//	ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
//  LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS 
//  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO 
//	EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE 
//	LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
//  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// 
//
//	[Author: Pedro Ramos			 ]
//	[Last Revision: 18/07/2023 ]

#ifndef _COMPLEX_H
#define _COMPLEX_H

#ifdef __cplusplus > 199711L

#include <iostream>
#include <math.h>
#include <vector>

namespace types
{	// begin namespace types
	
	constexpr auto PI = 3.1415926535897932384626433832795;

	template<typename T>
	class Complex
	{	
	public:
		T Re{};
		T Im{};

		Complex() = default;

		Complex(const T& Re, const T& Im):
			Re{ Re },
			Im{ Im }
		{
			// do nothing
		}

		Complex(const Complex& other) :
			Re{ other.Re },
			Im{ other.Im }
		{
			// do nothing
		}

		inline Complex operator +(const Complex& other) const
		{
			return Complex<T>{Re + other.Re, Im + other.Im};
		}

		inline Complex operator -(const Complex& other) const
		{
			return Complex<T>{Re - other.Re, Im - other.Im};
		}

		inline Complex operator *(const Complex& other) const
		{
			return Complex<T>{Re * other.Re - Im * other.Im, Re * other.Im + Im * other.Re};
		}

		inline Complex<T> operator *(const T& other) const
		{
			return Complex<T>{Re * other, Im * other};
		}

		inline Complex<T> operator /(const T& other) const
		{
			return Complex<T>{Re / other, Im / other};
		}

		inline Complex& operator +=(const Complex& other)
		{
			Re = Re + other.Re;
			Im = Im + other.Im;
			return *this;
		}

		inline Complex& operator *=(const Complex& other)
		{			
			return (*this = *this * other);
		}

		inline bool operator ==(const Complex& other) const
		{
			return Re == other.Re && Im == other.Im;
		}

		inline bool operator !=(const Complex& other) const
		{
			return Re != other.Re || Im != other.Im;
		}

		inline Complex& operator =(const Complex& other)
		{
			Re = other.Re;
			Im = other.Im;
			return *this;
		}

		inline Complex operator !() const
		{
			return Complex<T>{Re, -Im};
		}
	
		friend std::ostream& operator <<(std::ostream& os, const Complex& me)
		{
			os << "(" << me.Re << ", j" << me.Im << ")";
			return os;
		}	
	};	// Complex	

	template<typename T>
	T arg(const Complex<T>& A, bool radians = true)
	{
		T _arg{ atanf(A.Im / A.Re) };
		return radians ? _arg : (_arg * 180 / PI);
	}

	template<>
	double arg(const Complex<double>& complex, bool radians)
	{
		double _arg{ atan(complex.Im / complex.Re) };
		return radians ? _arg : (_arg * 180 / PI);
	}

	template<typename T>
	T mod(const Complex<T>& complex)
	{
		return sqrt(complex.Re * complex.Re + complex.Im * complex.Im);
	}

	template<typename T>
	std::vector<T> mod(const std::vector<Complex<T>>& x)
	{
		std::vector<T> y;

		for (size_t i = 0; i < x.size(); ++i)
			y.push_back(mod<T>(x[i]));

		return y;
	}

	template<typename T>
	std::vector<T> Re(const std::vector<Complex<T>>& x)
	{
		std::vector<T> y;

		for (size_t i = 0; i < x.size(); ++i)
			y.push_back(x[i].Re);

		return y;
	}

	template<typename T>
	std::vector<T> Im(const std::vector<Complex<T>>& x)
	{
		std::vector<T> y;

		for (size_t i = 0; i < x.size(); ++i)
			y.push_back(x[i].Im);

		return y;
	}

	template<typename T>
	inline Complex<T> operator *(const T& T1, const Complex<T>& T2)
	{
		return Complex<T>{T2.Re * T1, T2.Im * T1};
	}

	inline
	bool
	isPower2(size_t l)
	{
		bool k = false;
		for (size_t i = 0, j = sizeof(size_t) * 8; i < j; ++i)
		{
			if (l % 2 == 0)
				l >>= 1;
			else if (!k)
			{
				k = true;
				l >>= 1;
			}
			else
				return false;
		}
		return true;
	}

	size_t 
	paddingUpPower2(size_t x)
	{
		size_t last{}, 
			i = sizeof(size_t) * 8,
			k = (size_t)1 << (i-1);
		for (size_t i = sizeof(size_t)*8; i > 0; --i)
		{
			if (x > (size_t)1 << (i - 1))
			{
				last = i;
				break;
			}
		}

		return (size_t)1 << last;
	}

}// end namespace types

#endif	// __cplusplus
#endif	// _COMPLEX_H