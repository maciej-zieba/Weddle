// Disable warnings about redefining variables
option(noredefine);

ring baseRing = (0, a(0..5)(0..3)), (x(0..3)), dp;

// Load necessary procedures from main_procedures.cpp
< "procedures/main_procedures.cpp";

// We start from fefining generic 6 points in P^3
list point(0) = list(a(0)(0), a(0)(1), a(0)(2), a(0)(3));
list point(1) = list(a(1)(0), a(1)(1), a(1)(2), a(1)(3));
list point(2) = list(a(2)(0), a(2)(1), a(2)(2), a(2)(3));
list point(3) = list(a(3)(0), a(3)(1), a(3)(2), a(3)(3));
list point(4) = list(a(4)(0), a(4)(1), a(4)(2), a(4)(3));
list point(5) = list(a(5)(0), a(5)(1), a(5)(2), a(5)(3));

list points = list(point(0), point(1), point(2), point(3), point(4), point(5)); // List of points in P^3

// Seventh point is the point on Weddle surface that we want to compute (x(0), x(1), x(2), x(3))

// Compute the Weddle surface
poly weddle = compute_weddle_surface(points);

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
