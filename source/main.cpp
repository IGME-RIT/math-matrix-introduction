/*
Title: Matrix Mathematics
File Name: main.cpp
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

// The primary objects of study in linear algebra are matrices.
// This tutorial series will explore the applications of matrices to computer games and simulation,
//  especially in the realm of physical transformations.
// The exposition follows that of Eric Lengyel in "Foundations of Game Engine Development" (Volume 1).
// We have included the Vector structs from the previous series, and introduced Matrix structs that act similarly.
// These structs are based upon and largely follow code samples given in FGED.
//  As before, Matrix2D is heavily annotated, with other structs being annotated in places of difference.

// This tutorial goes through the basics of matrices.
// By the end of this tutorial you should know:
//  1) What is a matrix?
//  2) How do we represent matrices?
//  3) How do we add and subtract matrices?
//  4) How do we multiply matrices?

// Future tutorials will explain the types of matrices, along with other matrix operations.

#include "../header/Matrix4D.h"
#include "../header/tests.h"
#include "../header/helpers.h"

#include <iostream>
#include <ctime>

int main()
{
	// Required for some helper functions
	srand((unsigned)time(0));

	// Matrices enjoy a place of prominence in games and simulation.
	// First question we should ask ourselves is "What is a matrix?"
	
	// A short, but dense TL;DR is:
	// A matrix is a way to represent any linear map between two modules,
	//  including finite-dimensional vector spaces with a basis defined for each space.
	//  In our case, these vector spaces are almost always Euclidean spaces, particularly R2, R3, or R4.
	//  Then a m by n matrix defines a function f from Rn to Rm by f(x)=Ax satisfying
	//  f(ax_1 + x_2) = af(x_1) + f(x_2), i.e. is additive and homogeneous of degree 1.

	// Let's unpack that statement and approach it from a calculation perspective.

	// For our purposes, a matrix is a 2D grid of real numbers.
	// For example,
	// [ 0 1 ]
	// [ 2 3 ]
	// is a 2 by 2 matrix (it has 2 rows and 2 columns).
	// If a matrix has the same number of rows and columns, we can simply refer to it as a square `nD' matrix.
	//  For example, a 2D matrix is a 2 by 2 matrix, a 3D matrix is a 3 by 3 matrix, etc.
	// We reference the elements of a matrix by specifying the row, then the column (indexed at zero for consistency with computers).
	// So, in our above matrix, the element A(0, 0) = 0, A(0, 1) = 1, A(1, 0) = 2, and A(1, 1) = 3

	// They have some of the operations of regular numbers, particularly addition, subtraction, and multiplication.
	//  (Note that you cannot "divide" by a matrix)

	// We can make a 2D matrix in code as follows:
	Matrix2D A = Matrix2D(0, 1, 2, 3);
	std::cout << "A =\n" << A;
	std::cout << "A(0, 0) = " << A(0, 0) << ", A(0, 1) = " << A(0, 1) << "\n"
		"A(1, 0) = " << A(1, 0) << ", A(1, 1) = " << A(1, 1) << "\n";

	// In this code example, I have only coded 3 types of matrices: 2D, 3D, and 4D.
	// These constitute the vast majority of the types of matrices you will require in game development.
	// It is, of course, possible to have non-square matrices, say, a 3 by 2 matrix, and these have their use.
	// However, they are not common.

	// To add two matrices together, they must have the same number of rows and the same number of columns.
	// Addition is defined component-wise.
	// That is, given two n by m matrices A and B, the ij-th component of A+B is the ij-th component of A plus the ij-th component of B.
	// Symbolically, (A + B)(i, j) = A(i, j) + B(i, j), for all i, j such that 0 <= i < n, 0 <= j < m.
	// We can check this as follows:
	Matrix2D B = Matrix2D(randIntF(-10, 10), randIntF(-10, 10), randIntF(-10, 10), randIntF(-10, 10));
	std::cout << "B =\n" << B
		<< "A + B =\n" << A + B;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			std::cout << "(A + B)(" << i << ", " << j << ") = " << (A + B)(i, j) << " = " << A(i, j) << " + " << B(i, j) << "\n";
		}
	}

	// Subtraction is similarly defined:
	std::cout << "A - B =\n" << A - B;

	// Multiplication is a little more complicated.
	// Rather than requiring that the matrices have identical dimensions, we only require that the matrix on the left
	//  has the same number of columns as the matrix on the right has rows.
	// So, if A is an m by n matrix and B is an n by k matrix, the A*B is well-defined, but B*A is not well-defined unless m = k.
	// From this it should be immediately clear that matrix multiplication is not commutative in general.
	// We require this because of how matrix multiplication is defined.

	// Say we have two 2D matrices we wish to multiply.
	// Take the two matrices and set them up in a grid format as follows
	//         | [ e f ]
	//         | [ g h ]
	//---------+---------
	// [ a b ] | [ ? ? ]
	// [ c d ] | [ ? ? ]

	// As you can see, this means we will have a 2D matrix as a result of this calculation.
	// Now, for each ? in the result matrix, take the dot product of the corresponding row and column.
	// For example, the (0, 0)-th element is equal to the dot product of the left matrix's 0-th row and the top matrix's 0th column.
	// Hence the (0, 0)-th element is a*e + b*g.

	// For example,
	Matrix2D C = Matrix2D(3, 2, 1, 0);
	std::cout << "C =\n" << C;

	// Then A*C is
	//         | [ 3 2 ]
	//         | [ 1 0 ]
	//---------+---------
	// [ 0 1 ] | [ 1 0 ]
	// [ 2 3 ] | [ 9 4 ]
	std::cout << "A * C =\n" << A * C;

	// This can be extended to nD matrices.
	// It even works for non-square matrices! For example, say we had a 3x2 matrix (3 rows, 2 columns) multiplied by a 2x2 matrix.
	// Then their multiplication is
	//         | [ 3 2 ]
	//         | [ 1 0 ]
	//---------+---------
	// [ 0 1 ] | [ 1 0 ]
	// [ 2 3 ] | [ 9 4 ]
	// [ 4 5 ] | [ 17 8 ]

	// Now you may be asking `Why do we define matrix multiplication this way?'
	// For an answer, see the links attached to this tutorial.
	// The short answer is `It is the only natural way to compose matrices when treated as linear transformations.'

	std::cout << "\nPress Enter to exit . . . ";
	std::cin.get();
	return 0;
}
