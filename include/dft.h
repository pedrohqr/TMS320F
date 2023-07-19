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

#ifndef _DFT_H
#define _DFT_H

#ifdef __cplusplus > 199711L

#include <vector>
#include <math.h>
#include <cassert>
#include "complex.h"

namespace dft
{	// begin namespace dft

	using namespace types;

	template<typename T>
	void 
	bitReversalManipulation(std::vector<T>& x)
	{
		size_t N = x.size(), l = static_cast<size_t>(log2(N));

		for (size_t i = 0; i < N; ++i)
		{
			size_t j = 0;
			for (size_t k = 0; k < l; ++k)
			{
				j |= (i >> k) & 1;
				j <<= 1;
			}
			j >>= 1;

			if (j > i)
				std::swap(x[i], x[j]);
		}
	}

	template<typename T>
	void 
	fft(std::vector<Complex<T>>& X)
	{				
		assert(X.size() > 0, "Invalid input size");

		size_t oldN{ X.size() };

		if (!isPower2(oldN))
		{			
			size_t len{ types::paddingUpPower2(oldN) };
			for (size_t i = X.size(); i < len; ++i)
				X.push_back( Complex<T>{ 0, 0 } );
		}

		size_t N{ X.size() };
		X.resize(N);

		bitReversalManipulation<Complex<T>>(X);

		for (size_t s = 1, l = static_cast<size_t>(log2(N)); s <= l; ++s)
		{
			size_t m{ (size_t)1 << s };
			T theta{ -2.0 * PI / m };
			Complex<T> Wm { cos(theta), sin(theta) };
			for (size_t k = 0; k < N; k += m)
			{		
				Complex<T> w { 1, 0 };
				for (size_t j = 0; j < m/2; ++j)
				{					
					Complex<T> t { w * X[k + j + m / 2] };
					Complex<T> u { X[k + j] };
					X[k + j] = u + t;
					X[k + j + m/2] = u - t;
					w *= Wm;
				}
			}
		}
	}

	template<typename T>
	inline
	void 
	normalize(std::vector<Complex<T>>& X)
	{
		size_t N = X.size();
		size_t N2 = N / 2;
		for (size_t k = 0; k < N; ++k)		
			X[k] = X[k] / N2;		
	}

}	// end namespace dft

#endif	// __cplusplus
#endif	// _DFT_H