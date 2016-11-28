/*
Title: Matrix Mathematics
File Name: tests.cpp
Copyright © 2016
Author: Andrew Litfin
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "../header/tests.h"

void TestInverseSpeedReportHelper(unsigned n, unsigned numTests, long long totalfast, long long totalslow)
{
	std::cout << "Matrix" << n << "D tests (n=" << numTests << ")\nInverse:\n--------\nTotal: " << totalfast / 1000000 << " milliseconds\n"
		"Average: " << (float)totalfast / numTests << " nanoseconds/test\n";
	std::cout << "AdjInvs:\n--------\nTotal: " << totalslow / 1000000 << " milliseconds\n"
		"Average: " << (float)totalslow / numTests << " nanoseconds/test\n\n";
}

void TestMat2DInverseSpeed(unsigned numTests)
{
	Matrix2D m, inv;
	Clock::time_point fastt1, fastt2, slowt1, slowt2;
	long long totalslow = 0, totalfast = 0, delta;

	for (size_t i = 0; i < numTests; i++)
	{
		m = Matrix2D(randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX));

		fastt1 = Clock::now();
		inv = Inverse(m);
		fastt2 = Clock::now();
		delta = std::chrono::duration_cast<std::chrono::nanoseconds>(fastt2 - fastt1).count();
		totalfast += delta;

		slowt1 = Clock::now();
		inv = InverseAdj(m);
		slowt2 = Clock::now();
		delta = std::chrono::duration_cast<std::chrono::nanoseconds>(slowt2 - slowt1).count();
		totalslow += delta;
	}

	TestInverseSpeedReportHelper(2, numTests, totalfast, totalslow);
}

void TestMat3DInverseSpeed(unsigned numTests)
{
	Matrix3D m, inv;
	Clock::time_point fastt1, fastt2, slowt1, slowt2;
	long long totalslow = 0, totalfast = 0, delta;

	for (size_t i = 0; i < numTests; i++)
	{
		m = Matrix3D(randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX),
			randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX),
			randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX));

		fastt1 = Clock::now();
		inv = Inverse(m);
		fastt2 = Clock::now();
		delta = std::chrono::duration_cast<std::chrono::nanoseconds>(fastt2 - fastt1).count();
		totalfast += delta;

		slowt1 = Clock::now();
		inv = InverseAdj(m);
		slowt2 = Clock::now();
		delta = std::chrono::duration_cast<std::chrono::nanoseconds>(slowt2 - slowt1).count();
		totalslow += delta;
	}

	TestInverseSpeedReportHelper(3, numTests, totalfast, totalslow);
}

void TestMat4DInverseSpeed(unsigned numTests)
{
	Matrix4D m, inv;
	Clock::time_point fastt1, fastt2, slowt1, slowt2;
	long long totalslow = 0, totalfast = 0, delta;

	for (size_t i = 0; i < numTests; i++)
	{
		m = Matrix4D(randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX),
			randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX),
			randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX),
			randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX), randFloat(-FLT_MAX, FLT_MAX));

		fastt1 = Clock::now();
		inv = Inverse(m);
		fastt2 = Clock::now();
		delta = std::chrono::duration_cast<std::chrono::nanoseconds>(fastt2 - fastt1).count();
		totalfast += delta;

		slowt1 = Clock::now();
		inv = InverseAdj(m);
		slowt2 = Clock::now();
		delta = std::chrono::duration_cast<std::chrono::nanoseconds>(slowt2 - slowt1).count();
		totalslow += delta;
	}

	TestInverseSpeedReportHelper(4, numTests, totalfast, totalslow);
}
