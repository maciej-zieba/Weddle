// Disable warnings about redefining variables
option(noredefine);

ring baseRing = (0, a(0..3)), (x(0..3)), dp;

// Load necessary procedures from procedures.cpp
< "procedures.cpp";

// We start from fefining generic 6 points in P^3
list Point(0) = list(0, 0, 0, 1);
list Point(1) = list(0, 0, 1, 0);
list Point(2) = list(0, 1, 0, 0);
list Point(3) = list(1, 0, 0, 0);
list Point(4) = list(1, 1, 1, 1);
list Point(5) = list(a(0), a(1), a(2), a(3));

// Seventh point is the point on Weddle surface
list Point(6) = list(b(0), b(1), b(2), b(3));

// List of coefficients of monomials of degree 2 in P^3
list coefficients = list(x(0) ^ 2, x(1) ^ 2, x(2) ^ 2, x(3) ^ 2, x(0) * x(1), x(0) * x(2), x(0) * x(3), x(1) * x(2), x(1) * x(3), x(2) * x(3));

// Lists of derivatives of monomials of degree 2 in P^3
list derivatives_x0 = compute_derivative(coefficients, 0);
list derivatives_x1 = compute_derivative(coefficients, 1);
list derivatives_x2 = compute_derivative(coefficients, 2);
list derivatives_x3 = compute_derivative(coefficients, 3);

// List of elements of the matrix
list matrixList =
    substitute_point(coefficients, Point(0)) +
    substitute_point(coefficients, Point(1)) +
    substitute_point(coefficients, Point(2)) +
    substitute_point(coefficients, Point(3)) +
    substitute_point(coefficients, Point(4)) +
    substitute_point(coefficients, Point(5)) +
    derivatives_x0 +
    derivatives_x1 +
    derivatives_x2 +
    derivatives_x3;

// Create a matrix from the list of elements
matrix M = create_matrix(matrixList, 10, 10);

// Compute the determinant of the matrix
poly weddle = det(M);

// Check if the degree of Weddle surface is 4
if (deg(weddle) != 4)
{
    exit;
}

// Extract the coefficients of Weddle surface
list coeffList = extract_coefficients(weddle);
// (-2*a(1)*a(3)+2*a(2)*a(3)), (2*a(0)*a(3)-2*a(2)*a(3)), (-2*a(0)*a(3)+2*a(1)*a(3)) ...

// Compute the ideal of coefficients of Weddle surface
ideal coeffIdeal = ideal_from_list(coeffList);
// coeffIdeal = 1
